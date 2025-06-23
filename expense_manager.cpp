#include "expense_manager.h"
#include "json.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <ctime>

using json = nlohmann::json;
const std::string FILE_NAME = "expenses.json";

json readExpenses() {
    std::ifstream in(FILE_NAME);
    if (!in) return json::array();
    json data;
    in >> data;
    return data;
}

void writeExpenses(const json& data) {
    std::ofstream out(FILE_NAME);
    out << std::setw(4) << data << std::endl;
}

std::string getTodayDate() {
    time_t t = time(nullptr);
    char buf[11];
    strftime(buf, sizeof(buf), "%Y-%m-%d", localtime(&t));
    return std::string(buf);
}

void addExpense(const std::string& description, double amount) {
    json data = readExpenses();
    int id = data.empty() ? 1 : data.back()["id"].get<int>() + 1;

    data.push_back({
        {"id", id},
        {"date", getTodayDate()},
        {"description", description},
        {"amount", amount}
    });

    writeExpenses(data);
    std::cout << "Expense added successfully (ID: " << id << ")\n";
}

void deleteExpense(int id) {
    json data = readExpenses();
    bool found = false;
    for (auto it = data.begin(); it != data.end(); ++it) {
        if ((*it)["id"] == id) {
            data.erase(it);
            found = true;
            break;
        }
    }
    if (found) {
        writeExpenses(data);
        std::cout << "Expense deleted successfully\n";
    } else {
        std::cerr << "Error: Expense with ID " << id << " not found\n";
    }
}

void updateExpense(int id, const std::string& description, double amount) {
    json data = readExpenses();
    bool found = false;
    for (auto& item : data) {
        if (item["id"] == id) {
            item["description"] = description;
            item["amount"] = amount;
            found = true;
            break;
        }
    }
    if (found) {
        writeExpenses(data);
        std::cout << "Expense updated successfully\n";
    } else {
        std::cerr << "Error: Expense with ID " << id << " not found\n";
    }
}

void listExpenses() {
    json data = readExpenses();
    std::cout << "# ID  Date        Description    Amount\n";
    for (const auto& item : data) {
        std::cout << "# " << item["id"] << "   "
                  << item["date"] << "   "
                  << item["description"] << "     $"
                  << item["amount"] << "\n";
    }
}

void showSummary(int month) {
    json data = readExpenses();
    double total = 0;
    for (const auto& item : data) {
        std::string date = item["date"];
        if (month == -1 || std::stoi(date.substr(5, 2)) == month) {
            total += item["amount"].get<double>();
        }
    }
    if (month == -1)
        std::cout << "# Total expenses: $" << total << "\n";
    else
        std::cout << "# Total expenses for month " << month << ": $" << total << "\n";
}
