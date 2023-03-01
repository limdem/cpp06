#include "../includes/Converter.hpp"
#include <cctype>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <limits> 
#include <math.h>
#include <stdlib.h>
#include <string>
#include <bits/stdc++.h>

Converter::Converter(){}

Converter::Converter(std::string const &litteral)
{
    this->setLitteral(litteral);
    this->setFptr();
    this->setCharFlow(0);
    this->setIntFlow(0);
}

Converter::~Converter(){}

Converter::Converter(const Converter &src)
:_litteral(src._litteral), _realType(src._realType), _charType(src._charType),
_intType(src._intType), _floatType(src._floatType), _doubleType(src._doubleType),
_pseudoLit(src._pseudoLit), _charFlow(src._charFlow), _intFlow(src._intFlow)
{
    int i;

    i = 0;
    while (i < 4)
    {
        this->fptr[i] = src.fptr[i];
        i++;
    }
}

Converter&  Converter::operator=(const Converter &src)
{
    int i;

    i = 0;
    this->_litteral = src._litteral;
    this->_realType = src._realType;
    this->_charType = src._charType;
    this->_intType = src._intType; 
    this->_floatType = src._floatType;
    this->_doubleType = src._doubleType;
    this->_pseudoLit = src._pseudoLit;
    this->_charFlow = src._charFlow;
    this->_intFlow = src._intFlow;
    while (i < 4)
    {
        this->fptr[i] = src.fptr[i];
        i++;
    }
    return (*this);
}


void    Converter::initializer(std::string litteral)
{
    this->setLitteral(litteral);
    this->setFptr();
    this->setCharFlow(0);
    this->setIntFlow(0);
    this->setPseudoLit(0);
}

std::string Converter::getLitteral() const
{
    return (this->_litteral);
}

int     Converter::getRealType() const
{
    return (this->_realType);
}

char    Converter::getCharType() const
{
    return (this->_charType);
}

int    Converter::getIntType() const
{
    return (this->_intType);
}

float    Converter::getFloatType() const
{
    return (this->_floatType);
}

double    Converter::getDoubleType() const
{
    return (this->_doubleType);
}

int     Converter::getPseudoLit() const
{
    return (this->_pseudoLit);
}

void    Converter::setLitteral(std::string const &litteral)
{
    this->_litteral = litteral;
}

void    Converter::setRealType(int realType)
{
    this->_realType = realType;
}

void    Converter::setCharFlow(int over)
{
    this->_charFlow = over;
}

void    Converter::setIntFlow(int over)
{
    this->_intFlow = over;
}

void    Converter::setPseudoLit(int pseudo)
{
    this->_pseudoLit = pseudo;
}

void    Converter::setFptr()
{
    this->fptr[0] = &convertToChar;
    this->fptr[1] = &convertToInt;
    this->fptr[2] = &convertToFloat;
    this->fptr[3] = &convertToDouble;   
}

std::string Converter::displayCharType()
{
    int tmp;

    if (this->_pseudoLit)
        return ("impossible");
    if (this->_charFlow == 1)
        return ("overflow");
    if (this->_charFlow == 2)
        return ("underflow");
    tmp = this->getCharType();
    if (!isprint(tmp))
        return ("Non displayable");
    return ("'" + std::string(1, this->getCharType()) + "'");
}

std::string Converter::displayIntType()
{
    if (this->_pseudoLit)
        return ("impossible");
    if (this->_intFlow == 3)
        return ("overflow");
    if (this->_intFlow == 4)
        return ("underflow");
    return (std::string());
}

std::string Converter::displayFloatType()
{
    std::string strFloat;

    if (this->_pseudoLit == 1)
        return ("+inff");
    if (this->_pseudoLit == 2)
        return ("-inff");
    if (this->_pseudoLit == 3)
        return ("nanf");
    if (isinf(this->getFloatType()))
    {
        if (this->getFloatType() < 0)
            return ("-inff");
        else
            return ("+inff");
    }
    return (std::string());
}

std::string Converter::displayDoubleType()
{
    if (this->_pseudoLit == 1)
        return ("+inf");
    if (this->_pseudoLit == 2)
        return ("-inf");
    if (this->_pseudoLit == 3)
        return ("nan");
    if (isinf(this->getDoubleType()))
    {
        if (this->getDoubleType() < 0)
            return("-inf");
        else
            return("+inf");
    }
    return (std::string());
}

void        Converter::displayTypes()
{
    std::cout << "char: " << this->displayCharType() << std::endl;
    if (this->displayIntType().empty())
        std::cout << "int: " << this->getIntType() << std::endl;
    else
        std::cout << "int: " << this->displayIntType() << std::endl;
    if (this->displayFloatType().empty())
    {
        std::cout << "float: " << this->getFloatType();
        if (this->getFloatType() - static_cast<long>(this->getFloatType()) == 0)
            std::cout << ".0f";
        std::cout << std::endl;
    }
    else
        std::cout << "float: " << this->displayFloatType() << std::endl;
    if (this->displayDoubleType().empty())
    {
        std::cout << "double: " << this->getDoubleType();
        if (this->getDoubleType() - static_cast<long>(this->getDoubleType()) == 0)
            std::cout << ".0";
        std::cout << std::endl;
    }
    else
        std::cout << "double: " << this->displayDoubleType() << std::endl;
}

int    Converter::identifyRealType()
{
    if (this->isChar())
        return (0);
    if (this->isInt())
        return (0);       
    if (this->isFloat())
        return (0);       
    if (this->isDouble())
        return (0);       
    if (this->isPseudoLit())
        return (0);       
    this->setRealType(-1);
    return (1);
}

int Converter::isChar()
{
    if (this->_litteral.length() == 1 && !std::isdigit(this->_litteral[0]))
    {
        this->setRealType(0);
        return (1);
    }
    return (0);
}

int Converter::isInt()
{
    int i;

    i = 0;
    while (this->_litteral[i])
    {
        if (!std::isdigit(this->_litteral[i]))
            if (!((this->_litteral[i] == '-' || this->_litteral[i] == '+') && !i))
                return (0);
        i++;
    }
    this->setRealType(1);
    return (1);
}

int Converter::isFloat()
{
    std::size_t found;
    std::size_t i;
    int         digit;

    i = 0;
    digit = 0;
    if (this->_litteral[this->_litteral.length() - 1] != 'f')
        return (0);
    found = this->_litteral.find(".");
    if (found == std::string::npos)
        return (0);
    while (this->_litteral[i])
    {
        if (std::isdigit(this->_litteral[i]))
            digit = 1;
        else
        {
            if (!((this->_litteral[i] == '.' && i == found)
                    || (this->_litteral[i] == 'f' && i == this->_litteral.length() -1)
                    || ((this->_litteral[i] == '-' || this->_litteral[i] == '+') && i == 0)))
                return (0); 
        }
        i++;
    }
    if (!digit)
        return (0);
    this->setRealType(2);
    return (1);
}

int     Converter::isDouble()
{
    std::size_t found;
    std::size_t i;

    i = 0;
    found = this->_litteral.find(".");
    while (this->_litteral[i])
    {
        if (!std::isdigit(this->_litteral[i]))
        {
            if (!((this->_litteral[i] == '.' && i == found)
                    || ((this->_litteral[i] == '-' || this->_litteral[i] == '+') && i == 0)))
                return (0); 
        }
        i++;
    }
    this->setRealType(3);
    return (1);
}

int     Converter::isInfinitFloat()
{
    if (!this->_litteral.compare("+inff") || !this->_litteral.compare("-inff"))
    {
        this->setRealType(2);
        if (!this->_litteral.compare("+inff"))
            this->_pseudoLit = 1;
        else
            this->_pseudoLit = 2;
        return (1);
    }
    return (0);
}

int     Converter::isInfinitDouble()
{
    if (!this->_litteral.compare("+inf") || !this->_litteral.compare("-inf"))
    {
        this->setRealType(3);
        if (!this->_litteral.compare("+inf"))
            this->_pseudoLit = 1;
        else
            this->_pseudoLit = 2;
        return (1);
    }
    return (0);
}

int     Converter::isNotANumber()
{
    if (!this->_litteral.compare("nanf") || !this->_litteral.compare("nan"))
    {
        this->_pseudoLit = 3;
        if (!this->_litteral.compare("nanf"))
            this->setRealType(2);
        else
            this->setRealType(3);
        return (1);
    }
    return (0);
}

int     Converter::isPseudoLit()
{
    if (this->isInfinitFloat())
        return (1);
    if (this->isInfinitDouble())
        return (1);
    if (this->isNotANumber())
        return (1);
    return (0);
}

void    Converter::convertToRealType()
{
    int type;
    int flow;

    type = this->getRealType();
    flow = 0;
    if (type == 0 && !this->_pseudoLit)
        flow = this->fptr[type](&this->_charType, this->_litteral);
    if (type == 1 && !this->_pseudoLit)
        flow = this->fptr[type](&this->_intType, this->_litteral);
    if (type == 2 && this->_pseudoLit != 3)
        this->fptr[type](&this->_floatType, this->_litteral);
    if (type == 3 && this->_pseudoLit != 3)
        this->fptr[type](&this->_doubleType, this->_litteral);
    if (flow == 1 || flow == 2)
        this->_charFlow = flow;
    if (flow == 3 || flow == 4)
        this->_intFlow = flow;
}

int    Converter::convertToChar(void *convType, std::string litteral)
{
    char *pchar;
    char    *tmpStr;
    long tmp;
    
    pchar = static_cast<char *>(convType);
    tmpStr = const_cast<char *>(litteral.c_str());
    tmp = strtol(tmpStr, NULL, 10);
    if (tmp > std::numeric_limits<char>::max())
        return (1);
    if (tmp < std::numeric_limits<char>::min())
        return (2);
    *pchar = static_cast<char>(tmp);
    if (!*pchar && litteral[0] != '0' && litteral[0] != '.'
            && litteral[0] != '-' && litteral[0] != '+')
        *pchar = litteral[0];
    return (0);
}

int    Converter::convertToInt(void *convType, std::string litteral)
{
    int    *pint;
    char    *tmpStr;
    long    tmp;

    pint = static_cast<int *>(convType);
    tmpStr = const_cast<char *>(litteral.c_str());
    tmp = strtol(tmpStr, NULL, 10);
    if (tmp > std::numeric_limits<int>::max())
        return (3);
    if (tmp < std::numeric_limits<int>::min())
        return (4);
    *pint = static_cast<int>(tmp);
    if (!*pint && litteral[0] != '0' && litteral.length() == 1)
    {
        *pint = litteral[0];
        return (0);
    }
    return (0);
}

int    Converter::convertToFloat(void *convType, std::string litteral)
{
    float   *pfloat;
    char    *tmpStr;
    float   tmp;

    pfloat = static_cast<float *>(convType);
    if (!litteral.compare("+inff") || !litteral.compare("-inff")
            || !litteral.compare("+inf") || !litteral.compare("-inf"))
    {
        tmp = std::numeric_limits<float>::infinity();
        *pfloat = tmp;
        if (!litteral.compare("-inff"))
            *pfloat *= -1;
        return (0);
    }
    tmpStr = const_cast<char *>(litteral.c_str());
    tmp = strtof(tmpStr, NULL);
    pfloat = static_cast<float *>(convType);
    *pfloat = static_cast<float>(tmp);
    if (!*pfloat && litteral[0] != '0' && litteral.length() == 1)
    {
        *pfloat = litteral[0];
        return (0);
    }
    return (0);
}

int    Converter::convertToDouble(void *convType, std::string litteral)
{
    double *pdouble;
    char    *tmpStr;
    double  tmp;

    pdouble = static_cast<double *>(convType);
    if (!litteral.compare("+inff") || !litteral.compare("-inff")
            || !litteral.compare("+inf") || !litteral.compare("-inf"))
    {
        
        pdouble = static_cast<double *>(convType);
        tmp = std::numeric_limits<double>::infinity();
        *pdouble = tmp;
        if (!litteral.compare("-inf"))
            *pdouble *= -1;
        return (0);
    }
    tmpStr = const_cast<char *>(litteral.c_str());
    tmp = strtod(tmpStr, NULL);
    *pdouble = static_cast<double>(tmp);
    if (!*pdouble && litteral[0] != '0' && litteral.length() == 1)
    {
        *pdouble = litteral[0];
        return (0);
    }
    return (0);
}

void    Converter::convertToOtherType()
{
    int saveRealType;
    int i;

    saveRealType = this->getRealType();
    i = 0;
    while (i < 4)
    {
        if (i != saveRealType)
        {
            this->setRealType(i);
            this->convertToRealType();
        }
        i++;
    }
    this->setRealType(saveRealType);
}