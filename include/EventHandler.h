#pragma once

#include "Window.h"
#include "Camera.h"

namespace GLhf
{

    // Tells us if a key is pressed
    struct Keys {
        bool W    = false;
        bool S    = false;
        bool A    = false;
        bool D    = false;
        bool UP   = false;
        bool DOWN = false;
    };

    class EventHandler {
    private:
        inline static Window *window;
        inline static Camera *camera;

        // Callback functions
        static void FramebufferSizeCallback(int width, int height);
        static void MouseCallback(double xpos, double ypos);
        static void KeyCallback(int key, int scancode, int action, int mods);
        static void ScrollCallback(double xoffset, double yoffset);
        void SetEventCallback();

        // Key states
        inline static Keys keys;

        // Mouse callback variables
        inline static bool firstMouse = true;
        inline static float lastX = 0.0f;
        inline static float lastY = 0.0f;

    public:
        // Initialize EventHandler
        void Create(Camera * camera_);

        // Input functions
        void Process(float dt);
    };

}