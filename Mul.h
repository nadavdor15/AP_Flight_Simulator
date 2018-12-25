#ifndef MUL_H
#define MUL_H

#include "BinaryExpression.h"

using namespace std;

class Mul : public BinaryExpression {
public:
    Mul(Expression& left_expression,
          Expression& right_expression):
          BinaryExpression(left_expression, right_expression) {}

    double calculate(vector<string>& arguments, int index) {
        return _left_expression.calculate(arguments, index) *
               _right_expression.calculate(arguments, index);
    }
};

#endif //	!MUL_H