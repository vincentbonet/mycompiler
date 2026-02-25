pragma once
#include <string_view>
#include "token.h"

class Lexer {
public:
  explicit Lexer(std::string_view input);
  Token next();

private:
  char peek() const;
  char get();
  void skipWhitespace();

private:
  std::string_view input_;
  size_t pos_ = 0;
};

