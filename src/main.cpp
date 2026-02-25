#include <iostream>
#include <string>
#include "lexer.h" 

int main() {
  std::cout << "compiler starting... \n" 

  std::string input = "let x = 123;";
  Lexer lexer(input);

  while(true) {
     Token tok = lexer.next();
     std::cout << tok.lexeme << "\n";

     if(tok.kind == TokenKind::Eof)
       break;
  }

    return 0;
}
