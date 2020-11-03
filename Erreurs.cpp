//
// Created by dimit on 03/11/2020.
//

#include "Erreurs.h"

 Erreurs::Erreurs(int numero, string const & text, int niveau) noexcept
{
    this->m_niveau = niveau;
    this->m_numero = numero;
    this->phrase = text;
}

Erreurs::Erreurs( const string & text) noexcept
{
    this->m_numero = 0;
    this->m_niveau = 0;

    this->phrase = text;
}

const char* Erreurs::what()const noexcept
{
return this->phrase.c_str();
}

int Erreurs::getNiveau() const noexcept
{
    return this->m_niveau;
}