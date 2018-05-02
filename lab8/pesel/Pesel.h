//
// Created by dell on 25.04.2018.
//

#ifndef JIMP_EXERCISES_PESEL_H
#define JIMP_EXERCISES_PESEL_H

#include <string>
#include <stdexcept>


namespace academia {
    class Pesel {
    private:
        std::string pesel;
    public:
        Pesel(const std::string &);
        bool validatePESEL(const std::string &);
    };

    class AcademiaDataValidationError : public std::invalid_argument{
    private:
        std::string pesel;
    public:
        AcademiaDataValidationError(const std::string &p) : invalid_argument("wrong pesel"), pesel{p}{};

    };

    class InvalidPeselChecksum : public AcademiaDataValidationError{
    public:
        InvalidPeselChecksum(std::string, int);
    };

    class InvalidPeselLength : public AcademiaDataValidationError{
    public:
        InvalidPeselLength(const std::string &, int);
    };

    class InvalidPeselCharacter : public  AcademiaDataValidationError{
    public:
        InvalidPeselCharacter(const std::string &);
    };
}

#endif //JIMP_EXERCISES_PESEL_H
