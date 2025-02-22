#include "Application.hpp"
#include <iostream>

Application::Application() {
    std::cout << "QuillArt Application Initialized" << std::endl;
}

Application::~Application() {
    std::cout << "QuillArt Application Shutting Down" << std::endl;
}

void Application::run() {
    std::cout << "QuillArt is running..." << std::endl;
    // Main application loop or event handling would go here
    while (isRunning) {
        // Process events, update state, render frame, etc.
    }
}

void Application::stop() {
    isRunning = false;
    std::cout << "Stopping QuillArt..." << std::endl;
}
