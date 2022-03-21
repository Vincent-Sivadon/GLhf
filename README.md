# GLTemplate : OpenGL application abstraction

## Features
------------- Abstract Class Application -------------  
A program that uses this paradigm should look like :
```
class ExampleApp : public App
{
public:
    void startup() override {}           // Initialize OpenGL objects
    void render() override {}            // Rendering protocole
    void processInput() override {}      // Input Management
    void shutdown() override {}          // Memory cleaning
private:
    int member;
}
DECLARE_MAIN(ExampleApp);
```
The main will look like :
   * Glad and GLFW initialization
   * while loop with :
       * framerate management
       * rendering
       * input management
   * memory cleaning  

We can use this to avoid writing basic OpenGL blocks every time.  
In the future the application abstraction will hold many elementary functions that could be used to construct complex OpenGL application by assembling them together.