/* Supposed to print a orange quad on a green background */

#include "../include/GLhf.h"
#include "../primitives/Quad.h"

#include <iostream>
#include <string>
#include <math.h>
#include <unistd.h>

typedef float real;

#define W 1000  // Number of pixels of the frame (texture quad) on x-axis
#define H 800   // Number of pixels of the frame (texture quad) on y-axis

/****************************SIMULATION PARAMETERS****************************/
static const unsigned int Nx = 200;     // Number of inside points of the mesh on x-axis
static const unsigned int Ny = 200;     // Number of inside points of the mesh on y-axis

static const real Lx = 1.0;             // Domain Size on x-axis
static const real Ly = 1.0;             // Domain Size on y-axis

static const real dx = Lx / (Nx + 1);   // Mesh cell size on x-axis
static const real dy = Ly / (Ny + 1);   // Mesh cell size on y-axis

static const real dt = 0.01f;            // Time Step

static const real diff = 0.001f;          // Diffusion Coefficient
/****************************************************************************/


#define IdX(i,j) ((i)*(Nx+2) + (j))
#define SWAP(field,field0) {real *tmp=field0;field0=field;field=tmp;}


typedef struct {
    GLubyte r;
    GLubyte g;
    GLubyte b;    
} Pixel;

class Fluid : public GLhf::App
{
public:
    /********INITIALIZATION********/
    void InitFields();          // Physic fields allocation and initialization
    void InitTextureData();     // Texture data allocation
    void Startup() override;    // Global initialization (OpenGL objects, fields, ...)

    /********UPDATE********/
    void UpdatePhysics();               // Update velocity and density fields
    void UpdateTextureData();           // Update texture data according to velocity fields
    void Render(double ct) override;    // Global update (texture data, velocity fields...)
    void ProcessInput() override;

    /********PHYSICS********/
    void AddSource(real *field, real *source);
    // ------------------
    void DiffuseVelocity();
    void DiffuseDensity();
    // ------------------
    void AdvectVelocity();
    void AdvectDensity();
    // ------------------
    void Project();
    // ------------------
    void UpdateDensity();
    void UpdateVelocity();
    // ------------------
    void SetVelocityBoundaryConditions();
    void SetContinuityBoundaryConditions(real *field); // Set continuity boundary conditions for a given field


    /***********CLEANING***********/
    void Shutdown() override;   // Cleans memory


private:
    GLhf::Quad quad;  // Simulation frame quad

    Pixel * tex_data;           // Texture Data
    real *un, *un1, *vn, *vn1;  // Velocity Fields
    real *rhon, *rhon1;         // Density Fields
};

/* **************************INITIALIZATION************************** */

/* Physic fields allocation and initialization */
void Fluid::InitFields()
{
    /* Allocation */
    unsigned int size = (Nx+2)*(Ny+2);
    un  = (real *) malloc(size * sizeof(real));
    un1 = (real *) malloc(size * sizeof(real));
    vn  = (real *) malloc(size * sizeof(real));
    vn1 = (real *) malloc(size * sizeof(real));

    rhon  = (real *) malloc(size * sizeof(real));
    rhon1 = (real *) malloc(size * sizeof(real));

    /* Initialization */
    for (int i=0 ; i<Ny+2 ; i++) {
        for (int j=0 ; j<Nx+2 ; j++)
        {
            un[IdX(i,j)]  = i==0 ? 0.0 : (real)i/(Ny+2);
            un1[IdX(i,j)] = i==0 ? 0.0 : (real)i/(Ny+2);
            vn[IdX(i,j)] = 0.0f;
            vn1[IdX(i,j)] = 0.0f;
            if (i>(Ny+1)/2 - (Ny+1)/6 && i<(Ny+1)/2 + (Ny+1)/6 &&
                j>(Nx+1)/2 - (Nx+1)/6 && j<(Nx+1)/2 + (Nx+1)/6) {
                rhon[IdX(i,j)] = 0.5f;
                rhon1[IdX(i,j)] = 0.5f;
            }
            else {
                rhon[IdX(i,j)] = 0.0f;
                rhon1[IdX(i,j)] = 0.0f;
            }
        }
    }

}

/* Texture data allocation */
void Fluid::InitTextureData()
{
    tex_data = (Pixel *)malloc(W*H * sizeof(Pixel));
    UpdateTextureData();
}

/* Global initialization (OpenGL objects, fields, ...) */
void Fluid::Startup()
{
    /* Texture Quad creation */
    double coef = 0.0038f;
    quad.width = coef * W;
    quad.height = coef * H;
    quad.SetColor(0.6, 0.4, 0.85);
    quad.Create();

    /* ****Initialization**** */
    InitFields();
    InitTextureData();
    /* ********************** */

    /* Create and Set Texture */
    quad.SetTextureWrapMode(GL_NEAREST, GL_LINEAR);
    quad.SetTexture(W, H, (GLubyte *)tex_data);

    /* Add to App Objects */
    AddShape(&quad);
}



/* ********************************UPDATE******************************* */

/* Update velocity and density fields */
void Fluid::UpdatePhysics()
{
    UpdateVelocity();
    UpdateDensity();
}

/* Update texture data according to velocity fields */
void Fluid::UpdateTextureData()
{
    /* For every Pixels */
    for (int i=0 ; i<H ; i++)
        for (int j=0 ; j<W ; j++)
            {
                int ii = round(i * (Ny+1) / H);
                int jj = round(j * (Nx+1) / W);

                /* Update RGB channels of the pixel */
                tex_data[i * W + j].r = rhon1[IdX(ii,jj)]*255.0f;
                tex_data[i * W + j].g = rhon1[IdX(ii,jj)]*255.0f;
                tex_data[i * W + j].b = rhon1[IdX(ii,jj)]*255.0f;
            }
}

/* Global update (texture data, velocity fields...)
 * @param ct : current time */
void Fluid::Render(double ct)
{
    UpdatePhysics();
    UpdateTextureData();
    quad.UpdateTexture((GLubyte *)tex_data);
}

void Fluid::ProcessInput()
{
    int cursor_width = 10;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);

            int ii = round((H-ypos) * (Ny+1) / H);
            int jj = round(xpos * (Nx+1) / W);
            for (int i=ii-cursor_width ; i<ii+cursor_width ; i++)
                for (int j=jj-cursor_width ; j<jj+cursor_width ; j++)
                {
                    if (i>=0 && i<=Ny+2 && j>=0 && j<=Nx+2)
                        rhon1[IdX(i,j)] += 0.1f;
                }
        }

}

/* ********************************PHYSICS******************************* */

/* Add source to density field */
void Fluid::AddSource(real *field, real *source)
{
    for (int i=0 ; i<(Nx+2)*(Ny+2) ; i++)
        field[i] += dt * source[i];
}

void Fluid::DiffuseVelocity()
{
    real coef = dt * diff * Nx*Ny;

    for ( int k=0 ; k<20 ; k++ ) {
        for ( int i=1 ; i<Ny+1 ; i++ ) {
            for ( int j=1 ; j<Nx+1 ; j++ ) {
                real sum_u = un1[IdX(i-1,j  )] + un1[IdX(i+1,j  )] +
                             un1[IdX(i  ,j+1)] + un1[IdX(i  ,j-1)];
                real sum_v = vn1[IdX(i-1,j  )] + vn1[IdX(i+1,j  )] +
                             vn1[IdX(i  ,j+1)] + vn1[IdX(i  ,j-1)];

                un1[IdX(i,j)] = ( un[IdX(i,j)] + coef * sum_u ) / (1 + 4*coef);
                vn1[IdX(i,j)] = ( vn[IdX(i,j)] + coef * sum_v ) / (1 + 4*coef);
            }
        }
        SetVelocityBoundaryConditions();
    }
}

void Fluid::DiffuseDensity()
{
    real coef = dt * diff * Nx*Ny;

    for ( int k=0 ; k<20 ; k++ ) {
        for ( int i=1 ; i<Ny+1 ; i++ ) {
            for ( int j=1 ; j<Nx+1 ; j++ ) {
                real sum = rhon1[IdX(i-1,j  )] + rhon1[IdX(i+1,j  )] +
                           rhon1[IdX(i  ,j+1)] + rhon1[IdX(i  ,j-1)];
                rhon1[IdX(i,j)] = ( rhon[IdX(i,j)] + coef * sum ) / (1 + 4*coef);
            }
        }
        SetContinuityBoundaryConditions(rhon1);
    }
}

void Fluid::AdvectVelocity()
{
    real dtx = dt*Nx;
    real dty = dt*Ny;

    for ( int i=1 ; i<Ny+1 ; i++ ) {
        for ( int j=1 ; j<Nx+1 ; j++ ) {
            real x_u = j - dtx * un[IdX(i,j)];
            real y_u = i - dty * un[IdX(i,j)];
            real x_v = j - dtx * vn[IdX(i,j)];
            real y_v = i - dty * vn[IdX(i,j)];

            if (x_u<0.5   ) x_u=0.5;
            if (x_u>Nx+0.5) x_u=Nx+0.5;
            if (y_u<0.5   ) y_u=0.5;
            if (y_u>Ny+0.5) y_u=Ny+0.5;
            if (x_v<0.5   ) x_v=0.5;
            if (x_v>Nx+0.5) x_v=Nx+0.5;
            if (y_v<0.5   ) y_v=0.5;
            if (y_v>Ny+0.5) y_v=Ny+0.5;

            int j0_u = (int)x_u; int j1_u=j0_u+1;
            int i0_u = (int)y_u; int i1_u=i0_u+1;
            int j0_v = (int)x_v; int j1_v=j0_v+1;
            int i0_v = (int)y_v; int i1_v=i0_v+1;

            real s1_u = x_u-j0_u;
            real s0_u = 1-s1_u;
            real t1_u = y_u-i0_u;
            real t0_u = 1-t1_u;
            real s1_v = x_v-j0_v;
            real s0_v = 1-s1_v;
            real t1_v = y_v-i0_v;
            real t0_v = 1-t1_v;            

            un1[IdX(i,j)] = t0_u * (s0_u*un[IdX(i0_u,j0_u)] + s1_u*un[IdX(i0_u,j1_u)]) +
                            t1_u * (s0_u*un[IdX(i1_u,j0_u)] + s1_u*un[IdX(i1_u,j1_u)]);
            vn1[IdX(i,j)] = t0_v * (s0_v*vn[IdX(i0_v,j0_v)] + s1_v*vn[IdX(i0_v,j1_v)]) +
                            t1_v * (s0_v*vn[IdX(i1_v,j0_v)] + s1_v*vn[IdX(i1_v,j1_v)]);
        }
    }
    SetVelocityBoundaryConditions();
}

void Fluid::AdvectDensity()
{
    real dtx = dt*Nx;
    real dty = dt*Ny;

    for ( int i=1 ; i<Ny+1 ; i++ ) {
        for ( int j=1 ; j<Nx+1 ; j++ ) {
            real y = i - dty * rhon[IdX(i,j)];
            real x = j - dtx * rhon[IdX(i,j)];

            if (x<0.5   ) x=0.5;
            if (x>Nx+0.5) x=Nx+0.5;
            if (y<0.5   ) y=0.5;
            if (y>Ny+0.5) y=Ny+0.5;

            int j0 = (int)x; int j1=j0+1;
            int i0 = (int)y; int i1=i0+1;

            real s1 = x-j0;
            real s0 = 1-s1;
            real t1 = y-i0;
            real t0 = 1-t1;

            rhon1[IdX(i,j)] = t0 * (s0*rhon[IdX(i0,j0)] + s1*rhon[IdX(i0,j1)]) +
                              t1 * (s0*rhon[IdX(i1,j0)] + s1*rhon[IdX(i1,j1)]);
        }
    }
    SetContinuityBoundaryConditions(rhon1);
}

void Fluid::UpdateDensity()
{
    //AddSource(rhon1, rhon);
    SWAP(rhon, rhon1); DiffuseDensity();
    SWAP(rhon, rhon1); AdvectDensity();
}

void Fluid::Project()
{
    for ( int i=1 ; i<Ny+1 ; i++ ) {
        for ( int j=1 ; j<Nx+1 ; j++ ) {
            vn[IdX(i,j)] = -0.5*dy * ( un1[IdX(i+1,j)] - un1[IdX(i-1,j)] +
                                       vn1[IdX(i,j+1)] - vn1[IdX(i,j-1)]);
            un[IdX(i,j)] = 0;
        }
    }

    SetContinuityBoundaryConditions(un);
    SetContinuityBoundaryConditions(vn);

    for (int k=0 ; k<20 ; k++) {
        for (int i=1 ; i<Ny+1 ; i++) {
            for (int j=1 ; j<Nx+1 ; j++) {
                un[IdX(i,j)] = (vn[IdX(i,j)] + un[IdX(i-1,j  )] + un[IdX(i+1,j  )] +
                                               un[IdX(i  ,j-1)] + un[IdX(i  ,j+1)]) / 4;
            }
        }
        SetContinuityBoundaryConditions(un);
    }

    for (int i=1 ; i<Ny+1 ; i++) {
        for (int j=1 ; j<Nx+1 ; j++) {
            un1[IdX(i,j)] -= 0.5 * (un[IdX(i+1,j  )] - un[IdX(i-1,j  )]) / dx;
            vn1[IdX(i,j)] -= 0.5 * (un[IdX(i  ,j+1)] - un[IdX(i  ,j-1)]) / dy;
        }
    }
    SetVelocityBoundaryConditions();

}

void Fluid::UpdateVelocity()
{
    //AddSource(un1, un);
    //AddSource(vn1, vn);
    
    SWAP(un1, un);
    SWAP(vn1, vn);
    DiffuseVelocity();

    Project();

    SWAP(un1, un);
    SWAP(vn1, vn);
    AdvectVelocity();
    Project();
}

/* Set velocity fields boundary conditions
 * We consider the fluid is in a closed box */
void Fluid::SetVelocityBoundaryConditions()
{
    // Run through both horizontal walls
    for (int j=1 ; j<Nx+1 ; j++)
    {
        un1[IdX(0   ,j)] = un1[IdX(1 ,j)];
        un1[IdX(Ny+1,j)] = un1[IdX(Ny,j)];

        vn1[IdX(0   ,j)] = -vn1[IdX(1 ,j)];
        vn1[IdX(Ny+1,j)] = -vn1[IdX(Ny,j)];
    }

    // Run through both vertical walls
    for (int i=1 ; i<Ny+1 ; i++)
    {
        un1[IdX(i,0    )] = -un1[IdX(i,1 )];
        un1[IdX(i, Nx+1)] = -un1[IdX(i,Nx)];

        vn1[IdX(i,0    )] = vn1[IdX(i,1 )];
        vn1[IdX(i, Nx+1)] = vn1[IdX(i,Nx)];
    }

    // All corners un
    un1[IdX(0   ,0   )] = 0.5 * ( un1[IdX(1 ,0   )] + un1[IdX(0   ,1 )] );
    un1[IdX(0   ,Nx+1)] = 0.5 * ( un1[IdX(1 ,Nx+1)] + un1[IdX(0   ,Nx)] );
    un1[IdX(Ny+1,0   )] = 0.5 * ( un1[IdX(Ny,0   )] + un1[IdX(Ny+1,1 )] );
    un1[IdX(Ny+1,Nx+1)] = 0.5 * ( un1[IdX(Ny,Nx+1)] + un1[IdX(Ny+1,Nx)] );

    // All corners vn
    vn1[IdX(0   ,0   )] = 0.5 * ( vn1[IdX(1 ,0   )] + vn1[IdX(0   ,1 )] );
    vn1[IdX(0   ,Nx+1)] = 0.5 * ( vn1[IdX(1 ,Nx+1)] + vn1[IdX(0   ,Nx)] );
    vn1[IdX(Ny+1,0   )] = 0.5 * ( vn1[IdX(Ny,0   )] + vn1[IdX(Ny+1,1 )] );
    vn1[IdX(Ny+1,Nx+1)] = 0.5 * ( vn1[IdX(Ny,Nx+1)] + vn1[IdX(Ny+1,Nx)] );
}

/* Set continuity boundary conditions for a given field */
void Fluid::SetContinuityBoundaryConditions(real *field)
{
    // Run through both horizontal walls
    for (int j=1 ; j<Nx+1 ; j++)
    {
        field[IdX(0   ,j)] = field[IdX(1 ,j)];
        field[IdX(Ny+1,j)] = field[IdX(Ny,j)];
    }

    // Run through both vertical walls
    for (int i=1 ; i<Ny+1 ; i++)
    {
        field[IdX(i,0    )] = field[IdX(i,1 )];
        field[IdX(i, Nx+1)] = field[IdX(i,Nx)];
    }

    // All corners un
    field[IdX(0   ,0   )] = 0.5 * ( field[IdX(1 ,0   )] + field[IdX(0   ,1 )] );
    field[IdX(0   ,Nx+1)] = 0.5 * ( field[IdX(1 ,Nx+1)] + field[IdX(0   ,Nx)] );
    field[IdX(Ny+1,0   )] = 0.5 * ( field[IdX(Ny,0   )] + field[IdX(Ny+1,1 )] );
    field[IdX(Ny+1,Nx+1)] = 0.5 * ( field[IdX(Ny,Nx+1)] + field[IdX(Ny+1,Nx)] );
}


DECLARE_MAIN(Fluid);



/* Cleans memory */
void Fluid::Shutdown()
{
    // Texxture Data
    free(tex_data);

    // Velocity Fields
    free(un);
    free(un1);
    free(vn);
    free(vn1);

    // Density Field
    free(rhon);
    free(rhon1);
}