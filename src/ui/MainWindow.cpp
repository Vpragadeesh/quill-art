#include "MainWindow.hpp"

// Constructor: Save the window pointer and enable docking.
MainWindow::MainWindow(GLFWwindow *window) : m_window(window) {
  // Enable docking in ImGui (inspired by zide)
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

// Destructor.
MainWindow::~MainWindow() {}

// Render the main UI window.
void MainWindow::Render() {
  // Set up a full-screen window to host the dockspace.
  ImGuiViewport *viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->WorkPos);
  ImGui::SetNextWindowSize(viewport->WorkSize);
  ImGui::SetNextWindowViewport(viewport->ID);

  // Window flags to create a borderless, non-movable window.
  ImGuiWindowFlags window_flags =
      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
      ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
      ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

  ImGui::Begin("DockSpace Window", nullptr, window_flags);

  // Create the dockspace.
  ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
  ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));

  // Draw the main menu bar.
  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("New", "Ctrl+N")) {
        // Insert "New file" logic here.
      }
      if (ImGui::MenuItem("Open", "Ctrl+O")) {
        // Insert "Open file" logic here.
      }
      if (ImGui::MenuItem("Save", "Ctrl+S")) {
        // Insert "Save file" logic here.
      }
      if (ImGui::MenuItem("Exit", "Ctrl+Q")) {
        glfwSetWindowShouldClose(m_window, true);
      }
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Edit")) {
      if (ImGui::MenuItem("Undo", "Ctrl+Z")) {
        // Insert "Undo" logic here.
      }
      if (ImGui::MenuItem("Redo", "Ctrl+Y")) {
        // Insert "Redo" logic here.
      }
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }

  // (Optional) Insert additional UI elements here (e.g., a toolbar panel).

  ImGui::End(); // End the DockSpace window.
}
