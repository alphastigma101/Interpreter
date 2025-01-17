#ifndef _PARSER_H_
#define _PARSER_H_
#include <abstraction_tree_syntax.h>
namespace Parser {
    template<class Derived>
    class parseError {
        public:
            friend class parser;
            explicit parseError<Derived>(const Token t, const String msg) {
                token = std::move(t);
                message = std::move(msg);
            };
            ~parseError() = default;
            /** --------------------------------------------------------------------------------------
             * @brief A method that calls in the report method the error
             * -------------------------------------------------------------------------------------- 
            */
            inline String error() { return static_cast<Derived*>(this)->error();};
            /** --------------------------------------------------------------------------------------
             * @brief A method that calls in logging to store the error that occured
             * 
             * @param line: The line it occured 
             * @param where: The literal 
             * @param message: The error message
             * -------------------------------------------------------------------------------------- 
            */                   
            inline String report(int line, const String where, const String message) throw() {
                return static_cast<Derived*>(this)->report(line, where, message);
            };
        protected:
            parseError() = default;
        private:
            inline static Token token;
            inline static String message;
    };
    class parser: protected parseError<parser>, public logging<parser> {
        /** ----------------------------------------------------------------------------------------------------------------------------
         * @brief  object that represents a parser. 
         * @details To add more to the parser, you need to add the new rules to the existing grammar, and define it them inside the class field 
         * ----------------------------------------------------------------------------------------------------------------------------
        */
        public:
            friend class parseError;
            friend class ParserTest;
            /** ----------------------------------------------------------------------------------------------------------
             * @brief Copy constructor. You will need a default constructor if you want to inherit from this constructor
             * 
             * @param tokens: A vector that holds a list of Token instances
             * 
             * @details moves data over to tokens_  from tokens
             * ----------------------------------------------------------------------------------------------------------
            */
            explicit parser(std::vector<Token> tokens) {  tokens_ = std::move(tokens); };
            Vector<ContextFreeGrammar::Statement*> parse();
            void printNodes();
            inline static String getMessage() { return message; };
            ~parser() noexcept = default;
        protected:
            // Current rules that were made from a grammar 
            ContextFreeGrammar::Expr* equality();
            ContextFreeGrammar::Expr* comparison();
            ContextFreeGrammar::Expr* expression();
            ContextFreeGrammar::Expr* term();
            ContextFreeGrammar::Expr* factor();
            ContextFreeGrammar::Expr* unary();
            ContextFreeGrammar::Expr* primary();
            ContextFreeGrammar::Expr* methods();
            ContextFreeGrammar::Expr* ecosystem();
            ContextFreeGrammar::Expr* assignment();
            ContextFreeGrammar::Expr* logicalOr();
            ContextFreeGrammar::Expr* logicalAnd();
            ContextFreeGrammar::Expr* call();
            ContextFreeGrammar::Expr* finishCall(ContextFreeGrammar::Expr* expr);
            ContextFreeGrammar::Statement* statement();
            ContextFreeGrammar::Statement* printStatement();
            ContextFreeGrammar::Statement* ifStatement();
            ContextFreeGrammar::Statement* expressionStatement();
            ContextFreeGrammar::Statement* declarations();
            ContextFreeGrammar::Statement* varDeclaration();
            ContextFreeGrammar::Statement* whileStatement();
            ContextFreeGrammar::Statement* forStatement();
            ContextFreeGrammar::Statement* function(const char* function, Token* type = nullptr);
            ContextFreeGrammar::Statement* returnStatement();
            ContextFreeGrammar::Statement* classDeclaration();
            Vector<ContextFreeGrammar::Statement*> classProperties();
            Vector<ContextFreeGrammar::Statement*> classFields();
            Vector<ContextFreeGrammar::Statement*> block();
        protected:
            /** ----------------------------------------------------------------------------------------------------------
             * @brief Get the previous TokenType
             * ----------------------------------------------------------------------------------------------------------
            */
            inline Token previous() { return tokens_.at(current - 1); };
            /** ----------------------------------------------------------------------------------------------------------
             * @brief Peek at the current TokenType.
             * ----------------------------------------------------------------------------------------------------------
            */
            inline Token peek() {
                return tokens_.at(current);
            };
            /** ----------------------------------------------------------------------------------------------------------
             * @brief Copy constructor. You will need a default constructor if you want to inherit from this constructor
             * ----------------------------------------------------------------------------------------------------------
            */
            inline bool isAtEnd() { return peek().getType() == TokenType::END_OF_FILE; };
            /** ----------------------------------------------------------------------------------------------------------
             * @brief Advance the vector's iterator by one when it isn't at the end 
             * ----------------------------------------------------------------------------------------------------------
            */
            inline Token advance() {
                if (!isAtEnd()) current++;
                return previous();
            };
            /** ----------------------------------------------------------------------------------------------------------
             * @brief Sync.
             * ----------------------------------------------------------------------------------------------------------
            */
            inline void synchronize() {
                advance();
                while (!isAtEnd()) {                                                        
                    // TODO: Need to capture other boundaries that will simulate a new statement
                    // So instead of semicolons, other programming languages most likely do not use ; to indicate a new statement
                    if (previous().getType() == TokenType::SEMICOLON) return;               
                    switch (peek().getType()) {                                             
                        case TokenType::RADIATION:                                             
                        case TokenType::DOUBLE:
                        //case TokenType::VOID:
                        //case TokenType::POINTER:
                        case TokenType::INT:                                                
                        case TokenType::FOR:                                                
                        case TokenType::IF:                                                 
                        case TokenType::WHILE:                                              
                        case TokenType::RADIATE:                                              
                        case TokenType::RETURN:                                             
                        return;                                                             
                    }                                                                       
                    advance();
                }
            };
            /** --------------------------------------------------------------------------------------------------------------
             * @brief Checks the current TokenType
             * 
             * @details Throughout the iteration of the recrusive parser, this method will check what TokenType it is on.
             *          It does this by calling in another method called isAtEnd().
             * 
             * @return Returns the type it is on, or returns false indicating it is at the end
             * ---------------------------------------------------------------------------------------------------------------
            */
            inline bool check(const TokenType type) {
                if (isAtEnd()) return false;
                return peek().getType() == type;
            };
            /** --------------------------------------------------------------------------------------------------------------
             * @brief Calls in protected methods to match certain tokens. If a match exists, returns true. Otherwise, return false
             * ---------------------------------------------------------------------------------------------------------------
            */
            template<typename... Args>
            inline bool match(Args... types) {  return (... || (check(types) ? (advance(), true) : false)); };
            template<typename... Types>
            inline bool isOneOf(TokenType type, Types... types) {
                return ((type == types) || ...);
            };
            inline Token consume(const TokenType type, const String message) {
                if (check(type)) return advance();
                throw parseError<parser>(peek(), message);
            };
        private:
            Vector<Token> tokens_;
            inline static Map<String, Vector<String>> logs_{};
            int current = 0;
            static String error();
            static String report(int line, const String where, const String message) throw();
    };
};
using namespace Parser;
#endif