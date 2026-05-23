#ifndef KATALOGPROJEKT_KATALOGLINEAR_H
#define KATALOGPROJEKT_KATALOGLINEAR_H

#include <vector>
#include <string>
#include "katalog.hpp"

class KatalogLinear {
    std::vector<wpisKatalogowy> tablica;
    int pojemnosc;
    int liczbaElementow = 0;

    int haszuj(std::string& nazwaPliku, int size);

public:
    KatalogLinear(int poczatkowaPojemnosc=100);

    // Dodano typPliku
    void insert(std::string& nazwaPliku, int inode, std::string typPliku);
    bool usun(std::string& nazwaPliku);
    int szukaj(std::string& nazwaPliku);
    void wyswietl();
    void powieksz();
};

#endif //KATALOGPROJEKT_KATALOGLINEAR_H