// expense_manager.h
#ifndef EXPENSE_MANAGER_H
#define EXPENSE_MANAGER_H

#include <string>

void addExpense(const std::string& description, double amount);
void deleteExpense(int id);
void updateExpense(int id, const std::string& description, double amount);
void listExpenses();
void showSummary(int month = -1);

#endif
