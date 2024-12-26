#ifndef _RESOLVER_H_
#define _RESOLVER_H_
#include <user_stack.h>
#include <token.h>
namespace Resolver {
    // the resolver class is the semantic analyis 
    class resolver: public Visitor<resolver> {
        public:
            explicit resolver(Interpreter::interpreter* interp) noexcept;
            ~resolver() noexcept = default;
            Any visitBlockStmt(ContextFreeGrammar::Block* stmt);
            Any visitClassStmt(ContextFreeGrammar::Class* stmt);
            Any visitExpressionStmt(ContextFreeGrammar::Expression* stmt);
            Any visitVarStmt(ContextFreeGrammar::Statement* stmt);
            Any visitWhileStmt(ContextFreeGrammar::While* stmt);
            Any visitVariableExpr(ContextFreeGrammar::Variable* expr);
            Any visitAssignExpr(ContextFreeGrammar::Assign* expr);
            Any visitBinaryExpr(ContextFreeGrammar::Binary* expr);
            Any visitCallExpr(ContextFreeGrammar::Call* expr);
            Any visitGroupingExpr(ContextFreeGrammar::Grouping* expr);
            Any visitGetExpr(ContextFreeGrammar::Get* expr);
            Any visitLiteralExpr(ContextFreeGrammar::Literal* expr);
            Any visitLogicalExpr(ContextFreeGrammar::Logical* expr);
            Any visitSetExpr(ContextFreeGrammar::Set* expr);
            Any visitThisExpr(ContextFreeGrammar::This* expr);
            Any visitUnaryExpr(ContextFreeGrammar::Unary* expr);
            Any visitFunctionStmt(ContextFreeGrammar::Functions* stmt);
            Any visitIfStmt(ContextFreeGrammar::If* stmt);
            Any visitPrintStmt(ContextFreeGrammar::Print* stmt);
            Any visitReturnStmt(ContextFreeGrammar::Return* stmt);
            void resolve(Vector<ContextFreeGrammar::Statement*>& statements);
        protected:
            explicit resolver() noexcept = default;
        private:
            enum FunctionType {
                NONE,
                FUNCTION,
                METHOD,
                INITIALIZER
            };
            enum ClassType {
                EMPTY,
                CLASS
            };
            inline static Interpreter::interpreter* interp = nullptr;
            void resolve(ContextFreeGrammar::Statement* stmt);
            void resolve(ContextFreeGrammar::Expr* expr);
            static void beginScope();
            static void endScope();
            static void declare(Token name);
            static void define(Token name);
            void resolveFunction(ContextFreeGrammar::Functions* function, FunctionType type);
            static void resolveLocal(ContextFreeGrammar::Expr* expr, Token name);
            inline static Stack::stack* scopes = new Stack::stack();
            inline static FunctionType currentFunction = FunctionType::NONE;
            inline static ClassType currentClass = ClassType::EMPTY;
    };

};


#endif