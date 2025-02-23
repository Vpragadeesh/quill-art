#ifndef TOLL_HPP
#define TOLL_HPP

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

// Base Tool class declaration.
class Tool {
public:
    ToolType type;
    Tool(ToolType t = NONE);
    virtual ~Tool();

    // Mouse event handlers—override in derived classes as needed.
    virtual void onMouseDown(const ImVec2& pos);
    virtual void onMouseMove(const ImVec2& pos);
    virtual void onMouseUp(const ImVec2& pos);

    // Draw the tool’s preview or finalized shape on the canvas.
    virtual void draw(ImDrawList* draw_list);
};

// Pencil tool (using PATH)
class PencilTool : public Tool {
public:
    std::vector<ImVec2> points;
    PencilTool();

    void onMouseDown(const ImVec2& pos) override;
    void onMouseMove(const ImVec2& pos) override;
    void onMouseUp(const ImVec2& pos) override;
    void draw(ImDrawList* draw_list) override;
};

// Eraser tool
class EraserTool : public Tool {
public:
    float eraserRadius;
    EraserTool();

    void onMouseDown(const ImVec2& pos) override;
    void onMouseMove(const ImVec2& pos) override;
    void onMouseUp(const ImVec2& pos) override;
    void draw(ImDrawList* draw_list) override;
};

// Rectangle tool
class RectangleTool : public Tool {
public:
    ImVec2 startPos;
    ImVec2 currentPos;
    bool active;
    RectangleTool();

    void onMouseDown(const ImVec2& pos) override;
    void onMouseMove(const ImVec2& pos) override;
    void onMouseUp(const ImVec2& pos) override;
    void draw(ImDrawList* draw_list) override;
};

// Ellipse tool
class EllipseTool : public Tool {
public:
    ImVec2 startPos;
    ImVec2 currentPos;
    bool active;
    EllipseTool();

    void onMouseDown(const ImVec2& pos) override;
    void onMouseMove(const ImVec2& pos) override;
    void onMouseUp(const ImVec2& pos) override;
    void draw(ImDrawList* draw_list) override;
};

// Line tool
class LineTool : public Tool {
public:
    ImVec2 startPos;
    ImVec2 currentPos;
    bool active;
    LineTool();

    void onMouseDown(const ImVec2& pos) override;
    void onMouseMove(const ImVec2& pos) override;
    void onMouseUp(const ImVec2& pos) override;
    void draw(ImDrawList* draw_list) override;
};

// Eyedropper tool
class EyedropperTool : public Tool {
public:
    EyedropperTool();

    void onMouseDown(const ImVec2& pos) override;
    void draw(ImDrawList* draw_list) override;
};

// Zoom tool
class ZoomTool : public Tool {
public:
    float zoomFactor;
    ZoomTool();

    void onMouseDown(const ImVec2& pos) override;
    void onMouseMove(const ImVec2& pos) override;
    void onMouseUp(const ImVec2& pos) override;
};

// Pan tool
class PanTool : public Tool {
public:
    ImVec2 startPos;
    ImVec2 offset;
    bool active;
    PanTool();

    void onMouseDown(const ImVec2& pos) override;
    void onMouseMove(const ImVec2& pos) override;
    void onMouseUp(const ImVec2& pos) override;
};

#endif // TOLL_HPP
