#pragma once
#include <string_view>

enum class TokenKind {
  Identifier,
  Number,
  KeywordLet,
  Equal,
  Semicolon,
  Plus,
  Minus,
  Star,
  Slash
  Eof,
  Unknown
};

struct Token {
  TokenKind kind;
  std::string_view lexeme;
  std::size_t pos;
};
