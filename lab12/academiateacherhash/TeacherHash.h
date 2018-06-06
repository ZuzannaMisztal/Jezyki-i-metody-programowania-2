//
// Created by dell on 01.06.2018.
//

#ifndef JIMP_EXERCISES_TEACHERHASH_H
#define JIMP_EXERCISES_TEACHERHASH_H

namespace academia{
    class TeacherId{
    public:
        explicit TeacherId(int id);
        operator int() const;
    private:
        int id_;
    };
    class Teacher{
    public:
        Teacher(TeacherId id, std::string name, std::string department);
        const TeacherId &Id() const;
        const std::string &Name() const;
        const std::string &Department() const;
        bool operator==(const Teacher other)const;
        bool operator!=(const Teacher other)const;

    private:
        TeacherId id_;
        std::string name_;
        std::string department_;
    };
    class TeacherHash{
    public:
        explicit TeacherHash(){};
        size_t operator()(const Teacher &teacher)const;

    };

}


#endif //JIMP_EXERCISES_TEACHERHASH_H
