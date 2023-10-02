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


std::vector<std::string> splitString(std::string str, bool wsRemove = true) {
    if (str.empty()) throw std::invalid_argument("Empty string");

    std::vector<std::string> tokens;
    char operators[6] = {'(', ')', '+', '-', '*', '/'};

    if (wsRemove) str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    std::string number;
    for (char c : str) {
        std::string s(1, c);
        auto find = std::find(std::begin(operators), std::end(operators), c);
        if (c == ' ') {
            if (!number.empty()) {
                tokens.push_back(number);
                number.clear();
            }
        } else if ( find != std::end(operators)) { // Operator
            if (!number.empty()) {
                tokens.push_back(number);
                number.clear();
            }
            tokens.push_back(s);
        } else if (isdigit(c)) {                 // Number
            number += c;
        } else {                                 // Unknown symbol error
            throw std::runtime_error("Unknown symbol: " + s);
        }
    }
    if (!number.empty()) tokens.push_back(number);
    return tokens;
}


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


double calculate(double a, double b, std::string op) {
    switch (op[0]) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': {
            if (b == 0)
                throw std::runtime_error("Division by zero: " + std::to_string(a) + " / " + std::to_string(b));
            return a / b;
        }
        default: throw std::invalid_argument("Wrong operator: " + op);
    }
}


std::vector<std::string> toRPN(const std::string& expr, bool isDebugMode = false) {
    std::vector<std::string> result;

    Stack opStack;
    std::vector<std::string> tokens = splitString(expr);
    std::unordered_map<std::string, int> precedences {{"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}};

    if (isDebugMode) std::cout << "Translating to RPN...\n";
    for (std::string token : tokens) {
        if (isdigit(token[0])) result.push_back(token); // Number: Add to result immediately
        else if (token == "(") opStack.push(token);     // Open brace: Add to opStack
        else if (token == ")") {                           // Close brace: Read stack while not (
            while (*opStack.top() != "(") result.push_back(opStack.pop());
            if (opStack.isEmpty()) throw std::runtime_error("Unclosed brace");
            opStack.pop(); // Delete open brace from stack
        } else if (precedences.count(token) > 0) {                 // Operator
            while (!opStack.isEmpty() && *opStack.top() != "(" && precedences[token] <= precedences[*opStack.top()])
                result.push_back(opStack.pop());
            opStack.push(token);
        } else throw std::runtime_error("Invalid syntax: " + token);
        if (isDebugMode) printDebug(result, opStack, tokens);
    }
    while (!opStack.isEmpty()) {
        if (*opStack.top() == "(") throw std::runtime_error("Unclosed brace");
        result.push_back(opStack.pop());
        if (isDebugMode) printDebug(result, opStack, tokens);
    }
    return result;
}


double evaluate(const std::vector<std::string>& expr, bool isDebugMode = false) {
    Stack opStack;
    for (std::string token : expr) {
        if (isdigit(token[0])) {
            opStack.push(token);
            if (isDebugMode)
                std::cout << "Number found. \tStack: " << opStack << std::endl;
        } else {
            if (opStack.getSize() < 2) throw std::runtime_error("Nothing to calculate");
            double op2 = std::stod(opStack.pop());
            double op1 = std::stod(opStack.pop());
            std::string calc = std::to_string(calculate(op1, op2, token));
            opStack.push(calc);
            if (isDebugMode)
                std::cout << "Evaluate " << op1 << token << op2 << ". \tStack: " << opStack << std::endl;
        }
    }
    return std::stod(opStack.pop());
}

#endif //PRACTICE01_RPN_H