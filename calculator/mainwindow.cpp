#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      current_operation_(Operation::NO_OPERATION),
      input_number_(""),
      calculator_(),
      active_number_(0),
      memory_cell_(0),
      memory_saved_(false)
{
    ui->setupUi(this);
    ui->l_result->setText("0");
    ui->l_memory->setText("");
    ui->l_formula->setText("");

    connect(ui->pb_1, &QPushButton::clicked, this, &MainWindow::on_digit_button_clicked);
    connect(ui->pb_2, &QPushButton::clicked, this, &MainWindow::on_digit_button_clicked);
    connect(ui->pb_3, &QPushButton::clicked, this, &MainWindow::on_digit_button_clicked);
    connect(ui->pb_4, &QPushButton::clicked, this, &MainWindow::on_digit_button_clicked);
    connect(ui->pb_5, &QPushButton::clicked, this, &MainWindow::on_digit_button_clicked);
    connect(ui->pb_6, &QPushButton::clicked, this, &MainWindow::on_digit_button_clicked);
    connect(ui->pb_7, &QPushButton::clicked, this, &MainWindow::on_digit_button_clicked);
    connect(ui->pb_8, &QPushButton::clicked, this, &MainWindow::on_digit_button_clicked);
    connect(ui->pb_9, &QPushButton::clicked, this, &MainWindow::on_digit_button_clicked);
    connect(ui->pb_0, &QPushButton::clicked, this, &MainWindow::on_digit_button_clicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

//Методы обработки операций

QString MainWindow::PerformOperation(Operation op) {
    switch (op) {
        case Operation::ADDITION:
            return " + ";
        case Operation::SUBTRACTION:
            return " − ";
        case Operation::DIVISION:
            return " ÷ ";
        case Operation::MULTIPLICATION:
            return " × ";
        case Operation::POWER:
            return " ^ ";
        default:
            return "";
    }
}

void MainWindow::SetOperation(Operation op) {
    if(current_operation_ == Operation::NO_OPERATION) {
        calculator_.Set(active_number_);
    }
    input_number_ = "";
    current_operation_ = op;
    ui->l_formula->setText(QString::number(calculator_.GetNumber()) + PerformOperation(op));
}

//Методы нажатия кнопок

void MainWindow::on_digit_button_clicked() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QString digit = button->text();
        if (digit == "0" && input_number_ == "0") {
            return; 
        }

        if (input_number_ == "0") {
            input_number_ = digit;
        } else {
            input_number_.append(digit);
        }

        ui->l_result->setText(input_number_);
        active_number_ = input_number_.toDouble();
    }
}

void MainWindow::on_pb_dot_clicked() {
    if(input_number_.contains('.'))
        return;

    if(input_number_.isEmpty())
        input_number_.append('0');

    input_number_.append('.');
    ui->l_result->setText(input_number_);
    active_number_ = input_number_.toDouble();
}

void MainWindow::on_pb_add_clicked() {
    SetOperation(Operation::ADDITION);
}

void MainWindow::on_pb_div_clicked() {
    SetOperation(Operation::DIVISION);
}

void MainWindow::on_pb_mul_clicked() {
    SetOperation(Operation::MULTIPLICATION);
}

void MainWindow::on_pb_sub_clicked() {
    SetOperation(Operation::SUBTRACTION);
}

void MainWindow::on_pb_pow_clicked() {
    SetOperation(Operation::POWER);
}

void MainWindow::on_pb_eq_clicked() {

    if (current_operation_ == Operation::NO_OPERATION) {
        return;
    }
        
    auto op = PerformOperation(current_operation_);
    ui->l_formula->setText(QString::number(calculator_.GetNumber())+ op + QString::number(active_number_) + " =");

    switch (current_operation_) {
        case Operation::ADDITION:
            calculator_.Add(active_number_);
            break;
        case Operation::SUBTRACTION:
            calculator_.Sub(active_number_);
            break;
        case Operation::MULTIPLICATION:
            calculator_.Mul(active_number_);
            break;
        case Operation::DIVISION:
            calculator_.Div(active_number_);
            break;
        case Operation::POWER:
            calculator_.Pow(active_number_);
            break;
        default:
            break;
    }

    current_operation_ = Operation::NO_OPERATION;
    active_number_ = calculator_.GetNumber();
    input_number_ = "";
    ui->l_result->setText(QString::number(active_number_));
}

void MainWindow::on_pb_MS_clicked() {
    memory_cell_ = active_number_;
    memory_saved_ = true;
    ui->l_memory->setText("M");
}

void MainWindow::on_pb_MR_clicked() {
    if (memory_saved_ == false) {
        return;
    }
    active_number_ = memory_cell_;
    ui->l_result->setText(QString::number(active_number_));
}

void MainWindow::on_pb_MC_clicked() {
    memory_cell_ = 0;
    memory_saved_ = false;
    ui->l_memory->setText("");
}

void MainWindow::on_pb_C_clicked() {
    active_number_ = 0;
    calculator_.Set(active_number_);
    input_number_ = "";
    current_operation_ = Operation::NO_OPERATION;
    ui->l_result->setText("0");
    ui->l_formula->setText("");
}

void MainWindow::on_pb_erase_clicked() {
    if(current_operation_ == Operation::NO_OPERATION && input_number_ =="") {
        return;
    }
    else {
        input_number_.chop(1);
        if (input_number_ == "" || input_number_ == "-") {
            input_number_ = "0";
        } 
        ui->l_result->setText(input_number_);
        active_number_ = input_number_.toDouble();
    }
}

void MainWindow::on_pb_plusminus_clicked() {
    if(QString::number(active_number_) == "nan") {
        return;
    } else if (input_number_.startsWith('-')) {
        input_number_ = input_number_.mid(1);
    } else {
        input_number_ = "-" + input_number_;
    }
    ui->l_result->setText(input_number_);
    active_number_ = input_number_.toDouble();
}



