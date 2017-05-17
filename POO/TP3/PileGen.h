#include <iostream>
#include <malloc.h>
#include <string>
#include "ElementGen.h"


using namespace std;

template <typename T>
class PileGen{
  
  private:
    ElementGen<T> * ptr;
    string name;

  public:

    /***********************************/
    /*              LABAZ              */
    /***********************************/
    PileGen(string name = "defaultName");  
    PileGen(T, string name = "defaultName");
    PileGen(const PileGen<T> &);
    ~PileGen(void);


    /***********************************/
    /*            METHODES             */
    /***********************************/
    void push(T);
    T pop(void);
    int estVide(void);
    T top(void);
    void print(void);

    
};


/***********************************/
/*              LABAZ              */
/***********************************/
template <typename T>
PileGen<T>::PileGen(string name){
  this->name = name;
  this->ptr = NULL;
}

template <typename T>
PileGen<T>::PileGen(T value, string name){
  this->ptr = * new ElementGen<T>(value);
  this->name = name;
}

template <typename T>
PileGen<T>::PileGen(const PileGen<T> &e){
  this->ptr = e.prec;
  this->name = e.name;
}

template <typename T>
PileGen<T>::~PileGen(){
  cout << "Stack have been destroyed" << endl;
}


/***********************************/
/*            METHODES             */
/***********************************/

template <typename T>
void PileGen<T>::push(T value){
  ElementGen<T> * tmp = this->ptr;
  this->ptr = new ElementGen<T>(value,tmp);
}

template <typename T>
T PileGen<T>::pop(void){
  if(!estVide()){
    ElementGen<T> * tmp = this->ptr;
    this->ptr = this->ptr.prec;
    return *tmp;
  }else{
    return NULL;
  }
}

template <typename T>
int PileGen<T>::estVide(void){
  return (this->ptr.prec == NULL);
}

template <typename T>
T PileGen<T>::top(void){
  return * this->ptr;
}

template <typename T>
void PileGen<T>::print(void){
  cout << "Stack : " << name << endl << " > " ;
  this->ptr.print();
}
