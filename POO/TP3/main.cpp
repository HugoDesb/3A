#include <iostream>
#include "PileGen.h"
#include <string>

using namespace std;

int main(void){
  string a = "Youpi";
  PileGen<int> stack (4, a);
  stack.push(5);
  //affiche 5
  cout << stack.top() <<endl;

  stack.push(7);
  stack.push(12);
  stack.push(-1);
  stack.push(2);
  stack.push(1);
  //affiche stack 
  cout << stack <<endl;

  //affiche 1
  cout << stack.pop() <<endl;
  //affiche 2
  cout << stack.top() <<endl;

  //affiche -1
  stack.pop();
  cout << stack.top() <<endl ;


  
}
