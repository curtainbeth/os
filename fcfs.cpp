#include <iostream>
#include <vector>

using namespace std;

class Process {
public:
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;

    Process(int at, int bt) {
        arrivalTime = at;
        burstTime = bt;
        completionTime = 0;
        turnAroundTime = 0;
        waitingTime = 0;
    }

    void calculateTimes(int currentTime) {
        completionTime = currentTime + burstTime;
        turnAroundTime = completionTime - arrivalTime;
        waitingTime = turnAroundTime - burstTime;
    }
};

class FCFS {
private:
    vector<Process> processes;

public:
    void addProcess(int arrivalTime, int burstTime) {
        processes.push_back(Process(arrivalTime, burstTime));
    }

    void calculateSchedule() {
        int currentTime = 0;
        for (size_t i = 0; i < processes.size(); ++i) {
            if (currentTime < processes[i].arrivalTime) {
                currentTime = processes[i].arrivalTime;
            }
            processes[i].calculateTimes(currentTime);
            currentTime = processes[i].completionTime;
        }
    }

    void displayResults() {
        float totalTurnAroundTime = 0, totalWaitingTime = 0;
        cout << "Process\tAT\tBT\tCT\tTAT\tWT\n";
        for (size_t i = 0; i < processes.size(); ++i) {
            totalTurnAroundTime += processes[i].turnAroundTime;
            totalWaitingTime += processes[i].waitingTime;
            cout << "P" << i + 1 << "\t" 
                 << processes[i].arrivalTime << "\t"
                 << processes[i].burstTime << "\t"
                 << processes[i].completionTime << "\t"
                 << processes[i].turnAroundTime << "\t"
                 << processes[i].waitingTime << "\n";
        }
        cout << "\nAverage Turnaround Time: " 
             << totalTurnAroundTime / processes.size() << "\n";
        cout << "Average Waiting Time: "
             << totalWaitingTime / processes.size() << "\n";
    }
};

int main() {
    FCFS scheduler;

    int n;
    cout << "Enter the total number of processes: ";
    cin >> n;

    cout << "\nEnter the Process Arrival Time & Burst Time\n";
    for (int i = 0; i < n; ++i) {
        int at, bt;
        cout << "Enter Arrival time of process[" << i + 1 << "]: ";
        cin >> at;
        cout << "Enter Burst time of process[" << i + 1 << "]: ";
        cin >> bt;
        scheduler.addProcess(at, bt);
    }

    scheduler.calculateSchedule();
    scheduler.displayResults();

    return 0;
}
