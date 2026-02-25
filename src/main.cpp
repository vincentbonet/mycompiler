#include <fstream> 
#include <iostream> 
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "lexer.h"
#include "parser.h"
#include "ast_printer.h" 
 

// read entire file into string, return empty string and throw error if it failees

static std::string read_file(const std::string& path) {
  std::ifstream in(path);
  if (!in) {
    std::cerr << "Error: could not open file: " << path << "\n";
    return {};
  }
    std::stringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}

//convert txt to vector of tokens
static std::vector<Token> tokenize(std::string_view input) {
  Lexer lex(input); 
  std::vector<Token> out; 

  while(true) {
    Token t = lex.next(); 
    out.push_back(t); 

    if (t.kind == TokenKind :: Eof) break; 
  }

  return out; 
}

int main(int argc, char** argv) {
  std::string source;

  if (argc >= 2) {
    source = read_file(argv[1]); //file provided -> read file 
    if (source.empty()){
      return 1;
    }
  } else { //use default
    source = "let x = 123";
  }

  try{
    auto tokens = tokenize(source); 

    std::cout << "== TOKENS ==\n";

    for(const auto& t: tokens) {
      std::cout << token_kind_to_string(t.kind)
                << "  '" << t.lexeme << "'"
                << "  @ " << t.pos << "\n";
    }

    Parser parser(std::move(tokens));
    auto stmt = parser.parse_stmt();

    std::cout << "\n== AST ==\n";
      dump_ast(stmt.get());
  
  } catch (const std::exception& e) { // Catch parser errors
    std::cerr << e.what() << "\n";
      return 1;
  }

  return 0;
}

