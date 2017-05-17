#include <iostream>
#include "PileGen.h"

using namespace std;

int main(void){
  PileGen<int> stack;
  stack.push(5);
  cout << stack.top() <<endl;

  stack.push(7);
  cout << stack.pop() <<endl;
  cout << stack.top() <<endl;
}
