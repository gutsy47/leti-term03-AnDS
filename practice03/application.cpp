#include "application.h"

#include <iostream>
#include <iomanip>

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


/// Execute the main thread
int TApplication::execute() {
    char userChoice;
    while (true) {
        // Get command from the keyboard
        if (!menu(userChoice)) continue; // Error occurred
        if (userChoice == '0') break;

        // Execute
        switch (userChoice) {
            // Command 1
            case '1': {
                std::cout << "Command 1\n";
                break;
            }

            // Command 2
            case '2': {
                std::cout << "Command 2\n";
                break;
            }

            // Command 3
            case '3': {
                std::cout << "Command 3\n";
                break;
            }

            // Help menu
            case 'h': {
                help();
                break;
            }

            // Runtime error. Unknown command
            default: std::cout << "Runtime error. Unknown command\n";
        }
        system("pause");
    }

    return 0;
}


/// Print available Dynamic Array commands
void TApplication::help() {
    std::cout << "Available commands:\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << "h: Help (this menu)\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << "1: Command 1\n";
    std::cout << "2: Command 2\n";
    std::cout << "3: Command 3\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << "0: Exit\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << std::setfill(' ');
}


/**
 * Prints the menu of commands and reads the user action input via cin
 * @param[out] userChoice Reference to a declared user's choice variable
 * @return True if input was correct, else false (error)
 */
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