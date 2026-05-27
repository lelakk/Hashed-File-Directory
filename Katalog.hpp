#ifndef HASHED_FILE_DIRECTORY_KATALOG_HPP
#define HASHED_FILE_DIRECTORY_KATALOG_HPP
// Paweł Lelakowski
#include <vector>
#include <string>

struct wpisKatalogowy {
    std::string nazwaPliku;
    int inode;
    std::string typPliku;
    bool zajety = false;
    bool usuniety = false;
};

#endif // HASHED_FILE_DIRECTORY_KATALOG_HPP