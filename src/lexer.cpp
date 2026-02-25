#include "lexer.h"
#include <cctype>

Lexer::Lexer(std::string_view input) : input_(input) {}

char Lexer::peek() const {
  if (i_ >= input_.size()) return '\0';
  return input_[i_];
}

char Lexer::get() {
  if (i_ >= input_.size()) return '\0';
  return input_[i_++];
}

void Lexer::skip_ws() {
  while (std::isspace(static_cast<unsigned char>(peek()))) {
    get();
  }
}

Token Lexer::make(TokenKind kind, std::size_t start, std::size_t end) {
  return Token{ kind, input_.substr(start, end - start), start };
}

Token Lexer::identifier_or_keyword() {
  std::size_t start = i_;

  while (std::isalnum(static_cast<unsigned char>(peek())) || peek() == '_') {
    get();
  }

  auto lex = input_.substr(start, i_ - start);

  if (lex == "let") return Token{ TokenKind::KeywordLet, lex, start };
  return Token{ TokenKind::Identifier, lex, start };
}

Token Lexer::number() {
  std::size_t start = i_;

  while (std::isdigit(static_cast<unsigned char>(peek()))) {
    get();
  }

  return make(TokenKind::Number, start, i_);
}

Token Lexer::next() {
  skip_ws();

  std::size_t start = i_;
  char c = peek();

  if (c == '\0') return Token{ TokenKind::Eof, "", i_ };

  if (std::isalpha(static_cast<unsigned char>(c)) || c == '_') {
    return identifier_or_keyword();
  }

  if (std::isdigit(static_cast<unsigned char>(c))) {
    return number();
  }

  get();
  switch (c) {
    case '=': return make(TokenKind::Equal, start, i_);
    case ';': return make(TokenKind::Semicolon, start, i_);
    default:  return make(TokenKind::Unknown, start, i_);
  }
}

const char* token_kind_to_string(TokenKind k) {
  switch (k) {
    case TokenKind::Identifier: return "Identifier";
    case TokenKind::Number: return "Number";
    case TokenKind::KeywordLet: return "KeywordLet";
    case TokenKind::Equal: return "Equal";
    case TokenKind::Semicolon: return "Semicolon";
    case TokenKind::Eof: return "Eof";
    default: return "Unknown";
  }
}
