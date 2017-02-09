#include "ofMain.h"
#include "Schedule.h"



class Group{
public:
    Group(){};
    Group(string name);
    

    string groupname;
    vector <int> Number;

    
    vector <Schedule> schedule;
    
    
    void group_input(int num);
    //void drawview(int x,int y);
    
    ofTrueTypeFont font,title;
    
    void planIn(string time , int command);
    
    bool timeCheck(int number,string time);

   

};
