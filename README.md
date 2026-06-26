# Travel Manager

Travel Manager is a simple C++17 console application for recording and managing trips. It stores each trip's general information, daily plans, activities, and expenses, and it can save data to or load data from plain-text `.trip` files.

## Features

- Create trips with a title, destination, start date, end date, and notes
- Add multiple days to each trip
- Record activities such as tourist visits, meals, and transport
- Record expenses and calculate both daily totals and the total trip cost
- Save and load data using plain-text `.trip` files
- Use an interactive terminal menu

## Project structure

```text
TravelManager/
├── main.cpp
├── include/
│   ├── Activity.h
│   ├── DayPlan.h
│   ├── Expense.h
│   ├── TravelManager.h
│   └── Trip.h
├── src/
│   ├── Activity.cpp
│   ├── DayPlan.cpp
│   ├── Expense.cpp
│   ├── TravelManager.cpp
│   └── Trip.cpp
├── build.bat
├── build.sh
├── .gitignore
└── README.md
```

## Build and run

### Linux / macOS

```bash
chmod +x build.sh
./build.sh
./TravelManager
```

Or compile directly with `g++`:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -I include main.cpp src/*.cpp -o TravelManager
./TravelManager
```

### Windows with MinGW

```bat
build.bat
TravelManager.exe
```

## Save-file format

Example `.trip` file:

```text
TRIP|Paris Summer Trip|Paris|2026/07/10|2026/07/13|Family vacation
DAY|2026/07/10
ACT|Visit|Eiffel Tower|10:00|Take photos|Eiffel Tower
EXP|Food|Lunch|250000.00
```

Each line starts with a tag:

- `TRIP`: general trip information
- `DAY`: one day of the trip
- `ACT`: one activity on the current day
- `EXP`: one expense on the current day

## Implementation notes

- `Activity` is the base class for activities; `TouristVisit`, `MealActivity`, and `TransportActivity` derive from it.
- Each `Trip` contains multiple `DayPlan` objects, and each `DayPlan` contains multiple activities and expenses.
- Numeric input is validated so invalid user input does not stop the program.
- When loading a file, malformed or incomplete lines are skipped and the program continues.
- The save-file name is generated from the trip title, and invalid file-name characters are replaced.
