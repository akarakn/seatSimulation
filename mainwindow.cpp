#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    originalRenderArea = new RenderArea;
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(originalRenderArea, 0, 0);
    this->ui->widget->setLayout(layout);

    QPainterPath back;
//! [3]
    back.setFillRule(Qt::WindingFill);
    back.lineTo(0.0, -100.0);
    back.lineTo(10.0, -100.0);
    back.lineTo(10.0, 10.0);
    back.lineTo(0.0, 10.0);

    QPainterPath cushion;
//! [3]
    cushion.setFillRule(Qt::WindingFill);
    cushion.lineTo(-60.0, 0.0);
    cushion.lineTo(-60.0, 10.0);
    cushion.lineTo(10.0, 10.0);
    cushion.lineTo(10.0, 0.0);

    originalRenderArea->setShape1(back);
    originalRenderArea->setShape2(cushion);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_bLow_clicked()
{
    originalRenderArea->setHeight(30);
}

void MainWindow::on_bMed_clicked()
{
    originalRenderArea->setHeight(0);
}

void MainWindow::on_bHigh_clicked()
{
    originalRenderArea->setHeight(-30);
}

void MainWindow::on_b90_clicked()
{
    originalRenderArea->setAngle(0);
}

void MainWindow::on_b120_clicked()
{
    originalRenderArea->setAngle(30);
}

void MainWindow::on_b150_clicked()
{
    originalRenderArea->setAngle(60);
}
