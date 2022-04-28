/**
 * @file mainwindow.cpp
 * @brief Main window of the GUI, contains the main window and the functions used.
 */

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "calc.h"
#include <QButtonGroup>
#include <QKeyEvent>
#include <QtMath>
#include <cmath>
#include <QDesktopServices>

/// variable contains current value, to be written on display
double memory = 0;
/// variable contains currently selected number system
int numberSystem = 10;

/// group of number buttons
QButtonGroup *numberButtons;
/// group containing number system conversion buttons 
QButtonGroup *numberSystems;

/// first number in current binary operation
double firstNum; // prvni cislo binarni operace
/// variable to indicate that a second number can be entered
int newNum = 0;  // po stisknuti dalsi cislice vynulovat display
/// represents the current exponent of a float digit
int dot = 0;
/// variable to indicate wether memory contains positive or negative number
int sign = 0; //0 pozitivni, 1 negativni
/// stores the current operation number
int myOperator = 0; // pamatuje ktery operator pouzit
// 0=nic, 1=+, 2=-, 3=*, 4=/, 5=exp, 6=root

/**
 * GUI constructor
 * @param parent Parent widget
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // prevent window resizing
    QMainWindow::setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    this->setFixedSize(this->width(), this->height());

    // add numbers to the group and give them an appropriate id
    numberButtons = new QButtonGroup;
    numberButtons->addButton(ui->num0, 0);
    numberButtons->addButton(ui->num1, 1);
    numberButtons->addButton(ui->num2, 2);
    numberButtons->addButton(ui->num3, 3);
    numberButtons->addButton(ui->num4, 4);
    numberButtons->addButton(ui->num5, 5);
    numberButtons->addButton(ui->num6, 6);
    numberButtons->addButton(ui->num7, 7);
    numberButtons->addButton(ui->num8, 8);
    numberButtons->addButton(ui->num9, 9);
    numberButtons->addButton(ui->numA, 10);
    numberButtons->addButton(ui->numB, 11);
    numberButtons->addButton(ui->numC, 12);
    numberButtons->addButton(ui->numD, 13);
    numberButtons->addButton(ui->numE, 14);
    numberButtons->addButton(ui->numF, 15);
    // add number systems to the group and give them an appropriate id
    numberSystems = new QButtonGroup;
    numberSystems->addButton(ui->buttonTo2, 2);
    numberSystems->addButton(ui->buttonTo8, 8);
    numberSystems->addButton(ui->buttonTo10, 10);
    numberSystems->addButton(ui->buttonTo16, 16);

    // prirazeni funkci pri stisknuti tlacitek
    connect(ui->num0, SIGNAL(released()), this, SLOT(numClicked()));
    connect(ui->num1, SIGNAL(released()), this, SLOT(numClicked()));
    connect(ui->num2, SIGNAL(released()), this, SLOT(numClicked()));
    connect(ui->num3, SIGNAL(released()), this, SLOT(numClicked()));
    connect(ui->num4, SIGNAL(released()), this, SLOT(numClicked()));
    connect(ui->num5, SIGNAL(released()), this, SLOT(numClicked()));
    connect(ui->num6, SIGNAL(released()), this, SLOT(numClicked()));
    connect(ui->num7, SIGNAL(released()), this, SLOT(numClicked()));
    connect(ui->num8, SIGNAL(released()), this, SLOT(numClicked()));
    connect(ui->num9, SIGNAL(released()), this, SLOT(numClicked()));
    connect(ui->numA, SIGNAL(released()), this, SLOT(numClicked()));
    connect(ui->numB, SIGNAL(released()), this, SLOT(numClicked()));
    connect(ui->numC, SIGNAL(released()), this, SLOT(numClicked()));
    connect(ui->numD, SIGNAL(released()), this, SLOT(numClicked()));
    connect(ui->numE, SIGNAL(released()), this, SLOT(numClicked()));
    connect(ui->numF, SIGNAL(released()), this, SLOT(numClicked()));
    connect(ui->buttonSign, SIGNAL(released()), this, SLOT(unaryOperationClicked()));
    connect(ui->buttonFac, SIGNAL(released()), this, SLOT(unaryOperationClicked()));
    connect(ui->buttonPlus, SIGNAL(released()), this, SLOT(binaryOperationClicked()));
    connect(ui->buttonMinus, SIGNAL(released()), this, SLOT(binaryOperationClicked()));
    connect(ui->buttonTimes, SIGNAL(released()), this, SLOT(binaryOperationClicked()));
    connect(ui->buttonDiv, SIGNAL(released()), this, SLOT(binaryOperationClicked()));
    connect(ui->buttonExp, SIGNAL(released()), this, SLOT(binaryOperationClicked()));
    connect(ui->buttonRoot, SIGNAL(released()), this, SLOT(binaryOperationClicked()));
    connect(ui->buttonTo2, SIGNAL(released()), this, SLOT(changeNumberSystem()));
    connect(ui->buttonTo8, SIGNAL(released()), this, SLOT(changeNumberSystem()));
    connect(ui->buttonTo10, SIGNAL(released()), this, SLOT(changeNumberSystem()));
    connect(ui->buttonTo16, SIGNAL(released()), this, SLOT(changeNumberSystem()));
    connect(ui->buttonDot, SIGNAL(released()), this, SLOT(dotClicked()));
    connect(ui->buttonCE, SIGNAL(released()), this, SLOT(clear()));
    connect(ui->buttonEq, SIGNAL(released()), this, SLOT(equalClicked()));
    connect(ui->actionHelp, SIGNAL(triggered()), this, SLOT(openHelp()));
}

/**
 * GUI destructor
 */
MainWindow::~MainWindow()
{
    delete numberButtons;
    delete numberSystems;
    delete ui;
}

/**
 * Clear the memory and rewrite the display.
 */
void MainWindow::clear()
{
    newNum = 0;
    dot = 0;
    memory = 0;
    myOperator = 0;
    updateText();
}

/**
 * Number button is pressed, add the approptiate digit to the memory.
 */
void MainWindow::numClicked()
{
    if (newNum == 1) {
        newNum = 0;
        dot = 0;
        memory = 0;
        sign = 0;
        updateText();
    }
    QPushButton *button = (QPushButton *)sender();

    if (dot == 0)
        if(sign == 0){
            memory = memory * numberSystem + numberButtons->id(button);
        } else {
             memory = memory * numberSystem - numberButtons->id(button);
        }
    else {
        if(sign == 0){
            memory += numberButtons->id(button) * pow(numberSystem, (-dot));
        } else {
             memory -= numberButtons->id(button) * pow(numberSystem, (-dot));
        }

        dot++;
        // add a zero to the end of the decimal part, do not call updateText()
        if (numberButtons->id(button) == 0) {
            ui->display->setText(ui->display->text() + "0");
            return;
        }
    }

    updateText();
}

/**
 * Sets the decimal point and starts to accept fractions.
 */
void MainWindow::dotClicked()
{
    if (dot == 0) {
        ui->display->setText(ui->display->text() + ".");
    }
    dot = 1;
}

/**
 * An unary operator is pressed - either the sign button or the factorial.
 */
void MainWindow::unaryOperationClicked()
{
    QPushButton *button = (QPushButton *)sender();
    if (button->text() == "+/-") {
        // vynasob -1 a vypis na display
        memory *= -1;
        if(memory < 0){
            sign = 1;
        } else {
            sign = 0;
        }

    } else if (button->text() == "x!") {
        try {
            memory = MathLib::factorial((long)memory);
        } catch (const char* msg) {
            clear();
            ui->display->setText(msg);
            return;
        }

        newNum = 1;
    }
    updateText();
}

/**
 * A binary operator is pressed - either +, -, *, /, ^, √
 * The first operator is saved, after that it accepts the second operator.
 */
void MainWindow::binaryOperationClicked()
{
    QPushButton *button = (QPushButton *)sender();
    // podivej, jestli je tohle prvni stisk tlacitka operace popr. vyhodnot jiz zadanou operaci
    if (myOperator != 0) {
        MainWindow::equals();
    }
    firstNum = memory;
    // zapamatuj operator pro priste
    // bohuzel case funguje jen s cisly
    if (button->text() == "+") {
        myOperator = 1;
    } else if (button->text() == "-") {
        myOperator = 2;
    } else if (button->text() == "*") {
        myOperator = 3;
    } else if (button->text() == "/") {
        myOperator = 4;
    } else if (button->objectName() == "buttonExp") {
        myOperator = 5;
    } else if (button->objectName() == "buttonRoot") {
        myOperator = 6;
    }
    // pripravit na nove cislo
    newNum = 1;
}

/**
 * The equal button is pressed.
 * Calls the equals() function and resets the selected operator and first number memory.
 */
void MainWindow::equalClicked()
{
    MainWindow::equals();
    firstNum = 0;
    myOperator = 0;
}

/**
 * Evaluates the currently selected operation, calls the respective library function.
 * After that updated the text with the new value.
 */
void MainWindow::equals()
{
    double displayNum;
    QString displayText;

    try {
        // vyber operace na vykonani
        switch (myOperator) {
        case 0:
            break;
        case 1:
            memory = MathLib::sum(firstNum, memory);
            break;
        case 2:
            memory = MathLib::minus(firstNum, memory);
            break;
        case 3:
            memory = MathLib::multi(firstNum, memory);
            break;
        case 4:
            memory = MathLib::delit(firstNum, memory);
            break;
        case 5:
            memory = MathLib::pow(firstNum, memory);
            break;
        case 6:
            memory = MathLib::root(firstNum, memory);
            break;
        }
    } catch (const char* msg) {
        clear();
        ui->display->setText(msg);
        return;
    }
    updateText();
    // pripravit na nove cislo
    newNum = 1;
}

/**
 * MainWindow::updateText
 * Function updates the display according to the selected number system.
 */
void MainWindow::updateText()
{
    // variables store the integer and fraction part of the memory
    double intPart = 0, fractPart = 0;
    // define the selected precision digits
    int fractPrecision = 15;
    // separate the memory into integer part and fraction part
    fractPart = std::modf(memory, &intPart);
    fractPart = std::abs(fractPart);

    if (numberSystem == 10) {
        ui->display->setText(QString::number(memory, 'g', fractPrecision));
    } else {
        // cast to long to select the correct function
        ui->display->setText(QString::number((long)intPart, numberSystem).toUpper());
        // if fraction part is larger then selected precision
        if ((fractPart * qPow(numberSystem, fractPrecision)) >= 1) {
            // add dot character
            ui->display->setText(ui->display->text() + ".");
            // calculate the fraction digits and write them to display
            for (int i = 0; i < fractPrecision; ++i) {
                fractPart *= numberSystem;
                ui->display->setText(ui->display->text() + QString::number((long)fractPart, numberSystem).toUpper());
                fractPart -= (long)fractPart;
                if (fractPart <= std::numeric_limits<double>::epsilon())
                    break;
            }
        }
    }
}

/**
 * Function disables/enables number buttons according to the selected number system.
 */
void MainWindow::makeNumbersVisible()
{
    for (auto button : numberButtons->buttons()) {
        if (numberButtons->id(button) >= numberSystem)
            button->setVisible(false);
        else
            button->setVisible(true);
    }
}

/**
 * When the conversion button has been pressed, changes the current number system and rewrites the display.
 */
void MainWindow::changeNumberSystem()
{
    QPushButton *button = (QPushButton *)sender();
    // change the current number system
    numberSystem = numberSystems->id(button);

    // set the respective button text to indidate selection
    for (auto button : numberSystems->buttons()) {
        if (numberSystems->id(button) == numberSystem)
            button->setText("(.)" + QString::number(numberSystems->id(button)));
        else
            button->setText("()" + QString::number(numberSystems->id(button)));
    }

    // if in hexadecimal number system, resize window to show hex digits.
    if (numberSystem == 16)
        this->setFixedSize(202, 260);
    else
        this->setFixedSize(202, 200);

    // hide unusable digits
    makeNumbersVisible();
    // update display
    updateText();
}

/**
 * Function parses incoming keyboard events and sends signals to the appropriate buttons.
 *
 * @param event Incoming keyboard event.
 */
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_1:
        emit ui->num1->released();
        break;
    case Qt::Key_2:
        if (numberSystem > 2) {
            emit ui->num2->released();
        }
        break;
    case Qt::Key_3:
        if (numberSystem > 3) {
            emit ui->num3->released();
        }
        break;
    case Qt::Key_4:
        if (numberSystem > 4) {
            emit ui->num4->released();
        }
        break;
    case Qt::Key_5:
        if (numberSystem > 5) {
            emit ui->num5->released();
        }
        break;
    case Qt::Key_6:
        if (numberSystem > 6) {
            emit ui->num6->released();
        }
        break;
    case Qt::Key_7:
        if (numberSystem > 7) {
            emit ui->num7->released();
        }
        break;
    case Qt::Key_8:
        if (numberSystem > 8) {
            emit ui->num8->released();
        }
        break;
    case Qt::Key_9:
        if (numberSystem > 9) {
            emit ui->num9->released();
        }
        break;
    case Qt::Key_0:
        emit ui->num0->released();
        break;
    case Qt::Key_Period:
        emit ui->buttonDot->released();
        break;
    case Qt::Key_Slash:
        emit ui->buttonDiv->released();
        break;
    case Qt::Key_Asterisk:
        emit ui->buttonTimes->released();
        break;
    case Qt::Key_Plus:
        emit ui->buttonPlus->released();
        break;
    case Qt::Key_Minus:
        emit ui->buttonMinus->released();
        break;
    case Qt::Key_Exclam:
        emit ui->buttonFac->released();
        break;
    case Qt::Key_Return:
        emit ui->buttonEq->released();
        break;
    case Qt::Key_Equal:
        emit ui->buttonEq->released();
        break;
    case Qt::Key_Enter:
        emit ui->buttonEq->released();
        break;
    case Qt::Key_Delete:
        emit ui->buttonCE->released();
        break;
    case Qt::Key_Backspace:
        emit ui->buttonCE->released();
        break;
    case Qt::Key_A:
        if (numberSystem > 10) {
            emit ui->numA->released();
        }
        break;
    case Qt::Key_B:
        if (numberSystem > 11) {
            emit ui->numB->released();
        }
        break;
    case Qt::Key_C:
        if (numberSystem > 12) {
            emit ui->numC->released();
        }
        break;
    case Qt::Key_D:
        if (numberSystem > 13) {
            emit ui->numD->released();
        }
        break;
    case Qt::Key_E:
        if (numberSystem > 14) {
            emit ui->numE->released();
        }
        break;
    case Qt::Key_F:
        if (numberSystem > 15) {
            emit ui->numF->released();
        }
        break;
    }
}

void MainWindow::openHelp()
{
    QDesktopServices::openUrl(QUrl("file:///" + QApplication::applicationDirPath() + "/dokumentace.pdf"));
}
