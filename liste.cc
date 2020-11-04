#include "liste.h"
#include "Erreurs.h"

template<typename T>
class Element
{
public:
    // constructeur
    Element<T>(const T &s);
    bool operator==(Element<T> const &) const;

private:
    T valeur;

    // pointeurs vers les voisins
    Element<T> *precedent;
    Element<T> *suivant;



    friend class Liste<T>;

    friend class Iterateur<T>;
};



template<typename T>
Element<T>::Element(const T &s)
{
    valeur = s;
    precedent = suivant = NULL;
}

template<typename T>
bool Element<T>::operator==(const Element<T> & e) const
{
    return this->valeur == e.valeur;
}

template<typename T>
Iterateur<T>::Iterateur()
{
    position = dernier = NULL;
}

template<typename T>
Liste<T>::Liste()
{
    premier = dernier = NULL;
}


template<typename T>
Iterateur<T> Liste<T>::debut() const
{
    Iterateur<T> it;
    it.position = premier;
    it.dernier = dernier;
    return it;
}


template<typename T>
Iterateur<T> Liste<T>::fin() const
{
    Iterateur<T> it;
    it.position = NULL;
    it.dernier = dernier;
    return it;
}

template<typename T>
void Liste<T>::ajouter(const T &s)
{
    auto *e = new Element<T>(s);

    e->suivant = nullptr;
    e->precedent = this->dernier;

    if (this->premier != nullptr) this->dernier->suivant = e;
    else this->premier = e;

    this->dernier = e;
}

template<typename T>
void Liste<T>::inserer(Iterateur<T> &pos, const T &s)
{
    if (pos.position == nullptr)
    {
        ajouter(s);
        return;
    }

    auto *elt = new Element<T>(s);

    elt->suivant = pos.position;
    pos.position = pos.position == nullptr ? pos.dernier : pos.position->precedent;

    elt->suivant->precedent = elt;
    elt->precedent = pos.position;

    pos.position->suivant = elt;

    pos.position = elt;
}

template<typename T>
void Liste<T>::supprimer(Iterateur<T> &pos)
{
    // si la position est null, c'est que l'on est a la fin...
    if (pos.position == nullptr) throw Erreurs("Null pointer exeption: la liste est vide ou le dernier élément est atteint.");

    Element<T> *posTmp = pos.position;

    if (posTmp->precedent != nullptr)
        posTmp->precedent->suivant = posTmp->suivant;

    if (posTmp->suivant != nullptr)
        posTmp->suivant->precedent = posTmp->precedent;

    if (pos.position == pos.dernier)
    {
        pos.dernier = posTmp->precedent;
        this->dernier = pos.dernier;
    }

    if (this->premier == pos.position)
        this->premier = posTmp->suivant;

    pos.position = posTmp->suivant;

    delete posTmp;
}

template<typename T>
Liste<T>::Liste(Liste<T> &liste)
{
    try
    {
        for (Iterateur<T> i = liste.debut(); i != liste.fin(); i++)
            if( i.position != nullptr )
                this->ajouter(i.position->valeur);
    }
    catch (exception& e)
    {
        printf(e.what());
    }
}

template<typename T>
Liste<T>::~Liste()
{
    for (Iterateur<T> i = this->debut(); i != this->fin(); i++)
        free(i.position);

    this->premier = nullptr;
    this->dernier = nullptr;
}

template<typename T>
Liste<T> & Liste<T>::operator=(const Liste &l)
{
    if( &l == this ) return *this;

    try
    {
        for (Iterateur<T> i = l.debut(); i != l.fin(); i++)
            if( i.position != nullptr )
                this->ajouter(i.position->valeur);
    }
    catch (exception& e)
    {

    }

    return *this;
}

template<typename T>
bool Liste<T>::operator==(const Liste<T> & l)
{
    return (*this->premier) == (*l.premier) && (*this->dernier) == (*l.dernier);
}

template<typename T>
Iterateur<T> Iterateur<T>::operator++(int a)
{
    Iterateur it;

    it.position = this->position;
    it.dernier = this->dernier;

    if (this->position != nullptr )position = position->suivant;
    else                           throw Erreurs("sortie de la liste! la fin est déjà atteinte.");

    return it;
}

template<typename T>
Iterateur<T> Iterateur<T>::operator++()
{
    if (this->position != nullptr )position = position->suivant;
    else                           throw Erreurs("sortie de la liste! la fin est déjà atteinte.");

    return *this;
}

template<typename T>
T &Iterateur<T>::operator*() const
{
    if( position != nullptr )
        return position->valeur;
    else
        throw Erreurs("Null pointer execption!");
}

template<typename T>
Iterateur<T> Iterateur<T>::operator--()
{
    //Si la position est a null, on considère qu'on est a la fin de la liste.
    if( position == nullptr )                 position = dernier;
    else if( position->precedent == nullptr ) throw Erreurs("sortie de la liste! le début de la liste est déjà atteint");
    else                                      position = position->precedent;

    return *this;
}

template<typename T>
Iterateur<T> Iterateur<T>::operator--(int)
{
    Iterateur it;

    it.position = this->position;
    it.dernier = this->dernier;

    if( position == nullptr )                 position = dernier;
    else if( position->precedent == nullptr ) throw Erreurs("sortie de la liste! le début de la liste est déjà atteint");
    else                                      position = position->precedent;

    return it;
}

template<typename T>
bool Iterateur<T>::operator==(const Iterateur &b) const
{
    if( this->position == nullptr && b.position == nullptr ) return true;
    if( this->position == nullptr && b.position != nullptr ) return false;
    if( this->position != nullptr && b.position == nullptr ) return false;

    return (*this->position) == (*b.position);
}

template<typename T>
bool Iterateur<T>::operator!=(const Iterateur &b) const
{
    return !operator==(b);
}