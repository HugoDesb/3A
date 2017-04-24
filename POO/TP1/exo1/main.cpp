#include <iostream>
#include "swap.h"

using namespace std;



int main(void){

  
  int a(3),b(7);

  cout << "a = " << a << endl; 
  cout << "b = " << b << endl;
  
  swap_ref(a,b);
  
  cout << "a = " << a << endl; 
  cout << "b = " << b << endl;
  
}
