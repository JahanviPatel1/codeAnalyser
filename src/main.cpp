#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Lexer.hpp"
#include "Parser.hpp"
#include "DebugPrinter.hpp"
#include "Analyzer.hpp"

int main(int argc, char* argv[]) {
    std::cout << ">>> 8-BIT STATIC ANALYZER ONLINE <<<" << std::endl;
    std::cout << "System: C++ Custom Engine" << std::endl;
    
    if (argc < 2) {
        std::cout << "Usage: ./analyzer <source_file>" << std::endl;
        return 1;
    }

    std::string filepath = argv[1];
    std::cout << "Target Locked: " << filepath << std::endl;

    // Read file
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filepath << std::endl;
        return 1;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();
    
    // Lexer Phase
    std::cout << "\n[PHASE 1] Initializing Grinder (Lexer)..." << std::endl;
    Lexer lexer(source);
    std::vector<Token> tokens = lexer.tokenize();
    std::cout << ">> Tokens: " << tokens.size() << std::endl;
    
    // Parser Phase
    std::cout << "\n[PHASE 2] Constructing AST (Parser)..." << std::endl;
    Parser parser(tokens);
    auto program = parser.parse();
    
    // Debug Print
    // std::cout << ">> AST Structure:" << std::endl;
    // DebugPrinter printer;
    // program->accept(printer);
    
    // Analysis Phase
    std::cout << "\n[PHASE 3] Analyzing Complexity..." << std::endl;
    Analyzer analyzer;
    program->accept(analyzer);
    Metrics m = analyzer.getMetrics();
    
    std::cout << "\n" << std::endl;
    std::cout << "===========================================" << std::endl;
    std::cout << "||        COMPLEXITY REPORT CARD         ||" << std::endl;
    std::cout << "===========================================" << std::endl;
    std::cout << "|| [CYCLOMATIC COMPLEXITY] : " << m.cyclomaticComplexity << "           ||" << std::endl;
    std::cout << "|| [MAX NESTING DEPTH]     : " << m.maxNestingDepth << "           ||" << std::endl;
    std::cout << "|| [UNUSED VARIABLES]      : " << m.unusedVariables << "           ||" << std::endl;
    std::cout << "===========================================" << std::endl;
    
    if (m.maxNestingDepth > 3) {
        std::cout << "!! WARNING: NESTING MONSTER DETECTED !!" << std::endl;
    }

    return 0;
}
