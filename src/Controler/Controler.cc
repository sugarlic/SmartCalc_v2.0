#include "Controler.h"

void s21::Controler::SetElement(const std::string &str) { m_.Insert(str); }

int s21::Controler::GetErrorCode() const { return m_.GetErCode(); }

void s21::Controler::PolishCalculation() { m_.Polish(); }

long double s21::Controler::GetResult() const { return m_.GetExprRes(); }

void s21::Controler::SetXValue(double x_value) { m_.SetXValue(x_value); }

void s21::Controler::SetRange(const s21::GraphParametors &parametors) {
  gm_.SetRange(parametors);
}

void s21::Controler::CalculateGraph() { gm_.GraphCalculator(); }

void s21::Controler::CheckRange(const s21::GraphParametors &parametors) {
  m_.CheckRange(parametors);
}

double s21::Controler::GetXBegin() { return gm_.GetXBeg(); }

double s21::Controler::GetXEnd() { return gm_.GetXEn(); }

double s21::Controler::GetYBegin() { return gm_.GetYBeg(); }

double s21::Controler::GetYEnd() { return gm_.GetYEn(); }

std::vector<double> s21::Controler::GetXVec() { return gm_.GetXV(); }

std::vector<double> s21::Controler::GetYVec() { return gm_.GetYV(); }

void s21::Controler::Clear() { m_.Clear(); }

void s21::Controler::ClearGraph() { gm_.Clear(); }