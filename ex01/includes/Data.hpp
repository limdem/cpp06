#ifndef DATA_HPP
# define DATA_HPP

# include <string>

typedef unsigned long   uintptr_t;

struct Data
{
    char    c;
    int     nbr;
    float   nbrf;
    double  nbrd;
};

uintptr_t   serialize(Data* ptr);
Data*   deserialize(uintptr_t raw);
#endif
