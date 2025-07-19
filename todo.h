#ifndef TODOLIST_H
#define TODOLIST_H
#include <string>
#include <queue>
using namespace std;

//blueprints and containers for data
struct TaskNode {
    string title;
    string dueDate;
    bool completed;
    TaskNode* next;
};

struct QueuedTask {
    string title;
    string dueDate;
};

class ToDoList {
private:
    TaskNode* head = NULL;
    queue<QueuedTask> taskQueue;

public:
    void addToQueue();
    void undoLastQueuedTask();
    void processQueue();
    void viewAllTasks() const;
    void viewCompletedTasks() const;
    void markTaskComplete();
    void findTask();
    void deleteTask();
    void clearAllTasks();
    void loadFromFile(const string& filename);
    void saveToFile(const string& filename) const;
    void exitProgram(const string& filename);
    void displayQueuedTasks() const;
    void displayMenu() const;
};

#endif
