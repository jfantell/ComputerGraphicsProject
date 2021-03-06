#include "inputhandler.h"
#include "app_state.h"
#include <iostream>

// Define static variable in cpp file
Camera* InputHandler:: _c;

// Simple setter for the camera pointer.
void InputHandler::set_camera(Camera *c ) {
    _c = c;
}

// Switch through possible input keys and do their respective operations.
void InputHandler::key_callback(GLFWwindow *window, int key, int sancode, int action, int mods) {
    if (key == GLFW_KEY_UP) {
        _c->inputMoveUp();
    }
    if (key == GLFW_KEY_DOWN) {
        _c->inputMoveDown();
    }
    if (key == GLFW_KEY_LEFT) {
        _c->inputMoveLeft();
    }
    if (key == GLFW_KEY_RIGHT) {
        _c->inputMoveRight();
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        std::cout << " Reset " << std::endl;
        windowState.yaw = 0;
        windowState.pitch = 0;
        windowState.offset_x = 0;
        windowState.offset_y = 1;
        windowState.last_x = 0;
        windowState.last_y = 0;
        _c->restoreDefaultEyeLocation();
    }
    if (key == GLFW_KEY_F && action == GLFW_PRESS) {
      windowState.update_realsense = true;
    }
}

// When the window is resized, re-generate the perspective matrix (new aspect ratio)
void InputHandler::window_size_callback(GLFWwindow *window, int newWidth, int newHeight) {
    windowState.width = newWidth;
    windowState.height = newHeight;
    glViewport(0,0,windowState.width,windowState.height);
    _c->reset_aspect_ratio();
}

// If the mouse is clicked, handle it here.
void InputHandler::mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        windowState.ml = true;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        windowState.ml = false;
    }
}
// When the mouse is zoomed in X OR Y (2D scroll) move the camera appropriately.
void InputHandler::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    windowState.offset_x -= static_cast<float>(xoffset);
    windowState.offset_y -= static_cast<float>(yoffset);
    std::cout << "Zoom" << windowState.offset_y << std::endl;
    _c->zoom(yoffset);
    _c->strafe(xoffset);
}

// Handle Mouse position here. if the mouse moves anywhere within the window, callback is here.
void InputHandler::cursor_pos_callback(GLFWwindow *window, double x, double y) {
    if (windowState.ml){
        _c->updateMouse(glm::vec2(x,y));
    }
    else {
        windowState.last_x = x;
        windowState.last_y = y;
    }
}
