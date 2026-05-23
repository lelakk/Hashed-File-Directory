//
// Created by Jan Józwik on 12/05/2026.
//

#ifndef KATALOGPROJEKT_KATALOGQUADRATIC_H
#define KATALOGPROJEKT_KATALOGQUADRATIC_H
#include "katalog.hpp"


class KatalogQuadratic {

    std::vector<wpisKatalogowy> tablica;
    int pojemnosc;
    int liczbaElementow;

    int haszuj(std::string& nazwaPliku, int size);

public:
    KatalogQuadratic(int poczatkowaPojemnosc=100);

    void insert(std::string& nazwaPliku, int inode);
    bool usun(std::string& nazwaPliku);
    int szukaj(std::string& nazwaPliku);
    void wyswietl();
    void powieksz();
};


#endif //KATALOGPROJEKT_KATALOGQUADRATIC_H
