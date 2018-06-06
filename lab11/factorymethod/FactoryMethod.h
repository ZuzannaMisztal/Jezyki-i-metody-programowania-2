//
// Created by dell on 23.05.2018.
//

#ifndef JIMP_EXERCISES_FACTORYMETHOD_H
#define JIMP_EXERCISES_FACTORYMETHOD_H

#include <string>
#include <memory>
#include <typeinfo>

namespace factoryMethod {
    template<class T>
            T Create();
    class MyType{
    private:
        std::string say;
    public:
        MyType();
        std::string SayHello();
    };
    template<class T>
    T suma(T a, T b){
        return a+b;
    }

    template<class T>
    auto Value(const T &a){
            return *a;
    }


}

template<class T>
T factoryMethod::Create() {
    return T();
}


#endif //JIMP_EXERCISES_FACTORYMETHOD_H
