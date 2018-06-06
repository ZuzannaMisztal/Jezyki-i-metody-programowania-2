//
// Created by dell on 22.05.2018.
//

#ifndef JIMP_EXERCISES_SCHEDULER_H
#define JIMP_EXERCISES_SCHEDULER_H


#include <vector>
#include <map>
#include <set>

namespace academia{
    class SchedulingItem{
    private:
        int course_id_;
        int teacher_id_;
        int room_id_;
        int time_slot_;
        int year_;
    public:
        SchedulingItem(int course_id, int teacher_id, int room_id, int time_slot, int year);
        int TeacherId() const;
        int CourseId() const;
        int RoomId() const;
        int TimeSlot() const;
        int Year() const;
    };

    class Schedule{
    private:
        std::vector<academia::SchedulingItem> plan;
    public:
        Schedule OfTeacher(int teacher_id) const;
        Schedule OfRoom(int room_id) const;
        Schedule OfYear(int year) const;
        std::vector<int> AvailableTimeSlots(int n_time_slots) const;
        void InsertScheduleItem(const SchedulingItem &item);
        std::size_t Size()const;
        academia::SchedulingItem operator[](int i) const;
    };

    class Scheduler{
    public:
        virtual Schedule PrepareNewSchedule(const std::vector<int> &rooms,
                                    const std::map<int, std::vector<int>> &teacher_courses_assignment,
                                    const std::map<int, std::set<int>> &courses_of_year, int n_time_slots)=0;
    };

    class NoViableSolutionFound:public std::invalid_argument{
    public:
        NoViableSolutionFound() : invalid_argument("No possible solution"){};
    };

    class GreedyScheduler: public Scheduler{
    public:
        Schedule PrepareNewSchedule(const std::vector<int> &rooms,
                                    const std::map<int, std::vector<int>> &teacher_courses_assignment,
                                    const std::map<int, std::set<int>> &courses_of_year, int n_time_slots) override;
        void initTeacherTimeSlots(const std::map<int, std::vector<int>> &teacher_courses_assignment,
                                  int n_time_slots, std::map<int, std::vector<int>> &teacher_to_time_slots) const;
        void initYearTimeSlots(const std::map<int, std::set<int>> &courses_of_year, int n_time_slots,
                          std::map<int, std::vector<int>> &year_to_time_slots) const;
        void initRoomTimeSlots(const std::vector<int> &rooms, int n_time_slots,
                          std::map<int, std::vector<int>> &room_to_time_slots) const;
    };
}

#endif //JIMP_EXERCISES_SCHEDULER_H
