#include "application.h"
#include "structures/graph.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

/**
 * Reads the number input via cin
 * @param[out] variable Reference to a declared variable
 * @param[in] isSpaceSep If true, it does not check the last character of the input for newline
 * @param[in] isUnsigned If true, then negative numbers will lead to an error
 * @return True if input was correct, else false
 */
template <typename NumType>
bool inputNumber(NumType &variable, bool isSpaceSep = false, bool isUnsigned = false) {
    std::cin >> variable;
    if (std::cin.fail() || (isUnsigned && variable < 0) || (isSpaceSep && std::cin.peek() != '\n')) {
        std::cout << "Invalid input\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return false;
    }
    return true;
}


//// Print the menu and read the user input. Return true on success
bool TApplication::menu(char &userChoice) {
    std::cout << "<< Action:\n>> ";
    std::cin >> userChoice;

    // Error handler (i.e. more than one symbol input)
    if (std::cin.fail() || std::cin.get() != '\n') {
        std::cout << "RuntimeError. Unknown command\n";
        std::cin.clear();
        std::cin.ignore(100000, '\n');
        return false;
    }
    return true;
}


/// Print available commands
void TApplication::help() {
    std::cout << "Available commands:\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << "h: Help (this menu)\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << "1: Command 1\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << "0: Exit\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << std::setfill(' ');
}


/// Update <names> & <values> by data from <path>. Return 1 on success
/** Return values
 *  1 Success
 * -1 File Not Found
 * -2 Invalid Input
 * -3 Invalid Size
 * -4 Non-Zero Diagonals
 */
void parseFile(const std::string &path, std::vector<char> &names, std::vector<std::vector<int>> &values) {
    std::ifstream iFile(path);
    if (!iFile.is_open()) throw std::runtime_error("FileNotFound: Couldn't open '" + path + "' file");
    std::string line;

    // Get names
    std::getline(iFile, line);
    std::string name;
    for (auto &c : line) {
        if (c == ' ') {
            if (!name.empty()) names.push_back(name[0]);
            name.clear();
        } else {
            name += c;
            if (name.length() > 1) throw std::runtime_error("InvalidName: Invalid vertex name");
        }
    }
    names.push_back(name[0]);

    // Get values
    while (std::getline(iFile, line)) {
        std::vector<int> row;
        std::string number;
        for (auto &c : line) {
            if (c == ' ') {
                if (!number.empty()) row.push_back(std::stoi(number));
                number.clear();
            } else if (isdigit(c)) {
                number += c;
            } else {
                throw std::runtime_error("InvalidValue: Invalid character '" + std::string(1, c) + "' in file");
            }
        }
        row.push_back(std::stoi(number)); // Last row element
        if (!values.empty() && row.size() != values[0].size())
            throw std::runtime_error("InvalidSize: Invalid row size");
        values.push_back(row);
    }
    if (values.size() != values[0].size()) throw std::runtime_error("InvalidSize: Invalid matrix size");
    for (int i = 0; i < values.size(); ++i)
        if (values[i][i] != 0) throw std::runtime_error("LoopError: Non-zero diagonals");

    iFile.close();
}


/// Execute the main thread
int TApplication::execute() {
    // Read input file and create Graph object
    std::string path = std::getenv("INPUT_FILE_PATH");
    std::vector<char> names;
    std::vector<std::vector<int>> values;
    parseFile(path, names, values);
    Graph graph(names, values);

    // Searches
    std::vector<Vertex*> dfs = graph.depthFirstSearch();
    std::vector<Vertex*> bfs = graph.breadthFirstSearch();
    std::cout << "DFS: ";
    for (auto *el : dfs) std::cout << *el << ' ';
    std::cout << "\nBFS: ";
    for (auto *el : bfs) std::cout << *el << ' ';
    std::cout << '\n';

    // Sort by weight
    std::vector<Edge> sorted = graph.getSortedByWeight();
    std::cout << "Edges sorted by weight:\n";
    for (auto &edge : sorted)
        std::cout << "     " << edge << '\n';

    return 0;
}
