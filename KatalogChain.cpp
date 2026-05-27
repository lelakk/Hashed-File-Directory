#include "KatalogChain.hpp"
#include <iostream>
// Paweł Lelakowski
int KatalogChain::haszuj(std::string nazwaPliku) {
    int hash = 0;
    for (char c : nazwaPliku) {
        hash = hash + c;
    }
    return hash % this->pojemnosc;
}

KatalogChain::KatalogChain(int poczatkowaPojemnosc) {
    this->pojemnosc = poczatkowaPojemnosc;
    tablica.resize(pojemnosc);
}

void KatalogChain::insert(std::string nazwaPliku, int inode, std::string typPliku) {
    int idx = haszuj(nazwaPliku);

    for (auto& wpis : tablica[idx]) {
        if (wpis.nazwaPliku == nazwaPliku) {
            std::cout << "Plik o nazwie '" << nazwaPliku << "' juz istnieje!\n";
            return;
        }
    }

    wpisKatalogowy nowy;
    nowy.nazwaPliku = nazwaPliku;
    nowy.inode = inode;
    nowy.typPliku = typPliku;
    nowy.zajety = true;
    nowy.usuniety = false;

    tablica[idx].push_back(nowy);
    std::cout << "Chain: Dodano '" << nazwaPliku << "' pod indeks " << idx << "\n";
}

bool KatalogChain::usun(std::string nazwaPliku) {
    int index = haszuj(nazwaPliku);
    auto& kubelek = tablica[index];

    for (auto wpis = kubelek.begin(); wpis != kubelek.end(); ++wpis) {
        if (wpis->nazwaPliku == nazwaPliku) {
            kubelek.erase(wpis);
            return true;
        }
    }
    return false;
}

int KatalogChain::szukaj(std::string nazwaPliku) {
    int index = haszuj(nazwaPliku);

    for (auto& wpis : tablica[index]) {
        if (wpis.nazwaPliku == nazwaPliku) {
            return wpis.inode;
        }
    }
    return -1;
}

void KatalogChain::wyswietl() {
    std::cout << "Katalog Chain (pojemnosc: " << pojemnosc << "):\n";
    bool czyPusty = true;
    for (int i = 0; i < pojemnosc; i++) {
        if (!tablica[i].empty()) {
            czyPusty = false;
            std::cout << "[" << i << "]: ";
            for (auto& wpis : tablica[i]) {
                std::cout << "{ " << wpis.nazwaPliku << " (Typ: " << wpis.typPliku << ", inode: " << wpis.inode << ") } ";
            }
            std::cout << "\n";
        }
    }
    if (czyPusty) {
        std::cout << "Katalog jest pusty\n";
    }
}