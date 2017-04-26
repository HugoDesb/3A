#include <iostream>
#include "myvector.h"

using namespace std;

int main(void){
  MyVector a(4), b, c(a);

  //test set
  a.set_item(0, 4);
  a.set_item(1, 7);
  a.set_item(2, 18);
  a.set_item(3, -2);

  //test print
  a.print();
  b.print();
  c.print();

  // test adjust size
  a.adjustSize(-2);
  a.print();
  a.adjustSize(5);
  a.print();

  // test = operator
  b = a;
  b.print();

  //test nbAcces
  cout << b.get_item(1) << endl;
  b.print();
}
