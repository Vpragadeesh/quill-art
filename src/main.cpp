#include "app/Application.hpp"
#include "svg/containers/canvas.hpp"
#include "svg/shapes/circle.hpp"
#include "svg/shapes/line.hpp"
#include "svg/shapes/rect.hpp"
#include <fstream>
#include <iostream>
#include <memory>

int main() {
  // --- SVG Export Section (Original Code) ---
  Canvas canvas;

  // Add a circle
  canvas.addShape(std::make_unique<Circle>(100, 100, 50));

  // Add a rectangle
  canvas.addShape(std::make_unique<Rect>(10, 10, 200, 100));

  // Add a line
  canvas.addShape(std::make_unique<Line>(0, 0, 200, 200));

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

  // --- UI Application Section ---
  // Now run the UI part of your application.
  Application app;
  if (!app.initialize()) {
    std::cerr << "Failed to initialize application UI.\n";
    return 1;
  }
  app.run();
  app.shutdown();

  return 0;
}
