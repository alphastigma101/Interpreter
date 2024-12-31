#ifndef _CONTEXT_FREE_GRAMMAR_H_
#define _CONTEXT_FREE_GRAMMAR_H_
#include <run_time_error.h>
#if ENABLE_VISITOR_PATTERN
    #include <resolver.h>
    #include <interpreter.h>
#else 
    #include <token.h>
#endif
/*
 * A Context Free Grammar consists of a head and a body, which describes what it can generate.
 * The body's purest form will be a list of symbols and these symbols are:
    * (Terminal):
        * letter from the grammar’s alphabet, which you can think of it as a literal value.  They are the endpoints in a sense as you only produce one symbol
        * In a sense, the symbol will represent a token of some sort 
    * (Nonterminal):
        * is a reference of another grammar rule, which allows you to pick any rules for it 
 * The rule is on the very left side of the ->. On the other side of it are: 
    * Quoted strings which represent the "terminal"
    * Lowercase letters that are  "nonterminal"
*/
namespace ContextFreeGrammar {
    //template<class Derived>
    class Expr  {
        /** ------------------------------------------------------------------------------------------
         * @brief A representation of an abstraction classs which is also considered as a disoriented object
         *
         * @details By creating an abstraction class, and allowing a class to inherit it, you basically are allowing them to communicate with eachother
         *          Which allows it to not be associated with any type of behavior which usually methods/functions etc are what defined the behavior of an object
         * 
         * @details Maning that, it does nothing and the derived classes override the data member function (method).
         *          You make an abstract class, so the derived classes can access different types; 
         *          you basically access the types of the derived class through polymorphism.
         * ------------------------------------------------------------------------------------------
        */
        public:
            friend class Interpreter::interpreter;
            friend class Resolver::resolver;
            virtual ~Expr() noexcept = default;
            /** --------------------------------------------------------
             * @brief left represents the left binary node.
             * ---------------------------------------------------------
            */
            Expr* left = nullptr;
            /** --------------------------------------------------------
             * @brief right represents the left binary node.
             * ---------------------------------------------------------
            */
            Expr* right = nullptr;
            /** --------------------------------------------------------
             * @brief represents the callee node.
             * ---------------------------------------------------------
            */
            Expr* callee = nullptr;
            /** --------------------------------------------------------
             * @brief A token class instance wrapped in a unique_ptr. 
             *        It is included with the node that was created
             * ---------------------------------------------------------
            */
            Token op;
            /** --------------------------------------------------------
             * @brief expression represents the left/right binary nodes.
             *        It does not represent its own nodes. Used with Grouping class
             * ---------------------------------------------------------
            */
            Expr* expression = nullptr;
            /** --------------------------------------------------------
             * @brief expression represents the left/right binary nodes.
             *        It does not represent its own nodes. Used with Grouping class
             * ---------------------------------------------------------
            */
            Expr* paren = nullptr;
            /** --------------------------------------------------------
             * @brief expression represents the left/right binary nodes.
             *        It does not represent its own nodes. Used with Grouping class
             * ---------------------------------------------------------
            */
            Expr* object = nullptr;
            /** --------------------------------------------------------
             * @brief expression represents the left/right binary nodes.
             *        It does not represent its own nodes. Used with Grouping class
             * ---------------------------------------------------------
            */
            Expr* value = nullptr;
            Vector<Any> arguments{};
            virtual Any accept(Any visitor) = 0;
    };
    class Binary: public Expr {
        /** --------------------------------------------------------------------
             * @brief A class that represents a binary abstraction syntax tree
             * 
             * @details The 'visiting design pattern' is crucial for the abstraction syntax tree to work as it will visit the nodes
             *          It relies on recrusion to visit every node in a graph or tree 
             *          ---------------(Example of Ast Tree)--------------
                                              *
                                             / \
                                            /   \
                                            -   ()
                                           /      \
                                          123      45.67
             *          Would print out this: (* (- 123) (group 45.67)) Note: Parathesis are always included 
         */
        public:
            explicit Binary(Expr* left_, const Token& op_, Expr* right_);
            ~Binary() noexcept = default;
            inline Any accept(Any visitor) override { return visit(visitor); };
            inline Any visit(Any visitor) {
                #if ENABLE_VISITOR_PATTERN
                    if (visitor.type() == typeid(Interpreter::interpreter*))
                        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                            return visit->visitBinaryExpr(dynamic_cast<ContextFreeGrammar::Binary*>(this));
                        }
                    else 
                        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                            return visit->visitBinaryExpr(dynamic_cast<ContextFreeGrammar::Binary*>(this));
                        }
                    return nullptr;
                #else 
                    return nullptr;
                #endif 
            };
        protected:
            explicit Binary() = default;
        private:
            String parenthesize(String name, Expr* left, Expr* right);     
    };
    class Logical: public Expr, protected Visitor<Logical> {
        public:
            explicit Logical(Expr* left_, const Token& op_, Expr* right_);
            ~Logical() noexcept = default;
            inline Any accept(Any visitor) override { return visit(visitor); };
            inline Any visit(Any visitor) {
                #if ENABLE_VISITOR_PATTERN
                    if (visitor.type() == typeid(Interpreter::interpreter*))
                        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                            return visit->visitLogicalExpr(dynamic_cast<ContextFreeGrammar::Logical*>(this));
                        }
                    else 
                        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                            return visit->visitLogicalExpr(dynamic_cast<ContextFreeGrammar::Logical*>(this));
                        }
                    return nullptr;
                #else 
                    return nullptr;
                #endif
            }; 
        protected:
            explicit Logical() = default;
        private:
            String parenthesize(String name, Expr* left, Expr* right);     
    };
    class Set: public Expr, protected Visitor<Set> {
        public:
            explicit Set(Expr* left_, const Token& op_, Expr* right_);
            ~Set() noexcept = default;
            inline Any accept(Any visitor) override { return visit(visitor); };
            inline Any visit(Any visitor) {
                #if ENABLE_VISITOR_PATTERN
                    if (visitor.type() == typeid(Interpreter::interpreter*))
                        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                            return visit->visitSetExpr(dynamic_cast<ContextFreeGrammar::Set*>(this));
                        }
                    else
                        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                            return visit->visitSetExpr(dynamic_cast<ContextFreeGrammar::Set*>(this));
                        }
                    return nullptr;
                #else 
                    return nullptr;
                #endif
            };  
        protected:
            explicit Set() = default;
        private:
            String parenthesize(String name, Expr* left, Expr* right);     
    };
    class This: public Expr {
        public:
            explicit This(const Token&& oP);
            ~This() noexcept = default;
            inline Any accept(Any visitor) override { return visit(visitor); };
            inline Any visit(Any visitor)  {
                #if ENABLE_VISITOR_PATTERN
                    if (visitor.type() == typeid(Interpreter::interpreter*))
                        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                            return visit->visitThisExpr(dynamic_cast<ContextFreeGrammar::This*>(this));
                        }
                    else 
                        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                            return visit->visitThisExpr(dynamic_cast<ContextFreeGrammar::This*>(this));
                        }
                    return nullptr;
                #else 
                    return nullptr;
                #endif
            };
        protected:
            This() = default; 
    };
    class Unary: public Expr {
        public:
            explicit Unary(Expr* right_, const Token& op_);
            ~Unary() noexcept = default;
            inline Any accept(Any visitor) override { return visit(visitor); };
            inline Any visit(Any visitor) {
                #if ENABLE_VISITOR_PATTERN
                    if (visitor.type() == typeid(Interpreter::interpreter*))
                        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                            return visit->visitUnaryExpr(dynamic_cast<ContextFreeGrammar::Unary*>(this));
                        }
                    else 
                        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                            return visit->visitUnaryExpr(dynamic_cast<ContextFreeGrammar::Unary*>(this));
                        }
                    return nullptr;
                #else 
                    return nullptr;
                #endif  
            };
        protected:
            explicit Unary() = default;
        private:
            String parenthesize(String name, Expr* expr);
    };
    class Get: public Expr {
        public:
            explicit Get(Expr* object_, Token op_);
            ~Get() noexcept = default;
            inline Any accept(Any visitor) override { return visit(visitor); };
            inline Any visit(Any visitor) {
                #if ENABLE_VISITOR_PATTERN
                    if (visitor.type() == typeid(Interpreter::interpreter*))
                        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                            return visit->visitGetExpr(dynamic_cast<ContextFreeGrammar::Get*>(this));
                        }
                    else 
                        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                            return visit->visitGetExpr(dynamic_cast<ContextFreeGrammar::Get*>(this));
                        } 
                    return nullptr;
                #else 
                    return nullptr;
                #endif
            };
        protected:
            explicit Get() = default;
        private:        
            String parenthesize(String name, Expr* expr);
    };
    class Grouping: public Expr {
        public:
            /** ----------------------------------------------------------------------------------------------------------
             * @brief constructor for creating the memory addresses that will later on be accessed by a vector 
             *
             * @param expression is an rvalue that will get destroyed once it leaves the scope
             *
             * 
             * @details expression is used to represent grouping class. 
             *          It points to the left and right binary node trees
            */
            explicit Grouping(Expr* expression);
            ~Grouping() noexcept = default;
            inline Any accept(Any visitor) override { return visit(visitor); };
            inline Any visit(Any visitor) {
                #if ENABLE_VISITOR_PATTERN
                    if (visitor.type() == typeid(Interpreter::interpreter*))
                        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                            return visit->visitGroupingExpr(dynamic_cast<ContextFreeGrammar::Grouping*>(this));
                        }
                    else 
                        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                            return visit->visitGroupingExpr(dynamic_cast<ContextFreeGrammar::Grouping*>(this));
                        }
                #else 
                    return nullptr;
                #endif 
            };
        private:
            String parenthesize(String name, Expr* expr);
    };
    class Literal: public Expr {
        public:
            explicit Literal(const Token&& oP);
            ~Literal() noexcept = default;
            inline Any accept(Any visitor) override { return visit(visitor); };
            inline Any visit(Any visitor) {
                #if ENABLE_VISITOR_PATTERN
                    if (visitor.type() == typeid(Interpreter::interpreter*))
                        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                            return visit->visitLiteralExpr(dynamic_cast<ContextFreeGrammar::Literal*>(this));
                        }
                    else 
                        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                            return visit->visitLiteralExpr(dynamic_cast<ContextFreeGrammar::Literal*>(this));
                        } 
                    return nullptr;
                #else 
                    return nullptr;
                #endif
            };
        protected:
            Literal() = default; 
    };
    class Assign: public Expr {
        public:
            explicit Assign(const Token &op, Expr* expr);
            ~Assign() noexcept = default;
            inline Any accept(Any visitor) override { return visit(visitor); };
            inline Any visit(Any visitor) {
                #if ENABLE_VISITOR_PATTERN
                    if (visitor.type() == typeid(Interpreter::interpreter*))
                        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                            return visit->visitAssignExpr(dynamic_cast<ContextFreeGrammar::Assign*>(this));
                        }
                    else 
                        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                            return visit->visitAssignExpr(dynamic_cast<ContextFreeGrammar::Assign*>(this));
                        } 
                    return nullptr;
                #else 
                    return nullptr;
                #endif
            };
        protected:
            explicit Assign() = default;
        private:
            String parenthesize(String name, Expr* left);    
    };
    class Variable: public Expr {
        public:
            Variable(const Token&& oP);
            ~Variable() noexcept = default;
            inline Any accept(Any visitor) override { return visit(visitor); };
            inline Any visit(Any visitor) {
                #if ENABLE_VISITOR_PATTERN
                    if (visitor.type() == typeid(Interpreter::interpreter*))
                        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                            return visit->visitVariableExpr(dynamic_cast<ContextFreeGrammar::Variable*>(this));
                        }
                    else 
                        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                            return visit->visitVariableExpr(dynamic_cast<ContextFreeGrammar::Variable*>(this));
                        } 
                    return nullptr;
                #else 
                    return nullptr;
                #endif
            };
        protected:
            explicit Variable() = default;
    };
    class Call: public Expr {
        public:
            friend class catcher<Call>; // Use to output a message
            explicit Call(Expr* callee, Token paren, Vector<Expr*> arguments);
            ~Call() noexcept = default;
            inline Any accept(Any visitor) override { return visit(visitor); };
            inline Any visit(Any visitor)  {
                #if ENABLE_VISITOR_PATTERN
                    if (visitor.type() == typeid(Interpreter::interpreter*))
                        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                            return visit->visitCallExpr(dynamic_cast<ContextFreeGrammar::Call*>(this));
                        }
                    else 
                        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                            return visit->visitCallExpr(dynamic_cast<ContextFreeGrammar::Call*>(this));
                        } 
                    return nullptr;
                #else 
                    return nullptr;
                #endif  
            };
        protected:
            explicit Call() = default;
        private:
            String parenthesize(String name, Expr* left, Expr* right);
    };
    class Statement {
        /** ------------------------------------------------------------------------------------------
         * @brief A representation of an abstraction classs which is also considered as a disoriented object
         *
         * @details By creating an abstraction class, and allowing a class to inherit it, you basically are allowing them to communicate with eachother
         *          Which allows it to not be associated with any type of behavior which usually methods/functions etc are what defined the behavior of an object
         * 
         * @details Maning that, it does nothing and the derived classes override the data member function (method).
         *          You make an abstract class, so the derived classes can access different types; 
         *          you basically access the types of the derived class through polymorphism.
         * ------------------------------------------------------------------------------------------
        */
        public:
            friend class Interpreter::interpreter;
            friend class Resolver::resolver;
            ~Statement() noexcept = default;
            /** --------------------------------------------------------
             * @brief initializer represents the value.
             * ---------------------------------------------------------
            */
            Expr* initializer = nullptr;
            /** --------------------------------------------------------
             * @brief initializer represents the value.
             * ---------------------------------------------------------
            */
            Expr* condition = nullptr;
            /** --------------------------------------------------------
             * @brief A token class instance wrapped in a unique_ptr. 
             *        It is included with the node that was created
             * ---------------------------------------------------------
            */
            Token op;
            /** --------------------------------------------------------
             * @brief A token class instance wrapped in a unique_ptr. 
             *        It is included with the node that was created
             * ---------------------------------------------------------
            */
            Vector<ContextFreeGrammar::Statement*> statements{};
            /** --------------------------------------------------------
             * @brief A token class instance wrapped in a unique_ptr. 
             *        It is included with the node that was created
             * ---------------------------------------------------------
            */
            Statement* thenBranch = nullptr;
            /** --------------------------------------------------------
             * @brief A token class instance wrapped in a unique_ptr. 
             *        It is included with the node that was created
             * ---------------------------------------------------------
            */
            Statement* elseBranch = nullptr;
            /** --------------------------------------------------------
             * @brief initializer represents the value.
             * ---------------------------------------------------------
            */
            Statement* body = nullptr;
            /** --------------------------------------------------------
             * @brief initializer represents the value.
             * ---------------------------------------------------------
            */
            Expr* value = nullptr;
            /** --------------------------------------------------------
             * @brief initializer represents the value.
             * ---------------------------------------------------------
            */
            Vector<Token> params{};
            /** --------------------------------------------------------
             * @brief initializer represents the value.
             * ---------------------------------------------------------
            */
            Vector<Functions*> methods{};
            /** --------------------------------------------------------
             * @brief A token class instance wrapped in a unique_ptr. 
             *        It is included with the node that was created
             * ---------------------------------------------------------
            */
            Expr* expression = nullptr;
            virtual Any accept(Any visitor) = 0;
    };
    class Print: public Statement {
        public:
            Print(Expr* initalizer);
            ~Print() noexcept = default;
            Any accept(Any visitor) override { return visit(visitor); };
            inline Any visit(Any visitor) {
                #if ENABLE_VISITOR_PATTERN
                    if (visitor.type() == typeid(Interpreter::interpreter*))
                        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                            return visit->visitPrintStmt(dynamic_cast<ContextFreeGrammar::Print*>(this));
                        }
                    else
                        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                            return visit->visitPrintStmt(dynamic_cast<ContextFreeGrammar::Print*>(this));
                        }
                    return nullptr;
                #else 
                    return nullptr;
                #endif   
            };
            String parenthesize(String name, Statement* stmt);
        protected:
            Print() = default;
    };
    class Return: public Statement {
        public:
            Return(const Token& keyword, Expr* value);
            ~Return() noexcept = default;
            inline Any accept(Any visitor) override { return visit(visitor); };
            inline Any visit(Any visitor) {
                #if ENABLE_VISITOR_PATTERN
                    // TODO: Each visit method that contains a try and catch statement needs to either use typeid() or visitor.type()
                    // This will help prevent any other try and accept statements being intercepted
                    // TODO Move the visit methods inside the header and use directives to include the interpreter.h 
                    if (visitor.type() == typeid(Interpreter::interpreter*)) {
                        auto visit = std::any_cast<Interpreter::interpreter*>(visitor);
                        return visit->visitReturnStmt(dynamic_cast<ContextFreeGrammar::Return*>(this));
                    }
                    else 
                        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                            return visit->visitReturnStmt(dynamic_cast<ContextFreeGrammar::Return*>(this));
                        }
                    return nullptr;
                #else 
                    return nullptr;
                #endif
            };
        protected:
            explicit Return() = default;
    };
    class Var: public Statement {
        public:
            Var(const Token& op, Expr* initalizer);
            ~Var() noexcept = default;
            inline Any accept(Any visitor) override { return visit(visitor); };
            inline Any visit(Any visitor) {
                #if ENABLE_VISITOR_PATTERN
                    if (visitor.type() == typeid(Interpreter::interpreter*))
                        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                            return visit->visitVarStmt(dynamic_cast<ContextFreeGrammar::Var*>(this));
                        }
                    else 
                        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                            return visit->visitVarStmt(dynamic_cast<ContextFreeGrammar::Var*>(this));
                        } 
                    return nullptr;
                #else 
                    return nullptr;
                #endif 
            };
            String parenthesize(String name, Statement* left);
        protected:
            explicit Var() = default;
    };
    class While: public Statement, protected Visitor<While> {
        public:
            While(Expr* condition, Statement* body);
            ~While() noexcept = default;
            inline Any accept(Any visitor) override { return visit(visitor); };
            inline Any visit(Any visitor) {
                #if ENABLE_VISITOR_PATTERN
                    if (visitor.type() == typeid(Interpreter::interpreter*))
                        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                            return visit->visitWhileStmt(dynamic_cast<ContextFreeGrammar::While*>(this));
                        }
                    else 
                        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                            return visit->visitWhileStmt(dynamic_cast<ContextFreeGrammar::While*>(this));
                        } 
                    return nullptr;
                #else
                    return nullptr;
                #endif
            };
            String parenthesize(String name, Statement* left);
        protected:
            explicit While() = default;
    };
    class Expression: public Statement  {
        public:
            Expression(Expr* initalizer);
            ~Expression() noexcept = default;
            inline Any accept(Any visitor) override { return visit(visitor); };
            inline Any visit(Any visitor) {
                #if ENABLE_VISITOR_PATTERN
                    if (visitor.type() == typeid(Interpreter::interpreter*))
                        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                            return visit->visitExpressionStmt(dynamic_cast<ContextFreeGrammar::Expression*>(this));
                        }
                    else 
                        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                            return visit->visitExpressionStmt(dynamic_cast<ContextFreeGrammar::Expression*>(this));
                        } 
                    return nullptr;
                #else 
                    return nullptr;
                #endif 
            };
            String parenthesize(String name, Statement* stmt);
        protected:
            explicit Expression() = default;
    };
    class Block: public Statement {
        public:
            explicit Block(Vector<Statement*>&& statements);
            ~Block() noexcept = default;
            inline Any accept(Any visitor) override { return visit(visitor); };
            inline Any visit(Any visitor) {
                #if ENABLE_VISITOR_PATTERN
                    //std::cout << "Executing code!" << std::endl;
                    if (visitor.type() == typeid(Interpreter::interpreter*)) 
                        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                            return visit->visitBlockStmt(dynamic_cast<ContextFreeGrammar::Block*>(this));
                        }
                    else 
                        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                            return visit->visitBlockStmt(dynamic_cast<ContextFreeGrammar::Block*>(this));
                        }
                    return nullptr;
                #else 
                    return nullptr;
                #endif
            };
        protected:
            explicit Block() = default;
        private:
            String parenthesize(Vector<Statement*>&& expr);  
    };
    class Class: public Statement  {
        public:
            explicit Class(Token name, Vector<Functions*> methods);
            ~Class() noexcept = default;
            inline Any accept(Any visitor) override { return visit(visitor); };
            inline Any visit(Any visitor) {
                #if ENABLE_VISITOR_PATTERN
                    if (visitor.type() == typeid(Interpreter::interpreter*))
                        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                            return visit->visitClassStmt(this);
                        }
                    else 
                        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                            return visit->visitClassStmt(dynamic_cast<ContextFreeGrammar::Class*>(this));
                        }
                    return nullptr;
                #else 
                    return nullptr;
                #endif 
            };
        protected:
            explicit Class() noexcept = default;
        private:
            String parenthesize(String name, Statement* left, Statement* right);
    };
    class If: public Statement {
        public:
            explicit If(Expr* cond, Statement* thenbranch, Statement* elsebranch);
            ~If() noexcept = default;
            inline Any accept(Any visitor) override { return visit(visitor); };
            inline Any visit(Any visitor) {
                #if ENABLE_VISITOR_PATTERN
                    if (visitor.type() == typeid(Interpreter::interpreter*))
                        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                            return visit->visitIfStmt(dynamic_cast<ContextFreeGrammar::If*>(this));
                        }
                    else 
                        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                            return visit->visitIfStmt(dynamic_cast<ContextFreeGrammar::If*>(this));
                        }
                    return nullptr;
                #else 
                    return nullptr;
                #endif
            };
            String parenthesize(String name, Statement* stmt);
        protected:
            If() = default;
    };
    class Functions: public Statement {
        public:
            explicit Functions(Token name, Vector<Token> params, Vector<Statement*>& body);
            ~Functions() noexcept = default;
            inline Any accept(Any visitor) override { return visit(visitor); };
            inline Any visit(Any visitor) {
                #if ENABLE_VISITOR_PATTERN
                    if (visitor.type() == typeid(Interpreter::interpreter*))
                        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                            return visit->visitFunctionStmt(dynamic_cast<ContextFreeGrammar::Functions*>(this));
                        }
                    else 
                        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                            return visit->visitFunctionStmt(dynamic_cast<ContextFreeGrammar::Functions*>(this));
                        } 
                    return nullptr;
                #else 
                    return nullptr;
                #endif 
            };
        protected:
            explicit Functions() = default;
        private:
            String parenthesize(String name, Statement* left, Statement* right);
    };
    /*class Import: public Expr, public catcher<Import> {
        public:
            friend class catcher<Import>; // Use to output a message
            friend class Visitor<Import>;
            explicit Import(Expr* ecoSystem, const Token& op_);
            ~Import() noexcept = default;
            inline Any accept(Expr* visitor, bool tree = true) override { return visit(this, tree); };*/
        /*private:
            inline static Map<String, Vector<String>> logs_{};*/
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
            /*inline static const char* what(const char* msg = catcher<Import>::getMsg()) throw() { return msg;};
            static String parenthesize(String name, Expr* expr);
            inline String visit(Expr* expr, bool tree = true) override { 
                return "\0";
            };
        protected:
            Import() = default;
    };*/
};
using namespace ContextFreeGrammar;
#endif 
