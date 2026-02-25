#include "parser.h"
#include <stdexcept>
#include <string>

Parser::Parser(std::vector<Token> tokens)
  : tokens_(std::move(tokens)) {}

const Token& Parser::peek() const {
  if (pos_ >= tokens_.size()) return tokens_.back();
  return tokens_[pos_];
}

const Token& Parser::get() {
  const Token& t = peek();
  if (pos_ < tokens_.size()) pos_++;
  return t;
}

void Parser::expect(TokenKind kind, const char* message) {
  if (peek().kind != kind){
    //Include token position to better ID errors
  throw std::runtime_error(
      std::string("Parse error at pos ") + std::to_string(peek().pos) + ": " + message
      );
  }
  get();
}

std::unique_ptr<Stmt> Parser::parse_stmt() {
  if (peek().kind == TokenKind::KeywordLet) {
    return parse_declaration();
  }
  throw std::runtime_error("Expected a statement starting with 'let'");
}

std::unique_ptr<Stmt> Parser::parse_declaration() {
  expect(TokenKind::KeywordLet, "Expected 'let'");

  const Token& nameTok = peek();
  expect(TokenKind::Identifier, "Expected identifier after 'let'");

  expect(TokenKind::Equal, "Expected '=' after identifier");

  auto valueExpr = parse_primary();

  expect(TokenKind::Semicolon, "Expected ';' after expression");

  return std::make_unique<DeclarationStmt>(
    std::string(nameTok.lexeme),
    std::move(valueExpr)
  );
}

std::unique_ptr<Expr> Parser::parse_primary() {
  const Token& t = peek();

  if (t.kind == TokenKind::Number) {
    get();
    return std::make_unique<NumberExpr>(std::string(t.lexeme));
  }

  if (t.kind == TokenKind::Identifier) {
    get();
    return std::make_unique<IdentifierExpr>(std::string(t.lexeme));
  }

  throw std::runtime_error("Expected a number or identifier");
}
