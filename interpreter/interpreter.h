#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_
#include <language_specific_truthy_operations.h>
#include <tactical_nuke.h>
namespace Interpreter {
    class interpreter: protected ContextFreeGrammar::Binary,
                    protected ContextFreeGrammar::Variable, protected ContextFreeGrammar::Assign, protected ContextFreeGrammar::Var, 
                    protected ContextFreeGrammar::Block, 
                    protected ContextFreeGrammar::Print,  public Visitor<interpreter>, protected truthyOperations, 
                    protected binaryOperations, protected unaryOperations, public NuclearLang::Nuke<interpreter>,
                    public logging<interpreter>, protected runtimeerror<interpreter>, public catcher<interpreter>  {
        public:
            friend class catcher<interpreter>; // Useful for one error
            friend class runtimeerror<interpreter>;
            explicit interpreter(); 
            /** -----------------------------------------------
             * @brief A constructor that handles the traversing of the ast
             * ------------------------------------------------
            */
            explicit interpreter(Vector<ContextFreeGrammar::Statement*>& stmt);
            ~interpreter() noexcept = default;
            //truthyOperations* tO = new truthyOperations();
            //binaryOperations* bO = new binaryOperations();
            //unaryOperations* uO = new unaryOperations();
            static Any visitBinaryExpr(ContextFreeGrammar::Binary* expr);
            static Any visitUnaryExpr(ContextFreeGrammar::Unary* expr);
            inline void visitBlockStmt(ContextFreeGrammar::Block* stmt) {
                executeBlock(stmt->statements, new Environment::environment(*globals));
            };
            static Any visitExpressionStmt(ContextFreeGrammar::Expression* stmt);
            static Any visitPrintStmt(ContextFreeGrammar::Print* stmt);
            static Any visitVariableExpr(ContextFreeGrammar::Variable* expr);
            static void visitVarStmt(ContextFreeGrammar::Var* stmt);
            static Any visitAssignExpr(ContextFreeGrammar::Assign* expr);
            static void visitIfStmt(ContextFreeGrammar::If* stmt);
            static Any visitLogicalExpr(ContextFreeGrammar::Logical* expr);
            static void visitWhileStmt(ContextFreeGrammar::While* stmt);
            Any visitCallExpr(ContextFreeGrammar::Call* expr);
            Any visitFunctionStmt(ContextFreeGrammar::Functions* expr);
            static void visitReturnStmt(ContextFreeGrammar::Return* stmt);
            inline void getExecuteBlock(Vector<ContextFreeGrammar::Statement*> statements, Environment::environment* environment) { 
                executeBlock(statements, environment);
            };
            inline Environment::environment* getEnv() { return globals; };
            static int arity(int argc = 0) { return argc;};
            static Any call(Interpreter::interpreter* interpreter, Vector<Any>& arguments);
        private:
            inline static void execute(ContextFreeGrammar::Statement* stmt) {
                stmt->accept(stmt, false);
            };
            inline static Check<interpreter> check{};
            inline static Map<String, Vector<String>> logs_{};
            static Environment::environment* globals;
            inline static Environment::environment* environment = globals;
            template<typename T>
            static bool instanceof(const Any& object);
            static void moveCursor(int x, int y);
            static void drawStickFigures();
            static void drawNuke(int height);
            static void drawExplosion();
            static void clearScreen();
            static void drawMiniatureNuke(int x, int y);
            static void drawMiniatureNukeGrid(int numRows, int numCols);
            static void launch();
        protected:
            static Any evaluate(ContextFreeGrammar::Expr* conv);
            inline void executeBlock(Vector<ContextFreeGrammar::Statement*> statements, Environment::environment* environment) {
                Environment::environment* previous = this->globals;
                try {
                    this->globals = environment;
                    for (const auto& statement : statements) {
                        execute(statement);
                    }
                } catch(...) { this->globals = previous; }
                this->globals = previous;
            };
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
