#ifndef SRC_CONTROLER_H_
#define SRC_CONTROLER_H_

#include "../Model/GraphModel.h"

namespace s21 {
class Controler {
 public:
  Controler(){};
  ~Controler(){};

  void SetElement(const std::string &str);
  void SetXValue(double x_value);
  int GetErrorCode() const;
  void PolishCalculation();
  long double GetResult() const;
  void CalculateGraph();
  void SetRange(const s21::GraphParametors &parametors);
  void CheckRange(const s21::GraphParametors &parametors);
  std::vector<double> GetXVec();
  std::vector<double> GetYVec();
  double GetXBegin();
  double GetXEnd();
  double GetYBegin();
  double GetYEnd();
  void Clear();
  void ClearGraph();

 private:
  s21::Model m_{};
  s21::GraphModel gm_{};
};

}  // namespace s21

#endif  // SRC_CONTROLER_H_