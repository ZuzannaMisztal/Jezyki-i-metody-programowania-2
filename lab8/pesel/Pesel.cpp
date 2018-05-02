//
// Created by dell on 25.04.2018.
//

#include <string>
#include <w32api/dshow.h>
#include "Pesel.h"

academia::Pesel::Pesel(const std::string &s) {
    if (validatePESEL(s)){
        pesel=s;
    }
}

bool academia::Pesel::validatePESEL(const std::string &s) {

}

academia::InvalidPeselChecksum::InvalidPeselChecksum(std::string, int) {

}

academia::InvalidPeselLength::InvalidPeselLength(const std::string &, int) {

}


academia::InvalidPeselCharacter::InvalidPeselCharacter(const std::string &) : invalid_argument(

<unnamed>){

}
