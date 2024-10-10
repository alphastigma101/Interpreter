#pragma once
#ifndef _TOKEN_TYPES_H_
#define _TOKEN_TYPES_H_

/** ---------------------------------------------------------------------------
 * @brief The underlying are representations of literals
 *
 * ---------------------------------------------------------------------------
*/
enum TokenType {
    // Basic Syntax
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE,
    RIGHT_BRACE, COMMA, DOT, MINUS,
    PLUS, SEMICOLON, SLASH, STAR,
    BANG, BANG_EQUAL, EQUAL,
    EQUAL_EQUAL, GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL, IDENTIFIER, STRING,
    NUMBER, EQUALS,
    // KeyWords
    FALSE, TRUE, THIS, SUPER, RETURN, VAR,
    STATIC, FINAL, CATCH, CONST, TRY, EXCEPT,
    // Primitive Types
    FALSE, INT, FLOAT, CHAR, VOID, BOOL, NIL,
    // Complex Types
    AUTO, LIST, QUERY, MAP, POINTER, REF,
    // Control flow
    ELSE, IF,
    // Loops
    FOR, WHILE,
    // Logical operators
    OR, AND, DEATH, NOT, PRINT,
    // classes
    RADIATION, PUBLIC,
    PRIVATE, PROTECTED,
    // structs
    NUKE, // these are structs 
    POSION, // these are used for function declarations
    LAMBDA,
    MUSHROOMCLOUD, // the ecosystem mechanic
    ARROW,
    BRACES,
    PARENS,
    END_OF_FILE,
    MODULO
};
/** ------------------------------------------------------
 * @brief A map that maps enums to strings
 *
 * @details Add more tokens to the list below, if you add any to the tokenType enum class 
 * -------------------------------------------------------
*/
static const Unordered<TokenType, String> tokenTypeStrings = {
    {TokenType::LEFT_PAREN, "LEFT_PAREN"},
    {TokenType::RIGHT_PAREN, "RIGHT_PAREN"},
    {TokenType::LEFT_BRACE, "LEFT_BRACE"},
    {TokenType::RIGHT_BRACE, "RIGHT_BRACE"},
    {TokenType::COMMA, "COMMA"},
    {TokenType::DOT, "DOT"},
    {TokenType::MINUS, "MINUS"},
    {TokenType::PLUS, "PLUS"},
    {TokenType::SEMICOLON, "SEMICOLON"},
    {TokenType::SLASH, "SLASH"},
    {TokenType::STAR, "STAR"},
    {TokenType::BANG, "BANG"},
    {TokenType::BANG_EQUAL, "BANG_EQUAL"},
    {TokenType::EQUAL, "EQUAL"},
    {TokenType::EQUAL_EQUAL, "EQUAL_EQUAL"},
    {TokenType::GREATER, "GREATER"},
    {TokenType::GREATER_EQUAL, "GREATER_EQUAL"},
    {TokenType::LESS, "LESS"},
    {TokenType::LESS_EQUAL, "LESS_EQUAL"},
    {TokenType::IDENTIFIER, "IDENTIFIER"},
    {TokenType::STRING, "STRING"},
    {TokenType::NUMBER, "NUMBER"},
    {TokenType::INT, "INT"},
    {TokenType::FLOAT, "FLOAT"},
    {TokenType::CHAR, "CHAR"},
    {TokenType::VOID, "VOID"},
    {TokenType::AUTO, "AUTO"},
    {TokenType::BOOL, "BOOL"},
    {TokenType::AND, "AND"},
    {TokenType::RADIATION, "RADIATION"}, // these are classes
    {TokenType::ELSE, "ELSE"},
    {TokenType::FALSE, "FALSE"},
    {TokenType::FOR, "FOR"},
    {TokenType::IF, "IF"},
    {TokenType::NIL, "NIL"},
    {TokenType::OR, "OR"},
    {TokenType::PRINT, "PRINT"},
    {TokenType::RETURN, "RETURN"},
    {TokenType::SUPER, "SUPER"},
    {TokenType::THIS, "THIS"},
    {TokenType::TRUE, "TRUE"},
    {TokenType::VAR, "VAR"},
    {TokenType::WHILE, "WHILE"},
    {TokenType::PUBLIC, "PUBLIC"},
    {TokenType::PRIVATE, "PRIVATE"},
    {TokenType::PROTECTED, "PROTECTED"},
    {TokenType::STATIC, "STATIC"},
    {TokenType::FINAL, "FINAL"},
    {TokenType::CATCH, "CATCH"},
    {TokenType::NUKE, "NUKE"}, // these are structs 
    {TokenType::TRY, "TRY"},
    {TokenType::EXCEPT, "EXCEPT"},
    {TokenType::CONST, "CONST"},
    {TokenType::POSION, "POSION"}, // these are used for function declarations
    {TokenType::LAMBDA, "LAMBDA"},
    {TokenType::MUSHROOMCLOUD, "MUSHROOMCLOUD"}, // the ecosystem mechanic
    {TokenType::ARROW, "ARROW"},
    {TokenType::EQUALS, "EQUALS"},
    {TokenType::QUERY, "QUERY"},
    {TokenType::LIST, "LIST"},
    {TokenType::BRACES, "BRACES"},
    {TokenType::PARENS, "PARENS"},
    {TokenType::END_OF_FILE, "EOF"},
    {TokenType::MODULO, "MODULO"}
};
#endif
