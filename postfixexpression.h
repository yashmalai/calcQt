#ifndef POSTFIXEXPRESSION_H
#define POSTFIXEXPRESSION_H

#include <QString>

class PostfixExpression
{
public:
    PostfixExpression();
    PostfixExpression(QString expr);

    bool fromInfix(QString expr);
    bool solve(double& out);
    QString toString();
private:
    QString expr;

    int opPrecedence(QChar op);
    bool isOperand(QChar op);
    QString fixNegationsAndMult(QString infixExpr);
};

#endif // POSTFIXEXPRESSION_H
