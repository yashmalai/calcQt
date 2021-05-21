#include <QShortcut>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "postfixexpression.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(315, 600));

    label = new QLabel(this);
    movie = new QMovie(":/img/res/race-car-74.gif");
    label->setMovie(movie);
    label->resize(480,270);
    label->move(-83,390);
    label->show();
    movie->start();


    curExp = "";

    // Подключение клавиши Backspace для удаление символа с клавиатуры
    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::Key_Backspace), this);
    QObject::connect(shortcut, &QShortcut::activated, this, &MainWindow::on_backspace_pressed);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete movie;
    delete label;
}

// Обновляет текстовые поля графического интерфейса "Выражение" и "Ответ"
// для отображения текущего состояния
void MainWindow::updateCurrentExp()
{
    if (curExp.isEmpty())
    {
        ui->exprTextBox->setText("0");
        ui->ansTextBox->setText("Ответ");
    }
    else
    {
         ui->exprTextBox->setText(curExp);
    }
}

// Вызывается при нажатии горячей клавиши Backspace.
void MainWindow::on_backspace_pressed()
{
    if (curExp.isEmpty()) return;

    curExp.truncate(curExp.length() - 1);
    updateCurrentExp();
}

// Вызывается при нажатии кнопки "=" на калькуляторе
void MainWindow::on_equalsBtn_clicked()
{
    PostfixExpression pfExp;
    bool success = pfExp.fromInfix(curExp);

    if (!success)
    {
        ui->ansTextBox->setText("ERR: Недопустимое выражение");
        return;
    }

    double result = 0.0;
    success = pfExp.solve(result);

    if (!success)
    {
        ui->ansTextBox->setText("ERR: Недопустимое выражение");
        return;
    }

    QString ans = QString::number(result);
    ui->ansTextBox->setText(ans);
}

// Методы, которые вызываются при нажатии той или иной кнопки
// на калькуляторе ("С", "+", "-", "*" и так далее)
void MainWindow::on_clearBtn_clicked()
{
    curExp = "";
    updateCurrentExp();
}

void MainWindow::on_plusBtn_clicked()
{
    curExp.append("+");
    updateCurrentExp();
}

void MainWindow::on_subBtn_clicked()
{
    curExp.append("-");
    updateCurrentExp();
}

void MainWindow::on_multBtn_clicked()
{
    curExp.append("*");
    updateCurrentExp();
}

void MainWindow::on_divBtn_clicked()
{
    curExp.append("/");
    updateCurrentExp();
}

void MainWindow::on_exponentBtn_clicked()
{
    curExp.append("^");
    updateCurrentExp();
}

void MainWindow::on_periodBtn_clicked()
{
    curExp.append(".");
    updateCurrentExp();
}

void MainWindow::on_leftParenthBtn_clicked()
{
    curExp.append("(");
    updateCurrentExp();
}

void MainWindow::on_rightParenthBtn_clicked()
{
    curExp.append(")");
    updateCurrentExp();
}

void MainWindow::on_zeroBtn_clicked()
{
    curExp.append("0");
    updateCurrentExp();
}

void MainWindow::on_oneBtn_clicked() {
    curExp.append("1");
    updateCurrentExp();
}

void MainWindow::on_twoBtn_clicked() {
    curExp.append("2");
    updateCurrentExp();
}

void MainWindow::on_threeBtn_clicked() {
    curExp.append("3");
    updateCurrentExp();
}

void MainWindow::on_fourBtn_clicked() {
    curExp.append("4");
    updateCurrentExp();
}

void MainWindow::on_fiveBtn_clicked() {
    curExp.append("5");
    updateCurrentExp();
}

void MainWindow::on_sixBtn_clicked() {
    curExp.append("6");
    updateCurrentExp();
}

void MainWindow::on_sevenBtn_clicked() {
    curExp.append("7");
    updateCurrentExp();
}

void MainWindow::on_eightBtn_clicked() {
    curExp.append("8");
    updateCurrentExp();
}

void MainWindow::on_nineBtn_clicked() {
    curExp.append("9");
    updateCurrentExp();
}


