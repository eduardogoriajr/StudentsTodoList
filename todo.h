#ifndef TODO_H
#define TODO_H

#include <string>
using namespace std;

struct Task {
    string title;
    string description;
    bool completed;
};

class TodoList {
private:
    Task tasks[100];  // fixed-size array for simplicity
    int taskCount;

public:
    TodoList();

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

#endif
