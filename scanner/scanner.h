#ifndef _SCANNER_H_
#define _SCANNER_H_
#include <token.h>
class Scanner: public catcher<Scanner> {
    public:
        Scanner(const std::string source);
        ~Scanner() noexcept = default;
        std::vector<Token> ScanTokens();
        inline std::string getSource() { return source; };
    protected:
        void number_();          
        void string_(); 
        bool match(const char expected);
        void identifier();
        void addToken(const TokenType type, const std::string literal);
        void addToken(const TokenType type);
        void scanToken();
    private:
        std::string source;
        std::vector<Token> tokens; 
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
        static const std::unordered_map<std::string, TokenType> keywords;
};
#endif
