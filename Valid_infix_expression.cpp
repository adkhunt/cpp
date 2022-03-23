#include<iostream>
#include<stack>

using namespace std;

bool is_operator(char ch){

	switch(ch){
		case '+':
		case '-':
		case '*':
		case '%':
			return true;
		default:
			return false;
	}
}

bool is_operand(char ch){

	if (ch >= '0' && ch <= '9'){
		return true;
	}
	return false;
}

string make_valid_expression(string expression){

	stack<string> operand_stack;
	stack<char> operator_stack;
	string final_result = "";

	for (int i = 0 ; i < expression.size() ; ++i){
		if (is_operator(expression[i])){
			operator_stack.push(expression[i]);
		} else if (is_operand(expression[i])){
			operand_stack.push(string(1, expression[i]));
		} else if (expression[i] == ')'){
			string first_operand = operand_stack.top();
			operand_stack.pop();
			string second_operand = operand_stack.top();
			operand_stack.pop();
			char operator_ = operator_stack.top();
			operator_stack.pop();
			final_result = "(" + second_operand + string(1, operator_) + first_operand + ")";
			operand_stack.push(final_result);
		} else{
			continue;
		}
	}

	return operand_stack.top();
}

int main(){

	string expression = "1 + 2) * 3 - 4) * 5 - 6)))";

	string valid_expression = make_valid_expression(expression);

	cout << "Valid Expression = " << valid_expression << endl;
	return 0;
}
