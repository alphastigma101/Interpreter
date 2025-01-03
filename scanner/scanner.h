#ifndef _SCANNER_H_
#define _SCANNER_H_
#include <token.h>
class Scanner: public catcher<Scanner> {
    public:
        Scanner(const String source);
        ~Scanner() noexcept = default;
        Vector<Token> ScanTokens();
        inline String getSource() { return source; };
    protected:
        void number_();          
        void string_(); 
        bool match(const char expected);
        void identifier();
        void addToken(const TokenType type, const String literal);
        void addToken(const TokenType type);
        void scanToken();
    private:
        String source;
        Vector<Token> tokens; 
        int start = 0;
        int current = 0;
        int line = 1;
        inline static const char* what(const char* msg = getMsg()) throw() { return msg;};
        inline bool isAtEnd() { return current >= source.length();}; 
        inline char advance() { return source.at(current++); };
        inline bool isDigit(const char c) { return c >= '0' && c <= '9'; };
        inline bool isAlpha(const char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'; };
        inline bool isAlphaNumeric(const char c) { return isAlpha(c) || isDigit(c); };
        inline char peek() {
            if (isAtEnd()) return '\0';
            return source.at(current);
        };
        inline char peekNext() {
            if (current + 1 >= source.length()) return '\0';
            return source.at(current + 1);
        };
        inline bool isWhitespace(char c) {
            return c == ' ' || c == '\t' || c == '\r' || c == '\n';
        };
        static const Unordered<String, TokenType> keywords;
};
#endif
