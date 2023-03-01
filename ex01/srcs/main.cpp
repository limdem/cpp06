#include "../includes/Data.hpp"
#include <iostream>

int main()
{
    Data    data;
    Data    *dataPtr;
    uintptr_t   ptr;

    std::cout << "data: " << &data << std::endl;
    ptr = serialize(&data);
    dataPtr = deserialize(ptr);
    std::cout << "ptr: " << ptr << std::endl;
    std::cout << "dataPtr: " << dataPtr << std::endl;
    return (0);
}