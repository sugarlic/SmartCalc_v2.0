#ifndef GRAPH_H
#define GRAPH_H

#include "View.h"

namespace Ui {
class Graph;
}

class Graph : public QWidget {
  Q_OBJECT

 public slots:
  void RecieveData(QString str_xmin, QString str_xmax, QString str_ymin,
                   QString str_ymax, QString str, s21::Controler &controler);

 public:
  explicit Graph(QWidget *parent = nullptr);
  ~Graph();

 private:
  Ui::Graph *ui;
};

#endif  // GRAPH_H
