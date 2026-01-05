package com.staticanalyzer;

import com.github.javaparser.ast.body.MethodDeclaration;
import com.github.javaparser.ast.body.VariableDeclarator;
import com.github.javaparser.ast.expr.BinaryExpr;
import com.github.javaparser.ast.expr.NameExpr;
import com.github.javaparser.ast.stmt.*;
import com.github.javaparser.ast.visitor.VoidVisitorAdapter;

import java.util.HashMap;
import java.util.Map;

public class ComplexityVisitor extends VoidVisitorAdapter<Void> {
    
    // Metrics
    public int cyclomaticComplexity = 1; // Base complexity
    public int maxNestingDepth = 0;
    public int currentDepth = 0;
    
    // Void Scanner
    private Map<String, Boolean> variables = new HashMap<>();

    @Override
    public void visit(IfStmt n, Void arg) {
        cyclomaticComplexity++;
        super.visit(n, arg);
    }

    @Override
    public void visit(ForStmt n, Void arg) {
        cyclomaticComplexity++;
        super.visit(n, arg);
    }

    @Override
    public void visit(ForEachStmt n, Void arg) {
        cyclomaticComplexity++;
        super.visit(n, arg);
    }

    @Override
    public void visit(WhileStmt n, Void arg) {
        cyclomaticComplexity++;
        super.visit(n, arg);
    }

    @Override
    public void visit(SwitchStmt n, Void arg) {
        // Each case increases complexity
        cyclomaticComplexity += n.getEntries().size();
        super.visit(n, arg);
    }
    
    @Override
    public void visit(CatchClause n, Void arg) {
        cyclomaticComplexity++;
        super.visit(n, arg);
    }
    
    @Override
    public void visit(BinaryExpr n, Void arg) {
        if (n.getOperator() == BinaryExpr.Operator.AND || n.getOperator() == BinaryExpr.Operator.OR) {
            cyclomaticComplexity++;
        }
        super.visit(n, arg);
    }

    // Nesting
    @Override
    public void visit(BlockStmt n, Void arg) {
        currentDepth++;
        if (currentDepth > maxNestingDepth) {
            maxNestingDepth = currentDepth;
        }
        super.visit(n, arg);
        currentDepth--;
    }

    // Void Scanner
    @Override
    public void visit(VariableDeclarator n, Void arg) {
        variables.put(n.getNameAsString(), false); // Declared, likely unused
        super.visit(n, arg);
    }

    @Override
    public void visit(NameExpr n, Void arg) {
        if (variables.containsKey(n.getNameAsString())) {
            variables.put(n.getNameAsString(), true); // Used
        }
        super.visit(n, arg);
    }
    
    public int getUnusedVariableCount() {
        return (int) variables.values().stream().filter(used -> !used).count();
    }
}
