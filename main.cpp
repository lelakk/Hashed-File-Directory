#include <iostream>
#include "KatalogLinear.h"

int main() {
    KatalogLinear katalog(5);

    std::cout << "=== Wstawianie plikow ===\n";
    std::string f1 = "dokument.txt", f2 = "foto.jpg", f3 = "muzyka.mp3",
            f4 = "video.mp4", f5 = "archiwum.zip";

    katalog.insert(f1, 101);
    katalog.insert(f2, 102);
    katalog.insert(f3, 103);
    katalog.insert(f4, 104);
    katalog.insert(f5, 105);

    std::cout << "\n=== Stan katalogu ===\n";
    katalog.wyswietl();

    std::cout << "\n=== Duplikat ===\n";
    katalog.insert(f1, 999);

    std::cout << "\n=== Szukanie ===\n";
    std::string szukany = "foto.jpg";
    int inode = katalog.szukaj(szukany);
    if (inode != -1) {
        std::cout << "Znaleziono '" << szukany << "' -> inode: " << inode << "\n";
    }

    std::string nieznany = "brak.txt";
    inode = katalog.szukaj(nieznany);
    if (inode == -1) {
        std::cout << "Nie znaleziono '" << nieznany << "'\n";
    }

    std::cout << "\n=== Usuwanie ===\n";
    katalog.usun(f2);

    std::cout << "\n=== Stan po usunieciu ===\n";
    katalog.wyswietl();

    std::cout << "\n=== Szukanie usuniętego pliku ===\n";
    inode = katalog.szukaj(f2);
    if (inode == -1) {
        std::cout << "Nie znaleziono '" << f2 << "' (usunieto)\n";
    }

    return 0;
}
