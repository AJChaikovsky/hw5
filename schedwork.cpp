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
bool backtrack(size_t day, size_t slot, const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, std::vector<size_t>& shiftsUsed, DailySchedule& sched){
  size_t n = avail.size();
  size_t k = avail[0].size();

  // Base: every day filled
  if (day == n) {
    return true;
  }

  // If all slots are filled for this day, move to the next day
  if (slot == dailyNeed) {
    return backtrack(day + 1, 0, avail, dailyNeed, maxShifts, shiftsUsed, sched);
  }

  // Try every worker for this (day, slot)
  for (Worker_T w = 0; w < k; ++w) {
    // 1) must be available today
    if (!avail[day][w]) {
      continue;
    }

    //must not have exhausted maxShifts
    if (shiftsUsed[w] >= maxShifts){
      continue;
    }

    // must not already be scheduled earlier
    bool alreadyUsed = false;
    for (size_t i = 0; i < slot; ++i) {
      if (sched[day][i] == w) {
        alreadyUsed = true;
        break;
      }
    }
    if (alreadyUsed){
      continue;
    }

    sched[day][slot] = w;
    ++shiftsUsed[w];

    // recurse to next slot/day
    if (backtrack(day, slot + 1, avail, dailyNeed, maxShifts, shiftsUsed, sched)){
      return true;
    }
    // undo choice on failure
    --shiftsUsed[w];
    // (no need to reset sched[day][slot], it will be overwritten)
  }
  // no valid worker for this slot → backtrack
  return false;
}


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    size_t n = avail.size();
    if(n == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    size_t k = avail[0].size();
    //prepare an n x dailyNeed schedule
    sched.assign(n, std::vector<Worker_T>(dailyNeed));
    //track how many shifts each worker has been assigned
    std::vector<size_t> shiftsUsed(k, 0);
    //call recursive funtion
    return backtrack(0, 0, avail, dailyNeed, maxShifts, shiftsUsed, sched);

    

}

