//
// Created by Jan Józwik on 12/05/2026.
//

#include "KatalogChain.hpp"

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

void KatalogChain::insert(std::string nazwaPliku, int inode) {
    int idx = haszuj(nazwaPliku);

    wpisKatalogowy nowy;
    nowy.nazwaPliku = nazwaPliku;
    nowy.inode = inode;
    nowy.zajety = true;

    tablica[idx].push_back(nowy);
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
    std::cout << "Zawartosc:" << std::endl;
    int zajeteMiejsca=0;
    for (int i=0;i<pojemnosc;i++) {
        if (!tablica[i].empty()) {
            std::cout << "[" << i << "]: ";
            for (auto& wpis : tablica[i]) {
                std::cout << "{ " << wpis.nazwaPliku << "(i: " << wpis.inode << ") } -> ";
            }
        }
    }
}
