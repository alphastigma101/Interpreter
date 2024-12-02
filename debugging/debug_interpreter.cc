#include <scanner.h>
#include <parser.h>
#include <interpreter.h> 


int main(int argc, char **argv) {
    //Scanner scanner("(((34 + 15) * -2) - (-12 / (3 + 1))) + ((45 * 2) / 3);");
    Scanner scanner("int x = (((34 + 15) * -2) - (-12 / (3 + 1))) + ((45 * 2) / 3);");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    interpreter interp(res);
    //std::cout << evaluatedExpressions[evaluatedExpressions.size() - 1] << std::endl;
    return 0;
}
