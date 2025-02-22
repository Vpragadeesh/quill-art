#ifndef APPLICATION_H
#define APPLICATION_H

class Application {
public:
    Application();
    ~Application();

    void run();
    void stop();

private:
    bool isRunning = true;
};

#endif 
