#include "lexer.h"
#include <cctype>

Lexer::Lexer(std::string_view input) : input_(input) {}

char Lexer::peek() const {
  if (pos_ >= input_.size()) return '\0';
  return input_[pos_];
}

char Lexer::get() {
  if (pos_ >= input_.size()) return '\0';
  return input_[pos_++];
}

void Lexer::skipWhitespace() {
  while (std::isspace(peek())) get();
}

Token Lexer::next() {
  skipWhitespace();

  char c = peek();
  if (c == '\0')
    return { TokenKind::Eof, "" };

  if (std::isalpha(c)) {
    size_t start = pos_;
    while (std::isalnum(peek())) get();
    auto lexeme = input_.substr(start, pos_ - start);

    if (lexeme == "let")
      return { TokenKind::KeywordLet, lexeme };

    return { TokenKind::Identifier, lexeme };
  }

  if (std::isdigit(c)) {
    size_t start = pos_;
    while (std::isdigit(peek())) get();
    return { TokenKind::Number, input_.substr(start, pos_ - start) };
  }

  get();

  switch (c) {
    case '=': return { TokenKind::Equal, "=" };
    case ';': return { TokenKind::Semicolon, ";" };
    default:  return { TokenKind::Unknown, std::string_view(&c, 1) };
  }
}

