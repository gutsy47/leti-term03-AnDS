#ifndef ADS_APPLICATION_H
#define ADS_APPLICATION_H

class TApplication {
public:
    static int execute();    // Execute the main thread
private:
    static void help();      // Print the available commands
    static bool menu(char&); // Get user's choice
};

#endif //ADS_APPLICATION_H
