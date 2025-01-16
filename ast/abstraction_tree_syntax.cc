#include <abstraction_tree_syntax.h>

/** -----------------------------------------------------------------------------------------
 * @brief The default constructor that calls in generateAst to start creating the .txt file 
 * 
 * @param expr: The data structure that represents the compacted abstraction syntax tree 
 * -----------------------------------------------------------------------------------------
*/
AbstractionTreeSyntax::ast::ast(Vector<ContextFreeGrammar::Statement*> stmt) noexcept {
    String stringTree = gA.buildTree(stmt);
    gA.formatAst(stringTree);
}
/** ------------------------------------
 * @brief A simple method that creates the ast tree  
 * 
 * @details It iterates through a vector visiting each node to form the abstraction syntax tree
 * 
 * --------------------------------------
*/
String AbstractionTreeSyntax::ast::buildTree(Vector<ContextFreeGrammar::Statement*> stmt) {
    for (const auto it: stmt) {
        if (auto stmt = dynamic_cast<ContextFreeGrammar::Statement*>(it))
            outputDir_ += std::any_cast<String>(it->accept(stmt));
    }
    return outputDir_;
}
/** ----------------------------------------------
 * 
 * @brief formats outputDir_ string that will represent an ast
 * 
 * -----------------------------------------------
*/
void AbstractionTreeSyntax::ast::streamOutAst(String res) {
    try {
        std::filesystem::path filePath = "Ast.txt";
        std::ofstream fAst(filePath, std::ios::out | std::ios::trunc);
        if (!fAst.is_open()) {
            std::cerr << "Failed to open file: " << filePath << std::endl;
            return;
        }
        fAst << res;
        fAst.flush();  // Ensure all data is written
        fAst.close();
        if (fAst.fail()) { std::cerr << "Error occurred while writing to file: " << filePath << std::endl;
        } else { std::cout << "Successfully wrote to file: " << filePath << std::endl; }
    } catch (const std::exception& e) { std::cerr << "Exception occurred: " << e.what() << std::endl; }
    return;
}