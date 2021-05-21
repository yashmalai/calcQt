#include <stack>
#include <math.h>
#include "postfixexpression.h"

PostfixExpression::PostfixExpression() : expr("")
{
}

PostfixExpression::PostfixExpression(QString expr) : expr(expr)
{
}


// Фикс унарного минуса и умножения рядом со скобкой: 2(3+4) в 2*(3+4)
QString PostfixExpression::fixNegationsAndMult(QString infixExpr)
{
    if (infixExpr.isEmpty())
        return infixExpr;

    int expLen = infixExpr.length();


    for (int i = 0; i < (expLen - 1); i++)
    {
        QChar curCh = infixExpr.at(i);
        QChar nextChar = infixExpr.at(i + 1);

        if (curCh == '-' && isOperand(nextChar))
        {
            int operandEnd = i + 1;

            while (operandEnd < expLen &&
                   isOperand(infixExpr.at(operandEnd)))
            {
                operandEnd++;
            }

            if (i == 0)
            {
                infixExpr.insert(operandEnd, ")");
                infixExpr.insert(i, "(0");
                i = operandEnd + 3;
            }
            else
            {
                QChar prevChar = infixExpr.at(i - 1);
                if (!isOperand(prevChar) && prevChar != ')')
                {
                    infixExpr.insert(operandEnd, ")");
                    infixExpr.insert(i, "(0");
                    i = operandEnd + 3;
                }
            }
        }
        else if (curCh == '(' && i > 0)
        {
            QChar prevChar = infixExpr.at(i - 1);

            if (isOperand(prevChar))
            {
                infixExpr.insert(i, '*');
                i++;
            }
        }
        else if (curCh == ')' && isOperand(nextChar))
        {

            infixExpr.insert(i + 1, '*');
            i++;

        }
        else if (curCh == ')' && nextChar == '(')
        {
            infixExpr.insert(i + 1, '*');
            i++;
        }

        expLen = infixExpr.length();
    }

    return infixExpr;
}


bool PostfixExpression::fromInfix(QString infixExpr)
{
    if (infixExpr.isEmpty())
    {
        this->expr = "";
        return true;
    }

    infixExpr = fixNegationsAndMult(infixExpr);

    QString newExp = "";
    std::stack<QChar> expStack;
    const QChar STACK_BASE = 'B';

    expStack.push(STACK_BASE);

    const int expLen = infixExpr.length();

    for (int i = 0; i < expLen; i++)
    {
        QChar curCh = infixExpr.at(i);

        if (isOperand(curCh))
        {
            bool usedPeriod = false;

            while (i < expLen && isOperand(curCh))
            {
                if (curCh == '.')
                {
                    if (usedPeriod) return false;
                    else usedPeriod = true;
                }

                newExp.append(curCh);

                i++;
                if (i < expLen) curCh = infixExpr.at(i);
            }

            newExp.append('|');
            i--;
        }
        else if (curCh == '(') {
            expStack.push('('); }
        else if (curCh == ')')
        {
            while (expStack.top() != STACK_BASE && expStack.top() != '(')
            {
                newExp.append(expStack.top());
                expStack.pop();
            }

            if (expStack.top() != '(') {
                return false; }
            else {
                expStack.pop();
            }
        }
        else
        {
            while (expStack.top() != STACK_BASE && opPrecedence(curCh) <= opPrecedence(expStack.top()))
            {
                newExp.append(expStack.top());
                expStack.pop();
            }
            expStack.push(curCh);
        }
    }

    while (expStack.top() != STACK_BASE)
    {
        newExp.append(expStack.top());
        expStack.pop();
    }

    this->expr = newExp;
    return true;
}
//совершение математических операций
bool PostfixExpression::solve(double& out)
{
    if (expr.isEmpty())
    {
        out = 0.0;
        return true;
    }

    std::stack<double> operandStack;

    const int expLen = expr.length();
    for (int i = 0; i < expLen; i++)
    {
        QChar curCh = expr.at(i);

        if (isOperand(curCh))
        {
            QString curOperand = "";

            while (curCh != '|')
            {
                if (i >= expLen || !isOperand(curCh)) return false;

                curOperand.append(curCh);
                i++;

                if (i < expLen) curCh = expr.at(i);
            }

            operandStack.push(curOperand.toDouble());
        }
        else
        {
            if (operandStack.size() < 2) return false;

            double op1 = operandStack.top();
            operandStack.pop();
            double op2 = operandStack.top();
            operandStack.pop();

            switch (curCh.unicode())
            {
                case '+':
                    operandStack.push(op2 + op1);
                    break;
                case '-':
                    operandStack.push(op2 - op1);
                    break;
                case '*':
                    operandStack.push(op2 * op1);
                    break;
                case '/':
                    if (op1 == 0) return false;
                    operandStack.push(op2 / op1);
                    break;
                case '^':
                    operandStack.push(pow(op2, op1));
                    break;
            }
        }
    }

    if (operandStack.empty() || operandStack.size() > 1) return false;

    out = operandStack.top();
    operandStack.pop();

    return true;
}

//приоритет действий
int PostfixExpression::opPrecedence(QChar op)
{
    if (op == '^') {
        return 3;
    }
    else if (op == '*' || op == '/') {
        return 2;
    }
    else if (op == '+' || op == '-') {
        return 1;
    }
    else
    {
        return -1;
    }
}

bool PostfixExpression::isOperand(QChar op)
{
    if (op >= '0' && op <= '9') return true;
    if (op == '.') return true;

    return false;
}

QString PostfixExpression::toString()
{
    return this->expr;
}

