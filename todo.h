#ifndef TODO_H
#define TODO_H

#include <queue>
#include <string>
using namespace std;

void loadQueueFromFile(queue<string>&, const string&);
void saveQueueToFile(const queue<string>&, const string&);
void addTask(queue<string>&);
void markTaskComplete(queue<string>&);
void viewAllTask();
void viewCompletedTask();
void editTask();
void deleteTask();
void clearAllTask();
void display(const queue<string>&);
void displayMenu();

#endif
