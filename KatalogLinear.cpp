//
// Created by Jan Józwik on 12/05/2026.
//

#include "KatalogLinear.h"
#include <iostream>

int KatalogLinear::haszuj(std::string& nazwaPliku) {
    int hash = 0;
    for (char c : nazwaPliku) {
        hash = hash + c;
    }
    return hash % this->pojemnosc;
}

KatalogLinear::KatalogLinear(int poczatkowaPojemnosc) {
    pojemnosc = poczatkowaPojemnosc;
    tablica.resize(pojemnosc);
    for(int i = 0; i < pojemnosc; i++) {
        tablica[i].zajety = false;
        tablica[i].nazwaPliku = "";
    }
}

void KatalogLinear::insert(std::string& nazwaPliku, int inode) {
    int index = haszuj(nazwaPliku);
    int startowaPozycja = index;

    while (tablica[index].zajety == true && tablica[index].nazwaPliku != "DELETED") {
        if (tablica[index].nazwaPliku == nazwaPliku) {
            std::cout << "Plik o nazwie " << nazwaPliku << " juz istnieje!\n";
            return;
        }
        index = (index + 1) % pojemnosc;

        if (index == startowaPozycja) {
            std::cout << "Blad: Tablica mieszajaca jest pelna!\n";
            return;
        }
    }

    tablica[index].nazwaPliku = nazwaPliku;
    tablica[index].inode = inode;
    tablica[index].zajety = true;
    std::cout << "Dodano '" << nazwaPliku << "' pod indeks " << index << "\n";
}

bool KatalogLinear::usun(std::string& nazwaPliku) {
    int index = haszuj(nazwaPliku);
    int startowaPozycja = index;

    while (tablica[index].zajety == true || tablica[index].nazwaPliku == "DELETED") {
        if (tablica[index].nazwaPliku == nazwaPliku) {
            tablica[index].nazwaPliku = "DELETED";
            tablica[index].zajety = false;
            std::cout << "Usunieto plik: " << nazwaPliku << std::endl;
            return true;
        }
        index = (index + 1) % pojemnosc;
        if (index == startowaPozycja) break;
    }

    return false;
}

int KatalogLinear::szukaj(std::string& nazwaPliku) {
    int index = haszuj(nazwaPliku);
    int startowaPozycja = index;

    while (tablica[index].zajety == true || tablica[index].nazwaPliku == "DELETED") {
        if (tablica[index].nazwaPliku == nazwaPliku) {
            return tablica[index].inode;
        }
        index = (index + 1) % pojemnosc;

        if (index == startowaPozycja) {
            return -1;
        }
    }
}

void KatalogLinear::wyswietl() {
}
