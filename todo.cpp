#include "todo.h"
#include <iostream>
#include <fstream>
using namespace std;

//this code allows the user to add task by batch via queue before saving it into the systems linked list
void ToDoList::addToQueue() {
    QueuedTask temp;
    cout << "Enter task title: ";
    getline(cin, temp.title);
    cout << "Enter note/due date: ";
    getline(cin, temp.dueDate);
    taskQueue.push(temp);
    cout << "Task added to queue." << endl;
}

//this code allows the user to undo their latest data
void ToDoList::undoLastQueuedTask() {
    if (taskQueue.empty()) {
        cout << "Queue is already empty. Nothing to undo." << endl;
        return;
    }

    queue<QueuedTask> temp;
    QueuedTask lastTask;

    while (taskQueue.size() > 1) {
        temp.push(taskQueue.front());
        taskQueue.pop();
    }

    lastTask = taskQueue.front();
    taskQueue.pop();
    taskQueue = temp;

    cout << "Undid last queued task: " << lastTask.title
         << " (Due: " << lastTask.dueDate << ")" << endl;
}

//this code proceeds to save a batch of inputted task into the linked list
void ToDoList::processQueue() {
    if (taskQueue.empty()) {
        cout << "No tasks to process." << endl;
        return;
    }

    while (!taskQueue.empty()) {
        QueuedTask temp = taskQueue.front();
        taskQueue.pop();
        TaskNode* newTask = new TaskNode{temp.title, temp.dueDate, false, NULL};
        if (!head) head = newTask;
        else {
            TaskNode* curr = head;
            while (curr->next) curr = curr->next;
            curr->next = newTask;
        }
    }
    cout << "Recen tasks has been saved to task list." << endl;
}

//this code displays all the items that are saved/loaded into the system
void ToDoList::viewAllTasks() const {
    if (!head) {
        cout << "No tasks to display." << endl;
        return;
    }
    cout << "\n+--------------------+" << endl;
    cout << "|     Task List      |" << endl;
    cout << "+--------------------+" << endl;
    TaskNode* curr = head;
    int i = 1;
    while (curr) {
        cout << i++ << ". [" << (curr->completed ? "Done" : " ") << "] "
             << curr->title << " (Due: " << curr->dueDate << ")" << endl;
        curr = curr->next;
    }
}


//this code allows the user to view which task they have completed from the list
void ToDoList::viewCompletedTasks() const {
    TaskNode* curr = head;
    int i = 1;
    bool found = false;
    cout << "\n+--------------------------+" << endl;
    cout << "|  Completed Task Records  |" << endl;
    cout << "+--------------------------+" << endl;
    while (curr) {
        if (curr->completed) {
            cout << i << ". [Completed] " << curr->title
                 << " (Due: " << curr->dueDate << ")" << endl;
            found = true;
        }
        curr = curr->next;
        ++i;
    }
    if (!found) cout << "No completed tasks to show." << endl;
}

//this code allows the user to mark their task as completed
void ToDoList::markTaskComplete() {
    viewAllTasks();
    int pos;
    cout << "\nEnter task number to mark complete (or 0 to cancel): ";
    cin >> pos;
    cin.ignore();

    if (pos == 0) {
        cout << "Cancelled. Returning to menu." << endl;
        return;
    }

    TaskNode* curr = head;
    for (int i = 1; curr && i < pos; ++i) curr = curr->next;
    if (curr) {
        curr->completed = true;
        cout << "Task marked complete." << endl;
    } else {
        cout << "Invalid task number." << endl;
    }
}


//this code is to find items by their keyword in the list incase it becomes too long
void ToDoList::findTask() {
    string keyword;
    cout << "Enter keyword to search: ";
    getline(cin, keyword);
    TaskNode* curr = head;
    int i = 1;
    bool found = false;
    cout << "\nSearch Results:" << endl;
    while (curr) {
        if (curr->title.find(keyword) != string::npos ||
            curr->dueDate.find(keyword) != string::npos) {
            cout << i << ". " << curr->title << " (Due: " << curr->dueDate << ")" << endl;
            found = true;
        }
        curr = curr->next;
        ++i;
    }
    if (!found) cout << "No match for: " << keyword << endl;
}

//this code is to delete specific data in the list
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

//this code is to format the data of the system
void ToDoList::clearAllTasks() {
    while (head) {
        TaskNode* temp = head;
        head = head->next;
        delete temp;
    }
    cout << "All tasks cleared." << endl;
}


//this code loads data from the file name todo.txt
void ToDoList::loadFromFile(const string& filename) {
    ifstream file(filename.c_str());
    string title, due, status;
    while (getline(file, title, '|') &&
           getline(file, due, '|') &&
           getline(file, status)) {
        bool complete = (status == "1");
        TaskNode* newTask = new TaskNode{title, due, complete, NULL};
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


//this code saves the list(linked list)
void ToDoList::saveToFile(const string& filename) const {
    ofstream file(filename.c_str());
    TaskNode* curr = head;
    while (curr) {
        file << curr->title << "|" << curr->dueDate << "|" << curr->completed << endl;
        curr = curr->next;
    }
    file.close();
	cout << "Tasks saved locally under the file name \"todo.txt\"." << endl;
}


//this code confirms if the user wants to save the inputted items and if theyre sure they want to exit.
void ToDoList::exitProgram(const string& filename) {
    char saveChoice;
    cout << "\nDo you want to save your tasks before exiting? (y/n): ";
    cin >> saveChoice;
    cin.ignore();

    if (saveChoice == 'y' || saveChoice == 'Y') {
        saveToFile(filename);
    }

    char exitConfirm;
    cout << "Are you sure you want to exit? (y/n): ";
    cin >> exitConfirm;
    cin.ignore();

    if (exitConfirm == 'y' || exitConfirm == 'Y') {
        cout << "Exiting Student Task and Deadline Organizers..." << endl;
        exit(0); // forcefully exits the program
    } else {
        cout << "Exit cancelled. Returning to menu." << endl;
    }
}


//this code displays recently added items into the queue
void ToDoList::displayQueuedTasks() const {
    if (taskQueue.empty()) return;
    cout << "\n+---------------------------+" << endl;
    cout << "|  Recently Added Task        |" << endl;
    cout << "+-----------------------------+" << endl;
    queue<QueuedTask> temp = taskQueue;
    int i = 1;
    while (!temp.empty()) {
        QueuedTask t = temp.front();
        cout << " " << i++ << ". " << t.title << " (Due: " << t.dueDate << ")" << endl;
        temp.pop();
    }
}


//this code function displays the menu
void ToDoList::displayMenu() const {
    displayQueuedTasks();
    cout << "\n+-------------------------------------------+" << endl;
    cout << "|    Student Task and Deadline Organizers   |" << endl;
    cout << "+-------------------------------------------+" << endl;
    cout << "|  1. Add Task                              |" << endl;
    cout << "|  2. Undo Recently added Task              |" << endl;
    cout << "|  3. Save Task to the List                 |" << endl;
    cout << "|  4. View All Tasks                        |" << endl;
    cout << "|  5. View Completed Tasks                  |" << endl;
    cout << "|  6. Mark Task as Complete                 |" << endl;
    cout << "|  7. Find Task                             |" << endl;
    cout << "|  8. Delete Task                           |" << endl;
    cout << "|  9. Clear All Tasks                       |" << endl;
    cout << "| 10. Exit                                  |" << endl;
    cout << "+-------------------------------------------+" << endl;
    cout << "Choose an option: ";
}
