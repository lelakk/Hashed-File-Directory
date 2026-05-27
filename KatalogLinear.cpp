#include "KatalogLinear.h"
#include <iostream>
//Jan Józwik
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
        tablica[i].usuniety = false;
        tablica[i].nazwaPliku = "";
    }
}

void KatalogLinear::insert(std::string& nazwaPliku, int inode, std::string typPliku) {
    if (static_cast<double>(liczbaElementow) / pojemnosc > 0.7) {
        powieksz();
    }

    int index = haszuj(nazwaPliku, this->pojemnosc);
    int startowaPozycja = index;
    int pierwszeUsuniete = -1;

    while (tablica[index].zajety || tablica[index].usuniety) {
        if (tablica[index].zajety && tablica[index].nazwaPliku == nazwaPliku) {
            std::cout << "Plik o nazwie " << nazwaPliku << " juz istnieje!\n";
            return;
        }
        if (!tablica[index].zajety && tablica[index].usuniety && pierwszeUsuniete == -1) {
            pierwszeUsuniete = index;
        }
        index = (index + 1) % pojemnosc;

        if (index == startowaPozycja) {
            break;
        }
    }

    if (pierwszeUsuniete != -1) {
        index = pierwszeUsuniete;
    } else if (tablica[index].zajety) {
        std::cout << "Blad: Tablica mieszajaca jest pelna!\n";
        return;
    }

    tablica[index].nazwaPliku = nazwaPliku;
    tablica[index].inode = inode;
    tablica[index].typPliku = typPliku;
    tablica[index].zajety = true;
    tablica[index].usuniety = false;
    liczbaElementow++;
    std::cout << "Linear: Dodano '" << nazwaPliku << "' pod indeks " << index << "\n";
}

bool KatalogLinear::usun(std::string& nazwaPliku) {
    int index = haszuj(nazwaPliku, this->pojemnosc);
    int startowaPozycja = index;

    while (tablica[index].zajety || tablica[index].usuniety) {
        if (tablica[index].zajety && tablica[index].nazwaPliku == nazwaPliku) {
            tablica[index].zajety = false;
            tablica[index].usuniety = true;
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

    while (tablica[index].zajety || tablica[index].usuniety) {
        if (tablica[index].zajety && tablica[index].nazwaPliku == nazwaPliku) {
            return tablica[index].inode;
        }
        index = (index + 1) % pojemnosc;

        if (index == startowaPozycja) {
            break;
        }
    }
    return -1;
}

void KatalogLinear::wyswietl() {
    std::cout << "Katalog Linear (pojemnosc: " << pojemnosc << "):\n";
    for (int i = 0; i < pojemnosc; i++) {
        std::cout << "[" << i << "] ";
        if (!tablica[i].zajety && !tablica[i].usuniety) {
            std::cout << "-- puste --";
        } else if (tablica[i].usuniety) {
            std::cout << "-- usuniete --";
        } else {
            std::cout << tablica[i].nazwaPliku << " (Typ: " << tablica[i].typPliku << ", inode: " << tablica[i].inode << ")";
        }
        std::cout << "\n";
    }
}

void KatalogLinear::powieksz() {
    int nowaPojemnosc = pojemnosc * 2;
    std::vector<wpisKatalogowy> nowaTablica(nowaPojemnosc);

    for (int i = 0; i < nowaPojemnosc; i++) {
        nowaTablica[i].zajety = false;
        nowaTablica[i].usuniety = false;
        nowaTablica[i].nazwaPliku = "";
    }

    for (int i = 0; i < pojemnosc; i++) {
        if (tablica[i].zajety) {
            int nowyIndex = haszuj(tablica[i].nazwaPliku, nowaPojemnosc);

            while (nowaTablica[nowyIndex].zajety) {
                nowyIndex = (nowyIndex + 1) % nowaPojemnosc;
            }

            nowaTablica[nowyIndex] = tablica[i];
            nowaTablica[nowyIndex].usuniety = false;
        }
    }
    tablica = nowaTablica;
    pojemnosc = nowaPojemnosc;

    std::cout << "Powiekszono tablice (Linear) do rozmiaru " << pojemnosc << "\n";
}