#ifndef _PMUTEX_
#define _PMUTEX_

#include <mutex>
#include <condition_variable>
#include <atomic>

using namespace std;

class PriorityMutex {
 public : 
  PriorityMutex();
  void lock(bool priority = false);
  void unlock();
 private : 
  mutex m;
  condition_variable_any cv;
  atomic<int> numPriorityWaiting;
  enum state{unlocked, locked, priority_locked} stateVar;
};

#endif
