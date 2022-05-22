#include "App.h"

#include <iostream>

namespace GLhf
{

    // App's main function
    void App::Run()
    {
        window_.Create();
        camera_.Create();
        event_handler_.Create(&camera_);

        // Overrided function
        // ------------------
        Startup();

        renderer_.Create(scene_);

        // Game loop
        // ----------
        while (!glfwWindowShouldClose(window_.GetWindow()))
        {
            // per-frame time logic
            // -------------------
            float ct = static_cast<float>(glfwGetTime());
            dt = ct - lt;
            lt = ct;

            // Input management
            event_handler_.Process(dt);

            // Rendering
            renderer_.Clear();
            glm::mat4 view_matrix = camera_.GetViewMatrix();
            for (Cube& cube : scene_.cubes_)
                renderer_.Draw(cube, view_matrix, camera_.position_);

            glfwSwapBuffers(window_.GetWindow());

            // Input
            glfwPollEvents();
        }

        // Clean memory
        // ------------
        glfwDestroyWindow(window_.GetWindow());
        glfwTerminate();
    }

}