#include "KatalogDoubleHash.h"
#include <iostream>

int KatalogDoubleHash::haszuj(std::string& nazwaPliku, int size) {
    int hash = 0;
    for (char c : nazwaPliku) {
        hash = hash + c;
    }
    return hash % size;
}

int KatalogDoubleHash::haszuj2(std::string& nazwaPliku, int size) {
    int hash = 0;
    for (char c : nazwaPliku) {
        hash = hash * 19 + c;
    }
    return (hash % (size - 1)) + 1;
}

KatalogDoubleHash::KatalogDoubleHash(int poczatkowaPojemnosc) {
    pojemnosc = poczatkowaPojemnosc;
    tablica.resize(pojemnosc);
    liczbaElementow = 0;
    for(int i = 0; i < pojemnosc; i++) {
        tablica[i].zajety = false;
        tablica[i].usuniety = false;
        tablica[i].nazwaPliku = "";
    }
}

void KatalogDoubleHash::insert(std::string& nazwaPliku, int inode, std::string typPliku) {
    if (static_cast<double>(liczbaElementow + 1) / pojemnosc > 0.7) {
        powieksz();
    }
    int bazowy = haszuj(nazwaPliku, pojemnosc);
    int step = haszuj2(nazwaPliku, pojemnosc);
    int pierwszeUsuniete = -1;

    for (int i = 0; i < pojemnosc; i++) {
        int index = (bazowy + i * step) % pojemnosc;
        
        if (tablica[index].zajety && tablica[index].nazwaPliku == nazwaPliku) {
            std::cout << "Plik o takiej nazwie juz istnieje" << std::endl;
            return;
        }

        if (!tablica[index].zajety && tablica[index].usuniety && pierwszeUsuniete == -1) {
            pierwszeUsuniete = index;
        }

        if (!tablica[index].zajety && !tablica[index].usuniety) {
            if (pierwszeUsuniete != -1) {
                index = pierwszeUsuniete;
            }
            tablica[index].nazwaPliku = nazwaPliku;
            tablica[index].inode = inode;
            tablica[index].typPliku = typPliku;
            tablica[index].zajety = true;
            tablica[index].usuniety = false;
            liczbaElementow++;
            std::cout << "Double Hash: Dodano '" << nazwaPliku << "' pod indeks " << index << "\n";
            return;
        }
    }

    // Jeśli tablica pełna, ale ma usunięte miejsca
    if (pierwszeUsuniete != -1) {
        tablica[pierwszeUsuniete].nazwaPliku = nazwaPliku;
        tablica[pierwszeUsuniete].inode = inode;
        tablica[pierwszeUsuniete].typPliku = typPliku;
        tablica[pierwszeUsuniete].zajety = true;
        tablica[pierwszeUsuniete].usuniety = false;
        liczbaElementow++;
        std::cout << "Double Hash: Dodano '" << nazwaPliku << "' pod indeks " << pierwszeUsuniete << "\n";
        return;
    }

    std::cout << "Nie udalo sie znalezc miejsca (tablica moze nie byc pelna)" << std::endl;
}

bool KatalogDoubleHash::usun(std::string& nazwaPliku) {
    int bazowy = haszuj(nazwaPliku, this->pojemnosc);
    int step = haszuj2(nazwaPliku, pojemnosc);

    for (int i = 0; i < pojemnosc; i++) {
        int index = (bazowy + i * step) % pojemnosc;
        
        if (!tablica[index].zajety && !tablica[index].usuniety) {
            break;
        }
        
        if (tablica[index].zajety && tablica[index].nazwaPliku == nazwaPliku) {
            tablica[index].zajety = false;
            tablica[index].usuniety = true;
            liczbaElementow--;
            std::cout << "Usunieto plik: " << nazwaPliku << std::endl;
            return true;
        }
    }
    return false;
}

int KatalogDoubleHash::szukaj(std::string& nazwaPliku) {
    int bazowy = haszuj(nazwaPliku, this->pojemnosc);
    int step = haszuj2(nazwaPliku, pojemnosc);

    for (int i = 0; i < pojemnosc; i++) {
        int index = (bazowy + i * step) % pojemnosc;
        
        if (!tablica[index].zajety && !tablica[index].usuniety) {
            break;
        }

        if (tablica[index].zajety && tablica[index].nazwaPliku == nazwaPliku) {
            return tablica[index].inode;
        }
    }
    return -1;
}

void KatalogDoubleHash::wyswietl() {
    std::cout << "Katalog Double Hash (pojemnosc: " << pojemnosc << "):\n";
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

void KatalogDoubleHash::powieksz() {
    int nowaPojemnosc = pojemnosc * 2;
    std::vector<wpisKatalogowy> nowaTablica(nowaPojemnosc);

    for (int i = 0; i < nowaPojemnosc; i++) {
        nowaTablica[i].zajety = false;
        nowaTablica[i].usuniety = false;
        nowaTablica[i].nazwaPliku = "";
    }

    for (int i = 0; i < pojemnosc; i++) {
        if (tablica[i].zajety) {
            int bazowy = haszuj(tablica[i].nazwaPliku, nowaPojemnosc);
            int step = haszuj2(tablica[i].nazwaPliku, nowaPojemnosc);
            int nowyIndex = bazowy;
            
            int j = 0;
            while (nowaTablica[nowyIndex].zajety) {
                j++;
                nowyIndex = (bazowy + j * step) % nowaPojemnosc; 
            }

            nowaTablica[nowyIndex] = tablica[i];
            nowaTablica[nowyIndex].usuniety = false;
        }
    }
    tablica = nowaTablica;
    pojemnosc = nowaPojemnosc;

    std::cout << "Powiekszono tablice (Double Hash) do rozmiaru " << pojemnosc << "\n";
}