//
// Created by Jan Józwik on 12/05/2026.
//

#ifndef KATALOGPROJEKT_KATALOGLINEAR_H
#define KATALOGPROJEKT_KATALOGLINEAR_H
#include "katalog.hpp"

class KatalogLinear {
    std::vector<wpisKatalogowy> tablica;
    int pojemnosc;

    int haszuj(std::string& nazwaPliku);

public:
    KatalogLinear(int poczatkowaPojemnosc=100);

    void insert(std::string& nazwaPliku, int inode);
    bool usun(std::string& nazwaPliku);
    int szukaj(std::string& nazwaPliku);
    void wyswietl();
};


#endif //KATALOGPROJEKT_KATALOGLINEAR_H
