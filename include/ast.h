#pragma once 

#include <memory> // For smart pointers (memory management) 
#include <string>

struct Node {
  virtual ~Node() = default;
};

struct Expr : Node {}; //represents anything with a value 
  
struct NumberExpr : Expr { //Num Expression (ex: 123)
  std::string value; 
  NumberExpr(std::string val) : value(std::move(val)) {}
};

struct IdentifierExpr : Expr { // Identifier Expression (ex: x)
  std::string name;

  IdentifierExpr(std::string n) : name(std::move(n)) {}
};

struct BinaryExpr : Expr { // for Binary Expressions
  std::string op;
  std::unique_ptr<Expr> left; 
  std::unique_ptr<Expr> right;

  BinaryExpr(std::string oper, 
             std::unique_ptr<Expr> lhs,
             std::unique_ptr<Expr> rhs)
        : op(std::move(oper)),
          left(std::move(lhs)),
          right(std::move(rhs)) {}
};

struct Stmt : Node {};

struct DeclarationStmt : Stmt { // entire statement
  std::string name;
  std::unique_ptr<Expr> value;

  DeclarationStmt(std::string n, std::unique_ptr<Expr> val)
      : name(std::move(n)), 
        value(std::move(val)) {}
};
