#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QFileDialog"
#include "QMessageBox"
#include "SIRF.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
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
        ui->OpenTemplButton->setEnabled(false);
        ui->OpenImageButton->setEnabled(false);
        ui->StartScanerButton->setEnabled(false);

        SIRFDetector::Detection(templFileName.toStdString(), imageFileName.toStdString());

        ui->OpenTemplButton->setEnabled(true);
        ui->OpenImageButton->setEnabled(true);
        ui->StartScanerButton->setEnabled(true);
    }
}

