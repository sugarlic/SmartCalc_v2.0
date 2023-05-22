#include "graph.h"

#include "mainwindow.h"
#include "ui_graph.h"

Graph::Graph(QWidget *parent) : QWidget(parent), ui(new Ui::Graph) {
  ui->setupUi(this);
}

Graph::~Graph() { delete ui; }

void Graph::RecieveData(QString str_xmin, QString str_xmax, QString str_ymin,
                        QString str_ymax, QString str,
                        s21::Controler &controler) {
  controler.ClearGraph();
  ui->label_X_min->setText(str_xmin);
  ui->label_X_max->setText(str_xmax);
  ui->label_Y_min->setText(str_ymin);
  ui->label_Y_max->setText(str_ymax);
  ui->widget->clearGraphs();
  controler.SetRange({str_xmin.toStdString(), str_ymin.toStdString(),
                      str_xmax.toStdString(), str_ymax.toStdString(),
                      str.toStdString()});
  controler.CalculateGraph();
  std::vector<double> x_vec = controler.GetXVec();
  std::vector<double> y_vec = controler.GetYVec();
  QVector<double> x_vector(x_vec.begin(), x_vec.end());
  QVector<double> y_vector(y_vec.begin(), y_vec.end());
  ui->widget->xAxis->setRange(controler.GetXBegin(), controler.GetXEnd());
  ui->widget->yAxis->setRange(controler.GetYBegin(), controler.GetYEnd());
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x_vector, y_vector);
  ui->widget->replot();
}
