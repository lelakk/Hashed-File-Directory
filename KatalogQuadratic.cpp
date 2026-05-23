//
// Created by Jan Józwik on 12/05/2026.
//

#include "KatalogQuadratic.h"

int KatalogQuadratic::haszuj(std::string &nazwaPliku, int size) {
    int hash = 0;
    for (char c : nazwaPliku) {
        hash = hash + c;
    }
    return hash % size;
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
    if (static_cast<double>(liczbaElementow + 1) / pojemnosc > 0.7) {
        powieksz();
    }
    int bazowy = haszuj(nazwaPliku, pojemnosc);
    int startowaPozycja = bazowy;
    for (int i = 0; i < pojemnosc; i++) {
        int index = (bazowy + i * i) % pojemnosc;
        if (tablica[index].zajety == false && tablica[index].nazwaPliku != "DELETED") {
            tablica[index].nazwaPliku = nazwaPliku;
            tablica[index].inode = inode;
            tablica[index].zajety = true;
            liczbaElementow++;
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
    int bazowy = haszuj(nazwaPliku, this->pojemnosc);
    int startowaPozycja = bazowy;
    int i = 0;
    int index = (bazowy + i * i) % pojemnosc;
    while (tablica[index].zajety == true || tablica[index].nazwaPliku == "DELETED") {
        if (tablica[index].nazwaPliku == nazwaPliku) {
            tablica[index].nazwaPliku = "DELETED";
            tablica[index].zajety = false;
            liczbaElementow--;
            std::cout << "Usunieto plik: " << nazwaPliku << std::endl;
            return true;
        }
        i++;
        index = (bazowy + i * i) % pojemnosc;
        if (index == startowaPozycja) break;
    }

    return false;
}

int KatalogQuadratic::szukaj(std::string &nazwaPliku) {
    int bazowy = haszuj(nazwaPliku, this->pojemnosc);
    int startowaPozycja = bazowy;
    int i = 0;
    int index = (bazowy + i * i) % pojemnosc;
    while (tablica[index].zajety == true || tablica[index].nazwaPliku == "DELETED") {
        if (tablica[index].nazwaPliku == nazwaPliku) {
            return tablica[index].inode;
        }
        i++;
        index = (bazowy + i * i) % pojemnosc;

        if (index == startowaPozycja) {
            return -1;
        }
    }
    return -1;
}

void KatalogQuadratic::wyswietl() {
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

void KatalogQuadratic::powieksz() {
    int nowaPojemnosc = pojemnosc * 2;
    std::vector<wpisKatalogowy> nowaTablica(nowaPojemnosc);

    for (int i = 0; i < nowaPojemnosc; i++) {
        nowaTablica[i].zajety = false;
        nowaTablica[i].nazwaPliku = "";
    }

    for (int i = 0; i < pojemnosc; i++) {
        if (tablica[i].zajety && tablica[i].nazwaPliku != "DELETED") {
            int nowyIndex = haszuj(tablica[i].nazwaPliku, nowaPojemnosc);

            int bazowy = nowyIndex;
            int j = 1;
            while (nowaTablica[nowyIndex].zajety) {
                nowyIndex = (bazowy + j * j) % nowaPojemnosc;
                j++;
            }

            nowaTablica[nowyIndex] = tablica[i];
        }
    }
    tablica = nowaTablica;
    pojemnosc = nowaPojemnosc;

    std::cout << "Powiększono tablicę do rozmiaru " << pojemnosc << "\n";
}
