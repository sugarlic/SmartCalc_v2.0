#include "Parser.h"

s21::Parser::Parser(const std::string &str, double x_val)
    : str_{str}, x_val_{x_val} {}

std::stack<s21::Elem> s21::Parser::GetStack() const { return stack_out_; }

void s21::Parser::StackReverse(std::stack<Elem> &stack) {
  std::queue<Elem> help_queue;
  while (stack.size() > 0) {
    help_queue.push(stack.top());
    stack.pop();
  }
  while (!help_queue.empty()) {
    stack.push(help_queue.front());
    help_queue.pop();
  }
}

bool s21::Parser::ParserIt() {
  bool res_of_pars = true;
  for (auto it = str_.begin(); it < str_.end(); ++it) {
    if (!(res_of_pars = PushValueIt(it))) break;
    PushFuncIt(it);
    PushOperatorIt(it);
    if (*it == '(') stack_in_.push({'(', 0, 0});
    if (*it == ')') stack_in_.push({')', 0, 0});
  }
  StackReverse(stack_in_);
  if (res_of_pars) ReversePolishNotation();
  return res_of_pars;
}

bool s21::Parser::PushValueIt(std::string::iterator &it) {
  bool res = true;
  std::string help_str{};
  int e_res{};
  if (*it == 'x' || *it == 'X') {
    res = PushExpIt(++it, e_res);
    stack_in_.push({Num, 0, x_val_ * pow(10, e_res)});
  } else if (*it >= '0' && *it <= '9') {
    while ((*it >= '0' && *it <= '9') || *it == '.') {
      help_str.push_back(*it++);
    }
    if (std::count(help_str.begin(), help_str.end(), '.') > 1) res = false;
    if (res) res = PushExpIt(it, e_res);
    stack_in_.push({Num, 0, std::stod(help_str) * pow(10, e_res)});
  }
  return res;
}

bool s21::Parser::PushExpIt(std::string::iterator &it, int &e_res) {
  bool result = true;
  std::string e_str{};
  char sign{};
  if (*it == 'e' || *it == 'E') {
    sign = *(++it);
    if (!CheckSignInExp(sign))
      result = false;
    else {
      ++it;
      while ((*it >= '0' && *it <= '9')) e_str.push_back(*it++);
      try {
        sign == '+' ? e_res = std::stoi(e_str) : e_res = -std::stoi(e_str);
      } catch (...) {
        result = false;
      }
    }
  }
  return result;
}

void s21::Parser::PushFuncIt(std::string::iterator &it) {
  for (auto iter = math_func.begin(); iter != math_func.end(); ++iter) {
    if ((*iter).first[0] == *it && (*iter).first[1] == *(it + 1)) {
      if (*it != 'm')
        stack_in_.push({(*iter).second, 4, 0});
      else
        stack_in_.push({(*iter).second, 2, 0});
      for (size_t i = 0; i < (*iter).first.size() - 1; ++i, ++it)
        ;
    }
  }
}

void s21::Parser::PushOperatorIt(std::string::iterator &it) {
  if (*it == '+' && (it == str_.begin() || *(it - 1) == '(')) {
    stack_in_.push({UnPlus, 1, 0});
  } else if (*it == '-' && (it == str_.begin() || *(it - 1) == '(')) {
    stack_in_.push({UnMinus, 1, 0});
  } else {
    for (auto iter = operators.begin(); iter != operators.end(); ++iter) {
      if ((*iter).first[0] == *it)
        stack_in_.push({(*iter).first[0], (*iter).second, 0});
    }
  }
}

bool s21::Parser::CheckSignInExp(char sign) {
  return sign == '+' || sign == '-';
}

void s21::Parser::ReversePolishNotation() {
  std::stack<Elem> help_stack;
  while (!stack_in_.empty()) {
    PushValuePolish();
    PushFuncPolish(help_stack);
    PushOperatorPolish(help_stack);
    ClBraceProcessPolish(help_stack);
  }
  StackUnloadPolish(help_stack);
  StackReverse(stack_out_);
}

void s21::Parser::PushValuePolish() {
  if (stack_in_.top().value_type == Num || stack_in_.top().value_type == x) {
    stack_out_.push({Num, 0, stack_in_.top().value});
    stack_in_.pop();
  }
}

void s21::Parser::PushFuncPolish(std::stack<Elem> &help_stack) {
  if (stack_in_.empty()) return;
  if ((stack_in_.top().value_type >= Sin &&
       stack_in_.top().value_type <= Log) ||
      stack_in_.top().value_type == '(') {
    help_stack.push({stack_in_.top().value_type, stack_in_.top().priority,
                     stack_in_.top().value});
    stack_in_.pop();
  }
}

void s21::Parser::PushOperatorPolish(std::stack<Elem> &help_stack) {
  if (stack_in_.empty()) return;
  if (stack_in_.top().value_type >= 42 || stack_in_.top().value_type == Mod ||
      stack_in_.top().value_type == UnMinus ||
      stack_in_.top().value_type == UnPlus) {
    while (!help_stack.empty() &&
           help_stack.top().priority >= stack_in_.top().priority &&
           help_stack.top().value_type != '(') {
      stack_out_.push({help_stack.top().value_type, help_stack.top().priority,
                       help_stack.top().value});
      help_stack.pop();
    }
    help_stack.push({stack_in_.top().value_type, stack_in_.top().priority,
                     stack_in_.top().value});
    stack_in_.pop();
  }
}

void s21::Parser::StackUnloadPolish(std::stack<Elem> &help_stack) {
  while (!help_stack.empty()) {
    stack_out_.push({help_stack.top().value_type, help_stack.top().priority,
                     help_stack.top().value});
    help_stack.pop();
  }
}

void s21::Parser::ClBraceProcessPolish(std::stack<Elem> &help_stack) {
  if (stack_in_.empty() || help_stack.empty()) return;
  if (stack_in_.top().value_type == ')') {
    while (help_stack.top().value_type != '(') {
      stack_out_.push({help_stack.top().value_type, help_stack.top().priority,
                       help_stack.top().value});
      help_stack.pop();
    }
    help_stack.pop();
    stack_in_.pop();
  }
}