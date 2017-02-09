#include "Group.h"

Group::Group(string name){

    groupname = name;
    font.load("ヒラギノ角ゴシック W4.ttc", 10);
    title.load("ヒラギノ角ゴシック W5.ttc", 20);
}


void Group::group_input(int num){
    Number.push_back(num);
}

//void Group::drawview(int x, int y){
//    
//    title.drawString(groupname, x, y);
//    
//    for(int i=0; i<Number.size();i++){
//        font.drawString(, x, y+space*i+50);
//        font.drawString(PJNAME[i], x+200, y+space*i+50);
//    }
//    
//}

void Group::planIn(string time,int command){
    Schedule S = Schedule(time, command);
    schedule.push_back(S);
}

bool Group::timeCheck(int number,string time){
    if(schedule[number].Sche_time==time){
        return true;
    }else{
        return false;
    }
}

