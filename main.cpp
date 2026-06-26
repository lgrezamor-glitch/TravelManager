#include "TravelManager.h"
#include <cctype>
#include <iostream>
#include <string>

using namespace std;

namespace {
string getInput(const string& prompt, bool allowEmpty = true) {
    while (true) {
        cout << prompt;
        string value;
        getline(cin, value);

        if (allowEmpty || !value.empty()) {
            return value;
        }

        cout << "This value cannot be empty.\n";
    }
}

bool parseInt(const string& text, int& value) {
    try {
        size_t pos = 0;
        value = stoi(text, &pos);
        while (pos < text.size() && isspace(static_cast<unsigned char>(text[pos]))) {
            ++pos;
        }
        return pos == text.size();
    } catch (...) {
        return false;
    }
}

bool parseDouble(const string& text, double& value) {
    try {
        size_t pos = 0;
        value = stod(text, &pos);
        while (pos < text.size() && isspace(static_cast<unsigned char>(text[pos]))) {
            ++pos;
        }
        return pos == text.size();
    } catch (...) {
        return false;
    }
}

int getInt(const string& prompt) {
    while (true) {
        string text = getInput(prompt);
        int value = 0;
        if (parseInt(text, value)) {
            return value;
        }
        cout << "Please enter a valid integer.\n";
    }
}

double getAmount(const string& prompt) {
    while (true) {
        string text = getInput(prompt);
        double value = 0;
        if (parseDouble(text, value) && value >= 0) {
            return value;
        }
        cout << "Please enter a non-negative amount.\n";
    }
}

void menuAddActivity(DayPlan* day) {
    cout << "\nActivity type:\n"
         << "1. Tourist visit\n"
         << "2. Meal\n"
         << "3. Transport\n";

    int choice = getInt("Choice: ");
    if (choice < 1 || choice > 3) {
        cout << "Invalid choice.\n";
        return;
    }

    string name = getInput("Activity name: ", false);
    string time = getInput("Time: ");
    string notes = getInput("Notes: ");

    if (choice == 1) {
        string location = getInput("Place or attraction name: ", false);
        day->addActivity(new TouristVisit(name, time, notes, location));
    } else if (choice == 2) {
        string restaurant = getInput("Restaurant name: ", false);
        day->addActivity(new MealActivity(name, time, notes, restaurant));
    } else {
        string vehicle = getInput("Vehicle: ", false);
        day->addActivity(new TransportActivity(name, time, notes, vehicle));
    }

    cout << "Activity added.\n";
}

void menuAddExpense(DayPlan* day) {
    cout << "\nExpense category:\n"
         << "1. Food\n"
         << "2. Transport\n"
         << "3. Accommodation\n"
         << "4. Shopping\n"
         << "5. Entertainment\n"
         << "6. Other\n";

    int choice = getInt("Choice: ");
    const string categories[] = {"Food", "Transport", "Accommodation", "Shopping", "Entertainment", "Other"};
    string category = (choice >= 1 && choice <= 6) ? categories[choice - 1] : "Other";

    string description = getInput("Expense description: ", false);
    double amount = getAmount("Amount (toman): ");

    day->addExpense(Expense(category, description, amount));
    cout << "Expense recorded.\n";
}

void menuDayManagement(Trip* trip) {
    while (true) {
        cout << "\nTrip day management\n"
             << "1. Add a new day\n"
             << "2. View all days\n"
             << "3. Add an activity to a day\n"
             << "4. Add an expense to a day\n"
             << "0. Back\n";

        int choice = getInt("Choice: ");
        if (choice == 0) {
            break;
        }

        if (choice == 1) {
            string date = getInput("Date, e.g. 2026/06/25: ", false);
            trip->addDay(new DayPlan(date));
            cout << "Day added.\n";
        } else if (choice == 2) {
            trip->displayFull();
        } else if (choice == 3 || choice == 4) {
            auto& days = trip->getDays();
            if (days.empty()) {
                cout << "Add a day first.\n";
                continue;
            }

            cout << "Days:\n";
            for (int i = 0; i < static_cast<int>(days.size()); ++i) {
                cout << (i + 1) << ". " << days[i]->getDate() << "\n";
            }

            int index = getInt("Day number: ");
            if (index < 1 || index > static_cast<int>(days.size())) {
                cout << "Invalid day number.\n";
                continue;
            }

            DayPlan* day = days[index - 1];
            if (choice == 3) {
                menuAddActivity(day);
            } else {
                menuAddExpense(day);
            }
        } else {
            cout << "Invalid choice.\n";
        }
    }
}

void mainMenu(TravelManager& manager) {
    while (true) {
        cout << "\nTravel Manager\n"
             << "1. Create a new trip\n"
             << "2. View trip list\n"
             << "3. View trip details\n"
             << "4. Manage days, activities, and expenses\n"
             << "5. Save all trips to files\n"
             << "6. Load a trip from a file\n"
             << "0. Exit\n";

        int choice = getInt("Choice: ");

        if (choice == 0) {
            cout << "Exiting program.\n";
            break;
        }

        if (choice == 1) {
            cout << "\nCreate a new trip\n";
            string title = getInput("Trip title: ", false);
            string destination = getInput("Destination: ", false);
            string startDate = getInput("Start date: ");
            string endDate = getInput("End date: ");
            string notes = getInput("Notes, optional: ");

            manager.addTrip(new Trip(title, destination, startDate, endDate, notes));
            cout << "Trip created.\n";
        } else if (choice == 2) {
            cout << "\nTrip list\n";
            manager.listTrips();
        } else if (choice == 3) {
            Trip* trip = manager.selectTrip();
            if (trip != nullptr) {
                trip->displayFull();
            }
        } else if (choice == 4) {
            Trip* trip = manager.selectTrip();
            if (trip != nullptr) {
                menuDayManagement(trip);
            }
        } else if (choice == 5) {
            manager.saveAll();
        } else if (choice == 6) {
            string filename = getInput("File name, e.g. paris.trip: ", false);
            manager.loadFromFile(filename);
        } else {
            cout << "Invalid choice.\n";
        }
    }
}
}

int main() {
    TravelManager manager;
    mainMenu(manager);
    return 0;
}
