#pragma once

class Application {
public:
    Application();
    ~Application();

    void run();
    void stop();

private:
    bool isRunning = true;
};
