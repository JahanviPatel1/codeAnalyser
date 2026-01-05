package com.staticanalyzer;

import com.github.javaparser.StaticJavaParser;
import com.github.javaparser.ast.CompilationUnit;

import java.io.File;
import java.io.IOException;

public class AnalyzerMain {
    public static void main(String[] args) {
        System.out.println(">>> 8-BIT STATIC ANALYZER (JAVA CORE) <<<");
        
        if (args.length < 1) {
            System.out.println("Usage: gradle run --args='<source_file>'");
            return;
        }
        
        String filePath = args[0];
        System.out.println("Target Locked: " + filePath);
        
        try {
            // Parse
            System.out.println("\n[PHASE 1] Initializing JavaParser...");
            CompilationUnit cu = StaticJavaParser.parse(new File(filePath));
            
            // Analyze
            System.out.println("\n[PHASE 2] Analyzing Complexity...");
            ComplexityVisitor visitor = new ComplexityVisitor();
            visitor.visit(cu, null);
            
            // Report
            printReport(visitor);
            
        } catch (IOException e) {
            System.err.println("CRITICAL ERROR: " + e.getMessage());
        }
    }
    
    private static void printReport(ComplexityVisitor v) {
        System.out.println("\n");
        System.out.println("===========================================");
        System.out.println("||        COMPLEXITY REPORT CARD         ||");
        System.out.println("===========================================");
        System.out.println(String.format("|| [CYCLOMATIC COMPLEXITY] : %-11d ||", v.cyclomaticComplexity));
        System.out.println(String.format("|| [MAX NESTING DEPTH]     : %-11d ||", v.maxNestingDepth));
        System.out.println(String.format("|| [UNUSED VARIABLES]      : %-11d ||", v.getUnusedVariableCount()));
        System.out.println("===========================================");
        
        if (v.maxNestingDepth > 3) {
            System.out.println("!! WARNING: NESTING MONSTER DETECTED !!");
        }
    }
}
