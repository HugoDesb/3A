#include <iostream>

using namespace std;

class Vector {

 private:
  /***********************/
  /*      ATTRIBUTS      */
  /***********************/
  int taille;
  int *ptr;
  
  int nbSet;
  int nbGet;
  
  static int nbGlobalSet;
  static int nbGlobalGet;


 public :
  /***********************/
  /*        LABAZ        */
  /***********************/
  Vector (const int taille=1);
  Vector (const Vector &x);
  
  virtual ~Vector(void);

  
  /***********************/
  /*      METHODES       */
  /***********************/
  virtual void print(void) const;
  void printNbAccess() const;
  void printGlobalNbAccess() const;
  void adjust_size(const int newTaille);
  int getItem(int pos);
  void setItem(int pos, int value);
  
    
  /***********************/
  /*     OPERATEURS      */
  /***********************/
  Vector & operator = (const Vector &x);
  int & operator [] (int pos);

};


class Vector15 : public Vector {
 private:

  void adjust_size(const int newTaille);

 public:
  //Constructeurs
 Vector15(void) : Vector(15){
    cout << "Constructeur" << endl;
  }

 Vector15(const Vector15 &x) : Vector(x){
    cout << "Constructeur par recopie" << endl;
  }

  //Destructeur
  ~Vector15(void) {
    cout << "Destruction d'un Vector15" << endl;
  }
};
