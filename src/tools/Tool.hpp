#ifndef TOOL_H
#define TOOL_H

class Tool {
public:
    Tool();
    virtual ~Tool();

    // Pure virtual functions for tool behavior
    virtual void onMousePress(int x, int y) = 0;
    virtual void onMouseMove(int x, int y) = 0;
    virtual void onMouseRelease(int x, int y) = 0;
};

#endif // TOOL_H
