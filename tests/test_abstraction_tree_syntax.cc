#include <gtest/gtest.h>
#include <scanner.h>
#include <abstraction_tree_syntax.h>
// Forward declarations
class Binary;
class Grouping;
class Literal;
class Unary;

// Base visitor class using CRTP
/*template<typename Derived>
    class ExprVisitor {
        public:
            Any visit() { return static_cast<Derived>(this)->visit(); };
            Any accept() { return static_cast<Derived>(this)->accept(); };
        };

// Base expression class using CRTP
template<typename Derived>
class Expr {
    public:
        template<typename V>
        inline static Any accept(ExprVisitor<V>& visitor) {
            return visitor.visit(static_cast<Derived&>(*this));
        }
};

// Literal value variant type
using LiteralValue = std::variant<std::string, double, bool, std::nullptr_t>;

// Expression classes
class Binary : public Expr<Binary> {
    public:
        Binary(Unique<Expr<Binary>> left, Token op, Unique<Expr<Binary>> right)
            : left(std::move(left)), op(op), right(std::move(right)) {}

        Unique<Expr<Binary>> left;
        Token op;
        Unique<Expr<Binary>> right;
};

class Grouping : public Expr<Grouping> {
    public:
        explicit Grouping(Unique<Expr<Binary>> expression)
            : expression(std::move(expression)) {}

        std::unique_ptr<Expr<Binary>> expression;
};

class Literal : public Expr<Literal> {
    public:
        explicit Literal(LiteralValue value) : value(std::move(value)) {}

        LiteralValue value;
};

class Unary : public Expr<Unary> {
    public:
    Unary(std::string op, std::unique_ptr<Expr<Binary>> right)
        : op(op), right(std::move(right)) {}

    Token op;
    Unique<Expr<Binary>> right;
};
class ParseError : public std::runtime_error {
public:
    explicit ParseError(const std::string& message) : std::runtime_error(message) {}
};

class Parser {
public:
    explicit Parser(std::vector<Token> tokens) : tokens(std::move(tokens)), current(0) {}

    std::unique_ptr<Expr<Binary>> parse() {
        try {
            return expression();
        } catch (const ParseError& error) {
            // Handle error
            return nullptr;
        }
    }

private:
    std::vector<Token> tokens;
    size_t current;

    std::unique_ptr<Expr<Binary>> expression() {
        return equality();
    }

    std::unique_ptr<Expr<Binary>> equality() {
        auto expr = comparison();

        while (match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {
            Token op = previous();
            auto right = comparison();
            expr = std::make_unique<Binary>(std::move(expr), op.lexeme, std::move(right));
        }

        return expr;
    }

    std::unique_ptr<Expr<Binary>> comparison() {
        auto expr = term();

        while (match({TokenType::GREATER, TokenType::GREATER_EQUAL, 
                     TokenType::LESS, TokenType::LESS_EQUAL})) {
            Token op = previous();
            auto right = term();
            expr = std::make_unique<Binary>(std::move(expr), op.lexeme, std::move(right));
        }

        return expr;
    }

    std::unique_ptr<Expr<Binary>> term() {
        auto expr = factor();

        while (match({TokenType::MINUS, TokenType::PLUS})) {
            Token op = previous();
            auto right = factor();
            expr = std::make_unique<Binary>(std::move(expr), op.lexeme, std::move(right));
        }

        return expr;
    }

    std::unique_ptr<Expr<Binary>> factor() {
        auto expr = unary();

        while (match({TokenType::SLASH, TokenType::STAR})) {
            Token op = previous();
            auto right = unary();
            expr = std::make_unique<Binary>(std::move(expr), op.lexeme, std::move(right));
        }

        return expr;
    }

    std::unique_ptr<Expr<Binary>> unary() {
        if (match({TokenType::BANG, TokenType::MINUS})) {
            Token op = previous();
            auto right = unary();
            return std::make_unique<Unary>(op.lexeme, std::move(right));
        }

        return primary();
    }

    std::unique_ptr<Expr<Binary>> primary() {
        if (match({TokenType::FALSE})) 
            return std::make_unique<Literal>(false);
        if (match({TokenType::TRUE})) 
            return std::make_unique<Literal>(true);
        if (match({TokenType::NIL})) 
            return std::make_unique<Literal>(nullptr);

        if (match({TokenType::NUMBER, TokenType::STRING})) {
            return std::make_unique<Literal>(previous().literal);
        }

        if (match({TokenType::LEFT_PAREN})) {
            auto expr = expression();
            consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
            return std::make_unique<Grouping>(std::move(expr));
        }

        throw error(peek(), "Expect expression.");
    }

    bool match(std::initializer_list<TokenType> types) {
        for (TokenType type : types) {
            if (check(type)) {
                advance();
                return true;
            }
        }
        return false;
    }

    Token consume(TokenType type, const std::string& message) {
        if (check(type)) return advance();
        throw error(peek(), message);
    }

    bool check(TokenType type) const {
        if (isAtEnd()) return false;
        return peek().type == type;
    }

    Token advance() {
        if (!isAtEnd()) current++;
        return previous();
    }

    bool isAtEnd() const {
        return peek().type == TokenType::EOF_TOKEN;
    }

    Token peek() const {
        return tokens[current];
    }

    Token previous() const {
        return tokens[current - 1];
    }

    ParseError error(const Token& token, const std::string& message) {
        // Report error
        return ParseError(message);
    }
};
*/
// Test fixture for Parser
class ParserTest : public testing::Test {
    protected:
        Vector<Token> createTokens(const std::string& expression) {
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
        static std::string demangle(const char* name);
};
AbstractionTreeSyntaxTest::AbstractionTreeSyntaxTest() {}
AbstractionTreeSyntaxTest::~AbstractionTreeSyntaxTest() {}
std::string AbstractionTreeSyntaxTest::demangle(const char* name) {
    int status = -1;
    std::unique_ptr<char, void(*)(void*)> res {
        abi::__cxa_demangle(name, NULL, NULL, &status),
        std::free
    };
    return (status == 0) ? res.get() : name;
}

// Test construction of Binary node
TEST(CompressedAstTreeTest, ConstructBinaryNode) {
    
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}