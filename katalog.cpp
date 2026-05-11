#include "katalog.hpp"


katalog::katalog(int poczatkowaPojemnosc) {
    pojemnosc = poczatkowaPojemnosc;
    tablica.resize(pojemnosc);
    /*test
    tablica[2].nazwaPliku = "test.txt";
    tablica[2].inode = 101;
    tablica[2].zajety = true
    */
}

int katalog::haszuj(std::string nazwaPliku) {
    // funkcja co zmieni string na indeks {0, pojemnosc}
    return 0;
}

bool katalog::wstaw(std::string nazwaPliku, int inode) {
    // haszuj() znajdz miejsce
    // zajete -> kolizja, wolne -> zapisz i zajety=true ok
    return false;
}

bool katalog::usun(std::string nazwaPliku) {
    // zajete=false bedzie ok
    return false;
}

int katalog::szukaj(std::string nazwaPliku) {
    // niech zwraca numer inodea a jak nie to -1
    return -1;
}


void katalog::wyswietl() { // po prostu aby wyswietlalo wszystko
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