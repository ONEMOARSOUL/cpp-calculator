#pragma once

#include "calculator.h"
#include "enums.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <functional>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void SetInputText(const std::string& text);
    void SetErrorText(const std::string& text);
    void SetFormulaText(const std::string& text);
    void SetMemText(const std::string& text);
    void SetExtraKey(const std::optional<std::string>& key);

    void SetDigitKeyCallback(std::function<void(int key)> cb);
    void SetProcessOperationKeyCallback(std::function<void(Operation key)> cb);
    void SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb);
    void SetControllerCallback(std::function<void(ControllerType controller)> cb);

private:
    // UI элементы
    Ui::MainWindow* ui;
    QComboBox* cmb_controller;
    QPushButton* tb_extra;
    QLabel* l_result;
    QLabel* l_formula;
    QLabel* l_memory;

    // Колбэк-функции
    std::function<void(int key)> digit_cb_;
    std::function<void(Operation key)> operation_cb_;
    std::function<void(ControlKey key)> control_cb_;
    std::function<void(ControllerType controller)> controller_cb_;

    void SetupUI();
    void ConnectSignals();
    
};