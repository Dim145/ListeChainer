#include "liste.h"

template<typename  T> class Element
{
public:
   // constructeur
   Element<T>(const T& s);

private:
   T valeur;

   // pointeurs vers les voisins
   Element<T>* precedent;
   Element<T>* suivant;

friend class Liste<T>;
friend class Iterateur<T>;
};


template<typename  T> Element<T>::Element(const T& s) {
   valeur = s;
   precedent = suivant = NULL;
}


template<typename  T> Iterateur<T>::Iterateur() {
   position = dernier = NULL;
}

template<typename  T> Liste<T>::Liste() {
   premier = dernier = NULL;
}


template<typename  T> Iterateur<T> Liste<T>::debut() const {
   Iterateur<T> it;
   it.position = premier;
   it.dernier = dernier;
   return it;
}


template<typename  T> Iterateur<T> Liste<T>::fin() const {
   Iterateur<T> it;
   it.position = NULL;
   it.dernier = dernier;
   return it;
}

template<typename  T> void Liste<T>::ajouter(const T &s)
{
    auto * e = new Element<T>(s);

    e->suivant = nullptr;
    e->precedent = this->dernier;

    if( this->premier != nullptr ) this->dernier->suivant = e;
    else                           this->premier = e;

    this->dernier = e;
}

template<typename  T> void Liste<T>::inserer(Iterateur<T> &pos, const T &s)
{
    if( pos.position == nullptr )
    {
        ajouter(s);
        return;
    }

    auto * elt = new Element<T>(s);

    elt->suivant = pos.position;
    pos.position = pos.position == nullptr ? pos.dernier : pos.position->precedent;

    elt->suivant->precedent = elt;
    elt->precedent = pos.position;

    pos.position->suivant = elt;

    pos.position = elt;
}

template<typename  T> void Liste<T>::supprimer(Iterateur<T> &pos)
{
    if( pos.position == nullptr ) return;

    Element<T> * posTmp = pos.position;

    if ( posTmp->precedent != nullptr )
        posTmp->precedent->suivant = posTmp->suivant;

    if( posTmp->suivant != nullptr )
        posTmp->suivant->precedent = posTmp->precedent;

    if( pos.position == pos.dernier )
        pos.dernier = posTmp->precedent;

    if( this->premier == pos.position )
        this->premier = pos.position->suivant;

    pos.position = posTmp->suivant;

    delete posTmp;
}

template<typename  T> Liste<T>::Liste(Liste<T> & liste)
{
    this->premier = liste.premier;
    this->dernier = liste.dernier;
}

template<typename  T> Liste<T>::~Liste()
{
    for (Iterateur<T> i = this->debut(); i != this->fin(); i++)
        free(i.position);

    this->premier = nullptr;
    this->dernier = nullptr;
}

template<typename  T> Liste<T>& Liste<T>::operator=(const Liste & l)
{
    for( Iterateur<T> i = l.debut(); i != l.fin(); i++)
        this->ajouter(i.position->valeur);

    return *this;
}

template<typename  T> Iterateur<T> Iterateur<T>::operator++(int a)
{
    Iterateur it;

    it.position = this->position;
    it.dernier  = this->dernier;

    if( this->position != nullptr ) position = position->suivant;

    return it;
}

template<typename  T> Iterateur<T> Iterateur<T>::operator++()
{
    if( this->position != nullptr ) position = position->suivant;

    return *this;
}

template<typename  T> T& Iterateur<T>::operator*() const
{
    return position->valeur;
}

template<typename  T> Iterateur<T> Iterateur<T>::operator--()
{
    position = position == nullptr ? position : position->precedent;

    return *this;
}

template<typename  T> Iterateur<T> Iterateur<T>::operator--(int)
{
    Iterateur it;

    it.position = this->position;
    it.dernier  = this->dernier;

    position = position == nullptr ? dernier : position->precedent;

    return it;
}

template<typename  T> bool Iterateur<T>::operator==(const Iterateur & b) const
{
    return this->position == b.position;
}

template<typename  T> bool Iterateur<T>::operator!=(const Iterateur & b) const
{
    return !operator==(b);
}