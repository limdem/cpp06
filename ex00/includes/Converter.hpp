#ifndef CONVERTER_HPP
# define CONVERTER_HPP

# include <string>

class Converter
{
    private:
        std::string _litteral;
        int _realType;
        int (*fptr[4])(void *, std::string);
        char    _charType;
        int     _intType;
        float   _floatType;
        double  _doubleType;
        int     _pseudoLit;
        int     _charFlow;
        int     _intFlow;
    public:
        Converter();
        Converter(std::string const &);
        ~Converter();
        Converter(const Converter&);
        Converter& operator=(const Converter&);
        void    initializer(std::string);
        std::string getLitteral() const ;
        int     getRealType() const;
        char    getCharType() const;
        int     getIntType() const;
        float     getFloatType() const;
        double     getDoubleType() const;
        int     getPseudoLit() const;
        void    setLitteral(std::string const &);
        void    setRealType(int);
        void    setFptr();
        void    setCharFlow(int);
        void    setIntFlow(int);
        void    setPseudoLit(int);
        std::string displayCharType();
        std::string displayIntType();
        std::string displayFloatType();
        std::string displayDoubleType();
        void        displayTypes();
        int     identifyRealType();
        int     isChar();
        int     isInt();
        int     isFloat();
        int     isDouble();
        int     isPseudoLit();
        int     isInfinitFloat();
        int     isInfinitDouble();
        int     isNotANumber();
        void    convertToRealType();
        static int    convertToChar(void *, std::string);
        static int    convertToInt(void *, std::string);
        static int    convertToFloat(void *, std::string);
        static int    convertToDouble(void *, std::string);
        void    convertToOtherType();
};
#endif
