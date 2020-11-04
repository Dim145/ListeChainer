#ifndef LISTE_H

#define LISTE_H

#include <string>

using namespace std;

template<typename T>
class Element;

template<typename T>
class Iterateur;

template<typename T>
class Liste
{
public:
    // constructeur
    Liste<T>();

    Liste<T>(Liste &);

    ~Liste<T>();

    Liste<T> &operator=(const Liste &);
    bool operator==(const Liste<T>&);

    // ajouter s a la fin de la liste
    void ajouter(const T &s);

    // ajouter s avant la position pos
    void inserer(Iterateur<T> &pos, const T &s);

    // supprimer l'element a la position pos
    void supprimer(Iterateur<T> &pos);

    // la premiere position
    Iterateur<T> debut() const;

    // la fin de la liste (apres la derniere position)
    Iterateur<T> fin() const;

private:
    // pointeurs vers le premier et le dernier element
    Element<T> *premier;
    Element<T> *dernier;
};

template<typename T>
class Iterateur
{
public:
    // constructeur
    Iterateur<T>();

    // avance a la position suivante
    Iterateur<T> operator++();

    Iterateur<T> operator++(int);

    // recule a la position precedente
    Iterateur<T> operator--();

    Iterateur<T> operator--(int);

    // retourne la valeur dans cette position
    T &operator*() const;

    bool operator==(const Iterateur<T> &) const;

    bool operator!=(const Iterateur<T> &) const;

private:
    // pointeur vers l'element courant
    Element<T> *position;

    // pointeur vers le dernier element de la liste
    Element<T> *dernier;

    friend class Liste<T>;
};

#endif
