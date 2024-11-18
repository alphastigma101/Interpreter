#include <parser.h>
template struct std::shared_ptr<Variant<Binary, Unary, Grouping, Literal, Methods, Arguments, EcoSystem>>; // define the underlying of ExprTypes
Expr* parser::assignment() {
    auto expr = equality();
    if (match(TokenType::EQUAL)) {
      Token equals = previous();
      auto value = assignment();
      if (auto conv = dynamic_cast<Variable*>(expr)) {
        Token name = conv->op;
        //return new Assign(name, value);
      }
      error(); 
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
        auto expr = new Unary(right, op);
        return expr;
    }
    return primary();
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
    if (match(TokenType::IDENTIFIER, TokenType::DOT, TokenType::COMMA)) {
        Token&& op = previous();
        // TODO: The logic here still needs to be worked out 
        if (op.getType() == TokenType::DOT) return new Identifier(methods(), std::move(op)); 
        if (op.getType() == TokenType::COMMA) return new Identifier(arguments(), std::move(op)); 
        // TODO: It must not return if TokenType is not identifier 
        return new Variable(std::move(op));
    }
    std::cout << "Thowing!" << std::endl;
    throw new parseError<parser>(peek(), "Expect expression.");
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
 * @brief Expands into equality to start the recrusion
 *
 * @details It becomes equality's caller
 *
 * @return equality()
 * --------------------------------------------------------------------------
*/
Expr* parser::program() {
    while (!match(TokenType::END_OF_FILE)) return declarations(); 
    return nullptr;
}
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
Expr* parser::statement() {
    while (match(TokenType::IDENTIFIER)) {
        const Token op = previous();
        auto right = expression();
        consume(TokenType::SEMICOLON, "Expect ';' after value.");
        return new Statement(std::move(right), std::move(op));
    }
    return expression();
}
Expr* parser::declarations() {
    //auto expreco = ecosystem(); // TODO: Get the parser to work first with parsing variables and what not then add this feature into it 
    try {
      if (match(TokenType::VOID, TokenType::INT, TokenType::BOOL, 
                TokenType::STRING, TokenType::DOUBLE, TokenType::CHAR,
                TokenType::RADIATE, TokenType::CONTAINMENT)) return identifier();
      return statement();
    } catch (parseError<parser>& e) {
        synchronize();
        std::cout << "Logs have been updated!" << std::endl;
        logging<parser> logs(logs_, e.what());
        logs.update();
        logs.rotate();
        return nullptr;
    }
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
Expr* parser::identifier() {
    const Token name = consume(TokenType::IDENTIFIER, "Expect variable name.");
    Expr* initializer = nullptr;
    if (match(TokenType::EQUAL, TokenType::BRACES)) {
      initializer = expression();
    }
    consume(TokenType::SEMICOLON, "Expect ';' after variable declaration.");
    return new Statement(std::move(initializer), std::move(name));
}
/** ---------------------------------------------------------------------------
 * @brief A rule that will call to the left and to the right to parse. 
 * 
 * ---------------------------------------------------------------------------
*/
Expr* parser::arguments() {
    auto left = primary(); // this grabs the ( and expects it to be closed
    while(match(TokenType::COMMA, TokenType::IDENTIFIER)) {
        auto right = primary();
        //expr = std::make_unique<Arguments>(std::move(expr), std::move(right));
        left = new Functions(std::move(left), std::move(previous()), std::move(right));
        consume(TokenType::IDENTIFIER, "Expected Identifer after comma!");
    }
    return left;
}
/** ---------------------------------------------------------------------------
 * @brief A rule that will call to the left and to the right to parse. 
 * 
 * ---------------------------------------------------------------------------
*/
Expr* parser::methods() {
    if(match(TokenType::IDENTIFIER)) {
        const Token op = previous();
        auto right = new Methods(std::move(arguments()), std::move(op));
        consume(TokenType::SEMICOLON, "Expected ';' after indentifer!");
        return new Statement(std::move(right), std::move(op));
    }
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
Expr* parser::parse() {
    try { 
        auto result = program();
        return std::move(result);
    }
    catch (parseError<parser>& e) { 
        std::cout << "Logs have been updated!" << std::endl;
        logging<parser> logs(logs_, e.what());
        logs.update();
        logs.rotate();
        return nullptr; 
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
    logging<parser> logs(logs_, err); // Keep the logs updated throughout the whole codebase
    logs.update();
    logs.write();
    logs.rotate();
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
