#pragma once

#include <cstddef>
#include <string_view>
#include "token.h"

class Lexer {
public:
  explicit Lexer(std::string_view input);

  Token next();

private:
  char peek() const;
  char get();
  void skip_ws();

  Token make(TokenKind kind, std::size_t start, std::size_t end);
  Token identifier_or_keyword();
  Token number();

private:
  std::string_view input_;
  std::size_t i_ = 0;
};

const char* token_kind_to_string(TokenKind k);
