#ifndef DIV_H
#define DIV_H

#include "BinaryExpression.h"

using namespace std;

class Div : public BinaryExpression {
public:
    Div(Expression& left_expression,
          Expression& right_expression):
          BinaryExpression(left_expression, right_expression) {}

    double calculate(vector<string>& arguments, int index) {
    	double right = _right_expression.calculate(arguments, index);
    	if (right == 0)
    		throw "Cannot divide by zero!";
        return _left_expression.calculate(arguments, index) /
               right;
    }
};

#endif  //  !DIV_H