//
// Created by Kuba on 07.04.2018.
//
#include <regex>
#include <string>
#include <unordered_map>
#include <iostream>
#include "SimpleTemplateEngine.h"



nets::View::View(const std::basic_string<char>&t) {
    text=t;
}

nets::View::~View() {
}

std::string nets::View::Render(const std::unordered_map<std::string, std::string> &model) const {
    std::string s=text;
    std::string to_search=text;
    std::smatch m;
    std::regex e ("\\{\\{([^\\}\\{]*)\\}\\}");

    while (std::regex_search (s,m,e)) {
        std::string to_replace;
        if (model.count(m[1])>0){
            to_replace= model.at(m[1]);
        }else{
            to_replace="";
        }
        //m.length(0) - tyle znaków
        //m.position(0) - od tej pozycji
        //zamieniamy na to_replace
        s.replace(m.position(0),m.length(0),to_replace);


        std::cout << std::endl;
    }
    return s;
}