#include <iostream>
#include <malloc.h>
#include <string>



using namespace std;

template <typename T>
class ElementGen{


  public:
    T value;
    ElementGen<T> * prec;
    /***********************************/
    /*              LABAZ              */
    /***********************************/
    ElementGen(const T, ElementGen<T> * prec = NULL);
    ~ElementGen(void);

    void print(void);

};


template <typename T>
ElementGen<T>::ElementGen(const T val, ElementGen<T> *prece){
  this->value = val;
  this->prec = prece;
}


template <typename T>
ElementGen<T>::~ElementGen(void){
  cout << "DESTRUCTION ELEMENT MOTHERF**KER !!!" << endl;
}

template <typename T>
void ElementGen<T>::print(void){
  cout << value << endl;
  cout << "   ";
  prec.print();
}

