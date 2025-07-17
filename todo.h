#ifndef TODOLIST_H
#define TODOLIST_H

#include <string>
#include <queue>
using namespace std;

struct TaskNode {
    string title;
    bool completed;
    TaskNode* next;
};

class ToDoList {
private:
    TaskNode* head;
    queue<string> taskQueue;

public:
    ToDoList();
    ~ToDoList();

    void addToQueue();
    void processQueue();

    void viewAllTasks() const;
    void viewCompletedTasks() const;
    void markTaskComplete();
    void findTask();
    void deleteTask();
    void clearAllTasks();

    void loadFromFile(const string& filename);
    void saveToFile(const string& filename) const;

    void displayQueuedTasks() const;
    void displayMenu() const;
};

#endif
