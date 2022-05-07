#include "App.h"

#include <iostream>

// App's main function
void App::Run()
{
    window.Create();
    event_handler.Create(&camera);

    // Overrided function
    // ------------------
    Startup();

    // Game loop
    // ----------
    while (!glfwWindowShouldClose(window.GetWindow()))
    {
        // per-frame time logic
        // -------------------
        float ct = static_cast<float>(glfwGetTime());
        dt = ct - lt;
        lt = ct;

        // Input management
        event_handler.Process(dt);

        // Rendering
        // ---------
        static const GLfloat black[] = {0.f, 0.f, 0.f, 1.0f};
        glClearBufferfv(GL_COLOR, 0, black);

        // Draw every shapes
        for (Shape *shape : shapes)
        {
            shape->SetView(camera.GetViewMatrix());
            shape->Draw();
        }

        Render(ct);

        glfwSwapBuffers(window.GetWindow());

        // Input
        // -----
        glfwPollEvents();
    }

    // Clean memory
    // ------------
    for (Shape *shape : shapes)
        shape->Destroy();
    Shutdown();
    glfwDestroyWindow(window.GetWindow());
    glfwTerminate();
}