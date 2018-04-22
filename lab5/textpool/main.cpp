//
// Created by dell on 14.04.2018.
//

#include <iostream>
#include "TextPool.h"
pool::TextPool internstuff() {
    pool::TextPool pool;
    pool.Intern("abc");
    return pool;

}

void dostuff() {
    auto pool = internstuff();

    std::experimental::string_view str = *pool.pula.begin();
}
int main(){
    pool::TextPool *ppool=new pool::TextPool;
    ppool->Intern("abc");
    ppool->Intern("efg");
    for (const auto &n:ppool->pula){
        std::cout<<n<<std::endl;
    }
    std::cout<<"okaofjdokfjodsfjoasdfojas"<<std::endl;
    pool::TextPool pool;
    pool.Intern("aaa");
    pool.Intern("bbb");
    for (auto it=pool.pula.begin(); it!=pool.pula.end(); ++it){
        std::cout<<*it<<std::endl;
    }
    int wyst=pool.pula.count("aaa");
    std::cout<<wyst<<std::endl;
    return 0;
}