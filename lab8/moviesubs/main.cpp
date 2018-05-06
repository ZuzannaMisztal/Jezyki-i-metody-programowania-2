//
// Created by dell on 04.05.2018.
//

#include <chrono>
#include <memory>
#include <sstream>
#include <iostream>
#include "MovieSubtitles.h"

using ::moviesubs::MicroDvdSubtitles;
using ::moviesubs::NegativeFrameAfterShift;
using ::moviesubs::SubtitleEndBeforeStart;
using ::moviesubs::InvalidSubtitleLineFormat;

using namespace std;
using namespace std::literals;

int main(){
    auto subs = make_unique<MicroDvdSubtitles>();
    stringstream in {"{10}{}TEXT\n{260}{220}NEWLINE\n"};
    try{
        subs->ShiftAllSubtitlesBy(1000, 24, &in, &cout);
    }catch(NegativeFrameAfterShift){
        cout<<"NegativeFrameException"<<endl;
    }catch(InvalidSubtitleLineFormat){
        cout<<"InvalidSubtitleLineFormat"<<endl;
    }catch(SubtitleEndBeforeStart){
        cout<<"SubtitleEndBeforeStart"<<endl;
    }


    return 0;
}

