/**
 * @file mainwindow.h
 * @brief Header file for the calculator window, contains the class definition.
 */

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
    void clear();
    void numClicked();
    void unaryOperationClicked();
    void binaryOperationClicked();
    void dotClicked();
    void equalClicked();
    void equals();
    void updateText();
    void makeNumbersVisible();
    void changeNumberSystem();
    void keyPressEvent(QKeyEvent * event);
    void openHelp();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
