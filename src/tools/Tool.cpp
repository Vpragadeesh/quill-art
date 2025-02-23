// Tool.hpp
#ifndef TOOL_HPP
#define TOOL_HPP

#include "imgui.h"
#include <vector>
#include <algorithm>

// Define the available tool types.
enum ToolType {
    NONE,
    PATH,       // Typically used for free-hand drawing (pencil)
    ERASER,
    RECTANGLE,
    ELLIPSE,
    LINE,
    EYEDROPPER,
    ZOOM,
    PAN,
};

// Base Tool class
class Tool {
public:
    ToolType type;
    Tool(ToolType t = NONE) : type(t) {}
    virtual ~Tool() {}

    // Mouse event handlers—override in derived classes as needed.
    virtual void onMouseDown(const ImVec2& pos) {}
    virtual void onMouseMove(const ImVec2& pos) {}
    virtual void onMouseUp(const ImVec2& pos) {}

    // Draw the tool’s preview or finalized shape on the canvas.
    virtual void draw(ImDrawList* draw_list) {}
};

// Pencil tool (using PATH)
class PencilTool : public Tool {
public:
    std::vector<ImVec2> points;
    PencilTool() : Tool(PATH) {}

    void onMouseDown(const ImVec2& pos) override {
        points.clear();
        points.push_back(pos);
    }
    void onMouseMove(const ImVec2& pos) override {
        points.push_back(pos);
    }
    void onMouseUp(const ImVec2& pos) override {
        points.push_back(pos);
    }
    void draw(ImDrawList* draw_list) override {
        if (points.size() > 1) {
            draw_list->AddPolyline(points.data(), points.size(), IM_COL32(255, 255, 255, 255), false, 2.0f);
        }
    }
};

// Eraser tool
class EraserTool : public Tool {
public:
    float eraserRadius;
    EraserTool() : Tool(ERASER), eraserRadius(10.0f) {}

    void onMouseDown(const ImVec2& pos) override {
        // Begin erasing logic around pos.
    }
    void onMouseMove(const ImVec2& pos) override {
        // Continue erasing.
    }
    void onMouseUp(const ImVec2& pos) override {
        // Finalize erasing.
    }
    void draw(ImDrawList* draw_list) override {
        // For visual feedback, draw a circle at the current mouse position.
        draw_list->AddCircle(ImGui::GetMousePos(), eraserRadius, IM_COL32(255, 0, 0, 255), 32, 2.0f);
    }
};

// Rectangle tool
class RectangleTool : public Tool {
public:
    ImVec2 startPos;
    ImVec2 currentPos;
    bool active;
    RectangleTool() : Tool(RECTANGLE), active(false) {}

    void onMouseDown(const ImVec2& pos) override {
        active = true;
        startPos = pos;
        currentPos = pos;
    }
    void onMouseMove(const ImVec2& pos) override {
        if (active)
            currentPos = pos;
    }
    void onMouseUp(const ImVec2& pos) override {
        active = false;
        currentPos = pos;
    }
    void draw(ImDrawList* draw_list) override {
        ImVec2 minPos(std::min(startPos.x, currentPos.x), std::min(startPos.y, currentPos.y));
        ImVec2 maxPos(std::max(startPos.x, currentPos.x), std::max(startPos.y, currentPos.y));
        draw_list->AddRect(minPos, maxPos, IM_COL32(0, 255, 0, 255), 0.0f, 0, 2.0f);
    }
};

// Ellipse tool
class EllipseTool : public Tool {
public:
    ImVec2 startPos;
    ImVec2 currentPos;
    bool active;
    EllipseTool() : Tool(ELLIPSE), active(false) {}

    void onMouseDown(const ImVec2& pos) override {
        active = true;
        startPos = pos;
        currentPos = pos;
    }
    void onMouseMove(const ImVec2& pos) override {
        if (active)
            currentPos = pos;
    }
    void onMouseUp(const ImVec2& pos) override {
        active = false;
        currentPos = pos;
    }
    void draw(ImDrawList* draw_list) override {
        ImVec2 center((startPos.x + currentPos.x) * 0.5f, (startPos.y + currentPos.y) * 0.5f);
        ImVec2 radius(std::abs(currentPos.x - startPos.x) * 0.5f, std::abs(currentPos.y - startPos.y) * 0.5f);
        draw_list->AddEllipse(center, radius, IM_COL32(0, 0, 255, 255), 32, 2.0f);
    }
};

// Line tool
class LineTool : public Tool {
public:
    ImVec2 startPos;
    ImVec2 currentPos;
    bool active;
    LineTool() : Tool(LINE), active(false) {}

    void onMouseDown(const ImVec2& pos) override {
        active = true;
        startPos = pos;
        currentPos = pos;
    }
    void onMouseMove(const ImVec2& pos) override {
        if (active)
            currentPos = pos;
    }
    void onMouseUp(const ImVec2& pos) override {
        active = false;
        currentPos = pos;
    }
    void draw(ImDrawList* draw_list) override {
        draw_list->AddLine(startPos, currentPos, IM_COL32(255, 255, 0, 255), 2.0f);
    }
};

// Eyedropper tool
class EyedropperTool : public Tool {
public:
    EyedropperTool() : Tool(EYEDROPPER) {}

    void onMouseDown(const ImVec2& pos) override {
        // Sample the color at pos from your canvas.
    }
    void draw(ImDrawList* draw_list) override {
        // Optionally display the sampled color or a preview indicator.
    }
};

// Zoom tool
class ZoomTool : public Tool {
public:
    float zoomFactor;
    ZoomTool() : Tool(ZOOM), zoomFactor(1.0f) {}

    void onMouseDown(const ImVec2& pos) override {
        // Initialize zoom action.
    }
    void onMouseMove(const ImVec2& pos) override {
        // Update zoom level based on mouse movement.
    }
    void onMouseUp(const ImVec2& pos) override {
        // Finalize zoom action.
    }
};

// Pan tool
class PanTool : public Tool {
public:
    ImVec2 startPos;
    ImVec2 offset;
    bool active;
    PanTool() : Tool(PAN), active(false), offset(0, 0) {}

    void onMouseDown(const ImVec2& pos) override {
        active = true;
        startPos = pos;
    }
    void onMouseMove(const ImVec2& pos) override {
        if (active) {
            offset = ImVec2(pos.x - startPos.x, pos.y - startPos.y);
            // You would update your canvas/view offset here.
        }
    }
    void onMouseUp(const ImVec2& pos) override {
        active = false;
    }
};

#endif 