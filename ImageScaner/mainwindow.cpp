#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QFileDialog"
#include "QMessageBox"
#include "SIRF.h"
#include "QCloseEvent"

#include <opencv2/highgui.hpp>
#include <future>
#include <iostream>
#include <thread>
#include <chrono>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //setWindowFlags( Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint);
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QString templFileName;
QString imageFileName;

void MainWindow::on_OpenTemplButton_clicked()
{
    templFileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg)"));
    if(!templFileName.isEmpty()) ui->OpenTemplButton->setText("Файл");
}


void MainWindow::on_OpenImageButton_clicked()
{
    imageFileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg)"));
    if(!imageFileName.isEmpty()) ui->OpenImageButton->setText("Файл");
}


void MainWindow::on_StartScanerButton_clicked()
{
    if (templFileName.isEmpty() || imageFileName.isEmpty()){
        QMessageBox::critical(this,"ImageScaner", "Не все файлы выбраны");
    }
    else{

        SIRFDetector::Detection(templFileName.toStdString(), imageFileName.toStdString());
    }
}


void MainWindow::closeEvent(QCloseEvent *event){
    cv::destroyAllWindows();
    QMainWindow::closeEvent(event);
}
