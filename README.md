# mycompiler

## Goal
A tiny language to practice compiler stages: lexing → parsing → AST. (for now)

## Source file
Plain text (UTF-8). For now, input is a single line string in `main.cpp`.

## Tokens
The lexer recognizes these token kinds:

- `KeywordLet`  : the exact text `let`
- `Identifier`  : `[A-Za-z_][A-Za-z0-9_]*`
- `Number`      : `[0-9]+` (integers only)
- `Equal`       : `=`
- `Semicolon`   : `;`
- `Eof`         : end of input
- `Unknown`     : anything else (temporary; later becomes a lexer error)

Whitespace (spaces/tabs/newlines) is ignored between tokens.
