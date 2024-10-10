#include <token.h>


void debugDefaultConstructor() {
    //Token token;
    return;
}

void debugGetLexeme() {
    //Token token(TokenType::STRING, "\"Hello\"", "Hello", 1);
    return;
}


void debugTokenGetLiteral() {
    //Token token(TokenType::STRING, "\"World\"", "World", 1);
    return;
}


void debugGetLine() {
    //Token token(TokenType::PLUS, "+", "+", 10);
    return;
}

void debugToString() {
     Token token(TokenType::EQUAL, "=", "=", 1);                                 
     std::string result = std::any_cast<std::string>(token.toString());
     std::cout << result << std::endl;
}


// Driver Code
int main(void) {
    debugDefaultConstructor();
    debugTokenGetLiteral();
    debugGetLine();
    debugGetLexeme();
    debugToString();
    return 0;
}
