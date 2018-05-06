//
// Created by dell on 04.05.2018.
//

#include <iosfwd>
#include <string>
#include <iostream>
#include <regex>
#include "MovieSubtitles.h"

void
moviesubs::MicroDvdSubtitles::ShiftAllSubtitlesBy(int offset_in_micro_seconds, int frame_per_second, std::istream *in,
                                                  std::ostream *out) {
    if (frame_per_second<1){
        throw std::invalid_argument("msg");
    }
    std::string line;
    int i=1;
    while (getline(*in, line)){
        int number_of_frames_to_move;
        number_of_frames_to_move=(double)offset_in_micro_seconds/1000*frame_per_second;
        std::regex e ("\\{(\\d+)\\}\\{(\\d+)\\}(.*)");
        std::smatch s;
        std::regex_match(line, s, e);
        if (s[0]!=line){
            throw InvalidSubtitleLineFormat("Invalid format", s[0], i);
        }
        std::string to_out="{";
        std::string start=s[1];
        std::string end=s[2];
        int start_frame=atoi(start.c_str())+number_of_frames_to_move;
        int end_frame=atoi(end.c_str())+number_of_frames_to_move;
        if (start_frame<0 || end_frame<0){
            throw NegativeFrameAfterShift("Negative frame", std::string(), 0);
        }
        if (end_frame<start_frame){
            throw SubtitleEndBeforeStart("End before start", s[0], i);
        }
        to_out.append(std::to_string(start_frame));
        to_out.append("}{");
        to_out.append(std::to_string(end_frame));
        to_out.append("}");
        to_out.append(s[3]);
        ++i;
        *out<<to_out<<"\n";
    }
}

moviesubs::SubtitlesException::SubtitlesException(int number_of_line, std::string line) : invalid_argument(std::string("At line ")+std::to_string(number_of_line)+std::string(": ")+line){
    number_of_line_=number_of_line;
    line_=line;
}

int moviesubs::SubtitlesException::getNumber_of_line_() const {
    return number_of_line_;
}

int moviesubs::SubtitleEndBeforeStart::LineAt() const{
    return SubtitlesException::getNumber_of_line_();
}

moviesubs::SubtitleEndBeforeStart::SubtitleEndBeforeStart(std::string msg, std::string line, int lineNr) : SubtitlesException(lineNr, line){

}

moviesubs::NegativeFrameAfterShift::NegativeFrameAfterShift(std::string msg, std::string line, int lineNr) : SubtitlesException(lineNr, line){

}

moviesubs::InvalidSubtitleLineFormat::InvalidSubtitleLineFormat(std::string msg, std::string line, int lineNr) : SubtitlesException(lineNr, line){

}

void
moviesubs::SubRipSubtitles::ShiftAllSubtitlesBy(int offset_in_micro_seconds, int frame_per_second, std::istream *in,
                                                std::ostream *out) {
    if (frame_per_second<1){
        throw std::invalid_argument("msg");
    }
    int frame=1;
    bool timeline=false;
    std::string line;
    while (getline(*in, line)){
        std::smatch s;
        if(timeline){
            timeline=false;
            if (std::regex_match(line, s, std::regex("(\\d{2}:\\d{2}:\\d{2},\\d{3}) --> (\\d{2}:\\d{2}:\\d{2},\\d{3})"))) {
                int start_in_microseconds = to_microseconds(s[1])+offset_in_micro_seconds;
                int end_in_microseconds = to_microseconds(s[2])+offset_in_micro_seconds;
                if (start_in_microseconds<0){
                    throw NegativeFrameAfterShift("Negative frame", std::string(), 0);
                }
                if (end_in_microseconds<start_in_microseconds){
                    throw SubtitleEndBeforeStart("End before start", s[0], frame);
                }
                std::string start=to_hours(start_in_microseconds);
                std::string end=to_hours(end_in_microseconds);
                std::string result=start + " --> " + end;
                *out<<result<<"\n";
            }
            else{
                throw InvalidSubtitleLineFormat("Invalid format", std::string(), 0);
            }
        }
        else if (std::regex_match(line, std::regex("^\\d+$"))){
            timeline=true;
            if (line!=std::to_string(frame)){
                throw OutOfOrderFrames("Invalid frame", std::string(), 0);
            }
            *out<<line<<"\n";
        }
        else{
            *out<<line<<"\n";
        }
        if (line==""){
            ++frame;
        }
    }

}

int moviesubs::to_microseconds(const std::string &time) {
    std::smatch s;
    std::regex_match(time, s, std::regex("(\\d{2}):(\\d{2}):(\\d{2}),(\\d{3})"));
    std::string microseconds=s[4];
    std::string seconds=s[3];
    std::string minutes=s[2];
    std::string hours=s[1];
    int result=atoi(microseconds.c_str())+1000*atoi(seconds.c_str())+60000*atoi(minutes.c_str())+3600000*atoi(hours.c_str());
    return result;
}

std::string moviesubs::to_hours(int time) {
    int micro=time%1000;
    int seconds=time/1000;
    int minutes=seconds/60;
    seconds=seconds%60;
    int hours = minutes/60;
    minutes=minutes%60;
    //std::string result=std::to_string(hours)+":"+std::to_string(minutes)+":"+std::to_string(seconds)+","+std::to_string(micro);
    std::string result;
    if (hours<10){
        result+='0';
    }
    result.append(std::to_string(hours));
    result+=':';
    if (minutes<10){
        result+='0';
    }
    result.append(std::to_string(minutes));
    result+=':';
    if (seconds<10){
        result+='0';
    }
    result.append(std::to_string(seconds));
    result+=',';
    if (micro<100){
        result+='0';
    }
    if (micro<10){
        result+='0';
    }
    result.append(std::to_string(micro));
    return result;
}

moviesubs::MissingTimeSpecification::MissingTimeSpecification(std::string msg, std::string line, int lineNr) : SubtitlesException(lineNr, line){

}

moviesubs::OutOfOrderFrames::OutOfOrderFrames(std::string msg, std::string line, int lineNr) : SubtitlesException(lineNr, line){

}
