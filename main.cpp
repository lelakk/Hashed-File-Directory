#include <iostream>
#include "KatalogLinear.h"
#include "KatalogQuadratic.h"

int main() {
    KatalogLinear katalogL(5);

    std::cout << "=== Wstawianie plikow ===\n";
    std::string f1 = "dokument.txt", f2 = "foto.jpg", f3 = "muzyka.mp3",
            f4 = "video.mp4", f5 = "archiwum.zip";

    katalogL.insert(f1, 101);
    katalogL.insert(f2, 102);
    katalogL.insert(f3, 103);
    katalogL.insert(f4, 104);
    katalogL.insert(f5, 105);

    std::cout << "\n=== Stan katalogu ===\n";
    katalogL.wyswietl();

    std::cout << "\n=== Duplikat ===\n";
    katalogL.insert(f1, 999);

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

    std::cout << std::endl << "=== Quadratic ===" <<  std::endl;

    KatalogQuadratic katalogQ(5);
    std::cout << "=== Wstawianie plikow ===\n";

    katalogQ.insert(f1, 101);
    katalogQ.insert(f2, 102);
    katalogQ.insert(f3, 103);
    katalogQ.insert(f4, 104);
    katalogQ.insert(f5, 105);

    std::cout << "\n=== Stan katalogu ===\n";
    katalogQ.wyswietl();

    std::cout << "\n=== Duplikat ===\n";
    katalogQ.insert(f1, 999);

    std::cout << "\n=== Szukanie ===\n";
    std::string szukany = "foto.jpg";
    int inodeQ = katalogL.szukaj(szukany);
    if (inodeQ != -1) {
        std::cout << "Znaleziono '" << szukany << "' -> inode: " << inodeQ << "\n";
    }

    std::string nieznanyQ = "brak.txt";
    inodeL = katalogQ.szukaj(nieznanyQ);
    if (inodeQ == -1) {
        std::cout << "Nie znaleziono '" << nieznanyQ << "'\n";
    }

    std::cout << "\n=== Usuwanie ===\n";
    katalogQ.usun(f2);

    std::cout << "\n=== Stan po usunieciu ===\n";
    katalogQ.wyswietl();

    std::cout << "\n=== Szukanie usuniętego pliku ===\n";
    inodeQ = katalogQ.szukaj(f2);
    if (inodeQ == -1) {
        std::cout << "Nie znaleziono '" << f2 << "' (usunieto)\n";
    }
}
