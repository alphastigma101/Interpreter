#ifndef _PARSER_H_
#define _PARSER_H_
#include <abstraction_tree_syntax.h>
#include <symbol-table.h>
namespace Parser {
    template<class Derived>
    class parseError {
        public:
            friend class parser;
            explicit parseError<Derived>(const Token& t, const String& msg) {
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
            inline static Symbol::Table* table = new Symbol::Table();
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
            explicit parser(std::vector<Token>& tokens) {  tokens_ = std::move(tokens); };
            Vector<Statement*> parse();
            void printNodes();
            ~parser() noexcept = default; // This shouldn't be a virtual... 
        protected:
            // Current rules that were made from a grammar 
            Expr* equality();
            Expr* comparison();
            Expr* expression();
            Expr* term();
            Expr* factor();
            Expr* unary();
            Expr* primary();
            Expr* methods();
            Expr* ecosystem();
            Expr* assignment();
            Expr* logicalOr();
            Expr* logicalAnd();
            Expr* call();
            Expr* finishCall(Expr* expr);
            Statement* statement();
            Statement* printStatement();
            Statement* ifStatement();
            Statement* expressionStatement();
            Statement* declarations();
            Statement* varDeclaration();
            Statement* whileStatement();
            Statement* forStatement();
            Statement* function(const char* function, Token* type = nullptr);
            Statement* returnStatement();
            Statement* classDeclaration();
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
            inline Token consume(const TokenType type, const String message) {
                if (check(type)) return advance();
                /*auto clear = [this]() {
                    for (int i = 0; i < nodes.size(); i++) {
                        auto& [intVal, pairVal] = nodes[i];
                        if (std::holds_alternative<Expr*>(pairVal.second)) {
                            auto& clean = std::get<Expr*>(pairVal.second);
                            clean.release();
                        }
                    }
                };
                clear();*/
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