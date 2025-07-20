#include "todo.h"
#include <iostream>
using namespace std;

int main() {
//class and its object
    ToDoList todo;
    const string filename = "todo.txt";
    int choice;

//pre-loads data before the menu is displayed
    todo.loadFromFile(filename);
    todo.viewAllTasks();

//this code loops to the system menu unless the user decides to exit
    do {
        todo.displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:  todo.addToQueue();         break;
            case 2:  todo.undoLastQueuedTask(); break;
            case 3:  todo.processQueue();       break;
            case 4:  todo.viewAllTasks();       break;
            case 5:  todo.viewCompletedTasks(); break;
            case 6:  todo.markTaskComplete();   break;
            case 7:  todo.findTask();           break;
            case 8:  todo.deleteTask();         break;
            case 9:  todo.clearAllTasks();      break;
			case 10: todo.exitProgram(filename); break;
            default:
                cout << "Invalid choice." << endl;
        }

        cout << "\nPress Enter to continue...";
        cin.get();
        system("CLS"); //clears the screen after user is done with a switch case and used its function.
    } while (true);
}
