#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

   private:
    void createMenu();
    void createToolBars();
    void createStatusBars();



/*Menus*/
    QMenu* menu;
    /*Toolbar*/
    QToolBar* toolBar;





private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
