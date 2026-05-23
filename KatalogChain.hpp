//
// Created by Jan Józwik on 12/05/2026.
//

#ifndef KATALOGPROJEKT_KATALOGCHAIN_H
#define KATALOGPROJEKT_KATALOGCHAIN_H

#include <vector>
#include "KatalogDouble.hpp"


class KatalogChain {
    std::vector<std::vector<wpisKatalogowy>> tablica;
    int pojemnosc;

    int haszuj(std::string nazwaPliku);
public:
    KatalogChain(int poczatkowaPojemnosc=100);

    void insert(std::string nazwaPliku, int inode);
    bool usun(std::string nazwaPliku);
    int szukaj(std::string nazwaPliku);
    void wyswietl();
};


#endif //KATALOGPROJEKT_KATALOGCHAIN_H
