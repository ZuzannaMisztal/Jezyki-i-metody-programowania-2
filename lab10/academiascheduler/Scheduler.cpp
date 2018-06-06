//
// Created by dell on 22.05.2018.
//

#include "Scheduler.h"
#include <algorithm>
#include <iostream>

void academia::Schedule::InsertScheduleItem(const academia::SchedulingItem &item) {
    plan.emplace_back(item);
}

academia::Schedule academia::Schedule::OfTeacher(int teacher_id) const {
    academia::Schedule result;
    std::copy_if(plan.begin(), plan.end(), std::back_inserter(result.plan), [teacher_id](academia::SchedulingItem item){ return (
            item.TeacherId()==teacher_id);});
    return result;
}

academia::Schedule academia::Schedule::OfRoom(int room_id) const {
    academia::Schedule result;
    std::copy_if(plan.begin(), plan.end(), std::back_inserter(result.plan), [room_id](academia::SchedulingItem item){ return (
            item.RoomId()==room_id);});
    return result;
}

academia::Schedule academia::Schedule::OfYear(int year) const {
    academia::Schedule result;
    std::copy_if(plan.begin(), plan.end(), std::back_inserter(result.plan), [year](academia::SchedulingItem item){ return (
            item.Year()==year);});
    return result;
}

academia::SchedulingItem academia::Schedule::operator[](int i)const {
    return plan[i];
}

std::size_t academia::Schedule::Size() const {
    return plan.size();
}

std::vector<int> academia::Schedule::AvailableTimeSlots(int n_time_slots) const {
    std::vector<int> help;
    std::vector<int> result;
    std::transform(plan.begin(), plan.end(), std::back_inserter(help), [](academia::SchedulingItem item)->int{return item.TimeSlot();});
    for (int i=1; i<=n_time_slots;++i){
        if (std::find(help.begin(), help.end(), i)==help.end()){
            result.emplace_back(i);
        }
    }
    return result;
}


academia::SchedulingItem::SchedulingItem(int course_id, int teacher_id, int room_id, int time_slot, int year) {
    course_id_=course_id;
    teacher_id_=teacher_id;
    room_id_=room_id;
    time_slot_=time_slot;
    year_=year;
}

int academia::SchedulingItem::TeacherId() const {
    return teacher_id_;
}

int academia::SchedulingItem::CourseId() const {
    return course_id_;
}

int academia::SchedulingItem::RoomId() const {
    return room_id_;
}

int academia::SchedulingItem::TimeSlot() const {
    return time_slot_;
}

int academia::SchedulingItem::Year() const {
    return year_;
}

academia::Schedule academia::GreedyScheduler::PrepareNewSchedule(const std::vector<int> &rooms,
                                                                 const std::map<int, std::vector<int>> &teacher_courses_assignment,
                                                                 const std::map<int, std::set<int>> &courses_of_year,
                                                                 int n_time_slots) {

    //wyjątki
    int number_of_courses_to_do=0;
    for (const auto &one_teacher_courses:teacher_courses_assignment){
        number_of_courses_to_do+=one_teacher_courses.second.size();
    }
    if (number_of_courses_to_do>n_time_slots*rooms.size()){
        throw NoViableSolutionFound();
    }
    for (const auto &one_year_courses:courses_of_year){
        number_of_courses_to_do=0;
        for (const auto &course:one_year_courses.second){
            for (const auto &one_teacher_courses:teacher_courses_assignment){
                number_of_courses_to_do+=std::count(one_teacher_courses.second.begin(), one_teacher_courses.second.end(), course);
            }
        }
        if (number_of_courses_to_do>n_time_slots){
            throw NoViableSolutionFound();
        }
    }

    //układanie planu
    Schedule best_schedule;
    std::map<int, std::vector<int>> teacher_to_time_slots;
    std::map<int, std::vector<int>> year_to_time_slots;
    std::map<int, std::vector<int>> room_to_time_slots;

    initTeacherTimeSlots(teacher_courses_assignment, n_time_slots, teacher_to_time_slots);
    initYearTimeSlots(courses_of_year, n_time_slots, year_to_time_slots);
    initRoomTimeSlots(rooms, n_time_slots, room_to_time_slots);


    for (const auto &one_year:courses_of_year){
        for (const auto &course:one_year.second){
            for (const auto &one_teacher_courses:teacher_courses_assignment){
                int number_of_this_particular_course=std::count(one_teacher_courses.second.begin(),one_teacher_courses.second.end(), course);
                for (int i=0; i<number_of_this_particular_course; ++i){

                    //mamy wybrany rok, kurs i nauczyciela, który go poprowadzi
                    //teraz trzeba znaleźć wspólny termin dla roku i nauczyciela, a następnie poszukać pokoju


                    int avaible_room=0;
                    auto avaible_time_slot = teacher_to_time_slots.at(one_teacher_courses.first).begin();
                    while (avaible_room==0) {

                        std::vector<int> year_slots = year_to_time_slots.at(one_year.first);
                        while (std::find(year_slots.begin(), year_slots.end(), *avaible_time_slot) ==
                               year_slots.end()) {
                            ++avaible_time_slot;
                        }
                        //mamy znaleziony time slot dla nauczyciela i roku, teraz trzeba dobrać pokój

                        for (const auto &room:room_to_time_slots) {
                            if (std::find(room.second.begin(), room.second.end(), *avaible_time_slot) !=
                                room.second.end()) {
                                avaible_room = room.first;
                                break;
                            }
                        }
                        if (avaible_room==0){
                            ++avaible_time_slot;
                        }
                    }

                    SchedulingItem to_insert(course,one_teacher_courses.first, avaible_room, *avaible_time_slot, one_year.first);
                    best_schedule.InsertScheduleItem(to_insert);

                    auto to_erase_r=std::find(room_to_time_slots.at(avaible_room).begin(), room_to_time_slots.at(avaible_room).end(), *avaible_time_slot);
                    room_to_time_slots.at(avaible_room).erase(to_erase_r);
                    //te dwie poniższe linijki są ultra sprytne

                    auto to_erase_y=std::find(year_to_time_slots.at(one_year.first).begin(), year_to_time_slots.at(one_year.first).end(), *avaible_time_slot);
                    year_to_time_slots.at(one_year.first).erase(to_erase_y);
                    teacher_to_time_slots.at(one_teacher_courses.first).erase(avaible_time_slot);
                }
            }
        }
    }
    return best_schedule;
}

void academia::GreedyScheduler::initRoomTimeSlots(const std::vector<int> &rooms, int n_time_slots,
                                        std::map<int, std::vector<int>> &room_to_time_slots) const {
    for (const auto &room:rooms){
        std::vector<int> room_time_slots;
        for (int i=1; i<=n_time_slots; ++i){
            room_time_slots.emplace_back(i);
        }
        room_to_time_slots.emplace(room, room_time_slots);
    }
}

void academia::GreedyScheduler::initYearTimeSlots(const std::map<int, std::set<int>> &courses_of_year, int n_time_slots,
                                        std::map<int, std::vector<int>> &year_to_time_slots) const {
    for (const auto &year:courses_of_year){
        std::vector<int> years_time_slots;
        for (int i=1; i<=n_time_slots; ++i){
            years_time_slots.emplace_back(i);
        }
        year_to_time_slots.emplace(year.first, years_time_slots);
    }
}

void academia::GreedyScheduler::initTeacherTimeSlots(const std::map<int, std::vector<int>> &teacher_courses_assignment,
                                           int n_time_slots, std::map<int, std::vector<int>> &teacher_to_time_slots) const {
    for (const auto &teacher_id:teacher_courses_assignment){
        std::vector<int> teachers_time_slots;
        for (int i=1; i<=n_time_slots; ++i){
            teachers_time_slots.emplace_back(i);
        }
        teacher_to_time_slots.emplace(teacher_id.first, teachers_time_slots);
    }
}
