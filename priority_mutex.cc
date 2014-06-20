#include <thread>
#include "priority_mutex.h"

using namespace std;

PriorityMutex::PriorityMutex() {
  stateVar = unlocked;
  numPriorityWaiting = 0;
}

void PriorityMutex::lock(bool priority) {
  if(priority) numPriorityWaiting++;
  m.lock();
  if(!priority) {
    m.unlock();
    this_thread::yield(); //give a chance for all other threads that are priority to execute
    m.lock();
  }
  cv.wait(m, [this, priority] {return (priority || numPriorityWaiting == 0);});
  if(priority) {
    stateVar = priority_locked;
  } else {
    stateVar = locked;
  } 
}

void PriorityMutex::unlock() {
  if(stateVar == priority_locked) {
    numPriorityWaiting--;
  }
  if(numPriorityWaiting == 0) cv.notify_all();
  m.unlock();
}
