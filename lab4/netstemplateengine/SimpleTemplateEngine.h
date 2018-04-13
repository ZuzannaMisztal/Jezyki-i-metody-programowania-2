//
// Created by Kuba on 07.04.2018.
//

#ifndef JIMP_EXERCISES_SIMPLETEMPLATEENGINE_H
#define JIMP_EXERCISES_SIMPLETEMPLATEENGINE_H


#include <unordered_map>

namespace nets{
    class View {
        std::string text;
    public:
        View(const std::basic_string<char>&);
        ~View();
        std::string Render(const std::unordered_map <std::string, std::string> &model) const;
    };

}



#endif //JIMP_EXERCISES_SIMPLETEMPLATEENGINE_H
