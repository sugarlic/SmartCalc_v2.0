#include "Model.h"

// ------public------

double s21::Model::GetExprRes() const { return result_; }

s21::error_type s21::Model::GetErCode() const { return error_code_; }

void s21::Model::SetXValue(double x_val) { x_val_ = x_val; }

void s21::Model::Insert(const std::string &str) {
  IsFunction(str);
  IsOperator(str);
  IsDigit(str);
  IsX(str);
  IsExp(str);

  if (error_code_ == s21::OK) str_ += str;
}

void s21::Model::Polish() {
  if (error_code_ != s21::OK) return;
  if (!CheckBrackets()) {
    error_code_ = s21::error_type::BRACKETS_ERROR;
    return;
  }
  if (!Parser())
    error_code_ = NUMBER_ERROR;
  else if (!NotationCalc())
    error_code_ = CALCULATION_ERROR;
  else
    result_ = stack_out_.size() == 0 ? 0 : stack_out_.top().value;
}

void s21::Model::CheckRange(const s21::GraphParametors &parametors) {
  double x_begin = std::atof(parametors.x_begin.c_str());
  double x_end = std::atof(parametors.x_end.c_str());
  double y_begin = std::atof(parametors.y_begin.c_str());
  double y_end = std::atof(parametors.y_end.c_str());
  if ((x_begin >= x_end) || (y_begin >= y_end) || result_ < y_begin ||
      result_ > y_end) {
    error_code_ = DIAPOSON_ERROR;
  }
}

void s21::Model::Clear() {
  while (!stack_out_.empty()) {
    stack_out_.pop();
  }
  vector_.clear();
  str_.clear();
  error_code_ = s21::OK;
}

// ------private------

void s21::Model::IsFunction(const std::string &str) {
  if (str != "mod" && math_func.find(str) != math_func.end()) {
    if (std::isdigit(str_.back()) || str_.back() == ')' || str_.back() == 'X') {
      error_code_ = s21::FUNCTION_ERROR;
    }
  }
}

void s21::Model::IsOperator(const std::string &str) {
  if (str != "+" && str != "-" &&
      (operators.find(str) != operators.end() || str == "^(")) {
    if (!std::isdigit(str_.back()) && str_.back() != ')' &&
        str_.back() != 'E' && str_.back() != 'X') {
      error_code_ = s21::OPERATOR_ERROR;
    }
  } else if (str == "+" || str == "-") {
    if (str_.back() == '+' || str_.back() == '-' || str_.back() == '/' ||
        str_.back() == '*' || str_.back() == 'd') {
      error_code_ = s21::OPERATOR_ERROR;
    }
  }
}

void s21::Model::IsDigit(const std::string &str) {
  if (std::isdigit(str.back()) && (str_.back() == ')' || str_.back() == 'X')) {
    error_code_ = s21::NUMBER_ERROR;
  }
}

void s21::Model::IsX(const std::string &str) {
  if (str == "X") {
    if (std::isdigit(str_.back()) || str_.back() == ')' || str_.back() == 'X') {
      error_code_ = s21::NUMBER_ERROR;
    }
  }
}

void s21::Model::IsExp(const std::string &str) {
  if (str == "E" && !std::isdigit(str_.back()) && str_.back() != 'X') {
    error_code_ = s21::NUMBER_ERROR;
  }
}

bool s21::Model::CheckBrackets() const {
  if (str_.find('(') == std::string::npos &&
      str_.find(')') == std::string::npos)
    return true;
  bool result{true};
  std::stack<char> stack{};
  for (size_t i = 0; i < str_.size(); ++i) {
    if (str_[i] == '(') stack.push(1);
    if (str_[i] == ')' && stack.size() == 0) result = false;
    if (str_[i] == ')' && stack.size() > 0) stack.pop();
  }
  return result && stack.empty();
}

bool s21::Model::Parser() {
  bool res = true;
  s21::Parser p(str_, x_val_);
  if (!p.ParserIt()) res = false;
  stack_out_ = p.GetStack();
  return res;
}

bool s21::Model::NotationCalc() {
  bool res = true;
  while (stack_out_.size() > 1) {
    while (stack_out_.size() > 1 && stack_out_.top().value_type == Num) {
      vector_.push_back(stack_out_.top());
      stack_out_.pop();
    };
    vector_.push_back(stack_out_.top());
    stack_out_.pop();
    if (!(res = FuncCalc())) break;
    LexemCalc();
  }
  if (stack_out_.empty() || stack_out_.top().value_type != Num) res = false;
  return res;
}

bool s21::Model::FuncCalc() {
  if (vector_.size() == 1) return false;
  if (vector_.empty() || vector_.size() < 2) return true;
  size_t pos{vector_.size() - 2};
  if (vector_.back().value_type == UnPlus) {
    stack_out_.push({Num, 0, vector_[pos].value});
    EraseVectorL();
  } else if (vector_.back().value_type == UnMinus) {
    stack_out_.push({Num, 0, -vector_[pos].value});
    EraseVectorL();
  } else {
    for (auto it = v_func_.begin(); it != v_func_.end(); ++it) {
      if (vector_.back().value_type == (*it).first) {
        stack_out_.push({Num, 0, (*it).second(vector_[pos].value)});
        EraseVectorL();
        break;
      }
    }
  }
  return true;
}

void s21::Model::LexemCalc() {
  if (vector_.empty() || vector_.size() < 3) return;
  size_t first_pos{vector_.size() - 3};
  size_t second_pos{vector_.size() - 2};
  if (vector_.back().value_type == Mod) {
    stack_out_.push(
        {Num, 0, fmodl(vector_[first_pos].value, vector_[second_pos].value)});
    EraseVectorF();
  } else if (vector_.back().value_type == '^') {
    stack_out_.push(
        {Num, 0, pow(vector_[first_pos].value, vector_[second_pos].value)});
    EraseVectorF();
  } else {
    for (auto it = v_lxm.begin(); it != v_lxm.end(); ++it) {
      if (vector_.back().value_type == (*it).first) {
        stack_out_.push({Num, 0,
                         (*it).second(vector_[first_pos].value,
                                      vector_[second_pos].value)});
        EraseVectorF();
        break;
      }
    }
  }
}

void s21::Model::EraseVectorF() {
  vector_.erase(--vector_.end());
  vector_.erase(--vector_.end());
  vector_.erase(--vector_.end());
}

void s21::Model::EraseVectorL() {
  vector_.erase(--vector_.end());
  vector_.erase(--vector_.end());
}
