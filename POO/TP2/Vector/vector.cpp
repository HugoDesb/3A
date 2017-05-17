#include <iostream>
#include <math.h>
#include "vector.h"

using namespace std;

int Vector::nbGlobalSet = 0;
int Vector::nbGlobalGet = 0;

Vector::Vector(const int taille) {
  cout << "Contruction d'un Vecteur" << endl;

  this->taille = taille;
  this->ptr = new int[taille];

  //compteurs mis a zero
  nbGet = 0;
  nbSet = 0;

  //initialisation des valeurs du vecteur
  for (int i = 0; i < this->taille; ++i)
    {
      this->ptr[i] = 0;
    }
}

Vector::Vector(const Vector &x) {
  cout << "Contruction d'un Vecteur par recopie" << endl;

  this->taille = x.taille;
  this->ptr = new int[this->taille];

  //initialisation des compteurs
  nbGet = 0;
  nbSet = 0;

  //initialisation des valeurs du vecteur
  for (int i = 0; i < this->taille; ++i){
    this->ptr[i] = 0;
  }
}

Vector::~Vector(void){
  cout << "Destruction d'un Vecteur" << endl;
  delete[] ptr;
}

void Vector::print(void) const{
  cout << "( ";
  for(int i = 0; i<taille; i++){
    cout << ptr[i] << " ";
  }
  cout << ")" << "  \n\t GET: " << nbGet << " \n\t SET: " << nbSet << endl;
}

void Vector::printNbAccess() const{
  cout << "Nombre de get : " << nbGet << endl << "Nombre de set : " << nbSet << endl;
}

void Vector::printGlobalNbAccess() const{
  cout << "Nombre global de get : " << nbGlobalGet << endl << "Nombre global de set : " << nbGlobalSet << endl;
}


void Vector::adjust_size(const int newTaille) {

  int *tmp = ptr;
  int oldSize = taille;

  ptr = new int[newTaille];
  taille = newTaille;

  for (int i = 0; i < newTaille; ++i){
    ptr[i] = 0;
  }

  for (int i = 0; i < oldSize; ++i){
    ptr[i] = tmp[i];
  }

  delete[] tmp;
}

int Vector::getItem(int pos) {
  nbGet++;
  nbGlobalGet++;
  return ptr[pos];
}

void Vector::setItem(int pos, int value) {
  ptr[pos] = value;
  nbGlobalSet++;
  nbSet++;
}


Vector & Vector::operator = (const Vector &x) {

  if(this->taille < x.taille) {
    delete[] this->ptr;
    this->taille = x.taille;
    this->ptr = new int[x.taille];
  }

  for (int i = 0; i < this->taille; ++i){
    this->ptr[i] = x.ptr[i];
  }
  return *this;
}

int & Vector::operator [] (int pos) {
  return ptr[pos];
}
