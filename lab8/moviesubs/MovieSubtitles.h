//
// Created by dell on 04.05.2018.
//
#include <stdio.h>
#include <cstdio>
#ifndef JIMP_EXERCISES_MOVIESUBTITLES_H
#define JIMP_EXERCISES_MOVIESUBTITLES_H


namespace moviesubs{
    class MovieSubtitles{
    public:
        virtual void ShiftAllSubtitlesBy(int offset_in_micro_seconds, int frame_per_second, std::istream *in, std::ostream *out)=0;
    };

    class MicroDvdSubtitles : public MovieSubtitles{
    public:
        void ShiftAllSubtitlesBy(int offset_in_micro_seconds, int frame_per_second, std::istream *in, std::ostream *out) override;
    };

    class SubtitlesException : public std::invalid_argument{
        int number_of_line_;
        std::string line_;
    public:
        SubtitlesException(int number_of_line, std::string line);
        int getNumber_of_line_() const;
    };

    class NegativeFrameAfterShift : public SubtitlesException{
    public:
        NegativeFrameAfterShift(std::string msg, std::string line, int lineNr);
    };

    class SubtitleEndBeforeStart : public SubtitlesException{
    public:
        SubtitleEndBeforeStart(std::string msg, std::string line, int lineNr);
        int LineAt() const;
    };

    class InvalidSubtitleLineFormat : public SubtitlesException{
    public:
        InvalidSubtitleLineFormat(std::string msg, std::string line, int lineNr);
    };

    class SubRipSubtitles : public MovieSubtitles{
    public:
        void ShiftAllSubtitlesBy(int offset_in_micro_seconds, int frame_per_second, std::istream *in, std::ostream *out) override;
    };

    class MissingTimeSpecification : public SubtitlesException{
    public:
        MissingTimeSpecification(std::string msg, std::string line, int lineNr);
    };

    class OutOfOrderFrames : public  SubtitlesException{
    public:
        OutOfOrderFrames(std::string msg, std::string line, int lineNr);
    };

    int to_microseconds(const std::string &time);
    std::string to_hours(int time);
}


#endif //JIMP_EXERCISES_MOVIESUBTITLES_H
