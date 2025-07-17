#include "todo.h"
#include <iostream>
#include <queue>
using namespace std;

int main() {
    queue<string> taskQueue;
    const string filename = "todo.txt";

    int choice;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore(); // handle leftover newline

        switch (choice) {
            case 1:
                addTask(taskQueue);
                break;
            case 2:
                markTaskComplete(taskQueue);
                break;
            case 3:
                viewAllTask();
                break;
            case 4:
                viewCompletedTask();
                break;
            case 5:
                saveQueueToFile(taskQueue, filename);
                break;
            case 6:
                loadQueueFromFile(taskQueue, filename);
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
                return 0;
        }
    }
}
