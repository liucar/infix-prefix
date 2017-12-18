/*
 * @author Caroline Liu
 * @date 9/24/17
 * @course CSCI 61
 * @file Liu_HW01.cpp
 *
 * A program that asks the user to enter a math expression in infix
 * or prefix notation, converts it to the other notation, and prints
 * out the result. The program will run until the user enters 'x' to
 * quit.
 */

#include <iostream>   // For cout, cin
#include <stack>     // For stack, push, pop, top
#include <string>   // For string
#include <cctype>  // For isdigit

using namespace std;

/* Determines whether a character is an operator.
 * @param a symbol of type char
 * @return returns true if character is an operator
 */
bool isOperator(char sym)
{
    return ( sym == '+' ||
             sym == '-' ||
             sym == '*' ||
             sym == '/' ||
             sym == '^' ||
             sym == '(' ||
             sym == ')' );
}

/* Determines order of precedence for different math symbols.
 * @param a math symbol of type char
 * @return returns an integer value corresponding to precedence (the
 * higher the value, the higher the precedence)
 */
int preced(char sym)
{
    switch(sym)
    {
        case '+':
        case '-':
            return 0;
        case '*':
        case '/':
            return 1;
        case '^':
            return 2;
        case '(':
        case ')':
            return 3;
        default:
            return -1; // Should never execute
    }
}

/* Converts an expression from prefix form to infix form and prints
 * the result.
 * @param a prefix expression as a string
 * @return none
 */
void prefixToInfix(string prefix)
{
    stack <string> infix_stack;  // Output
    string  first_op,  // First operand
            sec_op,    // Second operand
            input_str, // Char input from prefix saved as a string
            sub_expr;  // Sub expression with parentheses


    // Scan from right to left
    for (int i = prefix.length() - 1; i >= 0; i--) {

        input_str = prefix[i];

        // If the character is a number, push onto infix stack
        if (isdigit(prefix[i])) infix_stack.push(input_str);

        // If the character is an operator
        else if (isOperator(prefix[i])) {

            // Set first and second operands
            first_op = infix_stack.top();
            infix_stack.pop();
            sec_op = infix_stack.top();
            infix_stack.pop();

            // Form sub expression with parentheses and operands
            sub_expr = "(" + first_op + input_str + sec_op + ")";

            // Push sub expression onto infix stack
            infix_stack.push(sub_expr);
        }
    }

    // Print result (should only have one item)
    while(!infix_stack.empty()) {
        cout << infix_stack.top();
        infix_stack.pop();
    }
}

/* Converts an expression from infix form to prefix form and prints
 * the result.
 * @param an infix expression as a string
 * @return none
 */
void infixToPrefix(string infix)
{
    stack <char> prefix_stack;  // Output
    stack <char> oprtr_stack;   // Operator tracker
    char input;  // Character from infix being read in

    // Scan from right to left
    for (int i = infix.length() - 1; i >= 0; i--) {

        input = infix[i];

        // If the character is a number, push to prefix stack
        if (isdigit(input)) prefix_stack.push(input);

        // If the character is an operator
        else if (isOperator(input)) {

            // Parenthetical expression handler:
            // If input is a left parenthesis, push each stored
            // operator from the operator stack onto prefix stack,
            // popping each from the operator stack after every push,
            // until a right parenthesis is reached in operator stack
            if (input == '(') {
                while (oprtr_stack.top() != ')') {
                    prefix_stack.push(oprtr_stack.top());
                    oprtr_stack.pop();
                }
                oprtr_stack.pop();   // Pop right parenthesis

            // Order of operations handler:
            // If precedence of the input operator is less than the
            // precedence of the previous stored operator, excluding
            // a right parenthesis, then push the previous operator
            // onto the prefix stack, pop it from operator stack,
            // then push the new operator onto the operator stack
            } else if (!oprtr_stack.empty() &&
                       preced(input) < preced(oprtr_stack.top()) &&
                       oprtr_stack.top() != ')') {
                prefix_stack.push(oprtr_stack.top());
                oprtr_stack.pop();
                oprtr_stack.push(input);

            // Otherwise, push operator onto operator stack
            } else {
                oprtr_stack.push(input);
            }
        }
    }

    // Push remaining operators onto prefix stack
    while (!oprtr_stack.empty()) {
        prefix_stack.push(oprtr_stack.top());
        oprtr_stack.pop();
    }

    // Print result
    while(!prefix_stack.empty()) {
        cout << prefix_stack.top();
        prefix_stack.pop();
    }
}

int main()
{
    string user_input;
    char first_char;

    cout << "Enter a mathematical expression "
            "in either infix or prefix notation ('x' to quit): ";

    cin >> user_input;
    first_char = user_input[0];

    // Sentinel-controlled loop, with 'x' to exit
    while (first_char != 'x') {

        // Assume user will correctly enter infix or prefix expression
        if (isdigit(first_char) || first_char == '(') {
            cout << "The prefix notation is: ";
            infixToPrefix(user_input);
        } else {
            cout << "The infix notation is: ";
            prefixToInfix(user_input);
        }

        cout << "\n\nEnter a mathematical expression "
                "in either infix or prefix notation ('x' to quit): ";

        cin >> user_input;
        first_char = user_input[0];
    }

    return 0;
}