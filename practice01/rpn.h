#ifndef PRACTICE01_RPN_H
#define PRACTICE01_RPN_H


#include "structures/stack.h"
#include <vector>
#include <string>
#include <unordered_map>

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <cmath>


/**
 * Split expression string to vector of tokens. Operators: + - * / ^ ( ) sin cos 0-9. WS-friendly
 * @param[in] str - The expression
 * @return vector<string> tokens
 */
std::vector<std::string> splitString(std::string str) {
    // Empty expression handler
    if (str.empty()) throw std::invalid_argument("Empty string");

    // Operators: + - * / ^ sin cos ( ) 0-9
    std::vector<std::string> tokens;
    char operators[7] = {'(', ')', '+', '-', '*', '/', '^'};

    // Remove whitespaces
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

    // Algorithm
    std::string number;  // Any number will be stored here
    for (size_t i = 0; i < str.size(); ++i) {
        char c = str[i];
        std::string s(1, c);  // Handle multiple char operators/operands (i.e. sin(), 123, etc.)

        // Digit found
        if (isdigit(c)) {
            number += c;
            continue;
        }

        // sin & cos operators
        if ((c == 's' || c == 'c') && i+2 < str.size()) {
            std::string substr = str.substr(i, 3);
            if (substr == "sin" || substr == "cos") tokens.push_back(substr); // Handle sin or cos
            else throw std::runtime_error("Unknown operator: " + substr);     // Handle wrong operator
            if (!number.empty()) {
                tokens.push_back(number);
                number.clear();
            }
            i += 2;
            continue;
        }

        // Single-char operators (look for char operators[8])
        if (std::find(std::begin(operators), std::end(operators), c) != std::end(operators)) {
            if (!number.empty()) {
                tokens.push_back(number);
                number.clear();
            }
            tokens.push_back(s);
            continue;
        }

        // Unknown symbol error
        throw std::runtime_error("Unknown symbol: " + s);
    }
    if (!number.empty()) tokens.push_back(number);
    return tokens;
}


/// toRPN() tool. Print the intermediate result and stack state
void printDebug(const std::vector<std::string> &result, const Stack &opStack, const std::vector<std::string> &tokens) {
    int size = 7;
    for (auto &op : tokens) if (op != "(" && op != ")") size += int(op.length()) + 1;
    std::cout << "Result: ";
    for (const std::string &token : result) {
        std::cout << token << ' ';
        size -= int(token.length()) + 1;
    }
    std::cout << std::setw(size) << "Stack: " << opStack << std::endl;
}


/**
 * Translates infix-form expression to the reverse polish-form
 * @param[in] expr - infix-form expression
 * @param[in] isDebugMode - print details of each operation if true
 * @return vector<string> tokens
 */
std::vector<std::string> toRPN(const std::string& expr, bool isDebugMode = false) {
    std::vector<std::string> result;

    // Auxiliary vars
    Stack opStack;                                          // Store unused expressions
    std::vector<std::string> tokens = splitString(expr);    // [expr] reform to the token-form
    std::unordered_map<std::string, int> precedences {      // Operands priority map
            {"+", 1}, {"-", 1},
            {"*", 2}, {"/", 2},
            {"^", 3},
            {"sin", 4}, {"cos", 4}
    };

    if (isDebugMode) std::cout << "Translating to RPN...\n";

    for (std::string token : tokens) {

        // Number: Add to result
        if (isdigit(token[0])) {
            result.push_back(token);
        }
        // Open brace: Add to stack
        else if (token == "(") {
            opStack.push(token);
        }
        // Close brace: Read stack while ( not found
        else if (token == ")") {
            while (*opStack.top() != "(") result.push_back(opStack.pop());
            if (opStack.isEmpty()) throw std::runtime_error("Unclosed brace");  // Error handler
            opStack.pop(); // Delete open brace
        }
        // Operators (look for map<string, int> precedences)
        else if (precedences.count(token) > 0) {
            while (!opStack.isEmpty() && *opStack.top() != "(" && precedences[token] <= precedences[*opStack.top()])
                result.push_back(opStack.pop());
            opStack.push(token);
        }
        // Invalid syntax
        else {
            throw std::runtime_error("Invalid syntax: " + token);
        }

        if (isDebugMode) printDebug(result, opStack, tokens);
    }

    // Push back remaining operators
    while (!opStack.isEmpty()) {
        if (*opStack.top() == "(") throw std::runtime_error("Unclosed brace");
        result.push_back(opStack.pop());
        if (isDebugMode) printDebug(result, opStack, tokens);
    }

    return result;
}


/**
 * Simply do the maths (+ - * / ^ sin cos)
 * @param[in] op - Operator
 * @param[in] a - 1st operand
 * @param[in] b - 2nd operand (may be anything if calculating sin/cos. careful)
 * @return math result
 */
double calculate(std::string op, double a, double b) {
    switch (op[0]) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': {
            if (b == 0)
                throw std::runtime_error("Division by zero: " + std::to_string(a) + " / " + std::to_string(b));
            return a / b;
        }
        case '^': return pow(a, b);
        case 's': return sin(a);
        case 'c': return cos(a);
        default: throw std::invalid_argument("Wrong operator: " + op);
    }
}


/**
 * Get tokens of expression and return [double] result
 * @param[in] expr - vector<string> tokens
 * @param[in] isDebugMode - print each operation details if true
 * @return math result
 */
double evaluate(const std::vector<std::string>& expr, bool isDebugMode = false) {
    Stack opStack;
    for (std::string token : expr) {
        if (isdigit(token[0])) {
            opStack.push(token);
            if (isDebugMode)
                std::cout << "Number found. \tStack: " << opStack << std::endl;
        } else {
            if (token != "sin" && token != "cos" && opStack.getSize() < 2)
                throw std::runtime_error("Nothing to calculate");

            // Calculate. If statement exist because of sin & cos take one arg
            std::string calc;
            double op2 = std::stod(opStack.pop());
            double op1;
            if (token == "sin" || token == "cos") {
                calc = std::to_string(calculate(token, op2, 0));
            } else {
                op1 = std::stod(opStack.pop());
                calc = std::to_string(calculate(token, op1, op2));
            }

            opStack.push(calc);
            if (isDebugMode)
                std::cout << "Evaluate " << op1 << token << op2 << ". \tStack: " << opStack << std::endl;
        }
    }
    return std::stod(opStack.pop());
}

#endif //PRACTICE01_RPN_H