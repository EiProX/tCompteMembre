/*
 * tGestMenbre.h
 *
 *  Created on: 14 juil 2025
 *      Author: prof2i
 */

#ifndef TCOMPTESMEMBRE_H_
#define TCOMPTESMEMBRE_H_
#include <cstring>

struct sMembre
{
    char numero[50];
    int  code;
    char nom[50];
};

class tComptesMembres
{
   private:
      char * NomFichier;
   public:
      tComptesMembres( char* apNomFichier ) ;
      bool ajouter( sMembre* psMembre ) ;
      // numero correspond au numero d'enregistrement
      // (0 pour le premier)
      bool lire_membre( int NumEnreg, sMembre* psMembre ) ;
      bool rechercher( sMembre* psMembre ) ;
      bool verifier( char* numero,int code ) ;
};

#endif
