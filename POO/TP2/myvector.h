#include <iostream>
#include <malloc.h>

using namespace std;

class MyVector{
 private:
  int dim; // nb de coordonnées du vecteur
  int * ptr_coor; // pointeur sur la 1ere coordonnées
  int nbAccesGET, nbAccesSET;
  
 public:
  
  /* LABAZ */
  MyVector(int = 1);
  ~MyVector();
  MyVector(const MyVector &);
  
  /* METHODES */
  void adjustSize(int);
  void print(void);
  int get_item(int);
  void set_item(int,int);
  
  /* ACCESSEURS */
  
   
  /* OPERATEURS */
  MyVector & operator = (const MyVector &);
   
};
