// main() program to test your schedule function.
// Feel free to modify this program in any way you need for testing.
// It will not be graded. 
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "schedwork.h"


using namespace std;

void printSchedule(const DailySchedule& sched);
bool verifySchedule(const DailySchedule& sched, const vector<vector<Worker_T>>& expected);

int main()
{
    vector<pair<AvailabilityMatrix, vector<vector<Worker_T>>>> testCases = {
        {
            {{1, 1, 1, 1}, {1, 0, 1, 0}, {1, 1, 0, 1}, {1, 0, 0, 1}}, // Availability
            {{0, 1}, {0, 2}, {0, 2}, {0, 3}} // Expected schedule
        },
        {
            {{1, 1, 1}, {0, 1, 1}, {1, 0, 1}}, // Fewer workers, some unavailable
            {{0, 1}, {1, 2}, {0, 2}} // Expected schedule
        },
        {
            {{1, 1}, {1, 1}}, // All workers always available
            {{0, 1}, {0, 1}} // Expected schedule
        }
    };

    for (int i = 0; i < testCases.size(); ++i) {
        DailySchedule sched;
        bool solutionFound = schedule(testCases[i].first, 2, 2, sched);
        cout << "Test Case " << i+1 << ": ";
        if (solutionFound && verifySchedule(sched, testCases[i].second)) {
            cout << "Success!" << endl;
            printSchedule(sched);
        } else {
            cout << "Failure or Incorrect Output!" << endl;
            printSchedule(sched);
        }
    }

    return 0;
}

void printSchedule(const DailySchedule& sched)
{
    int day = 0;
    for(auto s : sched)
    {
        cout << "Day " << day << ": ";
        for(auto nurse : s)
        {
            cout << nurse << " ";
        }
        cout << endl;
        day++;
    }
}

bool verifySchedule(const DailySchedule& sched, const vector<vector<Worker_T>>& expected)
{
    if (sched.size() != expected.size()) return false;
    for (size_t i = 0; i < sched.size(); i++) {
        // Sort to ignore order in comparison
        vector<Worker_T> schedDay = sched[i];
        vector<Worker_T> expectedDay = expected[i];
        sort(schedDay.begin(), schedDay.end());
        sort(expectedDay.begin(), expectedDay.end());
        if (schedDay != expectedDay) return false;
    }
    return true;
}

