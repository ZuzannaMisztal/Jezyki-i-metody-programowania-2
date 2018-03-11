//
// Created by dell on 10.03.2018.
//


#include "Polybius.h"


std::string PolybiusCrypt(std::string message) {
    std::string crypted;
    for (int i=0; i<message.length(); ++i){
        message[i]=std::tolower(message[i]);
        int asciicode = (int) message[i];
        if (97 <= asciicode && asciicode <= 122){
            if (asciicode <= 101){
                crypted.append("1");
            }
            else if (asciicode <= 107){
                crypted.append("2");
            }
            else{
                crypted.append(std::to_string((asciicode - 93) / 5));
            }
            if (asciicode==101 || (asciicode>105 && (asciicode-2)%5==0)){
                crypted.append("5");
            }
            else if (asciicode<=105){
                crypted.append(std::to_string((asciicode-1)%5));
            }
            else{
                crypted.append(std::to_string((asciicode-2)%5));
            }
        }
    }
    return crypted;
}

std::string PolybiusDecrypt(std::string crypted) {
    std::string message;
    while (crypted.length()>0){
        std::string to_decrypt=crypted.substr(0,2);
        crypted=crypted.substr(2);
        int number_to_decrypt;
        std::istringstream iss(to_decrypt);
        iss>>number_to_decrypt;
        if (number_to_decrypt<=24){
            int ascii_code=91+(number_to_decrypt/10)*5+(number_to_decrypt%10);
            char decrypted_letter= char(ascii_code);
            message += decrypted_letter;
        } else{
            int ascii_code=92+(number_to_decrypt/10)*5+(number_to_decrypt%10);
            message += char(ascii_code);
        }
    }
    return message;
}