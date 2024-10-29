#include <scanner.h>
#include <parser.h>
#include <interpreter.h>
#include <environment.h>


int main(int argc, char **argv) {
    Scanner scanner("(((34 + 15) * -2) - (-12 / (3 + 1))) + ((45 * 2) / 3)");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    p.beginParse();
    interpreter interp(cTree);
    std::cout << evaluatedExpressions[evaluatedExpressions.size() - 1] << std::endl;
    return 0;
}
