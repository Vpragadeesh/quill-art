#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QMenu;
class QAction;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void setupUI();
    void createActions();
    void createMenus();

    QMenu* fileMenu;
    QAction* openAction;
    QAction* saveAction;
    QAction* exitAction;
};

#endif // MAINWINDOW_H
