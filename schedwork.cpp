#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool findSchedule(size_t dayIndex,const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<size_t>& shiftsCount);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail, //matrix of workers availabilty 
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    //sched.clear();
    // Add your code below
    //need to make sure number of workers for the day is what it needs to be 
    //need to make sure a worker didnt pass the max number of shifts 
    //need to make sure the worker is available before adding her to schedule 

    /*
    1) start by adding the workers (if theyre available) to the schedule 
        - keep adding someone until we reach "d" (num of people needed for each day) 
    2) if we get to a point where a worker is exceeding "m" (max amount of shifts for a worker)...
        - choose someone else
        - if we get to a point where we cant schedule anyone else, backtrack and redo the schedule for the day before (i think)
    3) Base case: we got to the last row and column in the schedule, return true and the result 
    */

    //produce n by d matrix. n = number of days d = number of workers 
        //- each spot is filled in with the workers ID number

    size_t n = avail.size();  // Number of days
    size_t k = avail[0].size();  // Number of workers
    sched.resize(n, vector<Worker_T>(dailyNeed, INVALID_ID));
    vector<size_t> shiftsCount(k, 0);  // Track number of shifts for each worker

    return findSchedule(0, avail, dailyNeed, maxShifts, sched, shiftsCount);




}
bool findSchedule(size_t dayIndex, const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<size_t>& shiftsCount) {
    if (dayIndex == avail.size()) {
        return true;  // All days have been scheduled successfully
    }

    const size_t k = avail[dayIndex].size();
    vector<Worker_T>& today = sched[dayIndex];
    vector<Worker_T> candidates;

    // Collect all available workers for today who have not exceeded maxShifts
    for (size_t i = 0; i < k; ++i) {
        if (avail[dayIndex][i] && shiftsCount[i] < maxShifts) {
            candidates.push_back(i);
        }
    }

    if (candidates.size() < dailyNeed) {
        return false;  // Not enough candidates to meet daily need
    }

    vector<bool> select(candidates.size(), false);
    fill(select.end() - dailyNeed, select.end(), true);

    do {
        today.clear();
        bool valid = true;
        for (size_t i = 0; i < select.size(); ++i) {
            if (select[i]) {
                today.push_back(candidates[i]);
                shiftsCount[candidates[i]]++;
                if (shiftsCount[candidates[i]] > maxShifts) {
                    valid = false;
                    break;
                }
            }
        }

        if (valid && findSchedule(dayIndex + 1, avail, dailyNeed, maxShifts, sched, shiftsCount)) {
            return true;
        }

        // Undo the changes if not valid or solution not found
        for (Worker_T worker : today) {
            if (worker < shiftsCount.size()) { // Ensure we are within bounds
                shiftsCount[worker]--;
            } else {
                cerr << "Error: Worker index out of bounds. Worker index: " << worker << ", shiftsCount size: " << shiftsCount.size() << endl;
                // Handle the error appropriately
            }
        }
        today.clear();

    } while (next_permutation(select.begin(), select.end()));

    return false;
}