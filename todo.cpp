#include "Todo.h"
#include <iostream>
#include <fstream>
using namespace std;

TodoList::TodoList() {
    taskCount = 0;
}

void TodoList::addTask() {
    if (taskCount >= 100) {
        cout << "Task list full.\n";
        return;
    }

    cout << "Enter task title: ";
    getline(cin, tasks[taskCount].title);
    cout << "Enter task description: ";
    getline(cin, tasks[taskCount].description);
    tasks[taskCount].completed = false;
    taskCount++;

    cout << "Task added.\n";
}

void TodoList::viewAllTasks() const {
    if (taskCount == 0) {
        cout << "No tasks available.\n";
        return;
    }

    for (int i = 0; i < taskCount; ++i) {
        cout << i + 1 << ". " << tasks[i].title << " - " << tasks[i].description;
        if (tasks[i].completed) cout << " (Completed)";
        cout << "\n";
    }
}

void TodoList::viewCompletedTasks() const {
    int count = 0;
    for (int i = 0; i < taskCount; ++i) {
        if (tasks[i].completed) {
            cout << "- " << tasks[i].title << " - " << tasks[i].description << " (Completed)\n";
            count++;
        }
    }

    if (count == 0) cout << "No completed tasks.\n";
}

void TodoList::markTaskComplete() {
    int idx;
    cout << "Enter task number to mark complete: ";
    cin >> idx;
    cin.ignore();

    if (idx >= 1 && idx <= taskCount) {
        tasks[idx - 1].completed = true;
        cout << "Task marked as complete.\n";
    } else {
        cout << "Task not found.\n";
    }
}

void TodoList::findTask() const {
    string keyword;
    cout << "Enter keyword to search for: ";
    getline(cin, keyword);

    int found = 0;
    for (int i = 0; i < taskCount; ++i) {
        if (tasks[i].title == keyword || tasks[i].description == keyword) {
            cout << "- " << tasks[i].title << " - " << tasks[i].description;
            if (tasks[i].completed) cout << " (Completed)";
            cout << "\n";
            found++;
        }
    }

    if (found == 0) cout << "No matching task found.\n";
}

void TodoList::editTask() {
    int idx;
    cout << "Enter task number to edit: ";
    cin >> idx;
    cin.ignore();

    if (idx >= 1 && idx <= taskCount) {
        cout << "New title: ";
        getline(cin, tasks[idx - 1].title);
        cout << "New description: ";
        getline(cin, tasks[idx - 1].description);
        cout << "Task updated.\n";
    } else {
        cout << "Task not found.\n";
    }
}

void TodoList::deleteTask() {
    int idx;
    cout << "Enter task number to delete: ";
    cin >> idx;
    cin.ignore();

    if (idx >= 1 && idx <= taskCount) {
        for (int i = idx - 1; i < taskCount - 1; ++i) {
            tasks[i] = tasks[i + 1];  // shift left
        }
        taskCount--;
        cout << "Task deleted.\n";
    } else {
        cout << "Task not found.\n";
    }
}

void TodoList::clearTasks() {
    taskCount = 0;
    cout << "All tasks cleared.\n";
}

void TodoList::saveTasks(const string& filename) const {
    ofstream out(filename.c_str());
    for (int i = 0; i < taskCount; ++i) {
        out << tasks[i].title << "|" << tasks[i].description << "|" << tasks[i].completed << "\n";
    }
    out.close();
    cout << "Tasks saved to file.\n";
}

void TodoList::loadTasks(const string& filename) {
    ifstream in(filename.c_str());
    if (!in.is_open()) {
        cout << "File not found.\n";
        return;
    }

    clearTasks();
    string line;
    while (getline(in, line)) {
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        if (p1 == string::npos || p2 == string::npos) continue;

        tasks[taskCount].title = line.substr(0, p1);
        tasks[taskCount].description = line.substr(p1 + 1, p2 - p1 - 1);
        string completedStr = line.substr(p2 + 1);
        tasks[taskCount].completed = (completedStr == "1" || completedStr == "true");

        taskCount++;
    }
    in.close();
    cout << "Tasks loaded from file.\n";
}
