//defines the header file
#ifndef TODOLIST_H
#define TODOLIST_H

//includes required libraries
#include <string>
#include <queue>
using namespace std;

//blueprints and containers for data

//task node used for linked list structure, each node represents a saved task
struct TaskNode {
    string title;       //title of the task
    string dueDate;     //note or due date for task
    bool completed;     //status flag (true = done, false = pending)
    TaskNode* next;     //pointer to next task in the linked list
};

//temporary task container stored inside queue before committing to the main list
struct QueuedTask {
    string title;       //title of the task
    string dueDate;     //note or due date
};

//class definition that contains logic for task management
class ToDoList {
private:
    //pointer to the head of the linked list (used to store saved tasks)
    TaskNode* head = NULL;
    //queue to temporarily hold user input before saving
    queue<QueuedTask> taskQueue;

//public containts the fuctions that would be called by void
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

