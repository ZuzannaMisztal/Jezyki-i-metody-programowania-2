//
// Created by Kuba on 07.04.2018.
//

#include <string>
#include <iostream>

std::string raw_string(std::string to_copy) {
    std::string result ="\"";
    for (int i=0; i<to_copy.length(); ++i){
        if (to_copy[i]=='\\') {
            result += "\\";
        }
        if (to_copy[i]=='\"'){
            result+= "\\";
        }
        result+=to_copy[i];
    }
    result+="\"";
    return result;
}
int main(){
    std::string str="\"\\\"abc\\\"\"";
    double a=611118;
    //std::cout<<raw_string(str);
    //std::cout<<std::endl<<str.length()<<std::endl;
    std::string b=std::to_string(a);
    std::cout<<b<<std::endl;
    while (b.back()=='0'){
        //std::cout<<"cut"<<std::endl;
        b=b.substr(0,b.length()-1);
    }
    std::cout<<b;
//    std::cout<<b<<std::endl;
//    std::cout<<b.substr(0,b.length()-1);

}
