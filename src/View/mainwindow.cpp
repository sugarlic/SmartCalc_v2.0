#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  window = new Graph();

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(SetNum()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(SetNum()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(SetNum()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(SetNum()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(SetNum()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(SetNum()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(SetNum()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(SetNum()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(SetNum()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(SetNum()));
  connect(ui->pushButton_X, SIGNAL(clicked()), this, SLOT(SetX()));
  connect(ui->pushButton_exp, SIGNAL(clicked()), this, SLOT(SetExp()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(SetDot()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(SetOperand()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(SetOperand()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(SetOperand()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(SetOperand()));
  connect(ui->pushButton_dev, SIGNAL(clicked()), this, SLOT(SetOperand()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(SetOperand()));
  connect(ui->pushButton_brack1, SIGNAL(clicked()), this, SLOT(SetBracket()));
  connect(ui->pushButton_brack2, SIGNAL(clicked()), this, SLOT(SetBracket()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(SetFunction()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(SetFunction()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(SetFunction()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(SetFunction()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(SetFunction()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(SetFunction()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(SetFunction()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(SetFunction()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(SetFunction()));
  connect(ui->pushButton_eq, SIGNAL(clicked()), this, SLOT(EqButton()));
  connect(ui->pushButtonGraph, SIGNAL(clicked()), this,
          SLOT(onButtonGraphSend()));
  connect(this,
          SIGNAL(SendData(QString, QString, QString, QString, QString,
                          s21::Controler &)),
          window,
          SLOT(RecieveData(QString, QString, QString, QString, QString,
                           s21::Controler &)));
  ui->lineEdit_OpMin->setText(ui->lineEdit_OpMin->text() + "-10");
  ui->lineEdit_OpMax->setText(ui->lineEdit_OpMax->text() + "10");
  ui->lineEdit_ZnMin->setText(ui->lineEdit_ZnMin->text() + "-10");
  ui->lineEdit_ZnMax->setText(ui->lineEdit_ZnMax->text() + "10");
  QIntValidator *validator = new QIntValidator(this);
  validator->setRange(-1000000, 1000000);
  ui->lineEdit_OpMin->setValidator(validator);
  ui->lineEdit_OpMax->setValidator(validator);
  ui->lineEdit_ZnMin->setValidator(validator);
  ui->lineEdit_ZnMax->setValidator(validator);
}

MainWindow::~MainWindow() {
  delete ui;
  delete window;
}

void MainWindow::SetNum() {
  QPushButton *button = (QPushButton *)sender();
  ui->OutputLabel->setText(ui->OutputLabel->toPlainText() + button->text());
  controler_.SetElement(button->text().toStdString());
}

void MainWindow::SetX() {
  ui->OutputLabel->setText(ui->OutputLabel->toPlainText() + "X");
  controler_.SetElement("X");
}

void MainWindow::SetExp() {
  ui->OutputLabel->setText(ui->OutputLabel->toPlainText() + "E");
  controler_.SetElement("E");
}

void MainWindow::SetOperand() {
  QPushButton *button = (QPushButton *)sender();

  if (button->text() == "^") {
    ui->OutputLabel->setText(ui->OutputLabel->toPlainText() + button->text() +
                             "(");
    controler_.SetElement(button->text().toStdString() + "(");
  } else {
    ui->OutputLabel->setText(ui->OutputLabel->toPlainText() + button->text());
    controler_.SetElement(button->text().toStdString());
  }
}

void MainWindow::SetBracket() {
  QPushButton *button = (QPushButton *)sender();

  ui->OutputLabel->setText(ui->OutputLabel->toPlainText() + button->text());
  controler_.SetElement(button->text().toStdString());
}

void MainWindow::SetDot() {
  QPushButton *button = (QPushButton *)sender();

  ui->OutputLabel->setText(ui->OutputLabel->toPlainText() + button->text());
  controler_.SetElement(button->text().toStdString());
}

void MainWindow::SetFunction() {
  QPushButton *button = (QPushButton *)sender();

  ui->OutputLabel->setText(ui->OutputLabel->toPlainText() + button->text() +
                           "(");
  controler_.SetElement((button->text() + "(").toStdString());
}

void MainWindow::EqButton() {
  long double x_value{ui->lineEdit_X->text().toDouble()};
  int error_code{};
  controler_.SetXValue(x_value);
  controler_.PolishCalculation();
  error_code = controler_.GetErrorCode();
  if (error_code == s21::OK) {
    ui->OutputLabel->setText(QString().number(controler_.GetResult(), 0, 7));
    controler_.Clear();
    controler_.SetElement(ui->OutputLabel->toPlainText().toStdString());
  } else {
    ui->OutputLabel->setText(ErrorList(error_code));
    controler_.Clear();
  }
}

void MainWindow::on_pushButtonAC_clicked() {
  ui->OutputLabel->clear();
  controler_.Clear();
}

void MainWindow::onButtonGraphSend() {
  controler_.PolishCalculation();
  controler_.CheckRange({ui->lineEdit_OpMin->text().toStdString(),
                         ui->lineEdit_ZnMin->text().toStdString(),
                         ui->lineEdit_OpMax->text().toStdString(),
                         ui->lineEdit_ZnMax->text().toStdString(), ""});
  int error_code{controler_.GetErrorCode()};
  if (error_code == s21::OK) {
    emit SendData(ui->lineEdit_OpMin->text(), ui->lineEdit_OpMax->text(),
                  ui->lineEdit_ZnMin->text(), ui->lineEdit_ZnMax->text(),
                  ui->OutputLabel->toPlainText(), controler_);
    window->show();
  } else
    ui->OutputLabel->setText(ErrorList(error_code));
}

QString MainWindow::ErrorList(int er_code) {
  QString qstr{};
  switch (er_code) {
    case s21::UNKNOWN_ERROR:
      qstr = "UNKNOWN_ERROR";
      break;
    case s21::OK:
      qstr = "OK";
      break;
    case s21::OPERATOR_ERROR:
      qstr = "OPERATOR_ERROR";
      break;
    case s21::NUMBER_ERROR:
      qstr = "NUMBER_ERROR";
      break;
    case s21::BRACKETS_ERROR:
      qstr = "BRACKETS_ERROR";
      break;
    case s21::CALCULATION_ERROR:
      qstr = "CALCULATION_ERROR";
      break;
    case s21::DIAPOSON_ERROR:
      qstr = "DIAPOSON_ERROR";
      break;
    case s21::FUNCTION_ERROR:
      qstr = "FUNCTION_ERROR";
      break;
    default:
      break;
  }
  return qstr;
}
