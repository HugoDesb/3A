#include <stdio.h>
#include <stdlib.h>
#include <malloc/malloc.h>
#include <assert.h>

/* ---------------------------------------------------------------------------------------------- */

#define OUI 1
#define NON 0

typedef struct m
        {char nom ;
         int num ;
         int denom ;
         struct m * next ;
        }
t_liste ;

typedef t_liste * tpl ;

typedef struct mm
        {int arite ;
         int est_var ;
         int val ;
         char nom_etiq ;
         struct mm *fa ;
         struct mm *fb ;
        }
t_arbre ;

typedef t_arbre * tpa ;

/* ---------------------------------------------------------------------------------------------- */

tpl cree_vide ( void ) ;
tpl ajout_var_val ( char nom , int num , int denom , tpl l ) ;
int est_vide ( tpl l ) ;
char premier_nom ( tpl l ) ;
int premier_num ( tpl l ) ;
int premier_denom ( tpl l ) ;
tpl suite_var_val ( tpl l ) ;

tpa cree_val ( int valeur ) ;
tpa cree_var ( char nom ) ;
int est_feuille ( tpa arbre ) ;
int est_val ( tpa arbre ) ;
int est_var ( tpa arbre ) ;
int val_feuille ( tpa arbre ) ;
char nom_feuille ( tpa arbre ) ;

tpa cree_unaire ( tpa fils , char etiq ) ;
int est_unaire ( tpa arbre ) ;
tpa arbre_fils ( tpa arbre ) ;

tpa cree_binaire ( tpa gauche , tpa droite , char etiq ) ;
int est_binaire ( tpa arbre ) ;
tpa arbre_fg ( tpa arbre ) ;
tpa arbre_fd ( tpa arbre ) ;

char arbre_etiq ( tpa arbre ) ;

void supprime_fils_gauche ( tpa arbre ) ;
void supprime_fils_droit ( tpa arbre ) ;
void ajoute_fils_gauche ( tpa gauche , tpa arbre ) ;
void ajoute_fils_droit ( tpa droit , tpa arbre ) ;

int priorite ( char op ) ;

/* ---------------------------------------------------------------------------------------------- */

void print_arbre ( tpa a ) ;

void print_opt ( tpa a ) ; 
void print_opt_rec ( tpa a , int prio , int protege ) ;
void print_opt_unaire ( tpa fils , char etiq , int prio , int protege ) ;
void print_opt_binaire ( tpa fg , tpa fd , char etiq , int prio , int protege ) ;

int pgcd ( int a , int b ) ;
int puissance ( int nombre , int exp ) ;

void eval ( tpa arbre , int * rationnel , int * num , int * denom , tpl lvv ) ;
void eval_feuille ( tpa a , int * rationnel , int * num , int * denom , tpl lvv ) ;
void eval_unaire ( tpa fils , char etiq , int * rationnel , int * num , int * denom , tpl lvv ) ;
void eval_binaire ( tpa fg , tpa fd , char etiq ,
                    int * rationnel , int * num , int * denom , tpl lvv ) ;
void eval_exp_entier ( int * rationnel , int * num , int * denom ,
                       int num_g , int denom_g , int num_d ) ;
void eval_exp_rationnel ( int * rationnel , int * num , int * denom ,
                          int num_g , int denom_g , int num_d , int denom_d ) ;
void cherche_racine ( int resultat , int exp , int * ok , int * racine ) ;
void eval_mult ( char etiq , int * rationnel , int * num , int * denom ,
                 int num_g , int denom_g , int num_d , int denom_d ) ;
void eval_add ( char etiq , int * rationnel , int * num , int * denom ,
                int num_g , int denom_g , int num_d , int denom_d ) ;
void test_eval ( tpa a , tpl lvv ) ;

int main ( void ) ;

/* ---------------------------------------------------------------------------------------------- */

tpl cree_vide ( void )
    {return( (tpl)NULL ) ;
    }

tpl ajout_var_val ( char nom , int num , int denom , tpl l )
    {tpl nouv = (tpl)malloc( sizeof( t_liste ) ) ;
     nouv->nom = nom ;
     nouv->num = num ;
     nouv->denom = denom ;
     nouv->next = l ;
     return( nouv ) ;
    }

int est_vide ( tpl l )
    {return( l == cree_vide( ) ) ;
    }

char premier_nom ( tpl l )
     {assert( ! est_vide( l ) ) ;
      return( l->nom ) ;
     }

int premier_num ( tpl l )
    {assert( ! est_vide( l ) ) ;
     return( l->num ) ;
    }

int premier_denom ( tpl l )
    {assert( ! est_vide( l ) ) ;
     return( l->denom ) ;
    }

tpl suite_var_val ( tpl l )
    {assert( ! est_vide( l ) ) ;
     return( l->next ) ;
    }

/* ---------------------------------------------------------------------------------------------- */

tpa cree_val ( int valeur )
    {tpa nouv ;
     nouv = (tpa)malloc( sizeof( t_arbre ) ) ;
     nouv->arite = 0 ;
     nouv->est_var = NON ;
     nouv->val = valeur ;
     return( nouv ) ;
    }

tpa cree_var ( char nom )
    {tpa nouv ;
     nouv = (tpa)malloc( sizeof( t_arbre ) ) ;
     nouv->arite = 0 ;
     nouv->est_var = OUI ;
     nouv->nom_etiq = nom ;
     return( nouv ) ;
    }

int est_feuille ( tpa arbre )
    {return( arbre->arite == 0 ) ;
    }

int est_val ( tpa arbre )
    {return( arbre->arite == 0 && ! arbre->est_var ) ;
    }

int est_var ( tpa arbre )
    {return( arbre->arite == 0 && arbre->est_var ) ;
    }

int val_feuille ( tpa arbre )
    {assert( est_val( arbre ) ) ;
     return( arbre->val ) ;
    }

char nom_feuille ( tpa arbre )
     {assert( est_var( arbre ) ) ;
      return( arbre->nom_etiq ) ;
     }

tpa cree_unaire ( tpa fils , char etiq )
    {tpa nouv ;
     nouv = (tpa)malloc( sizeof( t_arbre ) ) ;
     nouv->arite = 1 ;
     nouv->nom_etiq = etiq ;
     nouv->fa = fils ;
     return( nouv ) ;
    }

int est_unaire ( tpa arbre )
    {return( arbre->arite == 1 ) ;
    }

tpa arbre_fils ( tpa arbre )
    {assert( est_unaire( arbre ) ) ;
     return( arbre->fa ) ;
    }

tpa cree_binaire ( tpa gauche , tpa droit , char etiq )
    {tpa nouv ;
     nouv = (tpa)malloc( sizeof( t_arbre ) ) ;
     nouv->arite = 2 ;
     nouv->nom_etiq = etiq ;
     nouv->fa = gauche ;
     nouv->fb = droit ;
     return( nouv ) ;
    }

int est_binaire ( tpa arbre )
    {return( arbre->arite == 2 ) ;
    }

tpa arbre_fg ( tpa arbre )
    {assert( est_binaire( arbre ) ) ;
     return( arbre->fa ) ;
    }

tpa arbre_fd ( tpa arbre )
    {assert( est_binaire( arbre ) ) ;
     return( arbre->fb ) ;
    }

char arbre_etiq ( tpa arbre )
     {assert( ! est_feuille( arbre ) ) ;
      return( arbre->nom_etiq ) ;
     }

void supprime_fils_gauche ( tpa arbre ) 
     {assert( est_binaire( arbre ) ) ;
      arbre-> arite = 1 ;
      arbre->fa = arbre->fb ;
      arbre->fb = NULL ; // Elle est facultative.
     }

void supprime_fils_droit ( tpa arbre )
     {assert( est_binaire( arbre ) ) ;
      arbre-> arite = 1 ;
      arbre->fb = NULL ; // Elle est facultative.
     }

void ajoute_fils_gauche ( tpa gauche , tpa arbre )
     {assert( est_unaire( arbre ) ) ;
      arbre->arite = 2 ;
      arbre->fb = arbre->fa ;
      arbre->fa = gauche ;
     }

void ajoute_fils_droit ( tpa droit , tpa arbre )
     {assert( est_unaire( arbre ) ) ;
      arbre->arite = 2 ;
      arbre->fb = droit ;
     }

int priorite ( char op )
    {if ( op == '^' )
        return( 2 ) ;
     else
        if ( op == '*' || op == '/' )
           return( 1 ) ;
        else
           return( 0 ) ;
    }

/* ---------------------------------------------------------------------------------------------- */

void print ( tpa a )
     {if ( est_feuille( a ) )
         if ( est_var( a ) )
            (void)printf( "%c" , nom_feuille( a ) ) ;
         else
            if ( val_feuille( a ) < 0 )
               print( cree_unaire( cree_val( - val_feuille( a ) ) , '-' ) ) ;
            else
               (void)printf( "%d" , val_feuille( a ) ) ;
      else
         {char etiq = arbre_etiq( a ) ;
          if ( est_unaire( a ) )
             if ( etiq == '^' )
                {(void)printf( "exp(" ) ;
                 print( arbre_fils( a ) ) ;
                }
             else
                {if ( priorite( etiq ) == 1 )
                    (void)printf( "(1%c" , etiq ) ;
                 else
                    (void)printf( "(0%c" , etiq ) ;
                 print( arbre_fils( a ) ) ;
                }
          else
             {(void)printf( "(" ) ;
              print( arbre_fg( a ) ) ;
              (void)printf( "%c" , etiq ) ;
              print( arbre_fd( a ) ) ;
             }
          (void)printf( ")" ) ;
         }
     }

void print_opt ( tpa a )
     {print_opt_rec( a , 0 , NON ) ;
     }

void print_opt_rec ( tpa a , int prio , int protege )
     {if ( est_feuille( a ) )
         if ( est_var( a ) )
            (void)printf( "%c" , nom_feuille( a ) ) ;
         else
            if ( val_feuille( a ) < 0 )
               print_opt_rec( cree_unaire( cree_val( - val_feuille( a ) ) , '-' ) ,
                              prio , protege ) ;
            else
               (void)printf( "%d" , val_feuille( a ) ) ;
      else
         if ( est_unaire( a ) )
            print_opt_unaire( arbre_fils( a ) , arbre_etiq( a ) , prio , protege ) ;
         else
            print_opt_binaire( arbre_fg( a ) , arbre_fd( a ) , arbre_etiq( a ) , prio , protege ) ;
     }

void print_opt_unaire ( tpa fils , char etiq , int prio , int protege )
     {if ( etiq == '^' )
         {(void)printf( "exp(" ) ;
          print_opt_rec( fils , 0 , NON ) ;
          (void)printf( ")" ) ;
         }
      else
         if ( etiq == '+' || etiq == '*' ) 
            print_opt_rec( fils , prio , protege ) ;
         else
            {int parenthese = ( protege && ( priorite( etiq ) <= prio ) ) ;
             if ( parenthese )
                (void)printf( "(" ) ;
             if ( etiq == '-' )
                (void)printf( "-" ) ;
             else
                (void)printf( "1/" ) ;
             print_opt_rec( fils , priorite( etiq ) , OUI ) ;
             if ( parenthese )
                (void)printf( ")" ) ;
            }
     }

void print_opt_binaire ( tpa fg , tpa fd , char etiq , int prio , int protege )
     {int prio_locale = priorite( etiq ) ;
      int parenthese = ( prio_locale < prio || ( protege && prio_locale <= prio ) ) ;
      if ( parenthese )
         (void)printf( "(" ) ;
      print_opt_rec( fg , prio_locale , NON ) ;
      if ( est_unaire( fd ) &&
           ( ( etiq == '*' && arbre_etiq( fd ) == '/' ) ||
             ( etiq == '+' && arbre_etiq( fd ) == '-' ) ) )
         {(void)printf( "%c" , arbre_etiq( fd ) ) ;
          print_opt_rec( arbre_fils( fd ) , prio_locale , OUI ) ;
         }
      else
         {(void)printf( "%c" , etiq ) ;
          print_opt_rec( fd , prio_locale , ( etiq == '^' || etiq == '-' || etiq == '/' ) ) ;
         }
      if ( parenthese )
         (void)printf( ")" ) ;
     }

/* ---------------------------------------------------------------------------------------------- */

int pgcd ( int a , int b )
    {int x = a , y = b , m ;
     while ( y != 0 )
           {m = y ;
            y = x % y ;
            x = m ; 
           }
     return( x ) ;
    }

int puissance ( int nombre , int exp )
    {int i , res = 1 ;
     for ( i = 0 ; i < exp ; i++ )
         res *= nombre ;
     return( res ) ;
    }

void eval ( tpa a , int * rationnel , int * num , int * denom , tpl lvv )
     {if ( est_feuille( a ) )
         eval_feuille( a , rationnel , num , denom , lvv ) ;
      else
         if ( est_unaire( a ) )
            eval_unaire( arbre_fils( a ) , arbre_etiq( a ) , rationnel , num , denom , lvv ) ;
         else
            eval_binaire( arbre_fg( a ) , arbre_fd( a ) , arbre_etiq( a ) ,
                          rationnel , num , denom , lvv ) ;
     }

void eval_feuille ( tpa a , int * rationnel , int * num , int * denom , tpl lvv )
     {* rationnel = OUI ;
      * denom = 1 ;
      if ( est_val( a ) ) 
         * num = val_feuille( a ) ;
      else
         {while ( ! est_vide( lvv ) && premier_nom( lvv ) != nom_feuille( a ) )
                lvv = suite_var_val( lvv ) ;
          if ( ! est_vide( lvv ) && premier_denom( lvv ) != 0 )
             {* num = premier_num( lvv ) ;
              * denom = premier_denom( lvv ) ;
             }
          else
             * rationnel = NON ;
         }
     }

void eval_unaire ( tpa fils , char etiq , int * rationnel , int * num , int * denom , tpl lvv )
     {if ( etiq == '^' )
         * rationnel = NON ;
      else
         {eval( fils , rationnel , num , denom , lvv ) ;
          if ( * rationnel && ( etiq == '-' || etiq == '/' ) )
             {if ( etiq == '-' )
                 * num *= - 1 ;
              else
                 {int aux = * num ;
                  * num = * denom ;
                  * denom = aux ;
                  if ( * denom < 0 )
                     {* num *= - 1 ;
                      * denom *= - 1 ;
                     }
                  else
                     if ( * denom == 0 )
                        * rationnel = NON ;
                 }
             }
         } 
     }

void eval_binaire ( tpa fg , tpa fd , char etiq ,
                    int * rationnel , int * num , int * denom , tpl lvv )
     {int rat_g , rat_d , num_g , num_d , denom_g , denom_d ;
      eval( fg , & rat_g , & num_g , & denom_g , lvv ) ;
      eval( fd , & rat_d , & num_d , & denom_d , lvv ) ;
      if ( ! rat_g || ! rat_d )
         * rationnel = NON ;
      else
         {* rationnel = OUI ;
          if ( etiq == '^' )
             if ( denom_d == 1 )
                eval_exp_entier( rationnel , num , denom , num_g , denom_g , num_d ) ;
             else
                eval_exp_rationnel( rationnel , num , denom , num_g , denom_g , num_d , denom_d ) ;
          else
             if ( priorite( etiq ) == 1 )
                eval_mult( etiq , rationnel , num , denom , num_g , denom_g , num_d , denom_d ) ;
             else
                eval_add( etiq , rationnel , num , denom , num_g , denom_g , num_d , denom_d ) ;
         } 
     }

void eval_exp_entier ( int * rationnel , int * num , int * denom ,
                       int num_g , int denom_g , int num_d )
     {if ( num_d < 0 )
         {* num = puissance( denom_g , abs( num_d ) ) ;
          * denom = puissance( num_g , abs( num_d ) ) ;
          if ( * denom < 0 )
             {* num *= - 1 ;
              * denom *= - 1 ;
             }
          else
             if ( * denom == 0 )
                * rationnel = NON ;
         }
      else
         {* num = puissance( num_g , num_d ) ;
          * denom = puissance( denom_g , num_d ) ;
         }
     }

void eval_exp_rationnel ( int * rationnel , int * num , int * denom ,
                          int num_g , int denom_g , int num_d , int denom_d )
     {int signe = 1 , ok_num , rac_num , ok_denom , rac_denom ;
      if ( num_g < 0 && denom_d % 2 == 0 )
         * rationnel = NON ;
      else
         {if ( num_g < 0 )
             {signe = - 1 ;
              num_g = - num_g ;
             }
          if ( num_g == 0 || num_g == 1 )
             {ok_num = 1 ;
              rac_num = num_g ;
             }
          else
             cherche_racine( num_g , denom_d , & ok_num , & rac_num ) ;
          cherche_racine( denom_g , denom_d , & ok_denom , & rac_denom ) ;
          if ( ok_num && ok_denom )
             eval_exp_entier( rationnel , num , denom , signe * rac_num , rac_denom , num_d ) ;
          else
             * rationnel = NON ;
         }
     }

void cherche_racine ( int resultat , int exp , int * ok , int * racine )
     {int rac , i , resu = 0 ;
      for ( rac = 2 ; resu < resultat ; rac++ )
          {resu = 1 ;
           for ( i = 0 ; i < exp ; i++ )
               resu *= rac ;
          }
      * ok = ( resu == resultat ) ;
      * racine = rac - 1 ;
     }

void eval_mult ( char etiq , int * rationnel , int * num , int * denom ,
                 int num_g , int denom_g , int num_d , int denom_d )
     {int numerateur , denominateur , gcd ;
      if ( etiq == '*' )
         {numerateur = num_g * num_d ;
          denominateur = denom_g * denom_d ;
         }
      else
         {numerateur = num_g * denom_d ;
          denominateur = denom_g * num_d ;
          if ( denominateur < 0 )
             {denominateur = - denominateur ;
              numerateur = - numerateur ;
             }
          else
             if ( denominateur == 0 )
                * rationnel = NON ;
         }
      if ( * rationnel )
         {gcd = pgcd( abs( numerateur ) , denominateur ) ;
          * num = numerateur / gcd ;
          * denom = denominateur / gcd ;
         }
     } 

void eval_add ( char etiq , int * rationnel , int * num , int * denom ,
                int num_g , int denom_g , int num_d , int denom_d )
     {int numerateur , denominateur , gcd ;
      denominateur = denom_g * denom_d ;
      if ( etiq == '+' )
         numerateur = num_g * denom_d + num_d * denom_g ;
      else
         numerateur = num_g * denom_d - num_d * denom_g ;
      gcd = pgcd( abs( numerateur ) , denominateur ) ;
      * num = numerateur / gcd ;
      * denom = denominateur / gcd ;
     }

void test_eval ( tpa a , tpl lvv )
     {int rationnel , num , denom ;
      (void)printf( "Evaluation de l'arbre " ) ;
      print( a ) ;
      (void)printf( " encore écrit " ) ;
      print_opt( a ) ;
      (void)printf( "\n" ) ;
      eval( a , & rationnel , & num, & denom , lvv ) ;
      if ( rationnel )
         if ( denom == 1 )
            (void)printf( "Le résultat donne la valeur %d\n" , num ) ;
         else
            (void)printf( "Le résultat donne la fraction %d/%d\n" , num , denom ) ;
      else
         (void)printf( "Le résultat n'est pas rationnel.\n" ) ;
     }

/* ---------------------------------------------------------------------------------------------- */

int main ( void )
    {tpa arbre , arbre_test ;
     tpl lvv = cree_vide( ) ;
     arbre = cree_binaire( cree_binaire( cree_unaire( cree_var( 'b' ) , '^' ) ,
                                         cree_binaire( cree_var( 'c' ) ,
                                                       cree_unaire( cree_unaire( cree_var( 'a' ) ,
                                                                                 '-' ) ,
                                                                    '+' ) ,
                                                       '/' ) ,
                                         '+' ) ,
                           cree_binaire( cree_binaire( cree_val( 3 ) ,
                                                       cree_binaire( cree_var( 'a' ) ,
                                                                     cree_binaire(
                                                                         cree_val( 2 ) ,
                                                                         cree_binaire(
                                                                             cree_val( 1 ) ,
                                                                             cree_var( 'a' ) ,
                                                                            '-' ) ,
                                                                         '-' ) ,
                                                                     '+' ) ,
                                                       '^' ) ,
                                         cree_binaire( cree_binaire( cree_unaire(
                                                                         cree_var( 'c' ) ,
                                                                         '*' ) ,
                                                                     cree_val( 125 ) ,
                                                                     '/' ) ,
                                                       cree_unaire( cree_val( 25 ) , '/' ) ,
                                                       '/' ) ,
                                         '*' ) ,
                           '-' ) ;
     (void)printf( "Un arbre en écriture non optimisée : " ) ;
     print( arbre ) ;
     (void)printf( "\net en écriture optimisée : " ) ;
     print_opt( arbre ) ;
     (void)printf( "\n" ) ;
     (void)printf( "On ajoute la feuille 2 comme fils gauche du 2e sous-arbre gauche.\n" ) ;
     ajoute_fils_gauche( cree_val( 2 ) , arbre_fg( arbre_fg( arbre ) ) ) ;
     (void)printf( "L'arbre en écriture non optimisée : " ) ;
     print( arbre ) ;
     (void)printf( "\net en écriture optimisée : " ) ;
     print_opt( arbre ) ;
     (void)printf( "\n" ) ;
      arbre_test = cree_val( 4 ) ;
      test_eval( arbre_test , lvv ) ;
      arbre_test = cree_var( 'x' ) ;
      test_eval( arbre_test , lvv ) ;
      arbre_test = cree_val( 5 ) ;
      test_eval( arbre_test , lvv ) ;
      arbre_test = cree_unaire( cree_val( 5 ) , '^' ) ;
      test_eval( arbre_test , lvv ) ;
      arbre_test = cree_unaire( cree_val( 5 ) , '+' ) ;
      test_eval( arbre_test , lvv ) ;
      arbre_test = cree_binaire( cree_unaire( cree_val( 5 ) , '^' ) , cree_val( 7 ) , '+' ) ;
      test_eval( arbre_test , lvv ) ;
      arbre_test = cree_binaire( cree_val( 5 ) , cree_val( 7 ) , '+' ) ;
      test_eval( arbre_test , lvv ) ;
      arbre_test = cree_binaire( cree_val( 5 ) , cree_val( 7 ) , '^' ) ;
      test_eval( arbre_test , lvv ) ;
      arbre_test = cree_binaire( cree_val( 5 ) , cree_unaire( cree_val( 7 ) , '/' ) , '+' ) ;
      test_eval( arbre_test , lvv ) ;
      arbre_test = cree_binaire( cree_val( 5 ) , cree_unaire( cree_val( 7 ) , '/' ) , '^' ) ;
      test_eval( arbre_test , lvv ) ;
      arbre_test = cree_binaire( cree_val( 4 ) ,
                                 cree_unaire( cree_unaire( cree_val( 3 ) , '-' ) , '-' ) ,
                                 '^' ) ;
      test_eval( arbre_test , lvv ) ;
      arbre_test = cree_binaire( cree_binaire( cree_val( 4 ) , cree_val( 9 ) , '*' ) ,
                                 cree_unaire( cree_val( 15 ) , '/' ) ,
                                 '*' ) ;
      test_eval( arbre_test , lvv ) ;
      arbre_test = cree_binaire( cree_binaire( cree_val( 4 ) , cree_val( 9 ) , '+' ) ,
                                 cree_unaire( cree_val( 15 ) , '-' ) ,
                                 '+' ) ;
      test_eval( arbre_test , lvv ) ;
      arbre_test = cree_binaire( cree_binaire( cree_val( 4 ) , cree_val( 9 ) , '*' ) ,
                                 cree_unaire( cree_unaire( cree_val( 15 ) , '/' ) , '-' ) ,
                                 '/' ) ;
      test_eval( arbre_test , lvv ) ;
      arbre_test = cree_binaire( cree_binaire( cree_val( 4 ) , cree_val( 9 ) , '*' ) ,
                                 cree_unaire( cree_val( 15 ) , '/' ) ,
                                 '+' ) ;
      test_eval( arbre_test , lvv ) ;
      arbre_test = cree_binaire( cree_unaire( cree_val( 15 ) , '/' ) ,
                                 cree_binaire( cree_val( 4 ) , cree_val( 9 ) , '*' ) ,
                                 '-' ) ;
      test_eval( arbre_test , lvv ) ;
      arbre_test = cree_binaire( cree_binaire( cree_val( 2 ) , cree_val( 3 ) , '/' ) ,
                                 cree_val( 5 ) ,
                                 '^' ) ;
      test_eval( arbre_test , lvv ) ;
      arbre_test = cree_binaire( cree_unaire( cree_unaire( cree_val( 15 ) , '/' ) , '-' ) ,
                                 cree_binaire( cree_val( 4 ) , cree_val( 9 ) , '*' ) ,
                                 '-' ) ;
      test_eval( arbre_test , lvv ) ;
      arbre_test = cree_binaire( cree_val( 4 ) ,
                                 cree_binaire( cree_val( 5 ) , cree_val( 6 ) , '-' ) ,
                                 '+' ) ;
      test_eval( arbre_test , lvv ) ;
      arbre_test = cree_binaire( cree_val( 4 ) ,
                                 cree_binaire( cree_val( 5 ) , cree_val( 6 ) , '+' ) ,
                                 '-' ) ;
      test_eval( arbre_test , lvv ) ;
      arbre_test = cree_binaire( cree_binaire( cree_val( - 216 ) ,
                                               cree_val( 125 ) ,
                                               '/' ) ,
                                 cree_unaire( cree_binaire( cree_val( 2 ) ,
                                                            cree_val( 3 ) ,
                                                            '/' ) ,
                                              '-' ) ,
                                 '^' ) ;
      test_eval( arbre_test , lvv ) ;
      test_eval( arbre , lvv ) ;
      lvv = ajout_var_val( 'x' , 7 , 1 ,
              ajout_var_val( 'b' , 5 , 1 ,
                ajout_var_val( 'a' , 3 , 2 ,
                  ajout_var_val( 'y' , 4 , 0 ,
                    ajout_var_val( 'c' , 8 , 7 ,
                      ajout_var_val( 'z' , 1 , 1 , cree_vide( ) ) ) ) ) ) ) ;
      test_eval( arbre , lvv ) ;
      test_eval( cree_binaire( arbre , cree_unaire( arbre , '-' ) , '/' ) , lvv ) ;
     (void)printf( "Bye !\n" ) ;
     return( 0 ) ;
     }

/* ---------------------------------------------------------------------------------------------- */
