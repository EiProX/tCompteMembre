#include <iostream>
#include <tComptesMembre.h>

using namespace std;

sMembre creerMembre(char* numero, int code, char* nom)
{
    sMembre m{};
    strncpy(m.numero, numero, sizeof(m.numero) - 1);
    m.numero[sizeof(m.numero) - 1] = '\0';
    m.code = code;
    strncpy(m.nom, nom, sizeof(m.nom) - 1);
    m.nom[sizeof(m.nom) - 1] = '\0';
    return m;
}
int main()
{
    tComptesMembres gestionnaire((char*)"Data.txt");

    sMembre m1 = creerMembre((char*)"1122", 7896, (char*)"PETIT");
    sMembre m2 = creerMembre((char*)"2200", 1234, (char*)"MARTIN");
    sMembre m3 = creerMembre((char*)"3768", 5555, (char*)"CHRETIEN");

    cout << "Ajout du membre 1... ";
    if (gestionnaire.ajouter(&m1)) cout << "OK" << endl;
    else cout << "ECHEC" << endl;

    cout << "Ajout du membre 2... ";
    if (gestionnaire.ajouter(&m2)) cout << "OK" << endl;
    else cout << "ECHEC" << endl;

    cout << "Ajout du membre 3... ";
    if (gestionnaire.ajouter(&m3)) cout << "OK" << endl;
    else cout << "ECHEC" << endl;

    cout << ">>> Ajouts terminés." << endl << endl;

    sMembre lu{};

    int indexALire = 3;
    cout << "Lecture de l’enregistrement d’index " << indexALire << "..." << endl;
    if (gestionnaire.lire_membre(indexALire, &lu))
     {
        cout << "Lecture réussie :" << endl;
        cout << "  Numéro : " << lu.numero << endl;
        cout << "  Code   : " << lu.code << endl;
        cout << "  Nom    : " << lu.nom << endl;
    }
    else
    {
        cout << "Erreur : impossible de lire l’enregistrement " << indexALire << endl;
    }
    cout << endl;

    char numTest1[] = "1122";
    char numTest2[] = "1122";
    char numTest3[] = "9999";

    cout << "Vérification des couples (numéro, code) :" << endl;
    cout << "  (" << numTest1 << ", 7896) -> "
         << (gestionnaire.verifier(numTest1, 7896) ? "OK" : "Existe pas") << endl;

    cout << "  (" << numTest2 << ", 9999) -> "
         << (gestionnaire.verifier(numTest2, 9999) ? "OK" : "Existe pas") << endl;

    cout << "  (" << numTest3 << ", 0000) -> "
         << (gestionnaire.verifier(numTest3, 0) ? "OK" : "Existe pas") << endl;

    cout << endl << ">>> Fin des tests." << endl;

    return 0;
}
