#include "Todo.h"
#include <iostream>
using namespace std;

int main() {
    TodoList todo;
    const string filename = "todo.txt";
    int choice;

    todo.loadTasks(filename);

    while (true) {
        cout << "\nMENU: \n"
             << "1. Add New Task\n"
             << "2. View All Tasks\n"
             << "3. View Completed Tasks\n"
             << "4. Mark Task as Complete\n"
             << "5. Find Task\n"
             << "6. Edit Task\n"
             << "7. Delete Task\n"
             << "8. Clear All Tasks\n"
             << "9. Save Task Transactions\n"
             << "10. Load Task Transactions\n"
             << "11. Exit\nChoose: ";
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
