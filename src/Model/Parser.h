#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_

#include "Polish.h"

namespace s21 {
class Parser {
 public:
  Parser(){};
  Parser(const std::string &str, double x_val);
  ~Parser(){};

  bool ParserIt();

  std::stack<s21::Elem> GetStack() const;

 private:
  void StackReverse(std::stack<Elem> &stack);

  bool CheckSignInExp(char sign);
  bool PushValueIt(std::string::iterator &it);
  bool PushExpIt(std::string::iterator &it, int &e_res);
  void PushFuncIt(std::string::iterator &it);
  void PushOperatorIt(std::string::iterator &it);

  void ReversePolishNotation();
  void PushValuePolish();
  void PushFuncPolish(std::stack<Elem> &help_stack);
  void PushOperatorPolish(std::stack<Elem> &help_stack);
  void StackUnloadPolish(std::stack<Elem> &help_stack);
  void ClBraceProcessPolish(std::stack<Elem> &help_stack);
  std::string str_;
  std::stack<s21::Elem> stack_in_{};
  std::stack<Elem> stack_out_{};
  double x_val_;
};
}  // namespace s21

#endif  // SRC_PARSER_H_