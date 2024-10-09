#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <cctype>
#include <cmath>

using namespace std;

// Function to check the precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3; // Exponent has the highest precedence
    return 0;
}

// Function to perform arithmetic operations
double applyOperation(double a, double b, char op) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b != 0) return a / b;
            else {
                cout << "Error: Division by zero!" << endl;
                exit(1);
            }
        case '^': return pow(a, b); // Exponentiation handled here
        default: return 0;
    }
}

// Function to evaluate an expression in postfix notation
double evaluatePostfix(const string& postfix) {
    stack<double> values;
    istringstream iss(postfix);
    string token;

    while (iss >> token) {
        if (isdigit(token[0])) {
            values.push(stod(token));  // Convert string to double and push to stack
        } else {
            // Operator
            double val2 = values.top(); values.pop();
            double val1 = values.top(); values.pop();
            values.push(applyOperation(val1, val2, token[0]));
        }
    }

    return values.top();
}

// Function to insert spaces between operators and numbers
string insertSpaces(const string& expression) {
    string spacedExpression;
    for (char ch : expression) {
        if (isdigit(ch) || ch == '.') {
            spacedExpression += ch;
        } else {
            spacedExpression += ' ';
            spacedExpression += ch;
            spacedExpression += ' ';
        }
    }
    return spacedExpression;
}

// Function to convert infix expression to postfix (RPN) using the Shunting Yard algorithm
string infixToPostfix(const string& expression) {
    stack<char> operators;
    string postfix;
    istringstream iss(expression);
    string token;

    while (iss >> token) {
        if (isdigit(token[0])) {
            postfix += token + " ";  // If it's a number, add it to the postfix output
        } else if (token[0] == '(') {
            operators.push('(');
        } else if (token[0] == ')') {
            // Pop from stack until matching '(' is found
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                postfix += " ";
                operators.pop();
            }
            operators.pop();  // Remove '('
        } else {
            // Operator
            while (!operators.empty() && precedence(operators.top()) >= precedence(token[0])) {
                postfix += operators.top();
                postfix += " ";
                operators.pop();
            }
            operators.push(token[0]);
        }
    }

    // Pop all remaining operators from the stack
    while (!operators.empty()) {
        postfix += operators.top();
        postfix += " ";
        operators.pop();
    }

    return postfix;
}

int main() {
    string expression;

    while (true) {
        cout << "Enter an expression (enter 0 to quit): ";
        getline(cin, expression);

        // Exit if user enters '0'
        if (expression == "0") {
            break;
        }

        // Automatically insert spaces between numbers and operators
        string spacedExpression = insertSpaces(expression);

        // Convert infix to postfix
        string postfix = infixToPostfix(spacedExpression);

        // Evaluate postfix expression
        double result = evaluatePostfix(postfix);

        // Output result
        cout << "Result: " << result << endl;
    }

    cout << "Calculator terminated." << endl;

    return 0;
}
