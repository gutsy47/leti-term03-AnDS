#ifndef OOP_APPLICATION_H
#define OOP_APPLICATION_H

class TApplication {
public:
    static int execute();    // Execute the main thread
private:
    static bool menu(char&); // Get user's choice
    static void help();      // Print the available commands
};

#endif //OOP_APPLICATION_H
