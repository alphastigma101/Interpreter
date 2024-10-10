#include <scanner.h>

void debugConstructor() {
    std::string source_ = "var x = 5;";
    Scanner scanner(source_);
}

void debugSingleCharacterTokens() {
    std::string source_ = "(){},.-+;*";
    Scanner scanner(source_);
    std::vector<Token> tokens = scanner.ScanTokens();
    for (int i = 0; i < tokens.size(); i++) {
        std::cout << std::any_cast<std::string>(tokens.at(i).toString()) << std::endl;
    }    
}

void debugDoubleCharacterTokens() {
    std::string source = "!= == <= >=";
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.ScanTokens();
    for (int i = 0; i < tokens.size(); i++) {
        std::cout << std::any_cast<std::string>(tokens.at(i).toString()) << std::endl;
    }
    return;
}

void debugKeywords() {
    std::string source_ = "and class else if while var";
    Scanner scanner(source_);
    std::vector<Token> tokens = scanner.ScanTokens();
    for (int i = 0; i < tokens.size(); i++) {
        std::cout << std::any_cast<std::string>(tokens.at(i).toString()) << std::endl;
    }
    return;
}


void debugIdentifiers() {
    std::string source = "variable_name anotherVar _underscoreVar";
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.ScanTokens();
    for (int i = 0; i < tokens.size(); i++) {
        std::cout << std::any_cast<std::string>(tokens.at(i).toString()) << std::endl;
    }
    return;
}


void debugNumbers() {
    std::string source = "123 45.67";
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.ScanTokens();
    for (int i = 0; i < tokens.size(); i++) {
        std::cout << std::any_cast<std::string>(tokens.at(i).toString()) << std::endl;
    }    
    return;
}


void debugStrings() {
    std::string source_ = "\"Hello, World!\" \"Another string\"";
    Scanner scanner(source_);
    std::vector<Token> tokens = scanner.ScanTokens();
    std::cout << FINAL(tokens[0].getLexeme())tokens[0].getLexeme() << std::endl;
    return;
}

// Test scanning of comments
void debugComments() {
    std::string source = "// This is a comment\nvar x = 5;";
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.ScanTokens();
    for (int i = 0; i < tokens.size(); i++) {
        std::cout << std::any_cast<std::string>(tokens.at(i).toString()) << std::endl;
    }    
}

// Test error handling (e.g., unterminated string)
void debugUnterminatedString() {
    std::string source_ = "\"This string never ends";
    Scanner scanner(source_);
    std::vector<Token> tokens = scanner.ScanTokens();
    for (int i = 0; i < tokens.size(); i++) {
        std::cout << std::any_cast<std::string>(tokens.at(i).toString()) << std::endl;
    }
    return;
}

// Test a complex case combining multiple elements
void debugComplexCase() {
    std::string source = "if (x == 10) { print \"Hello\"; } // End of line";
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.ScanTokens();
    for (int i = 0; i < tokens.size(); i++) {
        std::cout << std::any_cast<std::string>(tokens.at(i).toString()) << std::endl;
        //std::cout << tokens.at(i).toString() << std::endl;
    }    
}

// Driver Code
int main(void) {
    //debugConstructor();
    debugSingleCharacterTokens();
    //debugDoubleCharacterTokens();
    //debugKeywords();
    //debugIdentifiers();
    //debugNumbers();
    debugStrings();
    //debugComments();
    //debugUnterminatedString();
    //debugComplexCase();    
    return 0;
}
