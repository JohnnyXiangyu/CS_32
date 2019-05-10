#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

int evaluate(string infix, string& postfix, bool& result);
// Evaluates a boolean expression
//   If infix is a syntactically valid infix boolean expression,
//   then set postfix to the postfix form of that expression, set
//   result to the value of the expression, and return zero.  If
//   infix is not a syntactically valid expression, return 1; in
//   that case, postfix may or may not be changed, but result must.
//   be unchanged.

int evaluate(string infix, string& postfix, bool& result) {
	stack<char> operators;
	postfix = "";
	char prev;
	bool starting = true;

	//no idiotic empty input
	if (infix == "")
		return 1;

	//converting from infix to post fix
	for (unsigned int i = 0; i < infix.length(); i++) {
		char current = infix[i];
		if (current == ' ')
			continue;
		switch (current) {
		case 'T':
		case 'F':
			//if operand is repeaded, invalid input
			if (!starting && (prev == 'T' || prev == 'F' || prev == ')'))
				return 1;
			postfix += current;
			break;

		case '&':
			//if operator is repeaded it's invalid input
			if (!starting && (prev == '!' || prev == '^' || prev == '&' || prev == '(')) {
				return 1;
				break;
			}
			else if (!operators.empty() && (operators.top() == '&' || operators.top() == '!')) {
				//if & is slower
				while (!operators.empty() && operators.top() != '(' && operators.top() != '^') {
					postfix += operators.top();
					operators.pop();
				}
			}
			operators.push('&');
			break;

		case '^':
			//if operator is repeaded it's invalid input
			if (!starting && (prev == '!' || prev == '^' || prev == '&' || prev == '('))
				return 1;
			while (!operators.empty() && operators.top() != '(') {
				postfix += operators.top();
				operators.pop();
			}
			operators.push('^');
			break;
		
		case '!':
			//! can't go after a letter or a )
			if (!starting && (prev == 'T' || prev == 'F' || prev == ')'))
				return 1;
			operators.push('!');
			break;

		case '(':
			//there must be a operator preceding (
			if (!starting && (prev == 'T' || prev == 'F' || prev == ')'))
				return 1;
			operators.push('(');
			break;

		case ')':
			//(can't be empty)
			if (starting || prev == '(')
				return 1;
			while (!operators.empty() && operators.top() != '(') {
				postfix += operators.top();
				operators.pop();
			}
			if (operators.empty()) //there's no ( for a ) is not allowed
				return 1;
			else
				operators.pop();
			break;

		case ' ':
			//spaces are allowed
			break;

		default:
			//any unexpected input are rightfully invalid
			return 1;
			break;
		}
		prev = current;
		starting = false;
	}
	//then clear the remaining stack
	while (!operators.empty()) {
		//should no ( be left in the stack
		if (operators.top() == '(')
			return 1;
		postfix += operators.top();
		operators.pop();
	}

	//the resulting postfix notation must not contain only spaces
	bool empty = true;
	for (int i = 0; i < postfix.length(); i++) {
		if (postfix[i] != ' ')
			empty = false;
	}
	if (empty)
		return 1;

	//reading postfix
	stack<char> operands;
	for (int i = 0; i < postfix.length(); i++) {
		char current = postfix[i];
		char sec, first;
		switch (current) {
		case 'T':
		case 'F':
			operands.push(current);
			break;

		case '&':
			if (operands.size() < 2)
				return 1; //there must be stuff to compute
			sec = operands.top();
			operands.pop();
			first = operands.top();
			operands.pop();
			if (sec == 'F' || first == 'F')
				operands.push('F');
			else if (sec == first && first == 'T')
				operands.push('T');
			break;

		case '^':
			if (operands.size() < 2)
				return 1; //there must be stuff to compute
			sec = operands.top();
			operands.pop();
			first = operands.top();
			operands.pop();
			if (sec != first)
				operands.push('T');
			else
				operands.push('F');
			break;

		case '!':
			if (operands.size() < 1)
				return 1; //there must be at least one item to reverse
			char reversed = operands.top();
			operands.pop();
			if (reversed == 'T')
				operands.push('F');
			else
				operands.push('T');
			break;
		}
	}
	//after everything is done there should be only one left
	assert(operands.size() == 1);
	assert(operands.top() == 'T' || operands.top() == 'F');
	//and now we do something to it
	result = (operands.top() == 'T');


	return 0; //if nothing went wrong
}

void defaultTest();
void correctTest();
void incorrectTest();
void extraTest();
void debrahTest();

int main()
{
	defaultTest();
	correctTest();
	incorrectTest();
	extraTest();
	debrahTest();

	cout << "PASS." << endl;

	return 0;
}

void defaultTest() {
	string pf;
	bool answer;
	assert(evaluate("T^ F", pf, answer) == 0 && pf == "TF^"  &&  answer);
	assert(evaluate("T^", pf, answer) == 1);
	assert(evaluate("F F", pf, answer) == 1);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("()", pf, answer) == 1);
	assert(evaluate("()T", pf, answer) == 1);
	assert(evaluate("T(F^T)", pf, answer) == 1);
	assert(evaluate("T(&T)", pf, answer) == 1);
	assert(evaluate("(T&(F^F)", pf, answer) == 1);
	assert(evaluate("T|F", pf, answer) == 1);
	assert(evaluate("", pf, answer) == 1);
	assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0 && pf == "FF!TF&&^" && !answer);
	assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("((T))", pf, answer) == 0 && pf == "T"  &&  answer);
	cout << "Passed all default tests" << endl;
}

void correctTest() {
	string pf;
	bool answer;
	assert(evaluate("T^ F", pf, answer) == 0 && pf == "TF^"  &&  answer);
	assert(evaluate("T^(F)", pf, answer) == 0 && pf == "TF^"  &&  answer);
	assert(evaluate("T ^ !F", pf, answer) == 0 && pf == "TF!^"  &&  !answer);
	assert(evaluate("!(T&F)", pf, answer) == 0 && pf == "TF&!"  &&  answer);
	assert(evaluate("!T&F", pf, answer) == 0 && pf == "T!F&"  &&  !answer);
	assert(evaluate("T^F&F", pf, answer) == 0 && pf == "TFF&^"  &&  answer);
	assert(evaluate("T&!(F^T&T^F)^!!!(F&T&F)", pf, answer) == 0 && pf == "TFTT&^F^!&FT&F&!!!^"  &&  answer);

	cout << "Passed all correct-input tests." << endl;
}

void incorrectTest() {
	string pf;
	bool answer;
	assert(evaluate("T^", pf, answer) == 1);
	assert(evaluate("T&!F", pf, answer) == 0);
	assert(evaluate("T^!!F", pf, answer) == 0);
	assert(evaluate("T&(^F)", pf, answer) == 1);
	assert(evaluate("T&^F", pf, answer) == 1); 
	assert(evaluate("T^(FF)", pf, answer) == 1);
	assert(evaluate("T&!(F^T&T^F)^!!!(F&T&FF)", pf, answer) == 1);
	assert(evaluate("T&!T(F^T&T^F)^!!!(F&T&F)", pf, answer) == 1);
	assert(evaluate("T&!(F^T&T^F)F^!!!(F&T&F)", pf, answer) == 1);
	assert(evaluate("T&(!F", pf, answer) == 1);
	assert(evaluate("T&!F)", pf, answer) == 1);
	assert(evaluate("T&(!F))", pf, answer) == 1);

	cout << "Passed all incorect-input tests." << endl;
}

void extraTest() {
	string pf;
	bool answer;
	assert(evaluate("T^ F", pf, answer) == 0 && pf == "TF^"  &&  answer);
	assert(evaluate("T^", pf, answer) == 1);
	assert(evaluate("F F", pf, answer) == 1);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("()", pf, answer) == 1);
	assert(evaluate("()T", pf, answer) == 1);
	assert(evaluate("T(F^T)", pf, answer) == 1);
	assert(evaluate("T(&T)", pf, answer) == 1);
	assert(evaluate("(T&(F^F)", pf, answer) == 1);
	assert(evaluate("T|F", pf, answer) == 1);
	assert(evaluate("", pf, answer) == 1);
	assert(evaluate("(!!!!)&F", pf, answer) == 1);
	assert(evaluate("(!!!!F&F)", pf, answer) == 0 && pf == "F!!!!F&" && !answer);
	assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0
		&& pf == "FF!TF&&^" && !answer);
	assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("((T))", pf, answer) == 0 && pf == "T"  &&  answer);
	assert(evaluate(" (!F  & T)& !F  ", pf, answer) == 0 && pf == "F!T&F!&" && answer);
	assert(evaluate("T", pf, answer) == 0 && pf == "T" && answer);
	assert(evaluate("(F)", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("T^(F) ", pf, answer) == 0 && pf == "TF^" && answer);
	assert(evaluate("T ^ !F", pf, answer) == 0 && pf == "TF!^" && !answer);
	assert(evaluate("!(T&F) ", pf, answer) == 0 && pf == "TF&!" && answer);
	assert(evaluate("!T&F", pf, answer) == 0 && pf == "T!F&" && !answer);
	assert(evaluate("T^F&F", pf, answer) == 0 && pf == "TFF&^" && answer);
	assert(evaluate("T&!(F^T&T^F)^!!!(F&T&F)", pf, answer) == 0 && pf == "TFTT&^F^!&FT&F&!!!^" && answer);
	assert(evaluate("(T^F&F)^T&!F&!!!!!!F", pf, answer) == 0 && pf == "TFF&^TF!&F!!!!!!&^" && answer);
	cout << "Passed all tests" << endl;
}

void debrahTest() {
	string pf;
	bool answer;
	assert(evaluate("T^ F", pf, answer) == 0 && pf == "TF^"  &&  answer);
	assert(evaluate("T^", pf, answer) == 1);
	assert(evaluate("F F", pf, answer) == 1);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("()", pf, answer) == 1);
	assert(evaluate("()T", pf, answer) == 1);
	assert(evaluate("T(F^T)", pf, answer) == 1);
	assert(evaluate("T(&T)", pf, answer) == 1);
	assert(evaluate("(T&(F^F)", pf, answer) == 1);
	assert(evaluate("T|F", pf, answer) == 1);
	assert(evaluate("", pf, answer) == 1);
	assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0
		&& pf == "FF!TF&&^" && !answer);
	assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("((T))", pf, answer) == 0 && pf == "T"  &&  answer);
	assert(evaluate("T", pf, answer) == 0 && pf == "T" && answer);
	assert(evaluate("(F)", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("T^(F)", pf, answer) == 0 && pf == "TF^" && answer);
	assert(evaluate("T ^ !F", pf, answer) == 0 && pf == "TF!^" && !answer);
	assert(evaluate("!(T&F)", pf, answer) == 0 && pf == "TF&!" && answer);
	assert(evaluate("!T&F ", pf, answer) == 0 && pf == "T!F&" && !answer);
	assert(evaluate("T^F&F ", pf, answer) == 0 && pf == "TFF&^" && answer);
	assert(evaluate("T&!(F^T&T^F)^!!!(F&T&F)", pf, answer) == 0 && answer);
	assert(evaluate("T", pf, answer) == 0 && answer);
	assert(evaluate("F", pf, answer) == 0 && !answer);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("T&", pf, answer) == 1);
	assert(evaluate("T)", pf, answer) == 1);
	assert(evaluate("T(", pf, answer) == 1);
	assert(evaluate("T!", pf, answer) == 1);
	assert(evaluate("!T", pf, answer) == 0);
	cout << pf << endl;
	assert(evaluate(" T ", pf, answer) == 0);
	cout << pf << endl;
	assert(evaluate("T ", pf, answer) == 0);
	cout << pf << endl;
	assert(evaluate(" T", pf, answer) == 0);
	cout << pf << endl;
	assert(evaluate("!T&", pf, answer) == 1);
	assert(evaluate("!T^", pf, answer) == 1);
	assert(evaluate("!T)", pf, answer) == 1);
	assert(evaluate("!T(", pf, answer) == 1);
	assert(evaluate("!T^", pf, answer) == 1);
	string letters[9] = { "T", "F", "^", "&", "!", "(", ")"," ","" };
	string test;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int k = 0; k < 9; k++)
			{
				test = letters[i] + letters[j] + letters[k];

				if (evaluate(test, pf, answer) == 1)
					;
				else
					cout << "correct:" << pf << endl;
			}
		}
	}
	
	
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			for (int k = 0; k < 9; k++) {
				for (int l = 0; l < 9; l++) {
					for (int b = 0; b < 9; b++) {
						for (int c = 0; c < 9; c++) {
							for (int x = 0; x < 9; x++) {
								for (int z = 0; z < 9; z++) {
									evaluate(letters[i] + letters[j] + letters[k] + letters[l] + letters[b] + letters[c] + letters[x] + letters[z], pf, answer);
								}
							}
						}
					}
				}
			}
		}
	}
	assert(evaluate("T&T", pf, answer) == 0 && pf == "TT&" && answer);
	assert(evaluate("T&F", pf, answer) == 0 && pf == "TF&" && !answer);


	cout << "Passed all tests from Debrah." << endl;
}