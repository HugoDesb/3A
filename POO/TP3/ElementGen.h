#include <iostream>
#include <malloc.h>
#include <string>



using namespace std;

template <typename T>
class ElementGen{
  
  private:
    T value;
    ElementGen<T> * prec;


  public:
    /***********************************/
    /*              LABAZ              */
    /***********************************/
    ElementGen(const T, const ElementGen<T> * prec = NULL);
    ~ElementGen(void);

    void print(void);
};


template <typename T>
ElementGen<T>::ElementGen(const T val, const ElementGen<T> *prec){
  this->value = val;
  this->prec = prec;
}


template <typename T>
ElementGen<T>::~ElementGen(void){
  cout << "DESTRUCTION MOTHERFUCKER !!!" << endl;
}

template <typename T>
void ElementGen<T>::print(void){
  cout << value << endl;
  cout << "   ";
  prec.print();
}

