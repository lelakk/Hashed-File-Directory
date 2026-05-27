#include <iostream>
#include "KatalogChain.hpp"
#include "KatalogLinear.h"
#include "KatalogQuadratic.h"
#include "KatalogDoubleHash.h"

template <typename TypKatalogu>
void obslugujMenu() {
    int rozmiar;
    std::cout << "\nPodaj rozmiar nowego katalogu: ";
    std::cin >> rozmiar;

    TypKatalogu katalog(rozmiar);
    int wybor;

    do {
        std::cout << "\n=== INTERAKTYWNE MENU ===\n"
                  << "1. Dodaj plik\n"
                  << "2. Szukaj pliku\n"
                  << "3. Usun plik\n"
                  << "4. Wyswietl katalog\n"
                  << "0. Wroc do glownego menu / Zakoncz\n"
                  << "Wybierz operacje: ";
        std::cin >> wybor;

        std::string nazwa, typ;
        int inode;

        switch(wybor) {
            case 1:
                std::cout << "Podaj nazwe pliku: ";
                std::cin >> nazwa;
                std::cout << "Podaj inode (liczba calkowita): ";
                std::cin >> inode;
                std::cout << "Podaj typ pliku: ";
                std::cin >> typ;
                katalog.insert(nazwa, inode, typ);
                std::cout << "Wykonano probe dodania pliku.\n";
                break;
            case 2:
                std::cout << "Podaj nazwe pliku do wyszukania: ";
                std::cin >> nazwa;
                inode = katalog.szukaj(nazwa);
                if (inode != -1) {
                    std::cout << "Znaleziono plik " << nazwa << "Inode: " << inode << "\n";
                } else {
                    std::cout << "Nie znaleziono pliku " << nazwa << ".\n";
                }
                break;
            case 3:
                std::cout << "Podaj nazwe pliku do usuniecia: ";
                std::cin >> nazwa;
                katalog.usun(nazwa);
                std::cout << "Wykonano polecenie usuniecia pliku.\n";
                break;
            case 4:
                std::cout << "\n--- STAN KATALOGU ---\n";
                katalog.wyswietl();
                break;
            case 0:
                std::cout << "Wychodzenie z menu...\n";
                break;
            default:
                std::cout << "Nieprawidlowy wybor. Sprobuj ponownie.\n";
        }
    } while (wybor != 0);
}

int main() {
    // Przygotowanie zmiennych z nazwami i odpowiadającymi im typami
    std::string f1 = "dokument.txt", t1 = ".txt";
    std::string f2 = "foto.grafia.jpg",     t2 = ".jpg";
    std::string f3 = "muzyka.mp3",   t3 = ".mp3";
    std::string f4 = "video.mp4",    t4 = ".mp4";
    std::string f5 = "archiwum.zip", t5 = ".zip";

    // ========== METODA LANCUCHOWA (CHAIN) ==========
    std::cout << "\n========== CHAIN (LANCUCHOWA) ==========\n";
    KatalogChain katalogC(5);

    std::cout << "\n=== Wstawianie plikow ===\n";
    katalogC.insert(f1, 101, t1);
    katalogC.insert(f2, 102, t2);
    katalogC.insert(f3, 103, t3);
    katalogC.insert(f4, 104, t4);
    katalogC.insert(f5, 105, t5);

    std::cout << "\n=== Stan katalogu ===\n";
    katalogC.wyswietl();

    std::cout << "\n=== Duplikat ===\n";
    katalogC.insert(f1, 999, t1);

    std::cout << "\n=== Szukanie ===\n";
    std::string szukanyC = "foto.jpg";
    int inodeC = katalogC.szukaj(szukanyC);
    if (inodeC != -1) {
        std::cout << "Znaleziono '" << szukanyC << "' -> inode: " << inodeC << "\n";
    }

    std::string nieznanyC = "brak.txt";
    inodeC = katalogC.szukaj(nieznanyC);
    if (inodeC == -1) {
        std::cout << "Nie znaleziono '" << nieznanyC << "'\n";
    }

    std::cout << "\n=== Usuwanie ===\n";
    katalogC.usun(f2);

    std::cout << "\n=== Stan po usunieciu ===\n";
    katalogC.wyswietl();

    std::cout << "\n=== Szukanie usunietego pliku ===\n";
    inodeC = katalogC.szukaj(f2);
    if (inodeC == -1) {
        std::cout << "Nie znaleziono '" << f2 << "' (usunieto)\n";
    }

    // ========== METODA LINIOWA (LINEAR) ==========
    std::cout << "\n\n========== LINEAR (LINIOWA) ==========\n";
    KatalogLinear katalogL(5);

    std::cout << "\n=== Wstawianie plikow ===\n";
    katalogL.insert(f1, 101, t1);
    katalogL.insert(f2, 102, t2);
    katalogL.insert(f3, 103, t3);
    katalogL.insert(f4, 104, t4);
    katalogL.insert(f5, 105, t5);

    std::cout << "\n=== Stan katalogu ===\n";
    katalogL.wyswietl();

    std::cout << "\n=== Duplikat ===\n";
    katalogL.insert(f1, 999, t1);

    std::cout << "\n=== Szukanie ===\n";
    std::string szukanyL = "foto.jpg";
    int inodeL = katalogL.szukaj(szukanyL);
    if (inodeL != -1) {
        std::cout << "Znaleziono '" << szukanyL << "' -> inode: " << inodeL << "\n";
    }

    std::string nieznanyL = "brak.txt";
    inodeL = katalogL.szukaj(nieznanyL);
    if (inodeL == -1) {
        std::cout << "Nie znaleziono '" << nieznanyL << "'\n";
    }

    std::cout << "\n=== Usuwanie ===\n";
    katalogL.usun(f2);

    std::cout << "\n=== Stan po usunieciu ===\n";
    katalogL.wyswietl();

    std::cout << "\n=== Szukanie usuniętego pliku ===\n";
    inodeL = katalogL.szukaj(f2);
    if (inodeL == -1) {
        std::cout << "Nie znaleziono '" << f2 << "' (usunieto)\n";
    }

    // ========== METODA KWADRATOWA (QUADRATIC) ==========
    std::cout << "\n\n========== QUADRATIC (KWADRATOWA) ==========\n";
    KatalogQuadratic katalogQ(5);

    std::cout << "\n=== Wstawianie plikow ===\n";
    katalogQ.insert(f1, 101, t1);
    katalogQ.insert(f2, 102, t2);
    katalogQ.insert(f3, 103, t3);
    katalogQ.insert(f4, 104, t4);
    katalogQ.insert(f5, 105, t5);

    std::cout << "\n=== Stan katalogu ===\n";
    katalogQ.wyswietl();

    std::cout << "\n=== Duplikat ===\n";
    katalogQ.insert(f1, 999, t1);

    std::cout << "\n=== Szukanie ===\n";
    std::string szukanyQ = "foto.jpg";
    int inodeQ = katalogQ.szukaj(szukanyQ);
    if (inodeQ != -1) {
        std::cout << "Znaleziono '" << szukanyQ << "' -> inode: " << inodeQ << "\n";
    }

    std::string nieznanyQ = "brak.txt";
    inodeQ = katalogQ.szukaj(nieznanyQ);
    if (inodeQ == -1) {
        std::cout << "Nie znaleziono '" << nieznanyQ << "'\n";
    }

    std::cout << "\n=== Usuwanie ===\n";
    katalogQ.usun(f2);

    std::cout << "\n=== Stan po usunieciu ===\n";
    katalogQ.wyswietl();

    std::cout << "\n=== Szukanie usunietego pliku ===\n";
    inodeQ = katalogQ.szukaj(f2);
    if (inodeQ == -1) {
        std::cout << "Nie znaleziono '" << f2 << "' (usunieto)\n";
    }

    // ========== METODA PODWOJNEGO HASZOWANIA (DOUBLE HASH) ==========
    std::cout << "\n\n========== DOUBLE HASH (PODWOJNE HASZOWANIE) ==========\n";
    KatalogDoubleHash katalogD(5);

    std::cout << "\n=== Wstawianie plikow ===\n";
    katalogD.insert(f1, 101, t1);
    katalogD.insert(f2, 102, t2);
    katalogD.insert(f3, 103, t3);
    katalogD.insert(f4, 104, t4);
    katalogD.insert(f5, 105, t5);

    std::cout << "\n=== Stan katalogu ===\n";
    katalogD.wyswietl();

    std::cout << "\n=== Duplikat ===\n";
    katalogD.insert(f1, 999, t1);

    std::cout << "\n=== Szukanie ===\n";
    std::string szukanyD = "foto.jpg";
    int inodeD = katalogD.szukaj(szukanyD);
    if (inodeD != -1) {
        std::cout << "Znaleziono '" << szukanyD << "' -> inode: " << inodeD << "\n";
    }

    std::string nieznanyD = "brak.txt";
    inodeD = katalogD.szukaj(nieznanyD);
    if (inodeD == -1) {
        std::cout << "Nie znaleziono '" << nieznanyD << "'\n";
    }

    std::cout << "\n=== Usuwanie ===\n";
    katalogD.usun(f2);

    std::cout << "\n=== Stan po usunieciu ===\n";
    katalogD.wyswietl();

    std::cout << "\n=== Szukanie usunietego pliku ===\n";
    inodeD = katalogD.szukaj(f2);
    if (inodeD == -1) {
        std::cout << "Nie znaleziono '" << f2 << "' (usunieto)\n";
    }

    int wybranaMetoda;
    do {
        std::cout << "\n\n=================================================\n";
        std::cout << "            TRYB INTERAKTYWNY\n";
        std::cout << "=================================================\n";
        std::cout << "Wybierz metode haszowania do wlasnych testow:\n"
                  << "1. Metoda Lancuchowa (Chain)\n"
                  << "2. Metoda Liniowa (Linear)\n"
                  << "3. Metoda Kwadratowa (Quadratic)\n"
                  << "4. Podwojne Haszowanie (Double Hash)\n"
                  << "0. Zakoncz program\n"
                  << "Wybieram: ";
        std::cin >> wybranaMetoda;

        switch(wybranaMetoda) {
            case 1:
                std::cout << "\n--- Uruchomiono: METODA LANCUCHOWA ---";
                obslugujMenu<KatalogChain>();
                break;
            case 2:
                std::cout << "\n--- Uruchomiono: METODA LINIOWA ---";
                obslugujMenu<KatalogLinear>();
                break;
            case 3:
                std::cout << "\n--- Uruchomiono: METODA KWADRATOWA ---";
                obslugujMenu<KatalogQuadratic>();
                break;
            case 4:
                std::cout << "\n--- Uruchomiono: PODWOJNE HASZOWANIE ---";
                obslugujMenu<KatalogDoubleHash>();
                break;
            case 0:
                std::cout << "Zamykanie programu...\n";
                break;
            default:
                std::cout << "Nieprawidlowy wybor, sprobuj ponownie.\n";
        }
    } while (wybranaMetoda != 0);

    std::cout << "\n========== KONIEC PROGRAMU ==========\n";
    return 0;
}