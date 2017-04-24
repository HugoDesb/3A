#include <iostream>

using namespace std;

class Complexe{
 private:
  double a,b,module,argument;
  void majModuleArgument();

 public:
  /* LABAZ */
  Complexe(double, double);
  ~Complexe(void);
  Complexe(const Complexe &); // def du constructeur par copie
  
  /* METHODES */
  Complexe addition(Complexe);
  void modifier(void);
  void afficher(void);
  Complexe multiplication(Complexe);

  /* ACCESSEURS */
  const double get_a(void);
  const double get_b(void);
  double get_module(void);
  double get_argument(void);

  /* OPERATEURS */
  Complexe operator + (const Complexe&);
  Complexe operator * (const Complexe&);
  friend ostream & operator << (ostream & flot, const Complexe & z){
    return (flot << "z = " << z.a << "+"<< z.b << "i" <<endl);
  }
  
};




