#include <string>
#include <list>
#include <iostream>
#include "liste.h"

using namespace std;

int main() {
    list<string> personnel;

    // ajouter 4 elements
    personnel.push_back("Baleze Bruno");
    personnel.push_back("Costaud Claude");
    personnel.push_back("Doue Damien");
    personnel.push_back("Vaillant Veronique");

    // ajouter un element a la quatrieme position
    list<string>::iterator pos = personnel.begin();
    pos++; pos++; pos++;
    personnel.insert(pos, "Sage Stephane");

    // supprimer l'element a la deuxieme position
    pos = personnel.begin();
    pos++;
    personnel.erase(pos);

    // afficher tous les elements
    for (pos = personnel.begin(); pos != personnel.end(); pos++)
        cout << *pos << endl;

    cout << "\n--- Liste perso ---\n" << endl;

    Liste<string> liste;

    liste.ajouter("I'm the first");
    liste.ajouter("I'm the second");
    liste.ajouter("AND I'm the last");

    Iterateur<string> itInser = liste.debut();
    itInser++;
    itInser++;
    liste.inserer(itInser, "Je suis inserer avant the last");

    Iterateur<string> itInsertTest2 = liste.fin();
    liste.inserer(itInsertTest2, "Je suis inserer a la fin");

    Iterateur<string> pos2;

    for( pos2 = liste.debut(); pos2 != liste.fin(); pos2++ )
        cout << "val: " << *pos2 << endl;

    cout << "\n--parcourt inverse sans \"I'm the first\"--\n" << endl;

    Iterateur<string> pos3 = liste.fin();
    pos3--;
    pos3--;
    pos3--;
    pos3--;
    pos3--;
    liste.supprimer(pos3);

    //pos3.precedent();
    pos3++;
    pos3++;
    pos3++;

    for(; pos3 != liste.debut(); pos3-- )
        cout << "val: " << *pos3 << endl;
    cout << "val: " << *pos3 << endl;

    cout << "-- Test new Iterator --" << endl;

    Iterateur<string> pos4;

    for( pos4 = liste.debut(); pos4 != liste.fin(); pos4++ )
        cout << "val: " << *pos4 << endl;

    return 0;
}

