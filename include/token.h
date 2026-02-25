#pragma once
#include <string_view>

enum class TokenKind {
  Identifier,
  Number,
  KeywordLet,
  Equal,
  Semicolon,
  Eof,
  Unknown
};

struct Token {
  TokenKind kind;
  std::string_view lexeme;
}
