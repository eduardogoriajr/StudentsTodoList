#include "todo.h"
#include <iostream>
using namespace std;

int main() {
    ToDoList todo;
    const string filename = "todo.txt";
    int choice;

    do {
        system("CLS");            
        todo.displayMenu();         
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:  todo.addToQueue();         break;
            case 2:  todo.processQueue();       break;
            case 3:  todo.viewAllTasks();       break;
            case 4:  todo.viewCompletedTasks(); break;
            case 5:  todo.markTaskComplete();   break;
            case 6:  todo.findTask();           break;
            case 7:  todo.deleteTask();         break;
            case 8:  todo.clearAllTasks();      break;
            case 9:  todo.saveToFile(filename); break;
            case 10: todo.loadFromFile(filename); break;
            case 11:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice." << endl;
        }
        cout << "\nPress Enter to continue...";
        cin.get(); // waits for user input before refreshing menu

    } while (true);
}
