#include "AST.hpp"

// Dispatch implementations
void Block::accept(ASTVisitor& visitor) { visitor.visit(*this); }
void IfStatement::accept(ASTVisitor& visitor) { visitor.visit(*this); }
void WhileStatement::accept(ASTVisitor& visitor) { visitor.visit(*this); }
void ReturnStatement::accept(ASTVisitor& visitor) { visitor.visit(*this); }
void ExpressionStatement::accept(ASTVisitor& visitor) { visitor.visit(*this); }
void VariableDeclaration::accept(ASTVisitor& visitor) { visitor.visit(*this); }

void Literal::accept(ASTVisitor& visitor) { visitor.visit(*this); }
void BinaryExpression::accept(ASTVisitor& visitor) { visitor.visit(*this); }
void Identifier::accept(ASTVisitor& visitor) { visitor.visit(*this); }

void FunctionDeclaration::accept(ASTVisitor& visitor) { visitor.visit(*this); }
void Program::accept(ASTVisitor& visitor) { visitor.visit(*this); }
//tempcomment