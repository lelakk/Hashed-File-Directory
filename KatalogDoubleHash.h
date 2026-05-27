#ifndef KATALOGPROJEKT_KATALOGDOUBLEHASH_H
#define KATALOGPROJEKT_KATALOGDOUBLEHASH_H

#include <vector>
#include <string>
#include "katalog.hpp"
// Paweł Lelakowski
class KatalogDoubleHash {
    std::vector<wpisKatalogowy> tablica;
    int pojemnosc;
    int liczbaElementow;

    int haszuj(std::string& nazwaPliku, int size);
    int haszuj2(std::string& nazwaPliku, int size); // druga funkcja haszująca

public:
    KatalogDoubleHash(int poczatkowaPojemnosc=100);
    void insert(std::string& nazwaPliku, int inode, std::string typPliku);
    bool usun(std::string& nazwaPliku);
    int szukaj(std::string& nazwaPliku);
    void wyswietl();
    void powieksz();
};

#endif //KATALOGPROJEKT_KATALOGDOUBLEHASH_H