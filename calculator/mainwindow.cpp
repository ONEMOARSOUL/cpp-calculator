// Реальзуйте класс главного окна.
#include "mainwindow.h"

// Конструктор
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    cmb_controller = ui->cmb_controller;
    tb_extra = ui->tb_extra;
    l_result = ui->l_result;
    l_formula = ui->l_formula;
    l_memory = ui->l_memory;
    SetupUI();
    ConnectSignals();
}

// Деструктор
MainWindow::~MainWindow() {
    delete ui;
}

// Установка текста в поле ввода
void MainWindow::SetInputText(const std::string& text) {
    l_result->setStyleSheet("");
    l_result->setText(QString::fromStdString(text));
}

// Установка текста ошибки
void MainWindow::SetErrorText(const std::string& text) {
    l_result->setStyleSheet("color: red;");
    l_result->setText(QString::fromStdString(text));
}

// Установка текста формулы
void MainWindow::SetFormulaText(const std::string& text) {
    l_formula->setText(QString::fromStdString(text));
}

// Установка индикатора памяти
void MainWindow::SetMemText(const std::string& text) {
    l_memory->setText(QString::fromStdString(text));
}

// Установка экстра-кнопки
void MainWindow::SetExtraKey(const std::optional<std::string>& key) {
    if (key) {
        tb_extra->show();
        QString str = QString::fromStdString(key.value());
        tb_extra->setText(str);
    } else {
        tb_extra->hide();
    }
}

// Установка колбэка для цифровых кнопок
void MainWindow::SetDigitKeyCallback(std::function<void(int key)> cb) {
    digit_cb_ = cb;
}

// Установка колбэка для операций
void MainWindow::SetProcessOperationKeyCallback(std::function<void(Operation key)> cb) {
    operation_cb_ = cb;
}

// Установка колбэка для управляющих кнопок
void MainWindow::SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb) {
    control_cb_ = cb;
}

// Установка колбэка для смены типа чисел
void MainWindow::SetControllerCallback(std::function<void(ControllerType controller)> cb) {
    controller_cb_ = cb;
}

// Настройка интерфейса
void MainWindow::SetupUI() {
    cmb_controller->clear();
    cmb_controller->addItems({
        "double", "float", "uint8_t", "int",
        "int64_t", "size_t", "Rational"
    });
        
    tb_extra->setVisible(false);
    l_result->setText("0");
    l_formula->setText("");
    l_memory->setText("");
}

// Подключение сигналов
void MainWindow::ConnectSignals() {
    connect(cmb_controller, &QComboBox::currentTextChanged, [this](const QString& text) {
        if (text == "uint8_t") {
            controller_cb_(ControllerType::UINT8_T);
        } else if (text == "int") {
            controller_cb_(ControllerType::INT);
        } else if (text == "int64_t") {
            controller_cb_(ControllerType::INT64_T);
        } else if (text == "size_t") {
            controller_cb_(ControllerType::SIZE_T);
        } else if (text == "double") {
            controller_cb_(ControllerType::DOUBLE);
        } else if (text == "float") {
            controller_cb_(ControllerType::FLOAT);
        } else if (text == "Rational") {
            controller_cb_(ControllerType::RATIONAL);
        }
    });

    auto digitButtons = {ui->pb_0, ui->pb_1, ui->pb_2, ui->pb_3, ui->pb_4, 
                        ui->pb_5, ui->pb_6, ui->pb_7, ui->pb_8, ui->pb_9};
    for (auto* button : digitButtons) {
        connect(button, &QPushButton::clicked, [this, button]() {
            if (digit_cb_) {
                digit_cb_(button->text().toInt());
            }
        });
    }

    connect(ui->pb_add, &QPushButton::clicked, [this]() {
        if (operation_cb_) {
            operation_cb_(Operation::ADDITION);
        }
    });
    connect(ui->pb_sub, &QPushButton::clicked, [this]() {
        if (operation_cb_) {
            operation_cb_(Operation::SUBTRACTION);
        }
    });
    connect(ui->pb_mul, &QPushButton::clicked, [this]() {
        if (operation_cb_) {
            operation_cb_(Operation::MULTIPLICATION);
        }
    });
    connect(ui->pb_div, &QPushButton::clicked, [this]() {
        if (operation_cb_) {
            operation_cb_(Operation::DIVISION);
        }
    });
    connect(ui->pb_pow, &QPushButton::clicked, [this]() {
        if (operation_cb_) {
            operation_cb_(Operation::POWER);
        }
    });

    connect(ui->pb_eq, &QPushButton::clicked, [this]() {
        if (control_cb_) {
            control_cb_(ControlKey::EQUALS);
        }
    });
    connect(ui->pb_C, &QPushButton::clicked, [this]() {
        if (control_cb_) {
            control_cb_(ControlKey::CLEAR);
        }
    });
    connect(ui->pb_MS, &QPushButton::clicked, [this]() {
        if (control_cb_) {
            control_cb_(ControlKey::MEM_SAVE);
        }
    });
    connect(ui->pb_MR, &QPushButton::clicked, [this]() {
        if (control_cb_) {
            control_cb_(ControlKey::MEM_LOAD);
        }
    });
    connect(ui->pb_MC, &QPushButton::clicked, [this]() {
        if (control_cb_) {
            control_cb_(ControlKey::MEM_CLEAR);
        }
    });
    connect(ui->pb_plusminus, &QPushButton::clicked, [this]() {
        if (control_cb_) {
            control_cb_(ControlKey::PLUS_MINUS);
        }
    });
    connect(ui->pb_erase, &QPushButton::clicked, [this]() {
        if (control_cb_) {
            control_cb_(ControlKey::BACKSPACE);
        }
    });
    connect(ui->tb_extra, &QPushButton::clicked, [this]() {
        if (control_cb_) {
            control_cb_(ControlKey::EXTRA_KEY);
        }
    });
}