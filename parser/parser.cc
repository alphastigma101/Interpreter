#include <parser.h>
template struct std::shared_ptr<Variant<Binary, Unary, Grouping, Literal, Methods, Arguments, EcoSystem>>; // define the underlying of ExprTypes
Expr* parser::assignment() {
    auto expr = logicalOr();
    if (match(TokenType::EQUAL)) {
      Token equals = previous();
      auto value = assignment();
      if (auto conv = dynamic_cast<Variable*>(expr)) {
        Token name = conv->op;
        return new Assign(name, value);
      }
      error(); 
    }
    return expr;
}
Expr* parser::logicalOr() {
    auto expr = logicalAnd();
    while (match(TokenType::OR)) {
      Token op = previous();
      auto right = logicalAnd();
      expr = new Logical(expr, op, right);
    }
    return expr;
}
Expr* parser::logicalAnd() {
    auto expr = equality();
    while (match(TokenType::AND)) {
      Token op = previous();
      auto right = equality();
      expr = new Logical(expr, op, right);
    }
    return expr;
}
/** ---------------------------------------------------------------------------------------------------------------------------------------
 * @brief Used for calling the other rules for processing the tokens generated by the scanner
 *
 * @details This method represents the binary section in the grammar in parser.h. It uses variant which is known as a union type safe. 
    It will recrusive call itself functioning just like the grammar layout in parser.h
 * @details If it doesn't find a match it will step out of the loop and return back to expression(). 
    Otherwise, it will keep storing the calls into expr and push the res to a vector for farther processing 
 * @details This recrusive parser will not have any precendence embedded into it 
 *
 * @return comparision()
 *
 * ---------------------------------------------------------------------------------------------------------------------------------------
*/
Expr* parser::equality()  {
    // Recursion left !=
    auto expr = comparison();
    while (match(TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL)) {
        const Token op = previous();
        // Recursion right ==
        auto right = comparison();
        expr = new Binary(expr, op, right);
    }
    return expr;
}
/** --------------------------------------------------------------------------
 * @brief Called from the equality() method. Will call term() and start trying to create the Binary Nodes
 *
 * @return term()
 * --------------------------------------------------------------------------
*/
Expr* parser::comparison() {
    auto expr = term();
    while (match(TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL)) {
        const Token op = previous();
        auto right = term();
        expr = new Binary(expr, op, right);
    }
    return expr;
}
/** --------------------------------------------------------------------------
 * @brief Gets called from comparison and searches through the tokens for minus or plus
 *
 * @return expr 
 *
 * @details expr is a shared_ptr wrapped with variant that holds Binary, Unary, Grouping, and Literal instances
 * --------------------------------------------------------------------------
*/
Expr* parser::term() {
    auto expr = factor();
    while (match(TokenType::MINUS, TokenType::PLUS)) {
        const Token op = previous();
        auto right = factor();
        expr = new Binary(expr, op, right);
    }
    return expr;
}
/** --------------------------------------------------------------------------
 * @brief Gets called from term(). Searches the tokens for slash or star which are multiplication/division
 *
 * @return expr
 *
 * @details expr is a shared_ptr wrapper that wraps around variants that hold Binary, Unary, Grouping, and Literal instances
 * @details Also, grouping class is not needed if you do not want to parse the TokenTypes even farther.
   Ex: Factor can handle the () but Grouping is needed so it can get the nested () expression as it's own 
 * --------------------------------------------------------------------------
*/
Expr* parser::factor() {
    auto expr = unary(); 
    while (match(TokenType::SLASH, TokenType::STAR, TokenType::MODULO)) {
        const Token op = previous();
        auto right = unary();
        expr = new Binary(expr, op, right);
    }
    return expr;
}
/** --------------------------------------------------------------------------
 * @brief Gets called from factor(). Searches for != and minus tokens
 *
 * @return Either expr or primary()
 *
 * @details expr is a shared_ptr that wraps around a variant that holds Binary, Unary, Grouping, and Literal instances
 * --------------------------------------------------------------------------
*/
Expr* parser::unary() {
    if (match(TokenType::BANG, TokenType::MINUS)) {
        const Token op = previous();
        auto right = unary();
        return new Unary(right, op);
    }
    return call();
}
Expr* parser::finishCall(Expr* callee) {
    Vector<Expr*> arguments;
    if (!check(RIGHT_PAREN)) {
        do {
            if (arguments.size() >= 255) {
                //error(peek(), "Can't have more than 255 arguments.");
                throw parseError<parser>(peek(), "Can't have more than 255 arguments.");
            }
            arguments.push_back(expression());
        } while (match(TokenType::COMMA));
    }
    Token paren = consume(RIGHT_PAREN,
                          "Expect ')' after arguments.");
    return new Call(callee, paren, arguments);
}
Expr* parser::call() {
    auto expr = primary();
    while (true) { 
        if (match(TokenType::LEFT_PAREN)) {
            expr = finishCall(expr);
        } 
        else break;
    }
    return expr;
}
/** --------------------------------------------------------------------------
 * @brief Gets called from unary(). 
 *
 * @return expr after going through a series of if statements or will through an exception of '(' or ')'  
 * --------------------------------------------------------------------------
*/
Expr* parser::primary() {
    if (match(TokenType::FALSE)) return new Literal(previous());
    if (match(TokenType::TRUE)) return new Literal(previous());
    if (match(TokenType::NIL)) return new Literal(previous());
    if (match(TokenType::NUMBER, TokenType::STRING)) {
        return new Literal(previous());
    }
    if (match(TokenType::LEFT_PAREN)) {
        auto expr = expression();
        consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
        return new Grouping(expr);
    }
    if (match(TokenType::IDENTIFIER)) {
        Token&& op = previous();
        return new Variable(std::move(op));
    }
    throw parseError<parser>(peek(), "Expect expression.");
}
/** --------------------------------------------------------------------------
 * @brief Expands into equality to start the recrusion
 *
 * @details It becomes equality's caller
 *
 * @return equality()
 * --------------------------------------------------------------------------
*/
Expr* parser::expression() { return assignment(); }
/** --------------------------------------------------------------------------
 * @brief A grammar rule that will bind the statement and hold the value 
 *
 * @details Statements can represent a Variable, Functions or expression statement, but they do not evaluate to a value of some sort.
 *          This is called 'side effect'. 
 * @details State is 
 *          
 *
 * @return statement() or nullptr
 * --------------------------------------------------------------------------
*/
Statement* parser::statement() {
    if (match(TokenType::FOR)) return forStatement();
    if (match(TokenType::IF)) return ifStatement();
    if (match(TokenType::RADIATE)) return printStatement();
    if (match(TokenType::RETURN)) return returnStatement();
    if (match(WHILE)) return whileStatement();
    if (match(TokenType::LEFT_BRACE)) return new Block(block());
    return expressionStatement();
}
/** ---------------------------------------------------------------------------
 * @brief A rule that will call to the left and to the right to parse. 
 * 
 * ---------------------------------------------------------------------------
*/
Statement* parser::forStatement() {
    consume(TokenType::LEFT_PAREN, "Expect '(' after 'for'.");
    Statement* initializer;
    if (match(TokenType::SEMICOLON)) {
      initializer = nullptr;
    } else if (match(
                TokenType::VOID, TokenType::INT, TokenType::BOOL, 
                TokenType::STRING, TokenType::DOUBLE, TokenType::CHAR)) {
      initializer = varDeclaration();
    } else {
      initializer = expressionStatement();
    }
    Expr* condition = nullptr;
    if (!check(TokenType::SEMICOLON)) {
      condition = expression();
    }
    consume(TokenType::SEMICOLON, "Expect ';' after loop condition.");
    Expr* increment = nullptr;
    if (!check(TokenType::RIGHT_PAREN)) {
      increment = expression();
    }
    consume(TokenType::RIGHT_PAREN, "Expect ')' after for clauses.");
    Statement* body = statement();
    if (increment != nullptr) {
      body = new Block({body, new Expression(increment)});
    }
    if (condition == nullptr) condition = new Literal(Token(TokenType::BOOL, String("true"), String("true"), current));
    body = new While(condition, body);
    if (initializer != nullptr) {
      body = new Block({initializer, body});
    }
    return body;
}
/** ---------------------------------------------------------------------------
 * @brief A rule that will call to the left and to the right to parse. 
 * 
 * ---------------------------------------------------------------------------
*/
Statement* parser::ifStatement() {
    consume(TokenType::LEFT_PAREN, "Expect '(' after 'if'.");
    auto condition = expression();
    consume(TokenType::RIGHT_PAREN, "Expect ')' after if condition."); 
    Statement* thenBranch = statement();
    Statement* elseBranch = nullptr;
    if (match(TokenType::ELSE)) {
      elseBranch = statement();
    }
    return new If(condition, thenBranch, elseBranch);
}
/** ---------------------------------------------------------------------------
 * @brief A rule that will call to the left and to the right to parse. 
 * 
 * ---------------------------------------------------------------------------
*/
Statement* parser::printStatement() {
    auto value = expression();
    consume(TokenType::SEMICOLON, "Expect ';' after value.");
    return new Print(std::move(value));
}
Statement* parser::returnStatement() {
    Token keyword = previous();
    Expr* value;
    if (!check(TokenType::SEMICOLON)) {
      value = expression();
    }
    consume(TokenType::SEMICOLON, "Expect ';' after return value.");
    return new Return(keyword, value);
}
/** ---------------------------------------------------------------------------
 * @brief A rule that will call to the left and to the right to parse. 
 * 
 * ---------------------------------------------------------------------------
*/
Statement* parser::expressionStatement() {
    auto expr = expression();
    consume(TokenType::SEMICOLON, "Expect ';' after expression.");
    return new Expression(std::move(expr));
}
/** ---------------------------------------------------------------------------
 * @brief A rule that will call to the left and to the right to parse. 
 * 
 * ---------------------------------------------------------------------------
*/
Vector<ContextFreeGrammar::Statement*> parser::block() {
    Vector<Statement*> statements;
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
      statements.push_back(dynamic_cast<Statement*>(declarations()));
    }
    consume(TokenType::RIGHT_BRACE, "Expect '}' after block.");
    return std::move(statements);
}
/** ---------------------------------------------------------------------------
 * @brief A rule that will call to the left and to the right to parse. 
 * 
 * ---------------------------------------------------------------------------
*/
Statement* parser::declarations() {
    //auto expreco = ecosystem(); // TODO: Get the parser to work first with parsing variables and what not then add this feature into it 
    try {
        // NOTE: the if statement
        // You can probably create a node class that can capture the return types and later on be visited
      if (match(TokenType::VOID, TokenType::INT, TokenType::BOOL, 
                TokenType::STRING, TokenType::DOUBLE, TokenType::CHAR,
                TokenType::CONTAINMENT)) return varDeclaration(); /* return new Types(varDeclaration());*/
      return statement();
    } catch (parseError<parser>& e) {
        synchronize();
        auto err = String(error() + String(" Got '") + String(previous().getLexeme()) + String("' instead."));
        #if ENABLE_LOGGING
            std::cout << "Logs have been updated!" << std::endl;
            logging<parser> logs(std::move(err));
            logs.rotate();
            logs_ = logs.getLogs();
        #else 
            std::cout << err << std::endl;
        #endif
        return nullptr;
    }
}
Statement* parser::function(const char* kind, Token& name) {
    Vector<Token> parameters;
    if (!check(TokenType::RIGHT_PAREN)) {
      do {
        if (parameters.size() >= 255) 
          throw parseError<parser>(peek(), "Can't have more than 255 parameters.");
        if (match(TokenType::BOOL, TokenType::CHAR, TokenType::STRING, 
            TokenType::DOUBLE, TokenType::VOID, TokenType::INT)) 
        parameters.push_back(
            consume(TokenType::IDENTIFIER, "Expect parameter name."));
        else 
            throw parseError<parser>(peek(), "Unsupported type!");
      } while (match(TokenType::COMMA));
    }
    consume(TokenType::RIGHT_PAREN, "Expect ')' after parameters.");
    consume(LEFT_BRACE, "Expect '{' before " + String(kind) + " body.");
    Vector<Statement*> body = block();
    return new Functions(name, parameters, body);
}
/** -----------------------------------------------------------------------------
 * @brief A method that checks to see if the language has an identifier.
 *        A `variable name` is considered as the identifier. 
 * 
 * @details An identifier represents the type of something, essentially a variable type.
 * Rules usually require recursion. Think of calling a function again as if you're 
 * looking ahead:
 * 
 * - LR (Left-to-right) is look-ahead right.
 * - LL (Right-to-left) is look-ahead left.
 * - LAR (Look-Ahead Right) occurs when the rule (the function) gets called multiple times, typically in a loop.
 * - LAL (Look-Ahead Left) is similar, but it looks ahead to the left.
 * 
 * For more information, see the Bison manual: https://www.gnu.org/software/bison/manual/bison.html#Grammar-File
 * ------------------------------------------------------------------------------
*/
Statement* parser::varDeclaration() {
    const Token name = consume(TokenType::IDENTIFIER, "Expect a name.");
    Token&& op = previous();
    Expr* initializer = nullptr;
    if (match(TokenType::EQUAL)) {
      initializer = expression();
    }
    if (match(TokenType::LEFT_PAREN)) {
        return function("function", op);
    }
    consume(TokenType::SEMICOLON, "Expect ';' after variable declaration.");
    return new Var(std::move(name), std::move(initializer));
}
/** ---------------------------------------------------------------------------
 * @brief A rule that will call to the left and to the right to parse. 
 * 
 * ---------------------------------------------------------------------------
*/
Statement* parser::whileStatement() {
    consume(TokenType::LEFT_PAREN, "Expect '(' after 'while'.");
    auto condition = expression();
    consume(TokenType::RIGHT_PAREN, "Expect ')' after condition.");
    auto body = statement();
    return new While(condition, body);
}
/** ---------------------------------------------------------------------------
 * @brief A rule that will call to the left and to the right to parse. 
 * 
 * ---------------------------------------------------------------------------
*/
Expr* parser::methods() {
    /*if(match(TokenType::IDENTIFIER)) {
        const Token op = previous();
        auto right = new Methods(std::move(arguments()), std::move(op));
        consume(TokenType::SEMICOLON, "Expected ';' after indentifer!");
    }*/
    throw new catcher<parser>("Expected an identifier after '.' for method!");
    //return expression();
}
/** ---------------------------------------------------------------------------
 * @brief A rule that will call to the left and to the right to parse. 
 * 
 * ---------------------------------------------------------------------------
*/
Expr* parser::ecosystem() {
    auto expr = ecosystem();
    //while(TokenType::IMPORT) {

    //}

    return expr;
}
/** --------------------------------------------------------------------------
 * @brief Calls in expression to start the parsing sequence by following the grammar
 *
 * @details catches any exceptions that were thrown during run time 
 *
 * @return Either return from all the recrusive calls if nothing was thrown, otherwise return null 
 * --------------------------------------------------------------------------
*/
Vector<Statement*> parser::parse() {
    Vector<Statement*> statements;
    try { 
        while (!isAtEnd()) {
            statements.push_back(declarations());
        }
        return statements; 
    }
    catch (parseError<parser>& e) {
        #if ENABLE_LOGGING
            std::cout << "Logs have been updated!" << std::endl;
            logging<parser> logs(error());
            logs.rotate();
            logs_ = logs.getLogs();
        #else 
            std::cout << e.error() << std::endl;
        #endif
        return statements; 
    }
}

// Additional rules go above this line
//
//
//

// Error handling
/**
 * @brief custom exception thrower that throws syntax errors if detected
 * 
 * @return Calls in the report helper method
*/
String parser::error() {
    if (token.getType() == TokenType::END_OF_FILE) { return report(token.getLine(), " at end", message);}
    return report(token.getLine(), " at '" + token.getLexeme() + "'", message);
}
/** --------------------------------------------------------------------------------------
 * @brief A method that calls in logging to store the error that occured
 * 
 * @param line: The line it occured 
 * @param where: The literal 
 * @param message: The error message
 * 
 * @return Returns the error that occured
 * -------------------------------------------------------------------------------------- 
*/            
String parser::report(int line, const String where, const String message) throw() {
    String err = "[line " + std::to_string(line) + "] Error" + where +  ": " + message;
    #if ENABLE_LOGGING
        logging<parser> logs(err);
        logs.write();
        logs.rotate();
        logs_ = logs.getLogs();
    #endif
    return err;
}
void parser::printNodes() {
    ///nodes = std::move(cTree);
    /*for (int i = 0; i < nodes.size(); i++) {
        auto& [intVal, pairVal] = nodes[i];
        if (pairVal.first == "Grouping") {
            if (auto expression =  std::get<Expr*>(pairVal.second).get()->expression.get()) {
                std::cout << expression->op.get()->getLexeme() << std::endl;
            }
        }
        if (pairVal.first == "Binary") {
            if (auto expr = std::get<Expr*>(pairVal.second)) {
                if (expr->op.get() != nullptr) {
                    std::cout << expr->op.get()->getLiteral() << std::endl;
                }
            }
        }
        if (std::holds_alternative<Expr*>(pairVal.second)) {
            auto& clean = std::get<Expr*>(pairVal.second);
            clean.release();
        }
    }*/
    return;
}
