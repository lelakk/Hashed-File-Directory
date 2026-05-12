#ifndef HASHED_FILE_DIRECTORY_KATALOG_HPP
#define HASHED_FILE_DIRECTORY_KATALOG_HPP

#include <iostream>
#include <string>
#include <vector>
#include <list>

struct wpisKatalogowy {
    std::string nazwaPliku;
    int inode;
    bool zajety=false;
};

class katalog {
private:
    std::vector<wpisKatalogowy> tablica;
    int pojemnosc;

    int haszuj(std::string nazwaPliku);
    //do doubleHash
    int haszuj2(std::string nazwaPliku);

public:
    katalog(int poczatkowaPojemnosc=100);

    void insertChain(std::string nazwaPliku, int inode);
    void insertLinear(std::string nazwaPliku, int inode);
    void insertQuadratic(std::string nazwaPliku, int inode);
    void insertDoubleHash(std::string nazwaPliku, int inode);

    bool usun(std::string nazwaPliku);
    int szukaj(std::string nazwaPliku);
    void wyswietl();
};


#endif