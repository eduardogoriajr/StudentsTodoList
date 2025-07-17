#include "Todo.h"
#include <iostream>
using namespace std;

int main() {
    TodoList todo;
    const string filename = "todo.txt";
    todo.loadTasks(filename);

    int choice;
    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: todo.addTask(); break;
            case 2: todo.viewAllTasks(); break;
            case 3: todo.viewCompletedTasks(); break;
            case 4: todo.markTaskComplete(); break;
            case 5: todo.findTask(); break;
            case 6: todo.editTask(); break;
            case 7: todo.deleteTask(); break;
            case 8: todo.clearTasks(); break;
            case 9: todo.saveTasks(filename); break;
            case 10: todo.loadTasks(filename); break;
            case 11: cout << "Goodbye!\n"; return 0;
            default: cout << "Invalid choice.\n"; break;
        }
    }
}
