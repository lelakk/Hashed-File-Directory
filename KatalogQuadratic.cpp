//
// Created by Jan Józwik on 12/05/2026.
//

#include "KatalogQuadratic.h"

int KatalogQuadratic::haszuj(std::string &nazwaPliku) {
    int hash = 0;
    for (char c : nazwaPliku) {
        hash = hash + c;
    }
    return hash % this->pojemnosc;
}

KatalogQuadratic::KatalogQuadratic(int poczatkowaPojemnosc) {
    pojemnosc = poczatkowaPojemnosc;
    tablica.resize(pojemnosc);
    for(int i = 0; i < pojemnosc; i++) {
        tablica[i].zajety = false;
        tablica[i].nazwaPliku = "";
    }
}

void KatalogQuadratic::insert(std::string &nazwaPliku, int inode) {
    int index = haszuj(nazwaPliku);
    int startowaPozycja = index;

   for (int i = 0; i < pojemnosc; i++) {
       index = (index + i * i) % pojemnosc;
       if (tablica[index].zajety == false && tablica[index].nazwaPliku != "DELETED") {
           tablica[index].nazwaPliku = nazwaPliku;
           tablica[index].inode = inode;
           tablica[index].zajety = true;
           std::cout << "Dodano '" << nazwaPliku << "' pod indeks " << index << "\n";
           return;
       }
       if (tablica[index].nazwaPliku == nazwaPliku) {
           std::cout << "Plik o takiej nazwie juz istnieje" << std::endl;
           return;
       }
   }
   std::cout << "Nie udalo sie znalezc miejsca (tablica moze nie byc pelna)" << std::endl;
}

bool KatalogQuadratic::usun(std::string &nazwaPliku) {
}

int KatalogQuadratic::szukaj(std::string &nazwaPliku) {
}

void KatalogQuadratic::wyswietl() {
}
