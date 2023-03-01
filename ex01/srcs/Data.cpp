#include "../includes/Data.hpp"

uintptr_t   serialize(Data* ptr)
{
    uintptr_t   ps;

    ps = reinterpret_cast<uintptr_t>(ptr);
    return (ps);
}

Data*   deserialize(uintptr_t raw)
{
    Data    *ptr;

    ptr = reinterpret_cast<Data *>(raw);
    return (ptr);
}