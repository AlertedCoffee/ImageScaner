#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_OpenTemplButton_clicked();

    void on_OpenImageButton_clicked();

    void on_StartScanerButton_clicked();

private:
    Ui::MainWindow *ui;
    void closeEvent(QCloseEvent *event);
};
#endif // MAINWINDOW_H
