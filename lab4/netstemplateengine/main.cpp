#include <string>
#include <regex>
#include <iostream>

//
// Created by Kuba on 07.04.2018.
//
int main(){
    std::string s="Hello {{name}} and {{name1}} and {{lulu}}";
    std::string to_search=s;
    std::smatch m;
    std::regex e ("\\{\\{([^\\}\\{]*)\\}\\}");
    std::cout<<s<<std::endl;

    while (std::regex_search (to_search,m,e)) {
        std::cout <<m[0]<< " na " << m[1] << std::endl;
//        std::string to_replace;
//        if (model.count(m[1])>0){
//            to_replace= model.at(m[1]);
//        }else{
//            to_replace="";
//        }
        std::cout << std::endl;
        to_search = m.suffix().str();
    }
    return 0;
}
