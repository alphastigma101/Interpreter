#include <parser.h>
#include <scanner.h>
void runTest(const std::string& input) {
    std::cout << "Testing input: " << input << std::endl;
    
    // Create scanner and generate tokens
    Scanner scanner(input);
    std::vector<Token> tokens = scanner.ScanTokens();
    
    // Print tokens for debugging
    std::cout << "Lexemes:" << std::setw(15) << "Tokens:" << std::endl;
    for (auto& token : tokens) {
        std::string temp = token.getLexeme();
        std::cout << std::left << std::setw(15) << temp << token.getTypeStr() << std::endl;
    }
    
    // Parse tokens
    parser p(tokens);
    p.beginParse();
    std::cout << "------------------------" << std::endl;
}

parser createParser(std::vector<Token>& tokens) { return parser(tokens);}

static void debugEquality() {
    Vector<String> types = {
        "bool y = false;",
        "double a = 90.0000;",
        "int b = 2;",
        "string c = \"hello\";",
        "string d = 'bye!';",
        //"void &c = &funky;",
    };
    Vector<String> expressions = {
        /*"(1 == 1)",
        "2 != 3",
        "true == true",
        "false != true",
        "null == null",
        "5 % 0",*/
        //"'hello' == 'hello'",
        /*"('world' != 'World')",
        //"1 == 2 == false",
        //"1 != 2 != false",
        "(1 == 1) == true",
        "(1 != 1) == false",
        "true == !false",
        "null != undefined",
        "0 == false",
        "1 == true",
        "'' == false",
        "'0' != 0",
        "[] == []",
        "{} != {}", 
        "(Infinity == Infinity)",
        "NaN != NaN",
        "(1 < 2) == (3 > 2)",
        "(1 <= 1) != (2 >= 3)"*/
    };
    Vector<String> Exceptions = {
        //"double z = 90.0000",
        //"print one",
        //"print one;"
        //"foo.bar(1,2,3,4)",
        // "bar(int x, double y, string z)",
    };
    Vector<String> functions = {
        "radiate one;",
        //"foo.bar(1,2,3,4);",
        // "bar(int x, double y, string z);",
    };
    std::cout << "Debugging supported types:" << std::endl;
    for (const auto& testCase : types) runTest(testCase); // debug the supported types
    for (const auto& testCase : Exceptions) runTest(testCase); // debug the exceptions
    for (const auto& testCase : functions) runTest(testCase);
    
   
}

/*static void debugComparison() {
    std::vector<Token> tokens = {
        Token(TokenType::NUMBER, "1", 1.0, 1),
        Token(TokenType::LESS, "<", nullptr, 1),
        Token(TokenType::NUMBER, "2", 2.0, 1)
    };
    parser p = createParser(tokens);
    auto result = p.comparison();
}

static void debugTerm() {
    std::vector<Token> tokens = {
        Token(TokenType::NUMBER, "1", 1.0, 1),
        Token(TokenType::PLUS, "+", nullptr, 1),
        Token(TokenType::NUMBER, "2", 2.0, 1)
    };
    parser p = createParser(tokens);
    auto result = p.term();
}

static void debugFactor() {
    std::vector<Token> tokens = {
        Token(TokenType::NUMBER, "2", 2.0, 1),
        Token(TokenType::STAR, "*", nullptr, 1),
        Token(TokenType::NUMBER, "3", 3.0, 1)
    };
    parser p = createParser(tokens);
    auto result = p.factor();
}

static void debugUnary() {
    std::vector<Token> tokens = {
        Token(TokenType::MINUS, "-", nullptr, 1),
        Token(TokenType::NUMBER, "5", 5.0, 1)
    };
    parser p = createParser(tokens);
    auto result = p.unary();
}

static void debugPrimaryNumber() {
    std::vector<Token> tokens = {Token(TokenType::NUMBER, "42", 42.0, 1)};
    parser p = createParser(tokens);
    auto result = p.primary();
}

static void debugPrimaryString() {
    std::vector<Token> tokens = {Token(TokenType::STRING, "hello", "hello", 1)};
    parser p = createParser(tokens);
    auto result = p.primary();
}

static void debugPrimaryTrue() {
    std::vector<Token> tokens = {Token(TokenType::TRUE, "true", true, 1)};
    parser p = createParser(tokens);
    auto result = p.primary();
}

static void debugPrimaryFalse() {
    std::vector<Token> tokens = {Token(TokenType::FALSE, "false", false, 1)};
    parser p = createParser(tokens);
    auto result = p.primary();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Literal>(*result));
}*/

int main(int argc, char **argv) {
    debugEquality();
    return 0;
}
