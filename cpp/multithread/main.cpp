#include <iostream>
#include <thread>

using namespace std;

void print_message(int n) {
  for (int i = 0; i < n; i++) {
    cout << "Thread " << i << endl;
  }
}

int main() {
  // Create two threads.
  thread t1(print_message, 5);
  thread t2(print_message, 10);

  // Wait for the threads to finish.
  t1.join();
  t2.join();

  return 0;
}