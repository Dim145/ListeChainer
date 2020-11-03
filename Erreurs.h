//
// Created by dimit on 03/11/2020.
//

#ifndef TP2LISTECHAINER_ERREURS_H
#define TP2LISTECHAINER_ERREURS_H

#include <exception>
#include <string>

using namespace std;


class Erreurs : public exception
{
    int m_numero;
    int m_niveau;

    string phrase;

public:
    explicit Erreurs(int numero = 0, string const & text="", int niveau = 0) noexcept;

    explicit Erreurs( const string & text) noexcept;

    const char* what()const noexcept override;

    int getNiveau() const noexcept;

    ~Erreurs() noexcept override
    = default;
};


#endif //TP2LISTECHAINER_ERREURS_H
