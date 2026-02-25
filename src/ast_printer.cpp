#include "ast_printer.h"

#include <iostream>
#include <typeinfo> 

void dump_ast(const Stmt* stmt) {
  if (auto decl = dynamic_cast<const DeclarationStmt*>(stmt)){ 
    std::cout << "DeclarationStmt(name=\"" << decl->name << "\", value=";


    if(auto num = dynamic_cast<const NumberExpr*>(decl->value.get())) {
      std::cout << "NumberExpr(\"" << num->value << "\")";
    } else if (auto id = dynamic_cast<const IdentifierExpr*>(decl->value.get())) {
      std::cout << "IdentifierExpr(\"" << id->name << "\")";
    } else {
      std::cout << "<?>";
    }

    std::cout << ")\n";
    return;
  }
} 
