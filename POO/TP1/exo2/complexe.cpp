#include <iostream>
#include "complexe.h"
#include "math.h"

using namespace std;



/***********************************/
/*              LABAZ              */
/***********************************/

Complexe::Complexe(double a = 0, double b = 0){
  this->a = a;
  this->b = b;
  majModuleArgument();
}

Complexe::Complexe(const Complexe & z)
  :a(z.a),b(z.b)
{
  majModuleArgument();
}

Complexe::~Complexe(void){
  cout << "Passage dans le destructeur" << endl;
}

void Complexe::majModuleArgument(){
  //module=(a*a+b*b)**(1/2)
  this->module = sqrt((a*a+b*b));
  //argument= arctan(b/a)
  this->argument=atan2(b,a);
}


/***********************************/
/*            METHODES             */
/***********************************/

Complexe Complexe::addition(Complexe z1){
  float a = z1.get_a()+this->a;
  float b = z1.get_b()+this->b;
  majModuleArgument();
  return Complexe(a,b);
}

void Complexe::modifier(void){
  cout << "Entrez la partie réelle" << endl;
  cin >> this->a;
  cout << "Entrez la partie imaginaire" << endl;
  cin >> this->b;

  majModuleArgument();
}

void Complexe::afficher(void){
  cout << "z = " << this->a << "+"<< this->b << "i" <<endl;
}

Complexe Complexe::multiplication(Complexe z1){
  float module = this->module * z1.get_module();
  float argument = this->argument * z1.get_argument();
  return Complexe(module * cos(argument),module * sin(argument));
  
}


/***********************************/
/*           ACCESSEURS            */
/***********************************/

const double Complexe::get_a(void){
  return this->a;
}
const double Complexe::get_b(void){
  return this->b;
}
double Complexe::get_module(void){
  return this->module;
}
double Complexe::get_argument(void){
  return this->argument;
}



/***********************************/
/*           OPERATEURS            */
/***********************************/

Complexe Complexe::operator + (const Complexe &z1){
  return this->addition(z1);
}
Complexe Complexe::operator * (const Complexe &z1){
  return this->multiplication(z1);
}

