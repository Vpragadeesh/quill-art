#include "MainWindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setupUI();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    createActions();
    createMenus();
    
    setWindowTitle("QuillArt");
    resize(800, 600);
}

void MainWindow::createActions()
{
    openAction = new QAction(tr("&Open"), this);
    connect(openAction, &QAction::triggered, this, [](){
        // TODO: Implement the open file functionality
        QMessageBox::information(nullptr, "Open", "Open action triggered");
    });

    saveAction = new QAction(tr("&Save"), this);
    connect(saveAction, &QAction::triggered, this, [](){
        // TODO: Implement the save functionality
        QMessageBox::information(nullptr, "Save", "Save action triggered");
    });

    exitAction = new QAction(tr("E&xit"), this);
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
}
