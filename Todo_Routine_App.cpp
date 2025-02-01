<<<<<<< HEAD
//Program code for the App _ Todo_Routine_App planner - Des
//This is an app to manage daily recurring task as a way to
//manage time and be more productive while styaing focused.

//============== Code begins Here ============//
=======
// Todo_Routine_App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

>>>>>>> 970a6883e4bc3e14b8c2122a0d5a8781743e3905
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <windows.h>
#include <map>
#include <numeric> // For accumulate
#include <functional> // For count_if
<<<<<<< HEAD
#include <limits> // For numeric_limits

// Undefine the max macro to avoid conflicts
#ifdef max
#undef max
#endif

using namespace std;

// ANSI escape codes for colors
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string WHITE = "\033[37m";
const string BOLD = "\033[1m";

=======

using namespace std;

>>>>>>> 970a6883e4bc3e14b8c2122a0d5a8781743e3905
class Task {
public:
    string time;
    string description;
    int duration; // In minutes
    int priority; // 1-3 (1: High, 3: Low)
    bool completed;
    bool recurring;
    string category;

    Task(string t, string desc, int dur, int prio, bool rec, string cat)
        : time(t), description(desc), duration(dur), priority(prio),
        completed(false), recurring(rec), category(cat) {
    }
};

class TimeTracker {
private:
    map<string, pair<chrono::system_clock::time_point, bool>> timers; // <task_desc, <start_time, running>>

public:
    void startTimer(const string& taskDesc) {
        timers[taskDesc] = make_pair(chrono::system_clock::now(), true);
<<<<<<< HEAD
        auto startTime = chrono::system_clock::to_time_t(timers[taskDesc].first);
        char buffer[26];
        ctime_s(buffer, sizeof(buffer), &startTime);
        cout << GREEN << "Timer started for task: " << taskDesc << " at " << buffer << RESET;
=======
>>>>>>> 970a6883e4bc3e14b8c2122a0d5a8781743e3905
    }

    void stopTimer(const string& taskDesc) {
        if (timers.find(taskDesc) != timers.end()) {
            timers[taskDesc].second = false;
        }
    }

    double getElapsedTime(const string& taskDesc) {
        if (timers.find(taskDesc) != timers.end() && !timers[taskDesc].second) {
            auto end = chrono::system_clock::now();
            chrono::duration<double> elapsed = end - timers[taskDesc].first;
            return elapsed.count() / 60; // Return minutes
        }
        return 0.0;
    }
};

class TodoApp {
private:
    vector<Task> tasks;
    TimeTracker tracker;
    string filename = "schedule.csv";
    const vector<string> categories = { "Work", "Personal", "Health", "Learning" };

    // ... [Existing private methods] ...

    bool hasTimeConflict(const Task& newTask) {
        for (const auto& task : tasks) {
            if (task.time == newTask.time && !task.completed) {
                return true;
            }
        }
        return false;
    }

    void suggestOptimalSchedule() {
        sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
            return make_pair(a.priority, a.time) < make_pair(b.priority, b.time);
            });

<<<<<<< HEAD
        cout << BOLD << "\nRecommended Schedule:\n" << RESET;
=======
        cout << "\nRecommended Schedule:\n";
>>>>>>> 970a6883e4bc3e14b8c2122a0d5a8781743e3905
        cout << "=================================================\n";
        cout << "Time   | Priority | Duration | Category   | Task\n";
        cout << "=================================================\n";
        for (const auto& task : tasks) {
            if (!task.completed) {
                cout << left << setw(7) << task.time << "| "
                    << setw(9) << task.priority << "| "
                    << setw(9) << task.duration << "| "
                    << setw(11) << task.category << "| "
                    << task.description << endl;
            }
        }
        cout << "=================================================\n";
    }

    void showTimeAllocation() {
        map<string, int> categoryTime;
        for (const auto& task : tasks) {
            if (!task.completed) {
                categoryTime[task.category] += task.duration;
            }
        }

<<<<<<< HEAD
        cout << BOLD << "\nTime Allocation Breakdown:\n" << RESET;
=======
        cout << "\nTime Allocation Breakdown:\n";
>>>>>>> 970a6883e4bc3e14b8c2122a0d5a8781743e3905
        for (const auto& categoryTimePair : categoryTime) {
            const string& category = categoryTimePair.first;
            int minutes = categoryTimePair.second;
            cout << "- " << setw(10) << category << ": "
                << minutes / 60 << "h " << minutes % 60 << "m\n";
        }
    }

    void showProductivityReport() {
        int completedTasks = static_cast<int>(count_if(tasks.begin(), tasks.end(),
            [](const Task& t) { return t.completed; }));

        double totalPlanned = accumulate(tasks.begin(), tasks.end(), 0.0,
            [](double sum, const Task& t) { return sum + t.duration; });

        double totalActual = 0.0;
        for (const auto& task : tasks) {
            totalActual += tracker.getElapsedTime(task.description);
        }

<<<<<<< HEAD
        cout << BOLD << "\nProductivity Report:\n" << RESET;
=======
        cout << "\nProductivity Report:\n";
>>>>>>> 970a6883e4bc3e14b8c2122a0d5a8781743e3905
        cout << "Completed Tasks: " << completedTasks << "/" << tasks.size() << endl;
        cout << "Planned Time: " << totalPlanned << " minutes\n";
        cout << "Actual Time: " << fixed << setprecision(1) << totalActual << " minutes\n";
        cout << "Efficiency: " << (totalActual > 0 ? (totalPlanned / totalActual * 100) : 0) << "%\n";
    }

    void saveTasks() {
        ofstream file(filename);
        if (!file.is_open()) {
<<<<<<< HEAD
            cerr << RED << "Error opening file for saving tasks.\n" << RESET;
=======
            cerr << "Error opening file for saving tasks.\n";
>>>>>>> 970a6883e4bc3e14b8c2122a0d5a8781743e3905
            return;
        }

        for (const auto& task : tasks) {
            file << task.time << "," << task.description << "," << task.duration << ","
                << task.priority << "," << task.completed << "," << task.recurring << ","
                << task.category << "\n";
        }
        file.close();
    }

    void loadTasks() {
        ifstream file(filename);
        if (!file.is_open()) {
<<<<<<< HEAD
            cerr << RED << "Error opening file for loading tasks.\n" << RESET;
=======
            cerr << "Error opening file for loading tasks.\n";
>>>>>>> 970a6883e4bc3e14b8c2122a0d5a8781743e3905
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string time, description, category;
            int duration, priority;
            bool completed, recurring;

            getline(ss, time, ',');
            getline(ss, description, ',');
            ss >> duration;
            ss.ignore();
            ss >> priority;
            ss.ignore();
            ss >> completed;
            ss.ignore();
            ss >> recurring;
            ss.ignore();
            getline(ss, category, ',');

            tasks.emplace_back(time, description, duration, priority, recurring, category);
            tasks.back().completed = completed;
        }
        file.close();
    }

    void addRecurringTasks() {
        vector<Task> newTasks;
        for (const auto& task : tasks) {
            if (task.recurring && task.completed) {
                Task newTask = task;
                newTask.completed = false;
                newTasks.push_back(newTask);
            }
        }
        tasks.insert(tasks.end(), newTasks.begin(), newTasks.end());
    }

<<<<<<< HEAD
    // Helper function to validate integer input within a range
    int validateInput(int min, int max) {
        int choice;
        while (true) {
            cin >> choice;
            if (cin.fail() || choice < min || choice > max) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard any extra input
                cout << RED << "Invalid input. Please enter a number between " << min << " and " << max << ".\n" << RESET;
            }
            else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard any extra input
                return choice;
            }
        }
    }

    // Helper function to validate string input for categories
    string validateCategoryInput(const vector<string>& categories) {
        string category;
        while (true) {
            getline(cin, category);
            if (find(categories.begin(), categories.end(), category) != categories.end()) {
                return category;
            }
            else {
                cout << RED << "Invalid category. Please enter one of the following: ";
                for (const auto& cat : categories) {
                    cout << cat << " ";
                }
                cout << "\n" << RESET;
            }
        }
    }

    // Helper function to validate time input in HH:MM format
    string validateTimeInput() {
        string time;
        while (true) {
            getline(cin, time);
            if (time.size() == 5 && time[2] == ':' && isdigit(time[0]) && isdigit(time[1]) && isdigit(time[3]) && isdigit(time[4])) {
                int hours = stoi(time.substr(0, 2));
                int minutes = stoi(time.substr(3, 2));
                if (hours >= 0 && hours < 24 && minutes >= 0 && minutes < 60) {
                    return time;
                }
            }
            cout << RED << "Invalid time format. Please enter time in HH:MM format.\n" << RESET;
        }
    }

=======
>>>>>>> 970a6883e4bc3e14b8c2122a0d5a8781743e3905
public:
    TodoApp() {
        loadTasks();
        addRecurringTasks();
    }

    ~TodoApp() {
        saveTasks();
    }

    // ... [Existing public methods] ...

    void planDay() {
<<<<<<< HEAD
        cout << BOLD << "\nDaily Planning Assistant\n" << RESET;
        cout << "0. " << RED << "Exit" << RESET << "\n";
        cout << "1. " << GREEN << "Add Task with Name" << RESET << "\n";
        cout << "2. " << GREEN << "Add Task" << RESET << "\n";
        cout << "3. " << GREEN << "Edit Task" << RESET << "\n";
        cout << "4. " << GREEN << "Delete Task" << RESET << "\n";
        cout << "5. " << GREEN << "Auto-schedule Tasks" << RESET << "\n";
        cout << "6. " << GREEN << "Review Time Allocation" << RESET << "\n";
        cout << "7. " << GREEN << "Track Task Time" << RESET << "\n";
        cout << "8. " << GREEN << "View Productivity Report" << RESET << "\n";
        cout << "9. " << GREEN << "Mark Task as Completed" << RESET << "\n";
        cout << "10. " << GREEN << "Filter Tasks by Category" << RESET << "\n";
        cout << "11. " << GREEN << "View Overdue Tasks" << RESET << "\n";
        // ... Add more planning options
    }

    void addTaskWithName() {
        string taskName;
        cout << "Enter task name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
        getline(cin, taskName);

        string time, description, category;
        int duration, priority;
        bool recurring;

        cout << "Enter task time (HH:MM): ";
        time = validateTimeInput();
        cout << "Enter task description: ";
        getline(cin, description);
        cout << "Enter task duration (in minutes): ";
        duration = validateInput(1, numeric_limits<int>::max());
        cout << "Enter task priority (1-3): ";
        priority = validateInput(1, 3);
        cout << "Enter task category (Work, Personal, Health, Learning): ";
        category = validateCategoryInput(categories);
        cout << "Is the task recurring? (1 for yes, 0 for no): ";
        recurring = validateInput(0, 1);

        Task newTask(time, taskName + ": " + description, duration, priority, recurring, category);
        if (!hasTimeConflict(newTask)) {
            tasks.push_back(newTask);
            cout << GREEN << "Task added successfully.\n" << RESET;
        }
        else {
            cout << RED << "Task time conflicts with an existing task.\n" << RESET;
        }
    }

=======
        cout << "\nDaily Planning Assistant\n";
        cout << "1. Add Task\n";
        cout << "2. Edit Task\n";
        cout << "3. Delete Task\n";
        cout << "4. Auto-schedule Tasks\n";
        cout << "5. Review Time Allocation\n";
        cout << "6. Track Task Time\n";
        cout << "7. View Productivity Report\n";
        cout << "8. Mark Task as Completed\n";
        cout << "9. Filter Tasks by Category\n";
        cout << "10. View Overdue Tasks\n";
        // ... Add more planning options
    }

>>>>>>> 970a6883e4bc3e14b8c2122a0d5a8781743e3905
    void addTask() {
        string time, description, category;
        int duration, priority;
        bool recurring;

        cout << "Enter task time (HH:MM): ";
<<<<<<< HEAD
        time = validateTimeInput();
        cout << "Enter task description: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
        getline(cin, description);
        cout << "Enter task duration (in minutes): ";
        duration = validateInput(1, numeric_limits<int>::max());
        cout << "Enter task priority (1-3): ";
        priority = validateInput(1, 3);
        cout << "Enter task category (Work, Personal, Health, Learning): ";
        category = validateCategoryInput(categories);
        cout << "Is the task recurring? (1 for yes, 0 for no): ";
        recurring = validateInput(0, 1);
=======
        cin >> time;
        cout << "Enter task description: ";
        cin.ignore();
        getline(cin, description);
        cout << "Enter task duration (in minutes): ";
        cin >> duration;
        cout << "Enter task priority (1-3): ";
        cin >> priority;
        cout << "Enter task category (Work, Personal, Health, Learning): ";
        cin.ignore();
        getline(cin, category);
        cout << "Is the task recurring? (1 for yes, 0 for no): ";
        cin >> recurring;
>>>>>>> 970a6883e4bc3e14b8c2122a0d5a8781743e3905

        Task newTask(time, description, duration, priority, recurring, category);
        if (!hasTimeConflict(newTask)) {
            tasks.push_back(newTask);
<<<<<<< HEAD
            cout << GREEN << "Task added successfully.\n" << RESET;
        }
        else {
            cout << RED << "Task time conflicts with an existing task.\n" << RESET;
=======
            cout << "Task added successfully.\n";
        }
        else {
            cout << "Task time conflicts with an existing task.\n";
>>>>>>> 970a6883e4bc3e14b8c2122a0d5a8781743e3905
        }
    }

    void trackTaskTime() {
        showTasks();
        cout << "Enter task number to track: ";
<<<<<<< HEAD
        int index = validateInput(0, static_cast<int>(tasks.size()) - 1);

        cout << "1. Start Timer\n2. Stop Timer\nChoice: ";
        int choice = validateInput(1, 2);

        if (choice == 1) {
            tracker.startTimer(tasks[index].description);
            cout << GREEN << "Timer started for: " << tasks[index].description << endl << RESET;
        }
        else if (choice == 2) {
            tracker.stopTimer(tasks[index].description);
            double elapsed = tracker.getElapsedTime(tasks[index].description);
            cout << "Time spent: " << elapsed << " minutes\n";
=======
        int index;
        cin >> index;

        if (index >= 0 && index < tasks.size()) {
            cout << "1. Start Timer\n2. Stop Timer\nChoice: ";
            int choice;
            cin >> choice;

            if (choice == 1) {
                tracker.startTimer(tasks[index].description);
                cout << "Timer started for: " << tasks[index].description << endl;
            }
            else if (choice == 2) {
                tracker.stopTimer(tasks[index].description);
                double elapsed = tracker.getElapsedTime(tasks[index].description);
                cout << "Time spent: " << elapsed << " minutes\n";
            }
>>>>>>> 970a6883e4bc3e14b8c2122a0d5a8781743e3905
        }
    }

    void editTask() {
        showTasks();
        cout << "Enter task number to edit: ";
<<<<<<< HEAD
        int index = validateInput(0, static_cast<int>(tasks.size()) - 1);

        cout << "Enter new time (HH:MM): ";
        tasks[index].time = validateTimeInput();
        cout << "Enter new description: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
        getline(cin, tasks[index].description);
        cout << "Enter new duration (in minutes): ";
        tasks[index].duration = validateInput(1, numeric_limits<int>::max());
        cout << "Enter new priority (1-3): ";
        tasks[index].priority = validateInput(1, 3);
        cout << "Enter new category (Work, Personal, Health, Learning): ";
        tasks[index].category = validateCategoryInput(categories);
        cout << "Is it recurring? (1 for yes, 0 for no): ";
        tasks[index].recurring = validateInput(0, 1);
=======
        int index;
        cin >> index;

        if (index >= 0 && index < tasks.size()) {
            cout << "Enter new time: ";
            cin >> tasks[index].time;
            cout << "Enter new description: ";
            cin.ignore();
            getline(cin, tasks[index].description);
            cout << "Enter new duration: ";
            cin >> tasks[index].duration;
            cout << "Enter new priority: ";
            cin >> tasks[index].priority;
            cout << "Enter new category: ";
            cin.ignore();
            getline(cin, tasks[index].category);
            cout << "Is it recurring? (1 for yes, 0 for no): ";
            cin >> tasks[index].recurring;
        }
>>>>>>> 970a6883e4bc3e14b8c2122a0d5a8781743e3905
    }

    void deleteTask() {
        showTasks();
        cout << "Enter task number to delete: ";
<<<<<<< HEAD
        int index = validateInput(0, static_cast<int>(tasks.size()) - 1);

        tasks.erase(tasks.begin() + index);
        cout << GREEN << "Task deleted successfully.\n" << RESET;
=======
        int index;
        cin >> index;

        if (index >= 0 && index < tasks.size()) {
            tasks.erase(tasks.begin() + index);
        }
>>>>>>> 970a6883e4bc3e14b8c2122a0d5a8781743e3905
    }

    void markTaskAsCompleted() {
        showTasks();
        cout << "Enter task number to mark as completed: ";
<<<<<<< HEAD
        int index = validateInput(0, static_cast<int>(tasks.size()) - 1);

        tasks[index].completed = true;
        cout << GREEN << "Task marked as completed.\n" << RESET;
=======
        int index;
        cin >> index;

        if (index >= 0 && index < tasks.size()) {
            tasks[index].completed = true;
            cout << "Task marked as completed.\n";
        }
>>>>>>> 970a6883e4bc3e14b8c2122a0d5a8781743e3905
    }

    void filterTasksByCategory() {
        cout << "Enter category to filter by (Work, Personal, Health, Learning): ";
        string category;
        cin.ignore();
<<<<<<< HEAD
        category = validateCategoryInput(categories);

        cout << BOLD << "\nFiltered Tasks:\n" << RESET;
=======
        getline(cin, category);

        cout << "\nFiltered Tasks:\n";
>>>>>>> 970a6883e4bc3e14b8c2122a0d5a8781743e3905
        for (size_t i = 0; i < tasks.size(); ++i) {
            if (tasks[i].category == category) {
                cout << i << ". " << tasks[i].time << " - " << tasks[i].description << " ("
                    << tasks[i].duration << " mins, Priority: " << tasks[i].priority
                    << ", Recurring: " << tasks[i].recurring
                    << ", Completed: " << tasks[i].completed << ")\n";
            }
        }
    }

    void viewOverdueTasks() {
        auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
<<<<<<< HEAD
        tm localTime;
        localtime_s(&localTime, &now);
        stringstream ss;
        ss << setw(2) << setfill('0') << localTime.tm_hour << ":"
            << setw(2) << setfill('0') << localTime.tm_min;
        string currentTime = ss.str();

        cout << BOLD << "\nOverdue Tasks:\n" << RESET;
=======
        tm* localTime = localtime(&now);
        stringstream ss;
        ss << setw(2) << setfill('0') << localTime->tm_hour << ":"
            << setw(2) << setfill('0') << localTime->tm_min;
        string currentTime = ss.str();

        cout << "\nOverdue Tasks:\n";
>>>>>>> 970a6883e4bc3e14b8c2122a0d5a8781743e3905
        for (const auto& task : tasks) {
            if (task.time < currentTime && !task.completed) {
                cout << task.time << " - " << task.description << " ("
                    << task.duration << " mins, Priority: " << task.priority
                    << ", Category: " << task.category << ", Recurring: " << task.recurring
                    << ", Completed: " << task.completed << ")\n";
            }
        }
    }

    void showTasks() {
<<<<<<< HEAD
        cout << BOLD << "\nTasks:\n" << RESET;
=======
        cout << "\nTasks:\n";
>>>>>>> 970a6883e4bc3e14b8c2122a0d5a8781743e3905
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i << ". " << tasks[i].time << " - " << tasks[i].description << " ("
                << tasks[i].duration << " mins, Priority: " << tasks[i].priority
                << ", Category: " << tasks[i].category << ", Recurring: " << tasks[i].recurring
                << ", Completed: " << tasks[i].completed << ")\n";
        }
    }

    void run() {
        int choice;
        do {
            planDay();
            cout << "Enter choice: ";
<<<<<<< HEAD
            choice = validateInput(0, 11); // Assuming 0 is the exit option and 11 is the highest option

            switch (choice) {
            case 0:
                cout << GREEN << "Exiting the application.\n" << RESET;
                break;
            case 1:
                addTaskWithName();
                break;
            case 2:
                addTask();
                break;
            case 3:
                editTask();
                break;
            case 4:
                deleteTask();
                break;
            case 5:
                suggestOptimalSchedule();
                break;
            case 6:
                showTimeAllocation();
                break;
            case 7:
                trackTaskTime();
                break;
            case 8:
                showProductivityReport();
                break;
            case 9:
                markTaskAsCompleted();
                break;
            case 10:
                filterTasksByCategory();
                break;
            case 11:
                viewOverdueTasks();
                break;
            default:
                cout << RED << "Invalid choice. Please try again.\n" << RESET;
=======
            cin >> choice;

            switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                editTask();
                break;
            case 3:
                deleteTask();
                break;
            case 4:
                suggestOptimalSchedule();
                break;
            case 5:
                showTimeAllocation();
                break;
            case 6:
                trackTaskTime();
                break;
            case 7:
                showProductivityReport();
                break;
            case 8:
                markTaskAsCompleted();
                break;
            case 9:
                filterTasksByCategory();
                break;
            case 10:
                viewOverdueTasks();
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
>>>>>>> 970a6883e4bc3e14b8c2122a0d5a8781743e3905
                break;
            }
        } while (choice != 0);
    }
};

int main() {
    TodoApp app;
<<<<<<< HEAD
    app.run(); // Call the run method to start the application
    return 0; // Ensure the main function returns an integer
=======
    app.run();
    return 0;
>>>>>>> 970a6883e4bc3e14b8c2122a0d5a8781743e3905
}