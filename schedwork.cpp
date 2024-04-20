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
bool backtrack(size_t day, DailySchedule& sched, const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, vector<size_t>& shiftsCount);
bool findCombination(size_t start, size_t selected, size_t need, size_t day, DailySchedule& sched, const AvailabilityMatrix& avail, size_t maxShifts, vector<size_t>& shiftsCount, const vector<Worker_T>& possibleWorkers);
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
    sched.resize(n, std::vector<Worker_T>(dailyNeed, INVALID_ID));
    std::vector<size_t> shiftsCount(k, 0);  // Track number of shifts for each worker

    return backtrack(0, sched, avail, dailyNeed, maxShifts, shiftsCount);




}
bool backtrack(size_t day, DailySchedule& sched, const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, vector<size_t>& shiftsCount) {
    if (day == avail.size()) return true;

    vector<Worker_T> possibleWorkers;
    for (size_t worker = 0; worker < avail[day].size(); ++worker) {
        if (avail[day][worker] && shiftsCount[worker] < maxShifts) {
            possibleWorkers.push_back(worker);
        }
    }

    return findCombination(0, 0, dailyNeed, day, sched, avail, maxShifts, shiftsCount, possibleWorkers);
}

bool findCombination(size_t start, size_t selected, size_t need, size_t day, DailySchedule& sched, const AvailabilityMatrix& avail, size_t maxShifts, vector<size_t>& shiftsCount, const vector<Worker_T>& possibleWorkers) {
    if (selected == need) {
        return backtrack(day + 1, sched, avail, need, maxShifts, shiftsCount);
    }

    for (size_t i = start; i < possibleWorkers.size(); ++i) {
        Worker_T worker = possibleWorkers[i];
        sched[day][selected] = worker;
        ++shiftsCount[worker];
        if (shiftsCount[worker] <= maxShifts && findCombination(i + 1, selected + 1, need, day, sched, avail, maxShifts, shiftsCount, possibleWorkers)) {
            return true;
        }
        --shiftsCount[worker];
    }

    return false;
}