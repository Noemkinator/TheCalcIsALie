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
    void on_buttonCE_clicked();
    void numClicked();
    void unaryOperationClicked();
    void binaryOperationClicked();
    void on_buttonDot_released();
    void on_buttonEq_released();
    int equals();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
