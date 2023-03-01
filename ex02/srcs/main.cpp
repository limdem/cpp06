#include "../includes/Base.hpp"

int main()
{
    Base    *ptr;

    ptr = generate();
    if (!ptr)
        return (1);
    Base    &ref = *ptr;
    identify(ptr);
    identify(ref);
    delete ptr;
    return (0);
}