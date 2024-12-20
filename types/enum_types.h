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
    NUMBER, EQUALS, THIS,
    // KeyWords
    FALSE, TRUE, RETURN, BREAK,
    STATIC, CATCH, THROW, CONST, TRY, EXCEPT,
    SIGNED, UNSIGNED,
    // Primitive Types
    INT, DOUBLE, CHAR, VOID, BOOL, NIL, 
    CHAR32, CHAR16, 
    // Complex Types
    AUTO, LIST, QUERY, MAP, POINTER, REF,
    // Control flow
    ELSE, IF, ELSEIF,
    // Loops
    FOR, WHILE,
    // Logical operators
    OR, AND, NOT, 
    // built in methods
    // Radiate is for printing
    RADIATE, 
    // built-in operations 
    // concating/splitting operations
    // querying: RADIATION
    FUSION, FISSION, RADIATION,
    // classes
    CONTAINMENT, PUBLIC,
    PRIVATE, PROTECTED,
    // hidden functions
    LAMBDA,
    MUSHROOMCLOUD, // the ecosystem mechanic
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
    {TokenType::DOUBLE, "DOUBLE"},
    {TokenType::VOID, "VOID"},
    {TokenType::BOOL, "BOOL"},
    {TokenType::CHAR16, "CHAR16"},
    {TokenType::CHAR32, "CHAR32"},
    {TokenType::AND, "AND"},
    {TokenType::CONTAINMENT, "CONTAINMENT"}, // these are classes
    {TokenType::THIS, "THIS"}, 
    {TokenType::ELSE, "ELSE"},
    {TokenType::ELSEIF, "ELSEIF"},
    {TokenType::FALSE, "FALSE"},
    {TokenType::FOR, "FOR"},
    {TokenType::BREAK, "BREAK"},
    {TokenType::IF, "IF"},
    {TokenType::NIL, "NIL"},
    {TokenType::OR, "OR"},
    {TokenType::RADIATE, "RADIATE"}, // printing
    {TokenType::FUSION, "FUSION"}, // concating
    {TokenType::FISSION, "FISSION"}, // spliting
    {TokenType::RADIATION, "RADIATION"}, // querying such as making a database or modifying it
    {TokenType::RETURN, "RETURN"},
    {TokenType::TRUE, "TRUE"},
    {TokenType::FALSE, "FALSE"},
    {TokenType::WHILE, "WHILE"},
    {TokenType::PUBLIC, "PUBLIC"},
    {TokenType::PRIVATE, "PRIVATE"},
    {TokenType::PROTECTED, "PROTECTED"},
    {TokenType::STATIC, "STATIC"},
    {TokenType::SIGNED, "SIGNED"},
    {TokenType::UNSIGNED, "UNSIGNED"},
    {TokenType::CATCH, "CATCH"},
    {TokenType::THROW, "THROW"},
    {TokenType::TRY, "TRY"},
    {TokenType::EXCEPT, "EXCEPT"},
    {TokenType::CONST, "CONST"},
    {TokenType::CHAR, "CHAR"}, // these are used for function declarations
    {TokenType::LAMBDA, "LAMBDA"},
    {TokenType::MUSHROOMCLOUD, "MUSHROOMCLOUD"}, // the ecosystem mechanic
    {TokenType::LAMBDA, "LAMBDA"},
    {TokenType::EQUALS, "EQUALS"},
    {TokenType::LIST, "LIST"},
    {TokenType::BRACES, "BRACES"},
    {TokenType::PARENS, "PARENS"},
    {TokenType::END_OF_FILE, "EOF"},
    {TokenType::MODULO, "MODULO"}
};
#endif
