//
// Created by dimit on 21/10/2020.
//
#include <iostream>
#include "liste.cpp"

int main()
{
    Liste<int>    listeInt;
    Liste<string> listeString;
    Liste<char>   listeChar;
    Liste<void*>  listeAll;

    Iterateur<int> itInt = listeInt.debut();

    printf("----- Tests basiques -----\n");

    printf("test get sur liste vide: ");
    try
    {
        printf("réussite avec %d comme résultat\n", *itInt);
    }
    catch (exception& e)
    {
        printf("echec\n");
    }

    printf("test de deplacement sur liste vide:\n");
    printf("\tprécedent: ");
    try
    {
        itInt--;
        printf("réussite, on pointe sur %d\n", *itInt);
    }
    catch (exception& e)
    {
        printf("echec\n");
    }

    printf("\tsuivant: ");
    try
    {
        itInt++;
        printf("réussite, on pointe sur %d\n", *itInt);
    }
    catch ( exception& e)
    {
        printf("echec\n");
    }


    listeInt.ajouter(16);
    itInt = listeInt.debut();
    int tmp = *itInt;

    printf("\ntest get sur liste avec 1 elt: %d\n", tmp);
    printf("ajout de 17 dans la liste d'int pour la suite...\n");
    listeInt.ajouter(17);

    printf("\n----- Test liste de void* -----\n");
    printf("Ajout d'un pointeur sur int dans une liste de void*\n");
    int * pointeurTmp = &tmp;

    listeAll.ajouter(pointeurTmp);

    printf("Ajout d'un pointeur sur string dans une liste de void*\n");
    string tmpStr = "Test";
    string * pointeurTmpStr = &tmpStr;

    listeAll.ajouter(pointeurTmpStr);

    printf("\nTest affichage d'une liste de void*\n");
    Iterateur<void*> itAll;

    for( itAll = listeAll.debut(); itAll != listeAll.fin(); itAll++ )
        cout << (*itAll) << endl;

    printf("Impossibilité de savoir ce qui se cache derriere le pointeur. Donc impossibilité de l'afficher correctement.\n");

    printf("\n----- Tests string -----\n");
    printf("ajout de string dans la liste\n");
    listeString.ajouter("Test str");

    char* str = static_cast<char *>(malloc(sizeof(char) * 2));
    for (int cpt = 0; cpt < 2; cpt++)
        str[cpt] = 'C';

    printf("ajout d'un char* de longueur 2 dans une liste de string: ");
    try
    {
        listeString.ajouter(str);
        printf("effectuer\n");
    }
    catch (exception& e)
    {
        printf("echec\n");
    }

    printf("\nAffichage\n");
    Iterateur<string> itString;
    for( itString = listeString.debut(); itString != listeString.fin(); itString++ )
        cout << (*itString) << endl;

    printf("\n----- Test char -----\n");
    printf("Ajout de char dans une liste de char\n");
    listeChar.ajouter('A');
    listeChar.ajouter('B');
    listeChar.ajouter('C');

    printf("Ajout de int dans une liste de char: ");
    try
    {
        listeChar.ajouter(84);
        printf("Effectuer\n");
    }
    catch (exception& e)
    {
        printf("echec\n");
    }

    printf("\nAffichage: \n");
    Iterateur<char> itChar;
    for( itChar = listeChar.debut(); itChar != listeChar.fin(); itChar++ )
        cout << *itChar << endl;

    printf("\n----- Test constructeur par recopie -----\n");
    printf("On creer une nouvelle liste d'int en donnant l'ancienne au constructeur: ");
    Liste<int> listeSecond;
    listeSecond = * new Liste<int>(listeInt);
    printf("réussite\n");

    printf("Affichage: \n");
    for ( itInt = listeSecond.debut(); itInt != listeSecond.fin(); itInt++)
        cout << *itInt << endl;

    printf("\n----- Test bornes -----\n");
    Iterateur<char> itBornes = listeChar.debut();

    printf("On est sur le premier element de la liste de char:\n");

    printf("\t- précédent: ");
    try
    {
        itBornes--;
        printf("réussite\n");
    }
    catch (exception& e)
    {
        printf("echec\n");
    }
    printf("Premier element: %c\n", *itBornes);

    printf("\nOn se place sur le dernier element +1 avec liste.fin()...\n");
    itBornes = listeChar.fin();

    printf("tentative de get sur l'element pointer: ");
    try
    {
        printf("Réussite avec %c comme resultat\n", *itBornes);
    }
    catch (exception& e)
    {
        printf("Echec\n");
    }

    printf("On essaye maintenant d'aller plus loin avec un suivant: ");
    try
    {
        itBornes++;
        printf("réussite\n");
    }
    catch (exception& e)
    {
        printf("echec\n");
    }

    printf("On test maintenant un retour en arrière et un get: ");
    try
    {
        itBornes--;
        printf("réussite avec %c comme résulat\n", *itBornes);
    }
    catch (exception& e)
    {
        printf("echec\n");
    }


    printf("\n----- Supressions -----\n\n");
    printf("On ajoute 85 a la liste d'int...\n");
    itInt = listeInt.debut();
    listeInt.inserer(itInt, 85);
    printf("et on va tester les supression sur celle-ci, elle contient donc cela: ");
    for ( itInt = listeInt.debut(); itInt != listeInt.fin(); itInt++)
        cout << *itInt << " ";
    cout << endl;

    itInt = listeInt.debut();
    itInt++;

    printf("On suprime l'élément du milieu...");
    listeInt.supprimer(itInt);

    printf("le contenu de la liste est donc: ");
    Iterateur<int> itTmpInt;
    for ( itTmpInt = listeInt.debut(); itTmpInt != listeInt.fin(); itTmpInt++)
        cout << *itTmpInt << " ";
    cout << endl;

    printf("On va supprimer l'element pointé par l'iterateur sans le bouger.\nCe qui devrai supprimer le dernier\n");
    listeInt.supprimer(itInt);

    printf("la liste contient maintenant: ");
    for ( itInt = listeInt.debut(); itInt != listeInt.fin(); itInt++)
        cout << *itInt << " ";
    cout << endl;

    printf("Maintenant, on pointe vers la fin de la liste (dernier element+1 = null).\non essaye de le supprimer: ");
    try
    {
        listeInt.supprimer(itInt);
        printf("réussite\n");
    }
    catch (exception& e)
    {
        printf("echec\n");
    }

    printf("On revient en arrière une fois, et on suprime le dernier element...\n");
    --itInt;
    listeInt.supprimer(itInt);

    printf("la liste contient donc: ");
    for ( itTmpInt = listeInt.debut(); itTmpInt != listeInt.fin(); itTmpInt++)
        cout << *itTmpInt << " ";
    printf("\n");

    printf("\n----- Egalité des itérateurs et éléments -----\n");

    printf("\nOn as trois liste qui contiennent toutes la même choses.\n");
    printf("La troisieme est construite par recopie de la 1, et la seconde est juste construite de la même façon.\n");

    listeInt = listeSecond;

    printf("liste 1 = ");
    for ( itTmpInt = listeInt.debut(); itTmpInt != listeInt.fin(); itTmpInt++)
        cout << *itTmpInt << " ";
    printf("\nliste2 = ");
    for ( itTmpInt = listeSecond.debut(); itTmpInt != listeSecond.fin(); itTmpInt++)
        cout << *itTmpInt << " ";
    printf("\n");

    printf("\nliste1 == liste2 -> %s\n", listeInt == listeSecond ? "true" : "false");

    printf("On ajoute 20 a la fin de la liste 1 et on recommence:\n");
    listeInt.ajouter(20);
    printf("liste1 == liste2 -> %s\n", listeInt == listeSecond ? "true" : "false");

    itTmpInt = listeInt.debut();
    itInt    = listeSecond.debut();

    printf("\nPour 2 itérateurs, pointant tous 2 sur la premiere case de la liste 1 et 2:\n");
    printf("itérateur1 == itérateur2 -> %s\n", itTmpInt == itInt ? "true" : "false");

    printf("On incrémente l'itérateur 2 de 1 et on compare: \n");
    itInt++;
    printf("itérateur1 == itérateur2 -> %s\n", itTmpInt == itInt ? "true" : "false");
    printf("etsi on incrémente aussi l'itérateur1 de 1:\n");
    itTmpInt++;
    printf("itérateur1 == itérateur2 -> %s\n", itTmpInt == itInt ? "true" : "false");

    printf("\n----- AUTRES -----\n");

    printf("\nPour bien vérifier le constructeur par recopie, la seconde liste contient: ");
    for ( itTmpInt = listeSecond.debut(); itTmpInt != listeSecond.fin(); itTmpInt++)
        cout << *itTmpInt << " ";
    printf("\n");

    printf("Enfin, testons l'insertion en mettant 34 au milieu de la seconde liste.\n");
    itTmpInt = listeSecond.debut();
    itTmpInt++;
    listeSecond.inserer(itTmpInt, 34);

    printf("Et cela donne: ");
    for ( itTmpInt = listeSecond.debut(); itTmpInt != listeSecond.fin(); itTmpInt++)
        cout << *itTmpInt << " ";
    printf("\n\n----- FIN -----\n");

    return 0;
}