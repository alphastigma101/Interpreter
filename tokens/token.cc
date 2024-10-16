#include <token.h>


/* ---------------------------------------------------------------------------
 * @brief Default constructor is using list-initializing 
 * ---------------------------------------------------------------------------
*/
Token::Token(const TokenType type_, const String lexeme_, const String literal_, const int line_): line(line_) {
    try {
        type = type_;
        lexeme = std::move(lexeme_);
        literal = std::move(literal_);
    }
    catch(...) {
        throw new catcher<Token>("Undefined Behavior!");
    }
}

/** ---------------------------------------------------------------------------
 * @brief A getter method that gets the TokenType object
 * @return TokenType type-id
 * ---------------------------------------------------------------------------
*/
TokenType Token::getType() { return type; }

/** --------------------------------------------------------------------------
 * @brief A getter method to get the lexeme object
 * @return string type-id
 * --------------------------------------------------------------------------
*/ 
String Token::getLexeme() { return lexeme; }
/**  --------------------------------------------------------------------------
 * @brief A getter method to get the literal object
 * @return string type-id 
 * --------------------------------------------------------------------------
*/
String Token::getLiteral() { return literal; }
/** --------------------------------------------------------------------------
 * @brief A getter method to get the literal object
 * @return integer type-id 
 * --------------------------------------------------------------------------
*/
int Token::getLine() { return line; }
/** ---------------------------------------------------------------------------
 * @brief get the token type in string representation form
 * @return string
 * --------------------------------------------------------------------------
*/
String Token::getTypeStr() { return tokenTypeToString(); }

