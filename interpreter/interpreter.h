#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_
#include <language_specific_truthy_operations.h>
namespace Interpreter {
    class interpreter: 
                       public Visitor<interpreter>, protected truthyOperations, 
                    protected binaryOperations, protected unaryOperations, protected NuclearLang::NukeFunction,
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
            //truthyOperations* tO = new truthyOperations();
            //binaryOperations* bO = new binaryOperations();
            //unaryOperations* uO = new unaryOperations();
            Any visitBinaryExpr(ContextFreeGrammar::Binary* expr);
            Any visitUnaryExpr(ContextFreeGrammar::Unary* expr);
            Any visitLiteralExpr(ContextFreeGrammar::Literal* expr);
            Any visitGroupingExpr(ContextFreeGrammar::Grouping* expr);
            Any visitBlockStmt(ContextFreeGrammar::Block* stmt);
            Any visitClassStmt(ContextFreeGrammar::Class* stmt);
            Any visitExpressionStmt(ContextFreeGrammar::Expression* stmt);
            Any visitPrintStmt(ContextFreeGrammar::Print* stmt);
            Any visitVariableExpr(ContextFreeGrammar::Variable* expr);
            Any lookUpVariable(Token name, ContextFreeGrammar::Expr* expr);
            Any visitVarStmt(ContextFreeGrammar::Var* stmt);
            Any visitAssignExpr(ContextFreeGrammar::Assign* expr);
            Any visitIfStmt(ContextFreeGrammar::If* stmt);
            Any visitLogicalExpr(ContextFreeGrammar::Logical* expr);
            Any visitSetExpr(ContextFreeGrammar::Set* expr);
            Any visitThisExpr(ContextFreeGrammar::This* expr);
            Any visitWhileStmt(ContextFreeGrammar::While* stmt);
            Any visitCallExpr(ContextFreeGrammar::Call* expr);
            Any visitGetExpr(ContextFreeGrammar::Get* expr);
            Any visitFunctionStmt(ContextFreeGrammar::Functions* expr);
            Any visitReturnStmt(ContextFreeGrammar::Return* stmt);
            inline static void resolve(ContextFreeGrammar::Expr* expr, int depth) {
                locals.insert_or_assign(expr, depth);
            };
            inline void executeBlock(Vector<ContextFreeGrammar::Statement*> statements, Environment::environment* environment) {
                Environment::environment* previous = this->globals;
                this->globals = environment;
                for (const auto statement : statements) {
                    execute(statement);
                }
                this->globals = previous;
            };
            inline Environment::environment* getEnv() { return globals; };
            inline static int arity(int argc = 0) { return argc;};
            static Any call(Interpreter::interpreter* interpreter, Vector<Any> arguments);
        private:
            void execute(ContextFreeGrammar::Statement* stmt);
            inline static Check<interpreter> check{};
            inline static Map<String, Vector<String>> logs_{};
            static Environment::environment* globals;
            inline static Environment::environment* environment = globals;
            inline static Map<ContextFreeGrammar::Expr*, int> locals{}; //= new Map<ContextFreeGrammar::Expr*, int>();
            template<typename T>
            static bool instanceof(const Any& object);
        protected:
            Any evaluate(ContextFreeGrammar::Expr* conv);
           
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
            /** --------------------------------------
             * @brief A method that is overloaded here from this class 
             * 
             * @details The runtimeerror class will call this method and it will output something to the temrinal
             * 
             * @param msg A default argument that calls in a statically inlined method to output error message
             * @param type A temp object that will eventually be destroyed once it leaves the scope. 
             *             It also calls in a statically inlined method to get the TokenType
             * 
             * @return a concated string back to the caller method
             * 
             * ---------------------------------------
            */
            inline static const char* what(const TokenType& type = getType(), const char* msg = runtimeerror<interpreter>::getMsg()) throw() {
                static String output;
                try {
                    if (auto search = tokenTypeStrings.find(type); search != tokenTypeStrings.end()) {
                        output = search->second.c_str() + String(msg);
                        return output.c_str();
                    }
                    else 
                        throw catcher<interpreter>("In interpreter class: Error! conversion has failed!");
                }
                catch(catcher<interpreter>& e) {
                    std::cout << "Logs have been updated!" << std::endl;
                    logging<interpreter> logs(e.what());
                    logs_ = logs.getLogs();
                    logs.rotate();
                }
                return output.c_str();
            };
    };
};
using namespace Interpreter;
#endif
