#include "todo.h"
#include <iostream>
#include <fstream>
using namespace std;

ToDoList::ToDoList() { head = NULL; }

ToDoList::~ToDoList() { clearAllTasks(); }

void ToDoList::addToQueue() {
    string title;
    cout << "Enter task to queue: ";
    getline(cin, title);
    taskQueue.push(title);
    cout << "Task added to queue." << endl;
}

void ToDoList::processQueue() {
    if (taskQueue.empty()) {
        cout << "No tasks in queue to process." << endl;
        return;
    }
    while (!taskQueue.empty()) {
        string title = taskQueue.front();
        taskQueue.pop();
        TaskNode* newTask = new TaskNode{title, false, NULL};
        if (!head) head = newTask;
        else {
            TaskNode* curr = head;
            while (curr->next) curr = curr->next;
            curr->next = newTask;
        }
    }
    cout << "All queued tasks moved to task list." << endl;
}

void ToDoList::viewAllTasks() const {
    if (!head) {
        cout << "No tasks to display." << endl;
        return;
    }
    TaskNode* curr = head;
    int i = 1;
    while (curr) {
        cout << i++ << ". [" << (curr->completed ? "Done" : " ") << "] " << curr->title << endl;
        curr = curr->next;
    }
}

void ToDoList::viewCompletedTasks() const {
    TaskNode* curr = head;
    int i = 1;
    bool found = false;
    while (curr) {
        if (curr->completed) {
            cout << i << ". [Completed] " << curr->title << endl;
            found = true;
        }
        curr = curr->next;
        ++i;
    }
    if (!found) cout << "No completed tasks to show." << endl;
}

void ToDoList::markTaskComplete() {
    viewAllTasks();
    int pos;
    cout << "Enter task number to mark complete: ";
    cin >> pos;
    cin.ignore();
    TaskNode* curr = head;
    for (int i = 1; curr && i < pos; ++i) curr = curr->next;
    if (curr) {
        curr->completed = true;
        cout << "Task marked complete." << endl;
    } else {
        cout << "Invalid task number." << endl;
    }
}

void ToDoList::findTask() {
    string keyword;
    cout << "Enter keyword to search: ";
    getline(cin, keyword);
    TaskNode* curr = head;
    int i = 1;
    bool found = false;
    while (curr) {
        if (curr->title.find(keyword) != string::npos) {
            cout << i << ". " << curr->title << endl;
            found = true;
        }
        curr = curr->next;
        ++i;
    }
    if (!found) cout << "No match for: " << keyword << endl;
}

void ToDoList::deleteTask() {
    int pos;
    cout << "Enter task number to delete: ";
    cin >> pos;
    cin.ignore();
    TaskNode *curr = head, *prev = NULL;
    for (int i = 1; curr && i < pos; ++i) {
        prev = curr;
        curr = curr->next;
    }
    if (!curr) {
        cout << "Invalid task number." << endl;
        return;
    }
    if (!prev) head = curr->next;
    else prev->next = curr->next;
    delete curr;
    cout << "Task deleted." << endl;
}

void ToDoList::clearAllTasks() {
    while (head) {
        TaskNode* temp = head;
        head = head->next;
        delete temp;
    }
    cout << "All tasks cleared." << endl;
}

void ToDoList::loadFromFile(const string& filename) {
    clearAllTasks();
    ifstream file(filename.c_str());
    string line;
    while (getline(file, line)) {
        TaskNode* newTask = new TaskNode{line, false, NULL};
        if (!head) head = newTask;
        else {
            TaskNode* curr = head;
            while (curr->next) curr = curr->next;
            curr->next = newTask;
        }
    }
    file.close();
    cout << "Tasks loaded." << endl;
}

void ToDoList::saveToFile(const string& filename) const {
    ofstream file(filename.c_str());
    TaskNode* curr = head;
    while (curr) {
        file << curr->title << endl;
        curr = curr->next;
    }
    file.close();
    cout << "Tasks saved." << endl;
}

void ToDoList::displayQueuedTasks() const {
    if (taskQueue.empty()) return;
    cout << "\nRecently Added Tasks (Queue):" << endl;
    queue<string> temp = taskQueue;
    int i = 1;
    while (!temp.empty()) {
        cout << " " << i++ << ". " << temp.front() << endl;
        temp.pop();
    }
}

void ToDoList::displayMenu() const {
    displayQueuedTasks();
    cout << "\nStudents ToDO List:\n"
         << "1. Queue Task\n"
         << "2. Process Queued Tasks to List\n"
         << "3. View All Tasks\n"
         << "4. View Completed Tasks\n"
         << "5. Mark Task as Complete\n"
         << "6. Find Task\n"
         << "7. Delete Task\n"
         << "8. Clear All Tasks\n"
         << "9. Save Task Transactions\n"
         << "10. Load Task Transactions\n"
         << "11. Exit\n"
         << "Choose: ";
}
