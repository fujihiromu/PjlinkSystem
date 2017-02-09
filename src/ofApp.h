#pragma once

#include "ofMain.h"
#include "Status.h"
#include "ofxJSONElement.h"
#include "Group.h"


#define rate 30
#define space 30

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
        void mouseScrolled(int x, int y, float scrollX, float scrollY);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void json_output();
        void json_input();
        void data_erase(int n);
        void drawGroup(int x, int y , int i);
        void drawTimeSchedule(int x, int y , int i);
    
    
    
    
    vector < Status > projector;
    vector < bool > Gchoice;

    Status testPJ;
    
    ofTrueTypeFont Bfont,Bfont1,Bfont2,Bfont3,Bfont4,Bfont5;
    
    ofTrueTypeFont Mfont,Mfont1,Mfont2,Mfont3,Mfont4,Mfont5;
    
    ofTrueTypeFont Cfont,Cfont1,Cfont2,Cfont3,Cfont4,Cfont5;

    
    ofxJSONElement Input;
    
    string addsearch;
    string passearch;
    string group_name;

    bool schedule_interval;
    int schedule_interval_time;
    
    bool first_set;

    
    
    int count;
    int mstime;
    int page,page_group[2];
    int pro_choice;

    ofImage bo;
    ofImage on,off,open,close,hdmi,dvi,del,reset,edit,tab;
    
    ////グループ
    vector <Group> group;
    int scheduleCommand;
    int groupChoice;
    int commandChoice;
    ///time//
    string reservation;//時間
    string clock;
    string s,m,h;
    
    
    ///„Çπ„ÇØ„É≠„Éº„É´
    float Yscroll,Ymove;
    
    bool isTab,mouseTab;
    ofVec2f posTab;
    int choiceTab;
    int GroupTabNum;
};
