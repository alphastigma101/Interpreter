#include <scanner.h>
#include <parser.h>
#include <interpreter.h> 


int main(int argc, char **argv) {

    Scanner scanner("((34 + 15) / (12 * 6))");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    p.parse();
    interpreter interp(std::move(p.nodes), std::move(LanguageTokenTypes::Python));
    return 0;
}
