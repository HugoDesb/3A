#include <iostream>
#include "complexe.h"

using namespace std;

int main(void){

  Complexe a=Complexe(4, 2),b=Complexe(1,0),c=Complexe(6, 8);
  a.afficher();
  a.modifier();
  a.afficher();
  
  b.afficher();
  cout << "avec GETS b: " << b.get_a() << "et " << b.get_b() << endl;

  c.afficher();

  a.addition(b);
  a.afficher();
  

  return 0;
}
