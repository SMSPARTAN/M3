#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <filesystem>

std::fstream myFile;
std::string str;
int count = 1;
std::vector<std::string> vec;

std::string convertToLower(std::string& str)
{
    std::string result = "";
    for(char& c : str)
    {
        result += tolower(c);
    }
    return result;
}

int findItemIndex(std::vector<std::string>& vec,std::string& search)
{
    int index = 0;
    for(int i = 0; i < vec.size(); i++)
    {
        if(convertToLower(search) == convertToLower(vec[i]))
        {
            index = i;
        }
    }
    return index;
}


int main()
{
    myFile.open("testFile.txt", std::ios::in);

    while(std::getline(myFile, str))
    {
        vec.push_back(str);
    }

    for(std::string& it : vec)
    {
        std::cout << "Line " << count << " " << it << "\n";
        count++;
    }
    myFile.close();

    std::cout << "\nAlter file: ";
    char c;
    std::cin >> c;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int lineDeletus;
    std::cout << "\nEnter item to delete: ";
    std::getline(std::cin, str);

    std::vector<std::string>::iterator it = vec.begin();
    std::advance(it, findItemIndex(vec, str));
    vec.erase(it);     

    count = 1;
    for(std::string& it : vec)
    {
        std::cout << "Line " << count << " " << it << "\n";
        count++;
    }

    myFile.open("testFile.txt", std::ios::out);
    for(std::string& strIt : vec)
    {
        myFile << strIt << '\n';
    }
    myFile.close();

    return 0;
}