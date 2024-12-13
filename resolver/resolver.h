#ifndef _RESOLVER_H_
#define _RESOLVER_H_
#include <context_free_grammar.h>
#include <user_stack.h>
namespace Resolver {
    // the resolver class is the semantic analyis 
    class resolver: protected ContextFreeGrammar::Binary, protected ContextFreeGrammar::Print, public Visitor<resolver> {
        public:
            explicit resolver(Interpreter::interpreter* interp) noexcept;
            ~resolver() noexcept = default;
            static Any visitBlockStmt(ContextFreeGrammar::Block* stmt);
            static Any visitClassStmt(ContextFreeGrammar::Class* stmt);
            static Any visitExpressionStmt(ContextFreeGrammar::Expression* stmt);
            static Any visitVarStmt(ContextFreeGrammar::Statement* stmt);
            static Any visitWhileStmt(ContextFreeGrammar::While* stmt);
            static Any visitVariableExpr(ContextFreeGrammar::Variable* expr);
            static Any visitAssignExpr(ContextFreeGrammar::Assign* expr);
            static Any visitBinaryExpr(ContextFreeGrammar::Binary* expr);
            static Any visitCallExpr(ContextFreeGrammar::Call* expr);
            static Any visitGroupingExpr(ContextFreeGrammar::Grouping* expr);
            static Any visitLiteralExpr(ContextFreeGrammar::Literal* expr);
            static Any visitLogicalExpr(ContextFreeGrammar::Logical* expr);
            static Any visitSetExpr(ContextFreeGrammar::Set* expr);
            static Any visitThisExpr(ContextFreeGrammar::This* expr);
            static Any visitUnaryExpr(ContextFreeGrammar::Unary* expr);
            static Any visitFunctionStmt(ContextFreeGrammar::Functions* stmt);
            static Any visitIfStmt(ContextFreeGrammar::If* stmt);
            static Any visitPrintStmt(ContextFreeGrammar::Print* stmt);
            static Any visitReturnStmt(ContextFreeGrammar::Return* stmt);
            static void resolve(Vector<ContextFreeGrammar::Statement*>& statements);
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
            static void resolve(ContextFreeGrammar::Statement* stmt);
            static void resolve(Expr* expr);
            static void beginScope();
            static void endScope();
            static void declare(Token& name);
            static void define(Token& name);
            static void resolveFunction(ContextFreeGrammar::Functions* function, FunctionType type);
            static void resolveLocal(ContextFreeGrammar::Expr* expr, Token& name);
            inline static Stack::stack* scopes = new Stack::stack(new Map<String, bool>);
            inline static FunctionType currentFunction = FunctionType::NONE;
            inline static ClassType currentClass = ClassType::EMPTY;
            

    };

};


#endif