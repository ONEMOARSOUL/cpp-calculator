#pragma once

#include "calculator.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum Operation {
    NO_OPERATION = 0,
    MULTIPLICATION,
    DIVISION,
    SUBTRACTION,
    ADDITION,
    POWER,
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    
private slots:
    void on_digit_button_clicked();
    void on_pb_dot_clicked();   
    void on_pb_add_clicked();
    void on_pb_div_clicked();
    void on_pb_mul_clicked();
    void on_pb_sub_clicked();
    void on_pb_pow_clicked();
    void on_pb_eq_clicked();
    void on_pb_MS_clicked();
    void on_pb_MR_clicked();
    void on_pb_MC_clicked();
    void on_pb_C_clicked();
    void on_pb_erase_clicked();
    void on_pb_plusminus_clicked();

private:
    Ui::MainWindow* ui;
    QString PerformOperation(Operation op);
    void SetOperation(Operation op);

    Operation current_operation_;
    QString input_number_;
    Calculator calculator_;
    double active_number_;
    double memory_cell_;
    bool memory_saved_;
};
