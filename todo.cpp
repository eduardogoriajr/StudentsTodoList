#include "Todo.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <string>

using namespace std;

void displayMenu() {
    cout << "\nMENU:\n"
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

// Method: Add a new task to the queue
void TodoList::addTask() {
    Task newTask;
    cout << "Enter task title: ";
    getline(cin, newTask.title);
    newTask.completed = false;
    taskQueue.push(newTask);
    cout << "Task added!\n";
}

// Method: View all tasks
void TodoList::viewAllTasks() const {
    queue<Task> tempQueue = taskQueue;
    if (tempQueue.empty()) {
        cout << "No tasks available.\n";
        return;
    }

    int i = 1;
    while (!tempQueue.empty()) {
        Task t = tempQueue.front();
        cout << i++ << ". " << t.title << " [" << (t.completed ? "Completed" : "Pending") << "]\n";
        tempQueue.pop();
    }
}

// Method: View completed tasks
void TodoList::viewCompletedTasks() const {
    queue<Task> tempQueue = taskQueue;
    bool found = false;
    int i = 1;

    while (!tempQueue.empty()) {
        Task t = tempQueue.front();
        if (t.completed) {
            cout << i++ << ". " << t.title << " [Completed]\n";
            found = true;
        }
        tempQueue.pop();
    }

    if (!found) {
        cout << "No completed tasks found.\n";
    }
}

// Method: Mark a specific task as completed
void TodoList::markTaskComplete() {
    string title;
    cout << "Enter the title of the task to mark as complete: ";
    getline(cin, title);

    queue<Task> tempQueue;
    bool marked = false;

    while (!taskQueue.empty()) {
        Task t = taskQueue.front();
        taskQueue.pop();

        if (!marked && t.title == title) {
            t.completed = true;
            marked = true;
        }

        tempQueue.push(t);
    }

    taskQueue = tempQueue;

    if (marked) {
        cout << "Task marked as completed.\n";
    } else {
        cout << "Task not found.\n";
    }
}

// Method: Find a task by keyword
void TodoList::findTask() const {
    string keyword;
    cout << "Enter keyword to search: ";
    getline(cin, keyword);

    queue<Task> tempQueue = taskQueue;
    bool found = false;
    int i = 1;

    while (!tempQueue.empty()) {
        Task t = tempQueue.front();
        if (t.title.find(keyword) != string::npos) {
            cout << i++ << ". " << t.title << " [" << (t.completed ? "Completed" : "Pending") << "]\n";
            found = true;
        }
        tempQueue.pop();
    }

    if (!found) {
        cout << "No matching tasks found.\n";
    }
}

// Method: Edit the title of a specific task
void TodoList::editTask() {
    string oldTitle;
    cout << "Enter the title of the task to edit: ";
    getline(cin, oldTitle);

    queue<Task> tempQueue;
    bool edited = false;

    while (!taskQueue.empty()) {
        Task t = taskQueue.front();
        taskQueue.pop();

        if (!edited && t.title == oldTitle) {
            cout << "Enter new title: ";
            getline(cin, t.title);
            edited = true;
        }

        tempQueue.push(t);
    }

    taskQueue = tempQueue;

    if (edited) {
        cout << "Task updated.\n";
    } else {
        cout << "Task not found.\n";
    }
}

// Method: Delete a specific task
void TodoList::deleteTask() {
    string title;
    cout << "Enter the title of the task to delete: ";
    getline(cin, title);

    queue<Task> tempQueue;
    bool deleted = false;

    while (!taskQueue.empty()) {
        Task t = taskQueue.front();
        taskQueue.pop();

        if (!deleted && t.title == title) {
            deleted = true;
            continue;
        }

        tempQueue.push(t);
    }

    taskQueue = tempQueue;

    if (deleted) {
        cout << "Task deleted.\n";
    } else {
        cout << "Task not found.\n";
    }
}

// Method: Clear all tasks
void TodoList::clearTasks() {
    while (!taskQueue.empty()) {
        taskQueue.pop();
    }
    cout << "All tasks cleared.\n";
}

// Load tasks from file
void TodoList::loadTasks(const string& filename) {
    ifstream infile(filename.c_str());
    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            Task t;
            t.title = line;
            t.completed = false; // default for simplicity
            taskQueue.push(t);
        }
        infile.close();
    }
}

// Save tasks to file
void TodoList::saveTasks(const string& filename) const {
    ofstream outfile(filename.c_str());
    if (outfile.is_open()) {
        queue<Task> tempQueue = taskQueue;
        while (!tempQueue.empty()) {
            outfile << tempQueue.front().title << endl;
            tempQueue.pop();
        }
        outfile.close();
    }
}

