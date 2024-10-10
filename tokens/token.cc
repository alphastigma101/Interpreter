#include <token.h>


/* ---------------------------------------------------------------------------
 * @brief Default constructor is using list-initializing 
 * ---------------------------------------------------------------------------
*/
Token::Token(const TokenType type_, const std::string lexeme_, const std::string literal_, const int line_): line(line_) {
    try {
        type = type_;
        lexeme = std::move(lexeme_);
        literal = std::move(literal_);
    }
    catch(...) {
        catcher<Token> cT("Undefined Behavior!");
        throw cT;
    }
}

/* ---------------------------------------------------------------------------
 * @brief A getter method that gets the TokenType object
 * @return TokenType type-id
 * ---------------------------------------------------------------------------
*/
TokenType Token::getType() { return type; }

/* --------------------------------------------------------------------------
 * @brief A getter method to get the lexeme object
 * @return string type-id
 * --------------------------------------------------------------------------
*/ 
std::string Token::getLexeme() { return lexeme; }
/* --------------------------------------------------------------------------
 * @brief A getter method to get the literal object
 * @return string type-id 
 * --------------------------------------------------------------------------
*/
std::string Token::getLiteral() { return literal; }
/* --------------------------------------------------------------------------
 * @brief A getter method to get the literal object
 * @return integer type-id 
 * --------------------------------------------------------------------------
*/
int Token::getLine() { return line; }
/*---------------------------------------------------------------------------
 * @brief get the token type in string representation form
 * @return string
 * --------------------------------------------------------------------------
*/
std::string Token::getTypeStr() { return tokenTypeToString(); }

