/*
 * tGestMenbre.cpp
 *
 *  Created on: 07 oct. 2025
 *      Author: prof2i
 */
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <iostream>

#include "tComptesMembre.h"


tComptesMembres::tComptesMembres( char* apNomFichier )
{
   NomFichier = new char [strlen(apNomFichier)+1] ;
   strncpy ( NomFichier, apNomFichier, strlen(apNomFichier) ) ;
}

// Renvoie true si l'ajout a réussi et 0 dans le cas contraire
bool tComptesMembres::ajouter( sMembre *psMembre )
{
    std::ofstream fluxFile(NomFichier, std::ios::out | std::ios::app | std::ios::binary);
    if (!fluxFile)
    {
        std::cerr << "Erreur : impossible d'ouvrir le fichier pour l'ajout." << std::endl;
        return false;
    }

    fluxFile.write(reinterpret_cast<char*>(psMembre), sizeof(sMembre));
    //reinterpret_cast<char*> : permet de manipuler les données brutes (les octets)
    // de l’objet pointé. C’est souvent utilisé pour lire ou écrire des structures en mémoire dans un fichier binaire.
    if (!fluxFile)
    {
       std::cerr << "Erreur : échec de l'écriture dans le fichier." << std::endl;
       fluxFile.close();
       return false;
    }

    fluxFile.close();
    return true;
}



// Pour verifier la methode Ajouter, numero correspond au numero d'enregistrement
//(0 pour le premier)
bool tComptesMembres::lire_membre( int NumEnreg, sMembre* psMembre )
{
    psMembre->code = 9999; // valeur par défaut en cas d'échec

    std::ifstream fluxFile(NomFichier, std::fstream::in | std::fstream::binary);
    if (!fluxFile)
    {
        std::cerr << "Erreur : impossible d'ouvrir le fichier." << std::endl;
        return false;
    }

    // borne l’index
    fluxFile.seekg(0, std::ios::end);
    std::streampos fileSize = fluxFile.tellg();
    int nb_enreg = static_cast<int>(fileSize / sizeof(sMembre));
    if (NumEnreg < 0 || NumEnreg >= nb_enreg)
    {
        std::cerr << "Index hors bornes (" << NumEnreg << "/" << nb_enreg << ")." << std::endl;
        return false;
    }

    fluxFile.seekg( NumEnreg * sizeof(sMembre), std::ios::beg );
    if (!fluxFile) { std::cout << "Problème seekg\n"; return false; }

    fluxFile.read( reinterpret_cast<char*>(psMembre), sizeof(sMembre) );
    if (!fluxFile) { std::cout << "Problème read\n"; return false; }


    return true;
}



/**
 * @brief tComptesMembres::Rechercher
 * Recherche un membre à partir de son numéro (présent dans psMembre)
 * @param psMembre
 * @return 1 si trouvé, 0 sinon
 */
bool tComptesMembres::rechercher( sMembre *psMembre )
{
    sMembre tmpMembre;
    std::ifstream fluxFile ( NomFichier, std::fstream::in | std::fstream::binary ) ;
    if (!fluxFile)
    {
        std::cerr << "Erreur : impossible d'ouvrir le fichier." << std::endl;
        return false;
    }
    // Aller à la fin pour connaître la taille du fichier
    fluxFile.seekg ( 0, std::ios::end ) ;
    int nb_enreg = fluxFile.tellg() / sizeof( sMembre ) ;

    // Revenir au début pour commencer la lecture
    fluxFile.seekg(0, std::ios::beg);

    // Search...
    for (int i = 0; i < nb_enreg; i++ )
    {
     fluxFile.read(reinterpret_cast<char*>(&tmpMembre), sizeof(sMembre));
     if (!fluxFile)
     {
       std::cerr << "Erreur : lecture échouée à l'enregistrement " << i << "." << std::endl;
       break;
      }
     if ( strcmp( tmpMembre.numero, psMembre->numero ) == 0 )
      {
        psMembre->code = tmpMembre.code ;
        strcpy( psMembre->nom, tmpMembre.nom ) ;
        fluxFile.close() ;
        return true ;
      }
    }
  fluxFile.close() ;
  return false ;
}



/**
 * @brief tComptesMembres::Verifier
 * vérifie si le numéro de carte et le code correspondent à un membre.
 * @param Numero ex "1122"
 * @param Code  ex 7896
 * @return 1 si ok  et 0 dans le cas contraire
 */
bool tComptesMembres::verifier( char* numero, int code )
{
   sMembre tmpMembre;
   strcpy ( tmpMembre.numero, numero );
   if( rechercher( &tmpMembre ) )
   {
      if ( tmpMembre.code == code )
         return true ;
   }
   return false ;
}
