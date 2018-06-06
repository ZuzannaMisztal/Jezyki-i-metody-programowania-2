//
// Created by dell on 01.06.2018.
//

#ifndef JIMP_EXERCISES_SEQUENTIALGENERATOR_H
#define JIMP_EXERCISES_SEQUENTIALGENERATOR_H

template <class T, class C>
class SequentialIdGenerator {
private:
    C counter;
public:
    SequentialIdGenerator(){
        counter=C();
    }
    SequentialIdGenerator(C value){
        counter=C(value);
    }
    T NextValue(){
        C tmp=counter;
        ++counter;
        return T(tmp);
    }

};


#endif //JIMP_EXERCISES_SEQUENTIALGENERATOR_H
