//
// Created by Jan Józwik on 12/05/2026.
//

#include "KatalogLinear.h"
#include <iostream>

int KatalogLinear::haszuj(std::string& nazwaPliku, int size) {
    int hash = 0;
    for (char c : nazwaPliku) {
        hash = hash + c;
    }
    return hash % size;
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
    if (static_cast<double>(liczbaElementow) / pojemnosc > 0.7) {
        powieksz();
    }
    int index = haszuj(nazwaPliku, this->pojemnosc);
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
    liczbaElementow++;
    std::cout << "Dodano '" << nazwaPliku << "' pod indeks " << index << "\n";
}

bool KatalogLinear::usun(std::string& nazwaPliku) {
    int index = haszuj(nazwaPliku, this->pojemnosc);
    int startowaPozycja = index;

    while (tablica[index].zajety == true || tablica[index].nazwaPliku == "DELETED") {
        if (tablica[index].nazwaPliku == nazwaPliku) {
            tablica[index].nazwaPliku = "DELETED";
            tablica[index].zajety = false;
            liczbaElementow--;
            std::cout << "Usunieto plik: " << nazwaPliku << std::endl;
            return true;
        }
        index = (index + 1) % pojemnosc;
        if (index == startowaPozycja) break;
    }

    return false;
}

int KatalogLinear::szukaj(std::string& nazwaPliku) {
    int index = haszuj(nazwaPliku, this->pojemnosc);
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
    return -1;
}

void KatalogLinear::wyswietl() {
    std::cout << "Katalog (pojemnosc: " << pojemnosc << "):\n";
    for (int i = 0; i < pojemnosc; i++) {
        std::cout << "[" << i << "] ";
        if (!tablica[i].zajety && tablica[i].nazwaPliku != "DELETED") {
            std::cout << "-- puste --";
        } else if (tablica[i].nazwaPliku == "DELETED") {
            std::cout << "-- usuniete --";
        } else {
            std::cout << tablica[i].nazwaPliku << " (inode: " << tablica[i].inode << ")";
        }
        std::cout << "\n";
    }
}

void KatalogLinear::powieksz() {
    int nowaPojemnosc = pojemnosc * 2;
    std::vector<wpisKatalogowy> nowaTablica(nowaPojemnosc);

    for (int i = 0; i < nowaPojemnosc; i++) {
        nowaTablica[i].zajety = false;
        nowaTablica[i].nazwaPliku = "";
    }

    for (int i = 0; i < pojemnosc; i++) {
        if (tablica[i].zajety && tablica[i].nazwaPliku != "DELETED") {
            int nowyIndex = haszuj(tablica[i].nazwaPliku, nowaPojemnosc);

            while (nowaTablica[nowyIndex].zajety) {
                nowyIndex = (nowyIndex + 1) % nowaPojemnosc;
            }

            nowaTablica[nowyIndex] = tablica[i];
        }
    }
    tablica = nowaTablica;
    pojemnosc = nowaPojemnosc;

    std::cout << "Powiększono tablicę do rozmiaru " << pojemnosc << "\n";
}

