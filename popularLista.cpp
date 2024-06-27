#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <locale>
#include <cstdlib>

char randomLetter() 
{
    int r = rand() % 52;
    char base = (r < 26) ? 'A' : 'a';
    return (char) (base + r % 26);
}

int main()
{
    std::fstream file;
    file.open("teste.txt", std::ios::out);
    for(int i = 0; i < 1000; i++)
    {
        char ch = randomLetter();
        file << "Pessoa " << ch << " " << rand() % (1 + 1 - 0) + 0 << '\n';        
    }
    return 0;
}