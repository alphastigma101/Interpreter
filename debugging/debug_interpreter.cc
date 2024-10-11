#include <scanner.h>
#include <parser.h>
#include <interpreter.h> 


int main(int argc, char **argv) {

    Scanner scanner("((34 + 15) / (12 * 6))");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    p.beginParse();
    interpreter interp(cTree);
    return 0;
}
