#ifndef PLUS_H
#define PLUS_H


#include "BinaryExpression.h"

using namespace std;

class Plus : public BinaryExpression {
public:
    Plus(Expression& left_expression,
          Expression& right_expression):
          BinaryExpression(left_expression, right_expression) {}

    double calculate(vector<string>& arguments, int index) {
        return _left_expression.calculate(arguments, index) +
               _right_expression.calculate(arguments, index);
    }
};

#endif	//	!PLUS_H