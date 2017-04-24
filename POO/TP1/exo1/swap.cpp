#include "swap.h"

using namespace std;

void swap(int a, int b){
  int t(a);
  a=b;
  b=t;
}

void swap_ref(int  & a, int  & b){
  int t(a);
  a=b;
  b=t;
  
}
