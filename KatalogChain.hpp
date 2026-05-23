#ifndef KATALOGPROJEKT_KATALOGCHAIN_H
#define KATALOGPROJEKT_KATALOGCHAIN_H

#include <vector>
#include <string>
#include "katalog.hpp"

class KatalogChain {
    std::vector<std::vector<wpisKatalogowy>> tablica;
    int pojemnosc;

    int haszuj(std::string nazwaPliku);
public:
    KatalogChain(int poczatkowaPojemnosc=100);
    // Dodano typPliku
    void insert(std::string nazwaPliku, int inode, std::string typPliku);
    bool usun(std::string nazwaPliku);
    int szukaj(std::string nazwaPliku);
    void wyswietl();
};

#endif //KATALOGPROJEKT_KATALOGCHAIN_H