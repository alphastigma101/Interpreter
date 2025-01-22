#include <gtest/gtest.h>
#include <scanner.h>
#include <abstraction_tree_syntax.h>
template<class Derived>
class Expr;
class Binary;
class Unary;
class Grouping;
class Literal;
using ExprVariant = Variant<Unique<Binary>, Unique<Unary>, 
    Unique<Grouping>, Unique<Literal>>;
// Base expression class using CRTP
template<typename Derived>
class Expr {
    public:
        ~Expr() = default;
        /** --------------------------------------------------------
         * @brief left represents the left binary node.
         * ---------------------------------------------------------
        */
        Unique<Expr> left;
        /** --------------------------------------------------------
         * @brief right represents the left binary node.
         * ---------------------------------------------------------
        */
        Unique<Expr> right;
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
        Unique<Expr> expression;
        /** --------------------------------------------------------
         * @brief expression represents the left/right binary nodes.
         *        It does not represent its own nodes. Used with Grouping class
         * ---------------------------------------------------------
        */
        Unique<Expr> paren;
        /** --------------------------------------------------------
         * @brief expression represents the left/right binary nodes.
         *        It does not represent its own nodes. Used with Grouping class
         * ---------------------------------------------------------
        */
        Unique<Expr> object;
        /** --------------------------------------------------------
         * @brief expression represents the left/right binary nodes.
         *        It does not represent its own nodes. Used with Grouping class
         * ---------------------------------------------------------
        */
        Unique<Expr> value;
        Vector<Any> arguments{};
        Token method;
        inline Any visit(Any visitor) { return static_cast<Derived*>(this)->visit(visitor); };
        inline Any accept(Any visitor) { return static_cast<Derived*>(this)->accept(visitor); };
};
// Expression classes
class Binary : public Expr<Binary> {
    public:
        explicit Binary(Unique<Expr<Binary>> left, Token op, Unique<Expr<Binary>> right) {
            this->left = std::move(left);
            this->right = std::move(right);
            this->op = std::move(op);
        };
        ~Binary() = default;
        static Any visit(Any visitor);
        inline static Any accept(Any visitor) { return visit(visitor); };
        static String parenthesize(String name, Unique<Expr> left, Unique<Expr> right);  
};
Any Binary::visit(Any visitor) {
    auto res = std::any_cast<Expr<Binary>*>(visitor);
    return parenthesize(res->op.getLexeme(), std::move(res->left), std::move(res->right));
}

String Binary::parenthesize(String name, Unique<Expr> left, Unique<Expr> right) {
    String result = "(" + name;
    if (left.get()) {
        result += " " + std::any_cast<String>(left->accept(left.get()));
    }
    if (right.get()) {
        result += " " + std::any_cast<String>(right->accept(right.get()));
    }
    return result + ")";
}

class Grouping : public Expr<Grouping> {
    public:
        explicit Grouping(Unique<Expr<Grouping>> expression) {
            this->expression = std::move(expression);
        };
        ~Grouping() = default;
        static Any visit(Any visitor);
        inline static Any accept(Any visitor) { return visit(visitor); };
        static String parenthesize(String name, Unique<Expr> expr);
    private:
        explicit Grouping() noexcept = default;
};
Any Grouping::visit(Any visitor) {
    auto res = std::any_cast<Expr<Grouping>*>(visitor);
    return parenthesize(res->op.getLexeme(), std::move(res->expression));
}
String Grouping::parenthesize(String name, Unique<Expr> expr) {
    String result = "(" + name + " ";
    if (expr) result += std::any_cast<String>(expr->accept(expr.get()));
    return result + ")";
}

class Literal : public Expr<Literal> {
    public:
        explicit Literal(const Token op) {
            this->op = std::move(op);
        };
        ~Literal() = default;
        static Any visit(Any visitor);
        inline static Any accept(Any visitor) { return visit(visitor); };
        static String parenthesize(Token literal);

    private:
        explicit Literal() noexcept = default;
};

Any Literal::visit(Any visitor) {
    auto res = std::any_cast<Expr<Literal>*>(visitor);
    return parenthesize(res->op);
}

String Literal::parenthesize(Token literal) {
    return literal.getLexeme();
}

class Unary : public Expr<Unary> {
    public:
        explicit Unary(Token op, Unique<Expr<Unary>> right) {
            this->op = std::move(op);
            this->right = std::move(right);
        };
        ~Unary() = default;
        static Any visit(Any visitor);
        inline static Any accept(Any visitor) { return visit(visitor); };
        static String parenthesize(String name, Unique<Expr> expr);
};
Any Unary::visit(Any visitor) {
    auto res = std::any_cast<Expr<Unary>*>(visitor);
    return parenthesize(res->op.getLexeme(), std::move(res->right)); 
}
String Unary::parenthesize(String name, Unique<Expr> expr) {
    String result = "(" + name + " ";
    if (expr.get())
        result += std::any_cast<String>(expr->accept(expr.get()));
    return result + ")";
}
class ParseError : public std::runtime_error {
    public:
        explicit ParseError(const String& message) : std::runtime_error(message) {}
};

class StaticParser {
    public:
        explicit StaticParser(Vector<Token> tokens) : tokens(std::move(tokens)), current(0) {};

        inline Vector<ExprVariant> parse() {
            Vector<ExprVariant> statements;
            try { 
                while (!isAtEnd()) {
                    statements.push_back(expression());
                }
                return statements; 
            }
            catch (ParseError& e) {
                std::cout << e.what() << std::endl;
            }
        };
    private:
        Vector<Token> tokens;
        size_t current;

        inline ExprVariant expression() {
            return equality();
        };

        inline ExprVariant equality() {
            auto expr = comparison();

            while (match(TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL)) {
                Token op = previous();
                auto right = comparison();
                if (auto binary = std::move(std::get<Unique<Binary>>(expr))) {
                    if (auto right_binary = std::move(std::get<Unique<Binary>>(right))) {
                        expr = Unique<Binary>(new Binary(std::move(binary), op, std::move(right_binary)));
                    }
                }
            }
            return expr;
        };

        inline ExprVariant comparison() {
            auto expr = term();

            while (match(TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL)) {
                Token op = previous();
                auto right = term();
                if (auto binary = std::move(std::get<Unique<Binary>>(expr))) {
                    if (auto right_binary = std::move(std::get<Unique<Binary>>(right))) {
                        expr = Unique<Binary>(new Binary(std::move(binary), op, std::move(right_binary)));
                    }
                }
            }
            return expr;
        };

        inline ExprVariant term() {
            auto expr = factor();

            while (match(TokenType::MINUS, TokenType::PLUS)) {
                Token op = previous();
                auto right = factor();
                if (auto binary = std::move(std::get<Unique<Binary>>(expr))) {
                    if (auto right_binary = std::move(std::get<Unique<Binary>>(right))) {
                        expr = Unique<Binary>(new Binary(std::move(binary), op, std::move(right_binary)));
                    }
                }
            }

            return expr;
        };

        inline ExprVariant factor() {
            auto expr = unary();

            while (match(TokenType::SLASH, TokenType::STAR)) {
                Token op = previous();
                auto right = unary();
                if (auto binary = std::move(std::get<Unique<Binary>>(expr))) {
                    if (auto right_binary = std::move(std::get<Unique<Binary>>(right))) {
                        expr = Unique<Binary>(new Binary(std::move(binary), op, std::move(right_binary)));
                    }
                }
            }

            return expr;
        };

        inline ExprVariant unary() {
            if (match(TokenType::BANG, TokenType::MINUS)) {
                Token op = previous();
                auto right = unary();
                return std::make_unique<Unary>(op, std::move(std::get<Unique<Unary>>(right)));
            }

            return primary();
        };

        inline ExprVariant primary() {
            if (match(TokenType::FALSE)) 
                return std::make_unique<Literal>(previous());
            if (match(TokenType::TRUE)) 
                return std::make_unique<Literal>(previous());
            if (match(TokenType::NIL)) 
                return std::make_unique<Literal>(previous());

            if (match(TokenType::NUMBER, TokenType::STRING)) {
                return std::make_unique<Literal>(previous());
            }

            if (match(TokenType::LEFT_PAREN)) {
                auto expr = expression();
                consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
                return std::make_unique<Grouping>(std::move(std::get<Unique<Grouping>>(expr)));
            }

            throw error(peek(), "Expect expression.");
        };

        template<typename... Args>
        inline bool match(Args... types) {  return (... || (check(types) ? (advance(), true) : false)); };

        inline Token consume(TokenType type, const String& message) {
            if (check(type)) return advance();
            throw error(peek(), message);
        };

        inline bool check(TokenType type) const {
            if (isAtEnd()) return false;
            return peek().getType() == type;
        };

        inline Token advance() {
            if (!isAtEnd()) current++;
            return previous();
        };

        inline bool isAtEnd() const {
            return peek().getType() == TokenType::END_OF_FILE;
        };

        inline Token peek() const {
            return tokens[current];
        };

        inline Token previous() const {
            return tokens[current - 1];
        };

        ParseError error(const Token& token, const String& message) {
            // Report error
            return ParseError(message);
        };
};

// Test fixture for StaticParser
class StaticParserTest : public testing::Test {
    protected:
        Vector<Token> createTokens(const String& expression) {
            // This is a simplified tokenization for testing
            Vector<Token> tokens;
            // Add logic to create tokens from expression string
            return tokens;
        }
};
class AbstractionTreeSyntaxTest : public testing::Test/*, public AbstractionTreeSyntax::ast*/ {
    public:
        AbstractionTreeSyntaxTest();
        ~AbstractionTreeSyntaxTest();
        static String demangle(const char* name);
};
AbstractionTreeSyntaxTest::AbstractionTreeSyntaxTest() {}
AbstractionTreeSyntaxTest::~AbstractionTreeSyntaxTest() {}
/*String AbstractionTreeSyntaxTest::demangle(const char* name) {
    int status = -1;
    Unique<char, void(*)(void*)> res {
        abi::__cxa_demangle(name, NULL, NULL, &status),
        std::free
    };
    return (status == 0) ? res.get() : name;
}*/

// Test construction of Binary node
TEST(CompressedAstTreeTest, ConstructBinaryNode) {
    
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}