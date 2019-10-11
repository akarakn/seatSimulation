#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "renderarea.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    RenderArea *originalRenderArea;

private slots:
    void on_bLow_clicked();

    void on_bMed_clicked();

    void on_bHigh_clicked();

    void on_b90_clicked();

    void on_b120_clicked();

    void on_b150_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
