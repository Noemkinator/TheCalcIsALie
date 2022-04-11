#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "calc.h"
#include <QButtonGroup>
#include <cmath>

/// variable contains current value, to be written on display
double memory = 0;
/// variable contains currently selected number system
int numberSystem = 10;
/// groups containing selected buttons, for easier manipulation and iteration
QButtonGroup *numberButtons, *numberSystems;

double firstNum; //prvni cislo binarni operace
int newNum=0; //po stisknuti dalsi cislice vynulovat display
/// represents the current exponent of a float digit
int dot=0;
int myOperator = 0; //pamatuje ktery operator pouzit
//0=nic, 1=+, 2=-, 3=*, 4=/, 5=exp, 6=root

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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

    //prirazeni funkci pri stisknuti tlacitek
    connect(ui->num0,SIGNAL(released()),this,SLOT(numClicked()));
    connect(ui->num1,SIGNAL(released()),this,SLOT(numClicked()));
    connect(ui->num2,SIGNAL(released()),this,SLOT(numClicked()));
    connect(ui->num3,SIGNAL(released()),this,SLOT(numClicked()));
    connect(ui->num4,SIGNAL(released()),this,SLOT(numClicked()));
    connect(ui->num5,SIGNAL(released()),this,SLOT(numClicked()));
    connect(ui->num6,SIGNAL(released()),this,SLOT(numClicked()));
    connect(ui->num7,SIGNAL(released()),this,SLOT(numClicked()));
    connect(ui->num8,SIGNAL(released()),this,SLOT(numClicked()));
    connect(ui->num9,SIGNAL(released()),this,SLOT(numClicked()));
    connect(ui->numA,SIGNAL(released()),this,SLOT(numClicked()));
    connect(ui->numB,SIGNAL(released()),this,SLOT(numClicked()));
    connect(ui->numC,SIGNAL(released()),this,SLOT(numClicked()));
    connect(ui->numD,SIGNAL(released()),this,SLOT(numClicked()));
    connect(ui->numE,SIGNAL(released()),this,SLOT(numClicked()));
    connect(ui->numF,SIGNAL(released()),this,SLOT(numClicked()));
    connect(ui->buttonSign,SIGNAL(released()),this,SLOT(unaryOperationClicked()));
    connect(ui->buttonFac,SIGNAL(released()),this,SLOT(unaryOperationClicked()));
    connect(ui->buttonPlus,SIGNAL(released()),this,SLOT(binaryOperationClicked()));
    connect(ui->buttonMinus,SIGNAL(released()),this,SLOT(binaryOperationClicked()));
    connect(ui->buttonTimes,SIGNAL(released()),this,SLOT(binaryOperationClicked()));
    connect(ui->buttonDiv,SIGNAL(released()),this,SLOT(binaryOperationClicked()));
    connect(ui->buttonExp,SIGNAL(released()),this,SLOT(binaryOperationClicked()));
    connect(ui->buttonRoot,SIGNAL(released()),this,SLOT(binaryOperationClicked()));
    connect(ui->buttonTo2,SIGNAL(released()),this,SLOT(changeNumberSystem()));
    connect(ui->buttonTo8,SIGNAL(released()),this,SLOT(changeNumberSystem()));
    connect(ui->buttonTo10,SIGNAL(released()),this,SLOT(changeNumberSystem()));
    connect(ui->buttonTo16,SIGNAL(released()),this,SLOT(changeNumberSystem()));
}

MainWindow::~MainWindow()
{
    delete numberButtons;
    delete numberSystems;
    delete ui;
}

/**
 * @brief MainWindow::on_buttonCE_clicked
 * Clear the memory and rewrite the display.
 */
void MainWindow::on_buttonCE_clicked()
{
    newNum = 0;
    dot = 0;
    memory = 0;
    updateText();
}

/**
 * @brief MainWindow::numClicked
 * Number button is pressed, add the approptiate digit to the memory.
 */
void MainWindow::numClicked()
{
    if (newNum==1){
        MainWindow::on_buttonCE_clicked();
    }
    QPushButton * button = (QPushButton*)sender();

    if (dot == 0)
        memory = memory*numberSystem + numberButtons->id(button);
    else {
        memory += numberButtons->id(button) * pow(numberSystem,(-dot));
        dot++;
    }


    updateText();
}

/**
 * @brief MainWindow::on_buttonDot_released
 * Sets the decimal point and starts to accept fractions.
 */
void MainWindow::on_buttonDot_released()
{
    if (dot==0){
        ui->display->setText(ui->display->text() + ".");
    }
    dot=1;
}

/**
 * @brief MainWindow::unaryOperationClicked
 * An unary operator is pressed - either the sign button or the factorial.
 */
void MainWindow::unaryOperationClicked()
{
    QPushButton * button = (QPushButton*)sender();
    if (button->text()=="+/-")
    {
        //vynasob -1 a vypis na display
        memory*=-1;
        updateText();
    }
    else if (button->text()=="x!")
    {
        //TODO zavolej fci faktorial
        updateText();
    }
}

/**
 * @brief MainWindow::binaryOperationClicked
 * A binary operator is pressed - either +, -, *, /, ^, √
 * The first operator is saved, after that it accepts the second operator.
 */
void MainWindow::binaryOperationClicked()
{
    QPushButton * button = (QPushButton*)sender();
    //podivej, jestli je tohle prvni stisk tlacitka operace popr. vyhodnot jiz zadanou operaci
    if (myOperator!=0){
        MainWindow::equals();
    }
    firstNum=memory;
    //zapamatuj operator pro priste
    //bohuzel case funguje jen s cisly
    if(button->text()=="+"){
        myOperator=1;
    }
    else if(button->text()=="-"){
        myOperator=2;
    }
    else if(button->text()=="*"){
        myOperator=3;
    }
    else if(button->text()=="/"){
        myOperator=4;
    }
    else if(button->objectName()=="buttonExp")
    {
        myOperator=5;
    }
    else if(button->objectName()=="buttonSqrt")
    {
        myOperator=6;
    }
    //pripravit na nove cislo
    newNum=1;
}

/**
 * @brief MainWindow::on_buttonEq_released
 * The equal button is pressed.
 * Calls the equals() function and resets the selected operator and first number memory.
 */
void MainWindow::on_buttonEq_released()
{
    MainWindow::equals();
    firstNum=0;
    myOperator=0;
}

/**
 * @brief MainWindow::equals
 * Evaluates the currently selected operation, calls the respective library function.
 * After that updated the text with the new value.
 */
void MainWindow::equals()
{
    double displayNum;
    QString displayText;

    //vyber operace na vykonani
    switch (myOperator){
    case 0:
        break;
    case 1:
        memory=MathLib::plus(firstNum, memory);
        break;
    case 2:
        memory=MathLib::minus(firstNum, memory);
        break;
    case 3:
        memory=MathLib::multiply(firstNum, memory);
        break;
    case 4:
        memory=MathLib::divide(firstNum, memory);
        break;
    case 5:
        firstNum+=ui->display->text().toDouble();//<-- to be replaced
        displayText = QString::number(firstNum, 'g', 15);
        ui->display->setText(displayText);
        break;
    case 6:
        firstNum-=ui->display->text().toDouble();//<-- to be replaced
        displayText = QString::number(firstNum, 'g', 15);
        ui->display->setText(displayText);
        break;
    }
    updateText();
    //pripravit na nove cislo
    newNum=1;
}

/**
 * @brief MainWindow::updateText
 * Function updates the display according to the selected number system.
 */
void MainWindow::updateText() {
    // variables store the integer and fraction part of the memory
    double intPart = 0, fractPart = 0;
    // define the selected precision digits
    int fractPrecision = 15;

    if (numberSystem == 10)
        ui->display->setText(QString::number(memory, 'g', fractPrecision));
    else {
        // separate the memory into integer part and fraction part
        fractPart = std::modf(memory, &intPart);
        // cast to long to truncate the decimal part
        ui->display->setText(QString::number((long)intPart, numberSystem).toUpper());
    }
    // if fraction part is large then selected precision
    if ((long)(fractPart * pow(10, fractPrecision)) > 0){
        // add dot character
        ui->display->setText(ui->display->text() + "." );
        // calculate the fraction digits and write them to display
        for (int i = 0; i < fractPrecision; ++i) {
            fractPart *= numberSystem;
            ui->display->setText(ui->display->text() + QString::number((long)fractPart, numberSystem).toUpper());
            fractPart -= (long)fractPart;

        }
    }
}

/**
 * @brief MainWindow::makeNumbersVisible
 * Function disables/enables number buttons according to the selected number system.
 */
void MainWindow::makeNumbersVisible() {
    for (auto button: numberButtons->buttons()) {
        if (numberButtons->id(button) >= numberSystem)
            button->setVisible(false);
        else
            button->setVisible(true);
    }
}

/**
 * @brief MainWindow::changeNumberSystem
 * When the conversion button has been pressed, changes the current number system and rewrites the display.
 */
void MainWindow::changeNumberSystem() {
    QPushButton * button = (QPushButton*)sender();
    // change the current number system
    numberSystem = numberSystems->id(button);

    // set the respective button text to indidate selection
    for (auto button: numberSystems->buttons()) {
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