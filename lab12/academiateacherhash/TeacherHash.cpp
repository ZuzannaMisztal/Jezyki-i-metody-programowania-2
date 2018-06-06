//
// Created by dell on 01.06.2018.
//

#include <string>
#include "TeacherHash.h"
#include <functional>

academia::TeacherId::TeacherId(int id) :id_(id){
}

academia::TeacherId::operator int() const {
    return id_;
}

academia::Teacher::Teacher(academia::TeacherId id, std::string name, std::string department): id_(id),name_(name), department_(department){
}

const academia::TeacherId &academia::Teacher::Id() const {
    return id_;
}

const std::string &academia::Teacher::Name() const {
    return name_;
}

const std::string &academia::Teacher::Department() const {
    return department_;
}

bool academia::Teacher::operator==(const academia::Teacher other)const{
    return (id_==other.id_ and name_==other.name_ and department_==other.department_);
}

bool academia::Teacher::operator!=(const academia::Teacher other) const {
    return !(*this==other);
}

size_t academia::TeacherHash::operator()(const academia::Teacher &teacher) const {
    size_t h=std::hash<int>()(teacher.Id())+std::hash<std::string>()(teacher.Name())+std::hash<std::string>()(teacher.Department());
    return h;
}
