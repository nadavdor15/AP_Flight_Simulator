#ifndef MINUS_H
#define MINUS_H

#include <iostream>
#include "BinaryExpression.h"

using namespace std;

class Minus : public BinaryExpression {
public:
    Minus(Expression& left_expression,
          Expression& right_expression):
          BinaryExpression(left_expression, right_expression) {}

    double calculate(vector<string>& arguments, int index) {
        return _left_expression.calculate(arguments, index) -
               _right_expression.calculate(arguments, index);
    }
};

#endif	//	!MINUS_H