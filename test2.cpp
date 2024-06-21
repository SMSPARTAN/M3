int sumArray(int* mArr,int size)
{
    int result = 0;
    for(int i = 0; i < size; i++)
    {
        result += *(mArr + i);
    }
    return result;
}

int x = 1;
int* ptr = &x;

int main()
{
    std::cout << "Enter array size: ";
    std::cin >> x;
    
    int* arr = new int [x];

    for(int i = 0; i < x; i++)
    {
        std::cout << "Number: ";
        std::cin >> arr[i];
    }

    for(int i = 0; i < x; i++)
    {
        std::cout << "Array[" << i << "]" << " = " << *(arr + i) << " at adress " << arr+i << '\n';
    }

    std::cout << "Sum of all numbers on array is equal to: " << sumArray(arr, *ptr);

    delete []arr;
    arr = NULL;

    return 0;
}