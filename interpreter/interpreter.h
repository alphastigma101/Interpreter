#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_
#include <language_specific_truthy_operations.h>
namespace Interpreter {
    class interpreter: public Visitor<interpreter>, protected NuclearLang::NukeFunction,
                    public logging<interpreter>, protected runtimeerror<interpreter>, public catcher<interpreter>  {
        public:
            friend class catcher<interpreter>; // Useful for one error
            friend class runtimeerror<interpreter>;
            explicit interpreter(); 
            /** -----------------------------------------------
             * @brief A constructor that handles the traversing of the ast
             * ------------------------------------------------
            */
            explicit interpreter(Vector<ContextFreeGrammar::Statement*> stmt);
            ~interpreter() noexcept = default;
            static Any visitBinaryExpr(ContextFreeGrammar::Binary* expr);
            static Any visitUnaryExpr(ContextFreeGrammar::Unary* expr);
            static Any visitLiteralExpr(ContextFreeGrammar::Literal* expr);
            static Any visitGroupingExpr(ContextFreeGrammar::Grouping* expr);
            static Any visitBlockStmt(ContextFreeGrammar::Block* stmt);
            static Any visitClassStmt(ContextFreeGrammar::Class* stmt);
            static Any visitExpressionStmt(ContextFreeGrammar::Expression* stmt);
            static Any visitPrintStmt(ContextFreeGrammar::Print* stmt);
            static Any visitVariableExpr(ContextFreeGrammar::Variable* expr);
            static Any lookUpVariable(Token name, ContextFreeGrammar::Expr* expr);
            static Any visitVarStmt(ContextFreeGrammar::Var* stmt);
            static Any visitAssignExpr(ContextFreeGrammar::Assign* expr);
            static Any visitIfStmt(ContextFreeGrammar::If* stmt);
            static Any visitLogicalExpr(ContextFreeGrammar::Logical* expr);
            static Any visitSetExpr(ContextFreeGrammar::Set* expr);
            static Any visitSuperExpr(ContextFreeGrammar::Super* expr);
            static Any visitThisExpr(ContextFreeGrammar::This* expr);
            static Any visitWhileStmt(ContextFreeGrammar::While* stmt);
            static Any visitCallExpr(ContextFreeGrammar::Call* expr);
            static Any visitGetExpr(ContextFreeGrammar::Get* expr);
            static Any visitFunctionStmt(ContextFreeGrammar::Functions* expr);
            static Any visitReturnStmt(ContextFreeGrammar::Return* stmt);
            inline static void resolve(ContextFreeGrammar::Expr* expr, int depth) {
                locals.insert_or_assign(expr, depth);
            };
            inline static void executeBlock(Vector<ContextFreeGrammar::Statement*> statements, Environment::environment* environment) {
                Environment::environment* previous = globals;
                *globals = *environment;
                try {
                    for (const auto statement : statements) {
                        if (statement != nullptr) 
                            execute(statement);
                        else 
                            throw catcher<interpreter>("Inside of executeBlock() interpreter, a nullptr was detected!");
                    }
                    *globals = *previous;
                }
                catch(catcher<interpreter>& e) {
                    std::cout << e.what() << std::endl;
                    exit(0);
                }
            };
            inline Environment::environment* getEnv() { return globals; };
            inline static int arity(int argc = 0) { return argc;};
            static Any call(Interpreter::interpreter* interpreter, Vector<Any> arguments);
        private:
            Vector<Any> Fields;
            inline static TruthyOperations::truthyOperations* tO = new TruthyOperations::truthyOperations();
            inline static BinaryOperations::binaryOperations* bO = new BinaryOperations::binaryOperations();
            inline static UnaryOperations::unaryOperations* uO = new UnaryOperations::unaryOperations();
            String globalType;
            String localType;
            Token className;
            static void execute(ContextFreeGrammar::Statement* stmt);
            inline static Map<String, Vector<String>> logs_{};
            static Environment::environment* globals;
            inline static Environment::environment* environment = globals;
            inline static Map<ContextFreeGrammar::Expr*, int> locals{};
            template<typename T>
            static bool instanceof(const Any object);
        protected:
            static Any evaluate(ContextFreeGrammar::Expr* conv);
            inline static const TokenType& getType() { return *static_cast<const TokenType*>(std::move(runtimeerror<interpreter>::type));};
            /** --------------------------------------
             * @brief A method that is overloaded by this class 
             * 
             * @details It is a method that is defined here which gets called by the definition method inside catcher 
             * 
             * @param msg A default argument that calls in a statically inlined method to output the error message
             * 
             * @return a string literal. Usually will be ub. Something that you do not want to get
             * 
             * ---------------------------------------
            */
            inline static const char* what(const char* msg = catcher<interpreter>::getMsg()) throw() { return msg; };
            static const char* what(const TokenType& type = getType(), const char* msg = runtimeerror<interpreter>::getMsg()) throw();       
    };
};
#endif
