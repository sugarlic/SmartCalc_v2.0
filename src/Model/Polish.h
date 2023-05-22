#ifndef SRC_POLISH_H_
#define SRC_POLISH_H_

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

namespace s21 {
struct Elem {
  char value_type{};
  char priority{};
  long double value{};
};

struct GraphParametors {
  std::string x_begin{};
  std::string y_begin{};
  std::string x_end{};
  std::string y_end{};
  std::string expression;

  void Clear() {
    x_begin.clear();
    y_begin.clear();
    x_end.clear();
    y_end.clear();
    expression.clear();
  }
};

enum error_type {
  UNKNOWN_ERROR = 0,
  OK = 1,
  OPERATOR_ERROR = 2,
  NUMBER_ERROR = 3,
  BRACKETS_ERROR = 4,
  CALCULATION_ERROR = 5,
  DIAPOSON_ERROR = 6,
  FUNCTION_ERROR = 7
};

enum operands {
  x = 0,
  Num,
  Sin,
  Cos,
  Tan,
  Asin,
  Acos,
  Atan,
  Sqrt,
  Ln,
  Log,
  Mod,
  UnPlus,
  UnMinus
};

const std::map<std::string, char> math_func = {
    {"sin(", Sin},   {"cos(", Cos},   {"tan(", Tan}, {"asin(", Asin},
    {"acos(", Acos}, {"atan(", Atan}, {"ln(", Ln},   {"log(", Log},
    {"sqrt(", Sqrt}, {"mod", Mod}};
const std::map<std::string, char> operators = {{"+", 1}, {"-", 1}, {"^", 3},
                                               {"*", 2}, {"/", 2}, {".", 0}};
const std::vector<std::pair<int, long double (*)(long double)>> v_func_ = {
    {Sin, std::sin},   {Cos, std::cos},   {Tan, std::tan},
    {Asin, std::asin}, {Acos, std::acos}, {Atan, std::atan},
    {Sqrt, std::sqrt}, {Ln, std::log},    {Log, std::log10}};
const std::vector<
    std::pair<int, std::function<long double(long double, long double)>>>
    v_lxm = {{'+', std::plus<long double>()},
             {'-', std::minus<long double>()},
             {'*', std::multiplies<long double>()},
             {'/', std::divides<long double>()}};
}  // namespace s21

#endif  // SRC_POLISH_H_