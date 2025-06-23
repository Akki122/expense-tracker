#include <iostream>
#include <string>
#include "expense_manager.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./expense-tracker <command> [options]\n";
        return 1;
    }

    std::string command = argv[1];

    if (command == "add") {
        std::string description;
        double amount = 0.0;
        for (int i = 2; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "--description" && i + 1 < argc) {
                description = argv[++i];
            } else if (arg == "--amount" && i + 1 < argc) {
                amount = std::stod(argv[++i]);
            }
        }
        if (!description.empty() && amount > 0)
            addExpense(description, amount);
        else
            std::cerr << "Missing description or amount.\n";

    } else if (command == "delete") {
        int id = -1;
        for (int i = 2; i < argc; ++i) {
            if (std::string(argv[i]) == "--id" && i + 1 < argc) {
                id = std::stoi(argv[++i]);
            }
        }
        if (id > 0)
            deleteExpense(id);
        else
            std::cerr << "Invalid ID.\n";

    } else if (command == "update") {
        int id = -1;
        std::string description;
        double amount = -1;
        for (int i = 2; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "--id" && i + 1 < argc)
                id = std::stoi(argv[++i]);
            else if (arg == "--description" && i + 1 < argc)
                description = argv[++i];
            else if (arg == "--amount" && i + 1 < argc)
                amount = std::stod(argv[++i]);
        }
        if (id > 0 && !description.empty() && amount >= 0)
            updateExpense(id, description, amount);
        else
            std::cerr << "Invalid update parameters.\n";

    } else if (command == "list") {
        listExpenses();

    } else if (command == "summary") {
        int month = -1;
        for (int i = 2; i < argc; ++i) {
            if (std::string(argv[i]) == "--month" && i + 1 < argc)
                month = std::stoi(argv[++i]);
        }
        showSummary(month);

    } else {
        std::cerr << "Unknown command: " << command << "\n";
    }

    return 0;
}
