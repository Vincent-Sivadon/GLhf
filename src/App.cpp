#include "App.h"

#include <iostream>

namespace GLhf
{

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
            PollEvents(dt);

            // Rendering
            // ---------
            glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

}