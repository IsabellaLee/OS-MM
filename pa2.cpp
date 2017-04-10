#include "pa2.hpp"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char ** argv) {
    
    //arg[1] is the parameter for which algorithm to use,
    //best fit or worst fit
    string algorithm = argv[1];
    
    Memory* memory = new Memory();
    
    //Indicate which algorithm to use at the top
    if (algorithm == "best") {
        cout << "Using best fit algorithm.\n" << endl;
    }
    else if (algorithm == "worst") {
        cout << "Using worst fit algorithm.\n" << endl;
    }
    else {
        //Data validation: if input is neither best or worst
        //program will be terminated
        cout << "Invalid Input.\n" << endl;
        exit(0);
    }
    
    //Print out the main menu
    //Main menu includes all the operations provided to the user
    cout << "1. Add program\n" << "2. Kill program\n" << "3. Fragmentation\n" << "4. Print memory\n" << "5. Exit\n" << endl;
    
    while (true) {
        
        //Integer choice is used to store the information about
        //which actions to take. For example, if choice is 1, it means
        //an add program action will be taken
        
        int choice;
        cout << "choice - ";
        
        //Data validation: if user's input is not an integer,
        //it will not be read into the cin, therefore user needs
        //to try again until it pass the data validation test
        
        while(!(cin >> choice)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Invalid input. Try again.\n " << endl;
            cout << "choice - ";
        }
        
        //Implement the corresponding function based on the user's choice
        switch (choice) {
            //Add a program if case is 1
            case 1: {
                
                //Read in both the program's name and size
                cout << "Program name - ";
                string programName;
                cin >> programName;
                cin.clear();
                cout << "Program size (KB) - ";
                int programSize;
                cin >> programSize;
                cin.clear();
                
                printf("\n");
        
                if (algorithm == "worst")
                    memory->worstFitAlgorithm(programName, programSize);
                else if (algorithm == "best")
                    memory->bestFitAlgorithm(programName, programSize);
            }
                break;
            
            //Kill a program if case is 2
            case 2: {
                cout << "Program name - ";
                string programName;
                cin >> programName;
                cin.clear();
                cout << endl;
                memory->kill(programName);
            }
                break;
                
            //Show the number of fragments if case is 3
            case 3:
                printf("\n");
                printf("There are %d fragment(s).\n\n", memory->fragments());
                break;
             
            //Print out how the memory is allocated by now if case is 4
            case 4:
                printf("\n");
                memory->printMemory();
                break;
            
            //Exit the program if case is 5
            case 5:
                exit(0);
                
            //Otherwise, enter another integer to pass the data validation
            default:
                printf("\n");
                cout << "Invalid input, try again.\n" << endl;
                break;
        }
    }
}
