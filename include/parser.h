#pragma once

#include <cstddef>
#include <memory>
#include <vector>

#include "ast.h"
#include "token.h"

class Parser {
public:
  explicit Parser(std::vector<Token> tokens);

  std::unique_ptr<Stmt> parse_stmt();

private:
  const Token& peek() const;
  const Token& get();

  void expect(TokenKind kind, const char* message);

  std::unique_ptr<Stmt> parse_declaration();
  std::unique_ptr<Expr> parse_primary();

private:
  std::vector<Token> tokens_;
  std::size_t pos_ = 0;
};
