#ifndef TODO_H
#define TODO_H

#include <queue>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

struct Task {
    string title;
    bool completed;
};

class TodoList {
private:
    queue<Task> taskQueue;

public:
    void addTask();
    void viewAllTasks() const;
    void viewCompletedTasks() const;
    void markTaskComplete();
    void findTask() const;
    void editTask();
    void deleteTask();
    void clearTasks();
    void saveTasks(const string& filename) const;
    void loadTasks(const string& filename);
};

void displayMenu();

#endif
