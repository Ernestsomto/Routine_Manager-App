// Todo_Routine_App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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

using namespace std;

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

        cout << "\nRecommended Schedule:\n";
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

        cout << "\nTime Allocation Breakdown:\n";
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

        cout << "\nProductivity Report:\n";
        cout << "Completed Tasks: " << completedTasks << "/" << tasks.size() << endl;
        cout << "Planned Time: " << totalPlanned << " minutes\n";
        cout << "Actual Time: " << fixed << setprecision(1) << totalActual << " minutes\n";
        cout << "Efficiency: " << (totalActual > 0 ? (totalPlanned / totalActual * 100) : 0) << "%\n";
    }

    void saveTasks() {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file for saving tasks.\n";
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
            cerr << "Error opening file for loading tasks.\n";
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

    void addTask() {
        string time, description, category;
        int duration, priority;
        bool recurring;

        cout << "Enter task time (HH:MM): ";
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

        Task newTask(time, description, duration, priority, recurring, category);
        if (!hasTimeConflict(newTask)) {
            tasks.push_back(newTask);
            cout << "Task added successfully.\n";
        }
        else {
            cout << "Task time conflicts with an existing task.\n";
        }
    }

    void trackTaskTime() {
        showTasks();
        cout << "Enter task number to track: ";
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
        }
    }

    void editTask() {
        showTasks();
        cout << "Enter task number to edit: ";
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
    }

    void deleteTask() {
        showTasks();
        cout << "Enter task number to delete: ";
        int index;
        cin >> index;

        if (index >= 0 && index < tasks.size()) {
            tasks.erase(tasks.begin() + index);
        }
    }

    void markTaskAsCompleted() {
        showTasks();
        cout << "Enter task number to mark as completed: ";
        int index;
        cin >> index;

        if (index >= 0 && index < tasks.size()) {
            tasks[index].completed = true;
            cout << "Task marked as completed.\n";
        }
    }

    void filterTasksByCategory() {
        cout << "Enter category to filter by (Work, Personal, Health, Learning): ";
        string category;
        cin.ignore();
        getline(cin, category);

        cout << "\nFiltered Tasks:\n";
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
        tm* localTime = localtime(&now);
        stringstream ss;
        ss << setw(2) << setfill('0') << localTime->tm_hour << ":"
            << setw(2) << setfill('0') << localTime->tm_min;
        string currentTime = ss.str();

        cout << "\nOverdue Tasks:\n";
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
        cout << "\nTasks:\n";
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
                break;
            }
        } while (choice != 0);
    }
};

int main() {
    TodoApp app;
    app.run();
    return 0;
}