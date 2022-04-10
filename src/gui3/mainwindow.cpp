#include "mainwindow.h"
#include "./ui_mainwindow.h"

double firstNum; //prvni cislo binarni operace
int newNum=0; //po stisknuti dalsi cislice vynulovat display
int dot=0; //zajistuje jen jednu desetinnou carku v cisle
int myOperator = 0; //pamatuje ktery operator pouzit
                    //0=nic, 1=+, 2=-, 3=*, 4=/, 5=exp, 6=root

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    connect(ui->buttonSign,SIGNAL(released()),this,SLOT(unaryOperationClicked()));
    connect(ui->buttonFac,SIGNAL(released()),this,SLOT(unaryOperationClicked()));
    connect(ui->buttonPlus,SIGNAL(released()),this,SLOT(binaryOperationClicked()));
    connect(ui->buttonMinus,SIGNAL(released()),this,SLOT(binaryOperationClicked()));
    connect(ui->buttonTimes,SIGNAL(released()),this,SLOT(binaryOperationClicked()));
    connect(ui->buttonDiv,SIGNAL(released()),this,SLOT(binaryOperationClicked()));
    connect(ui->buttonExp,SIGNAL(released()),this,SLOT(binaryOperationClicked()));
    connect(ui->buttonRoot,SIGNAL(released()),this,SLOT(binaryOperationClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;    
}

//stisknuti Clear
void MainWindow::on_buttonCE_clicked()
{
    newNum=0;
    dot=0;
    ui->display->setText("0");
}

//stisknuti cislice
void MainWindow::numClicked()
{
    if (newNum==1){
        MainWindow::on_buttonCE_clicked();
    }
    QPushButton * button = (QPushButton*)sender();
    double displayNum;
    QString displayText;

    //upraveni formatu na double
    displayNum=(ui->display->text() + button->text()).toDouble();
    displayText = QString::number(displayNum, 'g', 15);

    ui->display->setText(displayText);
}

//stisknuti desetinna carka
void MainWindow::on_buttonDot_released()
{
    if (dot==0){
         ui->display->setText(ui->display->text() + ".");
    }
    dot=1;
}

//stisknuti +/- nebo x!
void MainWindow::unaryOperationClicked()
{
    double displayNum;
    QString displayText;
    QPushButton * button = (QPushButton*)sender();
    if (button->text()=="+/-")
    {
        //vynasob -1 a vypis na display
        displayNum=(ui->display->text().toDouble());
        displayNum*=-1;
        displayText = QString::number(displayNum, 'g', 15);

        ui->display->setText(displayText);
    }
    else if (button->text()=="x!")
    {
        //TODO zavolej fci faktorial
        displayNum=(ui->display->text().toDouble());
        //tady se bude volat fce
        displayNum=1234567890;// <--placeholder
        displayText = QString::number(displayNum, 'g', 15);

        ui->display->setText(displayText);
    }
}

//stisknuti binarni operace
void MainWindow::binaryOperationClicked()
{
    double tempFirstNum;
    double displayNum;
    QString displayText;
    QPushButton * button = (QPushButton*)sender();
    //podivej, jestli je tohle prvni stisk tlacitka operace popr. vyhodnot jiz zadanou operaci
    if (myOperator==0){
        //uloz cislo pro pristi operaci
        firstNum=ui->display->text().toDouble();
    }
    else{
        firstNum=MainWindow::equals();
    }
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

//stisknuti =
void MainWindow::on_buttonEq_released()
{
    MainWindow::equals();
    newNum=1;
    firstNum=0;
    myOperator=0;
}

//vypocet, volani funkci knihoven
int MainWindow::equals()
{
    double displayNum;
    QString displayText;

    //vyber operace na vykonani
    switch (myOperator){
        case 0:
           break;
        case 1:
           firstNum+=ui->display->text().toDouble();//<-- to be replaced
           displayText = QString::number(firstNum, 'g', 15);
           ui->display->setText(displayText);
           break;
        case 2:
           firstNum-=ui->display->text().toDouble();//<-- to be replaced
           displayText = QString::number(firstNum, 'g', 15);
           ui->display->setText(displayText);
           break;
        case 3:
           firstNum*=ui->display->text().toDouble();//<-- to be replaced
           displayText = QString::number(firstNum, 'g', 15);
           ui->display->setText(displayText);
           break;
        case 4:
           firstNum/=ui->display->text().toDouble();//<-- to be replaced
           displayText = QString::number(firstNum, 'g', 15);
           ui->display->setText(displayText);
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
    //pripravit na nove cislo
    newNum=1;
    return firstNum;
}

