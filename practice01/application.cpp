#include "application.h"

#include "structures/dl_list.h"
#include "structures/dynamic_array.h"
#include "structures/stack.h"
#include "rpn.h"
#include <vector>

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


/**
 * Executes the program
 * @return 0 if correct exit
 */
int TApplication::execute() {

    std::cout.setf(std::ios::boolalpha);

    char userChoice;
    while (true) {
        std::cout << "Choose the thread:\n";
        std::cout << "1. Doubly-linked list\n";
        std::cout << "2. Dynamic array\n";
        std::cout << "3. Stack\n";
        std::cout << "4. Reverse Polish Notation\n";

        // Get command from the keyboard
        if (!menu(userChoice)) continue; // Error occurred
        if (userChoice == '0') break;       // Exit command
        system("cls");

        // Execute sub thread
        if (userChoice == '1') {
            std::cout << "List thread executed. Enter 'h' to get list of commands\n";
            executeList();
        } else if (userChoice == '2') {
            std::cout << "Dynamic array thread executed. Enter 'h' to get list of commands\n";
            executeDArr();
        }
        else if (userChoice == '3') {
            std::cout << "Stack thread executed. Enter 'h' to get list of commands\n";
            executeStack();
        } else if (userChoice == '4') {
            std::cout << "Polish Notation thread executed.\n";
            executeRPN();
        } else {
            std::cout << "RuntimeError. Unknown command\n";
        }

        system("cls");
    }

    return 0;
}


/// Execute the list thread
int TApplication::executeList() {
    char userChoice;
    List list;

    while (true) {
        // Get command from the keyboard
        if (!menu(userChoice)) continue; // Error occurred
        if (userChoice == '0') break;       // Exit command

        // Execute
        switch (userChoice) {
            // Create list
            case '1': {
                // Get values
                int size;
                std::cout << "<< Enter the size of the list:\n>> ";
                if (!inputNumber<int>(size, true, true)) break;
                int values[size];
                std::cout << "<< Enter " << size << " elements separated by space:\n>> ";
                for (auto &el: values)
                    if (!inputNumber<int>(el)) break;

                // Create the list
                list = List(size, values);
                std::cout << "Created list: " << list << std::endl;

                break;
            }

            // Print list
            case '2': {
                std::cout << list << "(size = " << list.getSize() << ")\n";
                break;
            }

            // Find element
            case '3': {
                // Get user choice
                int choice;
                std::cout << "<< Choose the way of search: '1' to search by index and '2' to search by value:\n>> ";
                if (!inputNumber(choice, true, true)) break;

                // Search
                if (choice == 1) {
                    int index;
                    std::cout << "<< Enter the index:\n>> ";
                    if (!inputNumber(index, true, false)) break;

                    struct Node *element = list[index];
                    if (element) std::cout << "Element " << element->value << " found\n";
                    else std::cout << "Element not found\n";
                } else if (choice == 2) {
                    int value;
                    std::cout << "Enter the value:\n>> ";
                    if (!inputNumber(value, true, false)) break;

                    int index = list.find(value);
                    if (index != -1) std::cout << "Element found. Index: " << index << std::endl;
                    else std::cout << "Element not found\n";
                } else {
                    std::cout << "InputError: Unknown command '" << choice << "'\n";
                }

                break;
            }

            // Add new node
            case '4': {
                // Get user choice
                int choice;
                std::cout << "<< Choose the way of addition: '1' to push back and '2' to insert by index:\n>> ";
                if (!inputNumber(choice, true, true)) break;

                // InputError
                if (choice != 1 && choice != 2) {
                    std::cout << "InputError: Unknown command '" << choice << "'\n";
                    break;
                }

                // Get value
                int value;
                std::cout << "<< Enter the value:\n>> ";
                if (!inputNumber(value, true, false)) break;

                // Append or insert
                if (choice == 1) {
                    list.append(value);
                } else if (choice == 2) {
                    unsigned index;
                    std::cout << "<< Enter the index:\n>> ";
                    if (!inputNumber(index, true, true)) break;
                    list.insert(index, value);
                }

                std::cout << "Updated list: " << list << std::endl;

                break;
            }

            // Delete existing node
            case '5': {
                unsigned index;
                std::cout << "<< Enter index of existing node:\n>> ";
                if (!inputNumber(index, true, true)) break;

                list.remove(index);

                std::cout << "Updated list: " << list << std::endl;

                break;
            }

            // Swap two elements
            case '6': {
                unsigned index1, index2;
                std::cout << "<< Enter 1st index:\n>> ";
                if (!inputNumber(index1, true, true)) break;
                std::cout << "<< Enter 2nd index:\n>> ";
                if (!inputNumber(index2, true, true)) break;

                list.swap(index1, index2);

                std::cout << "Updated list: " << list << std::endl;

                break;
            }

            // Help menu
            case 'h': {
                helpList();
                break;
            }

            // Runtime error. Unknown command
            default: std::cout << "RuntimeError. Unknown command\n";
        }
        system("pause");
    }

    return 0;
}


/// Execute the dynamic array thread
int TApplication::executeDArr() {
    char userChoice;
    DArray arr;

    while (true) {
        // Get command from the keyboard
        if (!menu(userChoice)) continue; // Error occurred
        if (userChoice == '0') break;

        // Execute
        switch (userChoice) {
            // Create array
            case '1': {
                // Get values;
                int size;
                std::cout << "<< Enter the size of the array:\n>> ";
                if (!inputNumber(size, true, true)) break;
                int values[size];
                std::cout << "<< Enter " << size << " elements separated by space:\n>> ";
                for (auto &el : values)
                    if (!inputNumber(el)) break;

                // Reassign the array
                arr = DArray(size, values);
                std::cout << "Created array: " << arr << std::endl;

                break;
            }

            // Print array
            case '2': {
                std::cout << arr << "(size = " << arr.getSize() << ", capacity = " << arr.getCapacity() << ")\n";
                break;
            }

            // Find element
            case '3': {
                // Get choice
                int choice;
                std::cout << "<< Choose the way of search: '1' to search by index and '2' to search by value:\n>> ";
                if (!inputNumber(choice, true, true)) break;

                // Search
                if (choice == 1) {
                    int index;
                    std::cout << "<< Enter the index:\n>> ";
                    if (!inputNumber(index, true, true)) break;

                    int *value = arr[index];
                    if (value) std::cout << "Element " << *value << " found\n";
                    else std::cout << "Element not found\n";
                } else if (choice == 2) {
                    int value;
                    std::cout << "Enter the value:\n>> ";
                    if (!inputNumber(value, true, true)) break;

                    int index = arr.find(value);
                    if (index != -1) std::cout << "Element found. Index: " << index << std::endl;
                    else std::cout << "Element not found\n";
                } else {
                    std::cout << "InputError: Unknown command '" << choice << "'\n";
                }

                break;
            }

            // Add new element
            case '4': {
                // Get user choice
                int choice;
                std::cout << "<< Choose the way of addition: '1' to push back and '2' to insert by index:\n>> ";
                if (!inputNumber(choice, true, true)) break;

                // InputError
                if (choice != 1 && choice != 2) {
                    std::cout << "InputError: Unknown command '" << choice << "'\n";
                    break;
                }

                // Get value
                int value;
                std::cout << "<< Enter the value:\n>> ";
                if (!inputNumber(value, true, false)) break;

                // Append or insert
                if (choice == 1) {
                    arr.append(value);
                } else {
                    unsigned index;
                    std::cout << "<< Enter the index:\n>> ";
                    if (!inputNumber(index, true, true)) break;
                    arr.insert(index, value);
                }

                std::cout << "Updated array: " << arr << std::endl;

                break;
            }


            // Delete element
            case '5': {
                unsigned index;
                std::cout << "<< Enter index of existing element:\n>> ";
                if (!inputNumber(index, true, true)) break;

                arr.remove(index);

                std::cout << "Updated array: " << arr << std::endl;

                break;
            }

            // Help menu
            case 'h': {
                helpDArr();
                break;
            }

            // Runtime error. Unknown command
            default: std::cout << "Runtime error. Unknown command\n";
        }
        system("pause");
    }

    return 0;
}


/// Execute the dynamic array thread
int TApplication::executeStack() {
    char userChoice;
    Stack stack;

    while (true) {
        // Get command from the keyboard
        if (!menu(userChoice)) continue; // Error occurred
        if (userChoice == '0') break;

        // Execute
        switch (userChoice) {
            // Push back
            case '1': {
                std::string input;
                std::cout << "<< Enter a string to push back:\n>> ";
                getline (std::cin, input);
                stack.push(input);
                std::cout << "Updated stack: " << stack << std::endl;
                break;
            }

            // Pop element
            case '2': {
                std::cout << stack.pop() << std::endl;
                std::cout << "Updated stack: " << stack << std::endl;
                break;
            }

            // Print stack
            case '3': {
                std::cout << stack << " (size = " << stack.getSize() << ")\n";
                break;
            }

            // Help menu
            case 'h': {
                helpStack();
                break;
            }

            // Runtime error. Unknown command
            default: std::cout << "Runtime error. Unknown command\n";
        }
        system("pause");
    }

    return 0;
}


/// Execute the polish notation thread
int TApplication::executeRPN() {
    bool isDebugMode = true;
    while (true) {
        try {
            // Get expression or command
            std::cout << "<< Enter an expression ['0' - exit, 'd' - toggle debug mode]\n>> ";
            std::string expr;
            std::getline(std::cin, expr);

            // Exit or toggle debug
            if (expr == "0")
                break;
            if (expr == "d") {
                isDebugMode = !isDebugMode;
                std::cout << "Debug mode switched to " << isDebugMode << '\n';
                continue;
            }

            // Get RPN and evaluate
            std::vector<std::string> rpn = toRPN(expr, isDebugMode);
            double rpnAnswer = evaluate(rpn, isDebugMode);

            // Output
            std::cout << std::setw(64) << std::setfill('-') << ' ' << std::setfill(' ');
            std::cout << "\n Input: " << expr << "\n   RPN: ";
            for (auto &token : rpn) std::cout << token << ' ';
            std::cout << "\nAnswer: " << rpnAnswer << std::endl;
        }
        catch (std::invalid_argument& e) { std::cerr << "Invalid argument. " << e.what() << std::endl; }
        catch (std::runtime_error& e) { std::cerr << "Runtime error. " << e.what() << std::endl; }
    }

    return 0;
}


/// Print available List commands
void TApplication::helpList() {
    std::cout << "Available commands:\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << "h: Help (this menu)\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << "1: Create the list\n";
    std::cout << "2: Print the list\n";
    std::cout << "3: Find element\n";
    std::cout << "4: Add new node\n";
    std::cout << "5: Delete existing node\n";
    std::cout << "6: Swap two elements\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << "0: Exit\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << std::setfill(' ');
}


/// Print available Dynamic Array commands
void TApplication::helpDArr() {
    std::cout << "Available commands:\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << "h: Help (this menu)\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << "1: Create the dynamic array\n";
    std::cout << "2: Print the dynamic array\n";
    std::cout << "3: Find element\n";
    std::cout << "4: Add new element\n";
    std::cout << "5: Delete existing element\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << "0: Exit\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << std::setfill(' ');
}


/// Print available Dynamic Array commands
void TApplication::helpStack() {
    std::cout << "Available commands:\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << "h: Help (this menu)\n";
    std::cout << std::setw(32) << std::setfill('-') << '\n';
    std::cout << "1: Push back\n";
    std::cout << "2: Pop element\n";
    std::cout << "3: Print stack\n";
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