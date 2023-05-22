#ifndef SRC_MODEL_H_
#define SRC_MODEL_H_

#include "Parser.h"

namespace s21 {
class Model {
 public:
  Model() : error_code_{s21::OK} {};
  void Polish();
  double GetExprRes() const;
  error_type GetErCode() const;
  void SetXValue(double x_val);
  void Insert(const std::string &str);
  void CheckRange(const s21::GraphParametors &parametors);
  void Clear();

 private:
  void IsFunction(const std::string &str);
  void IsOperator(const std::string &str);
  void IsDigit(const std::string &str);
  void IsX(const std::string &str);
  void IsExp(const std::string &str);
  bool CheckBrackets() const;
  bool Parser();
  bool NotationCalc();
  void LexemCalc();
  bool FuncCalc();
  void EraseVectorF();
  void EraseVectorL();
  std::string str_{};
  double result_{};
  double x_val_{};
  error_type error_code_{};
  std::stack<Elem> stack_out_{};
  std::vector<Elem> vector_{};
};
}  // namespace s21

#endif  // SRC_MODEL_H_