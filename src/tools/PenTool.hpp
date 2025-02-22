#include "../svg/shapes/line.hpp"
#include "PenTool.hpp"

PenTool::PenTool(std::shared_ptr<Canvas> canvas) { m_canvas = canvas; }

void PenTool::OnMouseDown(ImVec2 pos) {
  // Start drawing a new line
  m_canvas->AddShape(std::make_shared<Line>(pos, pos));
}

void PenTool::OnMouseDrag(ImVec2 pos) {
  // Update the end position of the last line
  if (!m_canvas->GetShapes().empty()) {
    auto lastShape =
        std::dynamic_pointer_cast<Line>(m_canvas->GetShapes().back());
    if (lastShape) {
      lastShape->UpdatePosition(pos.x, pos.y);
    }
  }
}

void PenTool::OnMouseUp(ImVec2 pos) {
  // Finalize the drawing
  // No additional action needed as the line is already updated
}

void PenTool::DrawUI() {
  // Draw UI elements for the Pen tool if needed
}
