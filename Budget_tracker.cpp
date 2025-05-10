#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
using namespace std;

struct Expense {
string category;
double amount;
string description;
};

void loadExpensesFromFile(vector<Expense>& expenses) {
ifstream inFile("expenses.txt");
if (!inFile.is_open()) {
cout << "Could not open expenses.txt file for reading.\n";
return;
}

Expense e;
while (inFile >> e.category >> e.amount) {
inFile.ignore();
getline(inFile, e.description);
expenses.push_back(e);
}
}

void saveExpensesToFile(const vector<Expense>& expenses) {
ofstream outFile("expenses.txt");
for (const auto& e : expenses)
outFile << e.category << " " << e.amount << "\n" << e.description << "\n";
}

bool isValidAmount(double amount) {
return amount >= 0;
}

void clearExpensesFile() {
ofstream outFile("expenses.txt", ios::trunc);  
if (outFile.is_open()) {
outFile.close();  
cout << "All expenses data has been cleared.\n";
} else
cout << "Failed to clear the file.\n";
}

int main() {
vector<Expense> expenses;
loadExpensesFromFile(expenses);

int choice;
do {
cout << "\n---Budget Tracker---\n";
cout << "1. Add Expense\n";
cout << "2. View All Expenses\n";
cout << "3. View Total\n";
cout << "4. Clear All Data\n";
cout << "5. Exit\n";
cout << "Choose an option: ";
cin >> choice;

if (choice == 1) {
Expense e;
cin.ignore();
cout << "Enter category: ";
getline(cin, e.category);

do {
cout << "Enter amount: ";
cin >> e.amount;
if (cin.fail() || !isValidAmount(e.amount)) {
cin.clear();
cin.ignore(numeric_limits<streamsize>::max(), '\n');
cout << "Invalid amount. Please enter a valid amount.\n";
}
} while (cin.fail() || !isValidAmount(e.amount));

cin.ignore();
cout << "Enter description: ";
getline(cin, e.description);

expenses.push_back(e);
saveExpensesToFile(expenses);
}
else if (choice == 2) {
cout << "\n--- Expenses List ---\n";
if (expenses.empty())
cout << "No expenses added yet.\n";
else
for (const auto& e : expenses)
cout << e.category << " - $" << e.amount << " (" << e.description << ")\n";
}
else if (choice == 3) {
double total = 0;
for (const auto& e : expenses)
total += e.amount;
cout << "Total amount spent: $" << total << "\n";
}
else if (choice == 4) {
clearExpensesFile();
expenses.clear();
}
else if (choice == 5)
cout << "Thank you for using Budget Tracker!\n";
else {
cin.clear();
cin.ignore(numeric_limits<streamsize>::max(), '\n');
cout << "Invalid choice. Try again.\n";
}
} while (choice != 5);

return 0;
}