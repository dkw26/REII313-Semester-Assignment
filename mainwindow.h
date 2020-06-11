#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "methodsdialog.h"
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
    Ui::MainWindow *ui;
    MethodsDialog *method;


private slots:
    void on_EnterButton_clicked();
};

#endif // MAINWINDOW_H
