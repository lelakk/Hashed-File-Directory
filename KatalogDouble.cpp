#include "KatalogDouble.hpp"


KatalogDouble::KatalogDouble(int poczatkowaPojemnosc) {
    pojemnosc = poczatkowaPojemnosc;
    tablica.resize(pojemnosc);
    /*test
    tablica[2].nazwaPliku = "test.txt";
    tablica[2].inode = 101;
    tablica[2].zajety = true
    */
}


int KatalogDouble::haszuj(std::string nazwaPliku) {
    // funkcja co zmieni string na indeks {0, pojemnosc}
    int hash = 0;
    for (char c : nazwaPliku) {
        hash = hash + c;
    }
    return hash % this->pojemnosc;
}

int KatalogDouble::haszuj2(std::string nazwaPliku) {
    int hash = 0;
    for (char c : nazwaPliku) {
        hash = hash * 19 + c;
    }
    return hash % this->pojemnosc;
}

v
void KatalogDouble::insertDoubleHash(std::string nazwaPliku, int inode) {
    int hash = haszuj(nazwaPliku);
    int step = haszuj2(nazwaPliku);

    for (int i = 0; i < this->pojemnosc; i++) {
        int idx = (hash + step * i) % pojemnosc;

        if (tablica[idx].zajety != true) {
            tablica[idx] = {nazwaPliku, inode};
            tablica[idx].zajety = true;
            std::cout << "Double: Dodano " << nazwaPliku << " pod indeks " << idx << std::endl;
        }
    }
    std::cout << "Blad: tablica pelna";
}

bool KatalogDouble::usun(std::string nazwaPliku) {
    // zajete=false bedzie ok
    return false;
}

int KatalogDouble::szukaj(std::string nazwaPliku) {
    // niech zwraca numer inodea a jak nie to -1
    return -1;
}


void KatalogDouble::wyswietl() { // po prostu aby wyswietlalo wszystko
    std::cout << "Zawartosc:" << std::endl;
    int zajeteMiejsca=0;
    for (int i=0;i<pojemnosc;i++) {
        if (tablica[i].zajety==true) {
            std::cout << "indeks tablicy[" << i << "] z nazwa: " << tablica[i].nazwaPliku << std::endl;;
            std::cout << "i-node: " << tablica[i].inode<<std::endl;
            zajeteMiejsca++;
        }
    }
    if (zajeteMiejsca==0) {
        std::cout << "katalog jest pusty" << std::endl;
    }
}