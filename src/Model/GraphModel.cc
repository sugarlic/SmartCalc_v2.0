#include "GraphModel.h"

void s21::GraphModel::SetRange(const s21::GraphParametors &parametors) {
  parametors_.expression = parametors.expression;
  parametors_.x_begin = parametors.x_begin;
  parametors_.y_begin = parametors.y_begin;
  parametors_.y_end = parametors.y_end;
  parametors_.x_end = parametors.x_end;
}

void s21::GraphModel::GraphCalculator() {
  x_begin_ = std::atof(parametors_.x_begin.c_str());
  x_end_ = std::atof(parametors_.x_end.c_str());
  y_begin_ = std::atof(parametors_.y_begin.c_str());
  y_end_ = std::atof(parametors_.y_end.c_str());
  double precision = (x_end_ - x_begin_) / 2000;
  for (double x = x_begin_; x <= x_end_ && m_.GetErCode() == s21::OK;
       x += precision) {
    m_.SetXValue(x);
    m_.Insert(parametors_.expression);
    m_.Polish();
    x_vec_.push_back(x);
    y_vec_.push_back(m_.GetExprRes());
    m_.Clear();
  }
}

double s21::GraphModel::GetXBeg() { return x_begin_; }

double s21::GraphModel::GetXEn() { return x_end_; }

double s21::GraphModel::GetYBeg() { return y_begin_; }

double s21::GraphModel::GetYEn() { return y_end_; }

std::vector<double> s21::GraphModel::GetXV() { return x_vec_; }

std::vector<double> s21::GraphModel::GetYV() { return y_vec_; }

void s21::GraphModel::Clear() {
  m_.Clear();
  parametors_.Clear();
  x_begin_ = 0;
  y_begin_ = 0;
  x_end_ = 0;
  y_end_ = 0;
  x_vec_.clear();
  y_vec_.clear();
}