#include <iostream>
#include <malloc.h>
#include "myvector.h"
//#include "math.h"

using namespace std;


/***********************************/
/*              LABAZ              */
/***********************************/

MyVector::MyVector(int dim){
  this->dim = dim;
  this->ptr_coor = new int[dim];
  this->nbAccesGET = 0;
  this->nbAccesSET = 0;
}

MyVector::~MyVector(){
  cout << "Vector have been destroyed" << endl;
}

MyVector::MyVector(const MyVector & vect):dim(vect.dim){
  this->ptr_coor = new int [dim];
  this->nbAccesGET = 0;
  this->nbAccesSET = 0;
  for(int i = 0; i<this->dim; i++){
    ptr_coor[i] = vect.ptr_coor[i];
  }
}



/***********************************/
/*            METHODES             */
/***********************************/

void MyVector::adjustSize(int adjustBy){
  if(adjustBy!=0){
    int * tmp = ptr_coor;
    ptr_coor = new int[dim+adjustBy];

    if(adjustBy>0){
      int i;
      for(i = 0; i<dim; i++){
	ptr_coor[i] = tmp[i];
      }
      for(i=dim; i<dim+adjustBy; i++){
	ptr_coor[i] = 0;
      }
    }else{
      for(int i = 0; i<dim+adjustBy; i++){
	ptr_coor[i] = tmp[i];
      }
    }
    delete[] tmp;
    dim = dim+adjustBy;
  }
}

void MyVector::print(void){
  cout << "( ";
  for(int i = 0; i<this->dim; i++){
    cout << ptr_coor[i] << " ";
  }
  cout << ")" << "  || GET :" << nbAccesGET << " || SET:" << nbAccesSET << endl;
}

int MyVector::get_item(int i){
  //err si 0<=i<=dim

  this->nbAccesGET += 1; 
  return ptr_coor[i];
}


void MyVector::set_item(int i ,int val){
  //err si 0<=i<=dim

  this->nbAccesSET += 1;
  ptr_coor[i] = val;
}




/***********************************/
/*           ACCESSEURS            */
/***********************************/



/***********************************/
/*           OPERATEURS            */
/***********************************/

MyVector & MyVector::operator = (const MyVector & vect){
  if(dim!=vect.dim){
    //cas dim diff
    dim = vect.dim;
    delete[] ptr_coor;
    ptr_coor = new int[dim];    
  }
  //ici commun + cas dims égales
  for(int i = 0; i<dim; i++){
    ptr_coor[i] = vect.ptr_coor[i];
  }
  return *this;  
}



