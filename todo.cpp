#include "todo.h"
#include <iostream>
#include <fstream>
using namespace std;

void loadQueueFromFile(queue<string>& taskQueue, const string& filename) {
    ifstream infile(filename.c_str());
    string task;
    while (getline(infile, task)) {
        taskQueue.push(task);
    }
    infile.close();
}

void saveQueueToFile(const queue<string>& taskQueue, const string& filename) {
    ofstream outfile(filename.c_str());
    queue<string> tempQueue = taskQueue;
    while (!tempQueue.empty()) {
        outfile << tempQueue.front() << endl;
        tempQueue.pop();
    }
    outfile.close();
}

void addTask(queue<string>& taskQueue) {
    string task;
    cout << "Enter the title of your task: ";
    getline(cin, task);
    taskQueue.push(task);
    cout << "Task added: " << task << endl;
}

void markTaskComplete(queue<string>& taskQueue) {
    if (!taskQueue.empty()) {
        cout << "Marking your task " << taskQueue.front() << "as completed"<< endl;
        taskQueue.pop();
    } else {
        cout << "The queue is empty, no task to complete." << endl;
    }
}

void viewAllTask() { cout << "Viewing all tasks (not yet implemented)." << endl; }
void viewCompletedTask() { cout << "Viewing completed tasks (not yet implemented)." << endl; }
void editTask() {}
void deleteTask() {}
void clearAllTask() {}
void display(const queue<string>&) {}


void displayMenu() {
    cout << "\nStudents ToDO List:\n"
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
         << "11. Exit\n"
         << "Choose: ";
}
