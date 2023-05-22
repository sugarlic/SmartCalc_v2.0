#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "View.h"
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_pushButtonAC_clicked();
  void EqButton();
  void SetNum();
  void SetX();
  void SetExp();
  void SetOperand();
  void SetBracket();
  void SetDot();
  void SetFunction();
  QString ErrorList(int er_code);

 signals:
  void SendData(QString str_xmin, QString str_xmax, QString str_ymin,
                QString str_ymax, QString str, s21::Controler &controler);
 private slots:
  void onButtonGraphSend();

 private:
  s21::Controler controler_{};
  Ui::MainWindow *ui;
  Graph *window;
};
#endif  // MAINWINDOW_H
