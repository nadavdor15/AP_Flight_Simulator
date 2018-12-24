#include "BinaryExpression.h"

using namespace std;

class Div : public BinaryExpression {
public:
    Div(Expression& right_expression,
          Expression& left_expression):
          BinaryExpression(right_expression, left_expression) {}

    double calculate(vector<string>& arguments, int index) {
    	double right = _right_expression.calculate(arguments, index);
    	if (right == 0)
    		throw "Cannot divide by zero!";
        return _left_expression.calculate(arguments, index) /
               right;
    }
};
