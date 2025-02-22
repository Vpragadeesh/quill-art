#include "svg/canvas.hpp"
#include "svg/shapes/circle.hpp"
#include "svg/shapes/line.hpp"
#include "svg/shapes/rect.hpp"
#include <fstream>
#include <iostream>

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_vulkan.h>

int main() {

  Canvas canvas;

  // Add a circle
  std::string black = "black";
  std::string transparent = "transparent";
  canvas.addShape(std::make_unique<Circle>(100, 100, 50, black, transparent));
  canvas.addShape(std::make_unique<Rect>(10, 10, 200, 100, black, transparent));
  // Add a rectangle
  canvas.addShape(std::make_unique<Rect>(10, 10, 200, 100, black, transparent));
  canvas.addShape(std::make_unique<Line>(0, 0, 200, 200, black));
  // Add a line
  std::string blackLine = "aqua";
  canvas.addShape(std::make_unique<Line>(0, 0, 200, 200, blackLine));

  // Optionally add a path
  // canvas.addShape(std::make_unique<Path>("M10 10 H 80 V 80 H 10 Z"));

  // Export to SVG string
  std::string svgOutput = canvas.toSVG(500, 500);

  // Write to file
  std::ofstream outFile("output.svg");
  if (!outFile.is_open()) {
    std::cerr << "Error: Could not open file for writing.\n";
    return 1;
  }

  outFile << svgOutput;
  outFile.close();

  std::cout << "SVG file created successfully: output.svg\n";
  return 0;
}
