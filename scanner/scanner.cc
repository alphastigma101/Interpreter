#include <scanner.h>

/* ---------------------------------------------------------------------------------------------
 * This is the default constructor which can be used to create an instance of the Scanner Class
 * Params:
    *  std::string source: the source line of code from a file or from the runprompt function
 * --------------------------------------------------------------------------------------------  
 */
Scanner::Scanner(const std::string source): source(std::move(source)) {}

/* ----------------------------------------------------------------------------------
 * (keywords) is a dictionary that holds in various keywords of programming languages 
 * Using unordered_map type because I want O(n) at run time
 * ----------------------------------------------------------------------------------
*/
const std::unordered_map<std::string, TokenType> Scanner::keywords = {
    // Add all the Keywrods here
    {"and",    TokenType::AND},
    {"radiation",  TokenType::RADIATION},
    {"else",   TokenType::ELSE},
    {"false",  TokenType::FALSE},
    {"for",    TokenType::FOR},
    {"posion",  TokenType::POSION},
    {"if",     TokenType::IF},
    {"nil",    TokenType::NIL},
    {"or",     TokenType::OR},
    {"print",  TokenType::PRINT},
    {"return", TokenType::RETURN},
    {"super",  TokenType::SUPER},
    {"this",   TokenType::THIS},
    {"true",   TokenType::TRUE},
    {"var",    TokenType::VAR},
    {"while",  TokenType::WHILE},
    {"protected", TokenType::PROTECTED},
    {"private", TokenType::PRIVATE},
    {"catch", TokenType::CATCH},
    {"final", TokenType::FINAL},
    {"var", TokenType::VAR},
    {"nuke", TokenType::NUKE},
    {"void", TokenType::VOID},
    {"bool", TokenType::BOOL},
    {"pointer", TokenType::POINTER},
    {"ref", TokenType::REF}
};

/* ------------------------------------------------------------------------------------------------------
 * (ScanTokens) is a method that is apart of the scanner class 
 * Instead of (scanToken) method, this method scans the whole file until it reaches the EOF, (End Of File)
 * Takes no paramaters and returns void
 * ------------------------------------------------------------------------------------------------------
 */
std::vector<Token> Scanner::ScanTokens() {
    while (!isAtEnd()) {
        // We are at the beginning of the next lexeme.
        start = current;
        scanToken();
    }
    tokens.push_back(Token(TokenType::END_OF_FILE, static_cast<const std::string>(std::string("EOF")), static_cast<const std::string>(std::string("EOF")), line));
    return tokens;

}
/** ---------------------------------------------------------------------------------------------------------
 * @brief Apart of the (Scanner) class, it scans the string literals from the given file and turns them into tokens
 * 
 * @param None
 * ---------------------------------(Additional Info)-------------------------------------------------------
 * The purpose of (scanToken) is to perform a lexical analysis by gathering up lexemes 
 * lexemes are only the raw substrings of the source code.
    * Couple examples of lexemes would be 'v' 'a' 'r' group them together to make something useful out of them 
    * Lexeme is known as a string and so is a token
    * Note: grouping these bits of characters into lexemes are called its (lexical grammar). 
 * @details Adjust the case expressions so that it can support a certain string literal. 
    You should not adjust the parser beforehand without ajusting the scanner first!
 * @details If you add another Token Type to TokenType, then you must update tokenTypeStrings
 * ------------------------------------------------------------------------------------------
*/
void Scanner::scanToken() {
    char c = advance();
    switch (c) {
        // Single-character tokens
        case '(': addToken(TokenType::LEFT_PAREN); break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '{': addToken(TokenType::LEFT_BRACE); break;
        case '}': addToken(TokenType::RIGHT_BRACE); break;
        case ',': addToken(TokenType::COMMA); break;
        case '.': addToken(TokenType::DOT); break;
        case '-': addToken(TokenType::MINUS); break;
        case '+': addToken(TokenType::PLUS); break;
        case ';': addToken(TokenType::SEMICOLON); break;
        case '*': addToken(TokenType::STAR); break;
        case '!': addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG); break;
        //TODO: Make the case below the = so it searches for := and = 
        case '=': addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL); break;
        case '<': addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS); break;
        case '>': addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER); break;
        case '/':
        case '%':
            if (match(c == '/' ? '/' : '%')) {
                // A comment goes until the end of the line (only for '//')
                while (peek() != '\n' && !isAtEnd()) advance();
            } else {
                addToken(c == '/' ? TokenType::SLASH : TokenType::MODULO);
            }
            break;
        case 'o':
            // Need to also add support for | and || 
            if (match('r')) { addToken(TokenType::OR); }
            break;
        case ' ':
        case '\r':
        case '\t':
            // Ignore whitespace.
            break;
        case '\n':
            line++;
            break;
        case '"': string_(); break;
        case '\'': string_(); break;
        default: 
            if (isDigit(c)) { number_();} 
            else if (isAlpha(c)) { identifier(); }
            else { 
                //throw runtimeerror<Scaner>(line, "Unexcepted character");
            }                
            break;
    }
}
/** ---------------------------------------------------------------------------
 * @brief Helper function that adds tokens to a container
 * @param type: represents enum literals
 * ---------------------------------------------------------------------------
*/
void Scanner::addToken(const TokenType type) { addToken(type, ""); }

/** ---------------------------------------------------------------------------
 * @brief A method that gets called by a data memeber function helper
 * @param type: Is a Lexical grammar
 * @param literal: A representation of a primitive instance type 
 * @return Nothing. This method only pushes to a vector. 
 * ---------------------------------------------------------------------------
*/
void Scanner::addToken(const TokenType type, const std::string literal) {
    std::string text = source.substr(start, current - start);
    tokens.push_back(Token(type, text, literal, line));
}

/** ---------------------------------------------------------------------------
 * @brief Searches for the keyword inside a string literal.
 * @param None
 * @return None. It uses a dictionary to see if the object type is inside the dictionary 
 *  If it is not in the dictionary, it will be converted into TokenType::IDENTIFIER
 *  --------------------------------------------------------------------------
*/
void Scanner::identifier() {
    while (isAlphaNumeric(peek())) advance();
    std::string text = source.substr(start, current - start);
    auto it = keywords.find(text);
    TokenType type;
    if (it != keywords.end()) {
        type = it->second;
    } else {
        type = TokenType::IDENTIFIER; // Default type if not found in keywords
    }
    addToken(type);
}
/** --------------------------------------------------------------------------
 * @brief It scans through the string literal and matches it with a enum type
 * @param expected: A character literal that is matched with an enum type
 * @return True if there is a match. Otherwise false
*/
bool Scanner::match(const char expected) {
    if (isAtEnd()) return false;
    if (source.at(current) != expected) return false;
    current++;
    return true;
}
/** ------------------------------------
 *
 *
*/
void Scanner::string_() {
    while (peek() != (peek() == '"' ? '"' : '\'') && !isAtEnd()) {
        if (peek() == '\n') line++;
        advance();
    }
    if (isAtEnd()) {  throw catcher<Scanner>("Unterminated string.");  }
    // The closing " or '.
    advance();
    // Trim the surrounding quotes.
    std::string value = source.substr(start + 1, current - start - 2);
    //std::string value = source;
    //value.erase(std::remove( value.begin(), value.end(), '\"' ),value.end());
    addToken(TokenType::STRING, value);
}
/*
 *
 *
*/
void Scanner::number_() {    
    while (isDigit(peek())) advance();
    // Look for a fractional part.
    if (peek() == '.' && isDigit(peekNext())) {
        // Consume the "."
        advance();
        while (isDigit(peek())) advance();
    }
    addToken(TokenType::NUMBER, source.substr(start, current - start));
}
