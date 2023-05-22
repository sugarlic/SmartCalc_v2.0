#ifndef SRC_GRAPH_MODEL_H_
#define SRC_GRAPH_MODEL_H_

#include "Model.h"

namespace s21 {
class GraphModel {
 public:
  GraphModel(){};
  ~GraphModel(){};
  void SetRange(const s21::GraphParametors &parametors);
  void GraphCalculator();
  std::vector<double> GetXV();
  std::vector<double> GetYV();
  double GetXBeg();
  double GetXEn();
  double GetYBeg();
  double GetYEn();
  void Clear();

 private:
  Model m_{};
  GraphParametors parametors_{};
  double x_begin_;
  double x_end_;
  double y_begin_;
  double y_end_;
  std::vector<double> x_vec_{};
  std::vector<double> y_vec_{};
};
}  // namespace s21

#endif  // SRC_GRAPH_MODEL_H_