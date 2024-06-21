#include <iostream>
#include <string>
#include <vector>

std::vector<int> vec = {1, 2, 3, 4, 5};
std::vector<int>::iterator it;
int num[3] = {1, 2, 3};
int *ptr = &num[1];
int arr = *ptr;

int main()
{
    for(it = vec.begin(); it != vec.end(); it++)
    {
        std::cout << *it << " ";
    }

    arr = 5;

    ptr = &arr;

    num[1] = *ptr;

    std::cout << num[1] << std::endl;

    return 0;
}