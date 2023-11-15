#include "application.h"
#include "trees/bin-tree.h"
#include "trees/avl-tree.h"

#include <iostream>
#include <fstream>


/// Execute the main thread
int TApplication::execute() {
    // Get input from the first line of the INPUT_FILE_PATH file
    std::string path = std::getenv("INPUT_FILE_PATH");
    std::ifstream iFile(path);
    if (!iFile.is_open()) {
        std::cerr << "FileNotFoundError. No such file: `" << path << "`\n";
        return -1;
    }
    std::string input;
    std::getline(iFile, input);
    iFile.close();
    std::cout << "Input: " << input << std::endl;

    // Parse the input into the binary tree
    BinTree binTree;
    try {
        binTree = BinTree(input);
        std::cout << "Parsed binary tree:\n";
        std::cout << binTree;
    }
    catch (std::invalid_argument& e) { std::cerr << "Invalid argument. " << e.what() << std::endl; }
    catch (std::runtime_error& e) { std::cerr << "Runtime error. " << e.what() << std::endl; }

    // Some code uses binTree

    system("pause");

    return 0;
}