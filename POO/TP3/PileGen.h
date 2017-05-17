#include <iostream>
#include <malloc.h>
#include <string>
#include "ElementGen.h"


using namespace std;

template <typename T>
class PileGen{
  
  private:
    string name;

  public:
    ElementGen<T> * ptr;

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
   void afficher(ostream & out = cout) const ;

    /***********************************/
    /*             OPERATOR            */
    /***********************************/

    
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
  this->ptr = new ElementGen<T>(value,NULL);
  this->name = name;
}

template <typename T>
PileGen<T>::PileGen(const PileGen<T> &e){
  this->ptr = e.prec;
  this->name = e.name;
}

template <typename T>
PileGen<T>::~PileGen(){
  cout << "DESTRUCTION PILE MOTHERF**KER !!!" << endl;
}


/***********************************/
/*            METHODES             */
/***********************************/

template <typename T>
void PileGen<T>::push(T value){
  this->ptr = new ElementGen<T>(value,this->ptr);
}

template <typename T>
T PileGen<T>::pop(void){
  if(!estVide()){
    ElementGen<T> * tmp = this->ptr;
    this->ptr = (*this->ptr).prec;
    return (*tmp).value;
  }else{
    return (T)NULL;
  }
}

template <typename T>
int PileGen<T>::estVide(void){
  return ((*this->ptr).prec == NULL);
}

template <typename T>
T PileGen<T>::top(void){
  return (*this->ptr).value;
}

template <typename T>
void PileGen<T>::print(void){
  cout << "Stack : " << name << endl << " > " ;
  (*this->ptr).print();
}

template <typename T>
 void PileGen<T>::afficher(ostream &flux) const {
  flux << "Stack : " << name << endl << " > ";
  ElementGen<T> * temp = this->ptr;
  while(temp){
    flux << temp->value << endl << "   ";
    temp = temp->prec;
  }
}

/***********************************/
/*             OPERATOR            */
/***********************************/

template <typename T>
ostream & operator << (ostream & out, const PileGen<T> & stack){
  stack.afficher(out);
  return out;
}
