#include "priority_mutex.h"
#include "priority_mutex.cc"
#include <cstdio>
#include <thread>
#include <vector> 
#include <cstdlib>

using namespace std;

PriorityMutex pm;

void threadChildFn(int i) {
    bool priority = false;
   if(i % 2 == 0) priority = true;

   pm.lock(priority);
   printf("I'm a CHILD thread with %s executing.\n", ((priority)? "PRIORITY" : "NO PRIORITY"));
   pm.unlock();

}

void threadFn(int i) { 
   bool priority = false;
   if(i % 2 == 0) priority = true;

   pm.lock(priority);
   printf("I'm a PARENT thread with %s executing.\n", ((priority)? "PRIORITY" : "NO PRIORITY"));

   vector<thread> threads;
   for(int j = 0; j < 10; j++) {
      threads.push_back(thread(threadChildFn, j));
   }
   pm.unlock();
   for(thread& th : threads) {
      th.join();
   }
  
}

int main() {
   printf("Testing Priority Mutex\n");
   printf("Spawning 10 threads with interleaved priority\n");

   vector<thread> threads;
   for(int i = 0; i < 10; i++) {
      threads.push_back(thread(threadFn, i));
   }
   for(thread& th : threads) {
      th.join();
   }

   printf("All done!\n");
   return 0;
}
