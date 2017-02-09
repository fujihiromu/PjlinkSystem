#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(rate);
    ofBackground(245);
    count = 0;
    mstime = 0;
    ofSetLineWidth(0.1);
    //‰∏ã„Å´Èñ¢Êï∞‰ΩúÊàê
    json_input();
   
    ofSetCircleResolution(60);
    
    bo.load("bo.png");
    on.load("on.png");
    off.load("off.png");
    open.load("open.png");
    close.load("close.png");
    hdmi.load("hdmi.png");
    dvi.load("dvi.png");
    del.load("delete.png");
    reset.load("reset.png");
    edit.load("edit.png");
    tab.load("tab.png");
    
    Bfont.load("Arial Black.ttf", 140);
    Bfont1.load("ヒラギノ角ゴシック w6.ttc", 10);
    Bfont2.load("ヒラギノ角ゴシック W6.ttc", 15);
    Bfont3.load("ヒラギノ角ゴシック W6.ttc", 18);
    Bfont4.load("ヒラギノ角ゴシック W6.ttc", 25);
    Bfont5.load("ヒラギノ角ゴシック W6.ttc", 30);
    
   
    Mfont1.load("ヒラギノ角ゴシック w4.ttc", 10);
    Mfont2.load("ヒラギノ角ゴシック W3.ttc", 15);
    Mfont3.load("ヒラギノ角ゴシック W3.ttc", 18);
    Mfont4.load("ヒラギノ角ゴシック W3.ttc", 25);
    Mfont5.load("ヒラギノ角ゴシック W3.ttc", 30);
    
    Cfont1.load("ヒラギノ角ゴシック w5.ttc", 12);
    Cfont2.load("ヒラギノ角ゴシック W5.ttc", 15);
    Cfont3.load("ヒラギノ角ゴシック W5.ttc", 18);
    Cfont4.load("ヒラギノ角ゴシック W5.ttc", 25);
    Cfont5.load("ヒラギノ角ゴシック W5.ttc", 30);

    



}

//--------------------------------------------------------------
void ofApp::update(){
    

    clock.clear();
    //seconds
    if (ofGetSeconds()<10) {
        s = "0"+ofToString(ofGetSeconds(), 0);
    } else {
        s = ofToString(ofGetSeconds(), 0);
    }
    //minutes
    if (ofGetMinutes()<10) {
        m = "0"+ofToString(ofGetMinutes(), 0);
    } else {
        m = ofToString(ofGetMinutes(), 0);
    }
    //hours
    if (ofGetHours()<10) {
        h = "0"+ofToString(ofGetHours(), 0);
    } else {
        h = ofToString(ofGetHours(), 0);
    }
    
    
  //  int w = ofGetWeekday();//
  
    clock = h+":"+m+":"+s;
  
    


    string T = h+ m;
 
    for(int i=0;i<group.size();i++){
        for(int j=0;j<group[i].schedule.size();j++){
        
            if(T == group[i].schedule[j].Sche_time){
                if(s=="00"){
                    for(int k=0;k<group[i].Number.size();k++){
                       
                        projector[group[i].Number[k]].schedule_command(group[i].schedule[j].mode);
                        
                    }
                }
            }
            
            
        }
        
    }
    
    
    
    
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    
    ofPushMatrix();
    ofTranslate(0,Ymove);
    
    
    //realtime
    ofSetColor(70);
    string time = ofToString(h, 0) + " : " + ofToString(m, 0) + " : " + ofToString(s, 0);
    Bfont2.drawString("Day Time   1/14 : " + time, ofGetWidth()*0.05, 50);
    Bfont2.drawString("LIST", ofGetWidth()*0.4, 50);
    Bfont2.drawString("SCHEDULE / GROUP", ofGetWidth()*0.5, 50);
    Mfont1.drawString("Responce => ",ofGetWidth()*0.8,50);
    
    
    ///////message//////////
    if(testPJ.timer){
        mstime++;
        
        ofSetColor(255, 0, 0);
        Bfont1.drawString(testPJ.message, ofGetWidth()*0.8+100, 50);
        
        if(mstime>rate*2){
            mstime=0;
            testPJ.timer=false;
            
        }
        
    }
    
    for(int i=0;i<projector.size();i++){
        if(projector[i].timer==true){
            mstime++;
            
            ofSetColor(255, 0, 0);
            Bfont1.drawString(projector[i].message, ofGetWidth()*0.8+100, 50);
            
            if(mstime>rate*2){
                mstime=0;
                projector[i].timer=false;
                
            }
            
            
        }
        
    }
    
    
 
    //fade///
    int a ;
    if(ofGetFrameNum()%125 > 62){
        a = ofGetFrameNum()%125 *2;
    }else{
        a = 250 - ofGetFrameNum()%125 *2;
    }
    
    if(page==0||page==1) {
 
        
        
        //// headder /////
        
        ofSetColor(70);
        
        Mfont1.drawString("Name",ofGetWidth()*0.12,230);
        Mfont1.drawString("IP Address",ofGetWidth()*0.25,230);
        Mfont1.drawString("Lamp Time",ofGetWidth()*0.38,230);
        Mfont1.drawString("Input",ofGetWidth()*0.5,230);
        Mfont1.drawString("Power",ofGetWidth()*0.58,230);
        Mfont1.drawString("Shutter",ofGetWidth()*0.64,230);
        
        
        
        
        ////projectior status/////////
        
        
        for (int i=0; i<projector.size();i++){
            
            ofSetColor(80);
            ofNoFill();
            ofDrawRectangle(38, space*i+270, 14 , 14 );
            
            ofFill();
            if(i==pro_choice){
                ofSetColor(a);
                ofDrawRectangle(40,space*i+272,10,10);
            }
            
            
    
            
            ofSetColor(100);
            
          //  projector[i].Name = "2";
            Cfont1.drawString(projector[i].Name,ofGetWidth()*0.12-55,space*i+282);
            Cfont1.drawString(projector[i].IP,ofGetWidth()*0.25-5,space*i+282);
            Cfont1.drawString(projector[i].lamptime+"   h",ofGetWidth()*0.38-5,space*i+282);
            Cfont1.drawString(projector[i].INPT,ofGetWidth()*0.5-10,space*i+282);
           
          

                 
            //POWER , SHUTTER
            if(projector[i].Power==true){
                ofSetColor(ofColor::green);
            }else{
                ofSetColor(ofColor::red);
            }
            ofDrawCircle(ofGetWidth()*0.58+25, space*i+275, 10);
            
            if(projector[i].Shutter==true){
                ofSetColor(255,105,0);
            }else{
                ofSetColor(0, 255, 255);
            }
            ofDrawCircle(ofGetWidth()*0.64+25, space*i+275, 10);

            
        }
        
    
        
    //////button //////////
        
        ofSetColor(255,200);
        on.draw(ofGetWidth()*0.8,300);
        off.draw(ofGetWidth()*0.9,300);
        
        open.draw(ofGetWidth()*0.8,400);
        close.draw(ofGetWidth()*0.9,400);
        
        hdmi.draw(ofGetWidth()*0.8,500);
        dvi.draw(ofGetWidth()*0.9,500);
        
        del.draw(ofGetWidth()*0.8,600);
   
     

        if(first_set){
            count++;
            if(count==18){
                
                addsearch.clear();
                passearch.clear();
                
                
                testPJ.lamp();
            }
            if(count==40){
                testPJ.name_Check();
                
            }
            if(count==58){
                testPJ.INPT_Check();
             
            }
            if(count==72){
                testPJ.shutter_Check();
                
                projector.push_back(testPJ);
            }
            if(count==73){
                first_set=false;
                count=0;
                //Ê†ºÁ¥ç
                
               
                
            }
           
            
            ofSetColor(255);
            Bfont.drawString("SEARCH", 20, 400);
        }
        
        
        
        ///input form///////
        ofSetColor(230);
        ofDrawRectangle(ofGetWidth()*0.2-20, 110, ofGetWidth()*0.6, 45);
        if(page==0){
            
            ofSetColor(100,a);
            Mfont2.drawString("IP Address :   " +addsearch, ofGetWidth()*0.2, 140);
            ofSetColor(100);
            Mfont2.drawString("Passward :   " +passearch, ofGetWidth()*0.51, 140);
            
        }else if(page==1){
            
            ofSetColor(100);
            Mfont2.drawString("IP Address :   " +addsearch, ofGetWidth()*0.2, 140);
            ofSetColor(100,a);
            Mfont2.drawString("Passward :   " +passearch, ofGetWidth()*0.51, 140);
            
        }
        //入力フォーム
        ofSetColor(100);
        ofDrawLine(ofGetWidth()*0.3, 150, ofGetWidth()*0.46, 150);
        ofDrawLine(ofGetWidth()*0.6, 150, ofGetWidth()*0.75, 150);

       
        
        
    }
    
    
    
    /////Group/////
    if(page==2){
        
        
        //tittle
        ofSetColor(80);
        ofDrawRectangle(ofGetWidth()*0.08, 100, ofGetWidth()*0.34,20);
        ofDrawRectangle(ofGetWidth()*0.58, 100, ofGetWidth()*0.34,20);
        ofSetColor(255);
        Mfont1.drawString("Make Group / Make Schedule", ofGetWidth()*0.17, 116);
        Mfont1.drawString("Group List / Time Schedule", ofGetWidth()*0.67, 116);
        
          ofSetColor(255,150);
            bo.draw(ofGetWidth()/2, 200,5,1200);
        
        if(page_group[0]==0){
            
          
            
            //入力フォーム
            ofSetColor(230);
            ofDrawRectangle(ofGetWidth()*0.125-15, 185, ofGetWidth()*0.27, 35);
            ofSetColor(100);
            Mfont2.drawString("Group Name :   " +group_name, ofGetWidth()*0.125, 210);
            ofDrawLine(ofGetWidth()*0.245, 215, ofGetWidth()*0.365, 215);
         
            ofSetColor(255,150);
            reset.draw(ofGetWidth()*0.05-25,250);
            
            for (int i=0; i<projector.size();i++){
                
                ofSetColor(80);
                ofNoFill();
                ofDrawRectangle(ofGetWidth()*0.05, space*i+290, 14 , 14 );
                
                ofFill();
                if(Gchoice[i]){
                    ofDrawRectangle(ofGetWidth()*0.05+2,space*i+292,10,10);
                }
                
                ofSetColor(100);
                Cfont1.drawString(projector[i].Name,ofGetWidth()*0.1,space*i+302);
                Cfont1.drawString(projector[i].IP,ofGetWidth()*0.32,space*i+302);
               
            }
          
        }else if(page_group[0]==1){
            
            //入力フォーム
            ofSetColor(230);
            ofDrawRectangle(ofGetWidth()*0.125-15, 185, ofGetWidth()*0.27, 35);
            ofSetColor(100);
            Mfont2.drawString("  Input Time :       " +reservation, ofGetWidth()*0.125, 210);
            ofDrawLine(ofGetWidth()*0.245, 215, ofGetWidth()*0.365, 215);
            
            
            
            for(int i=0;i<group.size();i++){
                
                ofSetColor(80);
                ofNoFill();
                ofDrawRectangle(ofGetWidth()*0.05, space*i+290, 14 , 14 );
                
                ofFill();
                if(groupChoice==i){
                    ofDrawRectangle(ofGetWidth()*0.05+2,space*i+292,10,10);
                }
                ofSetColor(100);
                Cfont1.drawString(group[i].groupname,ofGetWidth()*0.1,303+i*space);
                
            }
            
            ofSetColor(255,50);
            on.draw(ofGetWidth()*0.3,300);
            off.draw(ofGetWidth()*0.4,300);
            
            open.draw(ofGetWidth()*0.3,400);
            close.draw(ofGetWidth()*0.4,400);
            
            hdmi.draw(ofGetWidth()*0.3,500);
            dvi.draw(ofGetWidth()*0.4,500);
            
            ofSetColor(255,200);
            if(commandChoice==0){
                on.draw(ofGetWidth()*0.3,300);
            }else if(commandChoice==1){
                off.draw(ofGetWidth()*0.4,300);
            }else if(commandChoice==2){
                open.draw(ofGetWidth()*0.3,400);
            }else if(commandChoice==3){
                close.draw(ofGetWidth()*0.4,400);
            }else if(commandChoice==4){
                hdmi.draw(ofGetWidth()*0.3,500);
            }else if(commandChoice==5){
                dvi.draw(ofGetWidth()*0.4,500);
            }

        }
        
 ///////
        
        if(page_group[1]==0){
            ofSetColor(100);
            int num=0;
            for(int i= 0;i<group.size();i++){
                drawGroup(ofGetWidth()*0.6, 200+num*20+100*i, i);
                num+= group[i].Number.size();
            }
            if(isTab){
                ofSetColor(255);
                ofDrawRectangle(posTab, 220, 110);
                if(mouseTab){
                    ofSetColor(0,255,255,125);
                    ofDrawRectangle(posTab.x,posTab.y+12+choiceTab*30, 220, 30);
                    
                }
                ofSetColor(255);
                tab.draw(posTab.x+10,posTab.y+10);
            }
        }else if(page_group[1]==1){
            ofSetColor(100);
            int num=0;
            for(int i= 0;i<group.size();i++){
                drawTimeSchedule(ofGetWidth()*0.6, 200+num*20+100*i, i);
                num+= group[i].schedule.size();
            }

        }
    }
   
    
    ofPopMatrix();
}
//--------------------------------------------------------------

void ofApp::exit(){
    //書き出し
    json_output();
   
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
    
    if(count==0){
        if(page==0||page==1){
            if(key == OF_KEY_RETURN){
                
                Status S = Status(addsearch,passearch);
                testPJ = S;
                testPJ.setup(addsearch,passearch);
                testPJ.setProjectorIP(addsearch);
                testPJ.setProjectorPassword(passearch);
             
                testPJ.pjLink_Check();
                
               // if(testPJ.getconnection()&&first_set==false){
                    first_set=true;
                    testPJ.timer=true;
              // }else{
                    addsearch.clear();
                    passearch.clear();
              // }
                
            
             
            }
        }
        
    }

    

    
    if(page == 0){
        
        if(key!=OF_KEY_BACKSPACE){
            if( key!=OF_KEY_RETURN){
                 addsearch += key;
            }
        }
        
        if(key == OF_KEY_BACKSPACE && addsearch.size()>0){
            addsearch.erase( --addsearch.end() );
        }
    }
    
    if(page == 1){
        
        if(key!=OF_KEY_BACKSPACE){
            if(key!=OF_KEY_RETURN){
                passearch += key;
            }
        }
        
        
        if(key == OF_KEY_BACKSPACE && passearch.size()>0){
            passearch.erase( --passearch.end() );
        }
    }
    if(page ==2&&page_group[0]==0){
        if(key!=OF_KEY_BACKSPACE){
            if(key!=OF_KEY_RETURN){
                if(group_name.size()<10){
                    group_name += key;
                }
            }
        }
        
        
        if(key == OF_KEY_BACKSPACE && group_name.size()>0){
            
           
                group_name.erase( --group_name.end() );
            
            
        }
        if(key == OF_KEY_RETURN){
            Group p = Group(group_name);
            group.push_back(p);
            group_name.clear();
            for(int i=0;i<Gchoice.size();i++){
                if(Gchoice[i]){
                    group[group.size()-1].group_input(i);
                }
            }
        }
    }
    if(page ==2&&page_group[0]==1){
        if(key!=OF_KEY_BACKSPACE){
            if(key!=OF_KEY_RETURN){
                if(reservation.size()<10){
                    reservation += key;
                }
            }
        }
        
        
        if(key == OF_KEY_BACKSPACE && reservation.size()>0){
            
            reservation.erase( --reservation.end() );
            
        }
        if(key == OF_KEY_RETURN){
            group[groupChoice].planIn(reservation, commandChoice);
            reservation.clear();
        }
    }

    
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    float correctionY = mouseY - Ymove;
    if(isTab){
        if(posTab.y+10<correctionY&&correctionY<posTab.y+100&&posTab.x<mouseX&&mouseX<posTab.x+220){
            mouseTab=true;
        }else{
            mouseTab=false;
        }
        
        for(int i=0;i<3;i++){
            if(posTab.y+10+30*i<correctionY&&correctionY<posTab.y+10+30*(i+1)  &&posTab.x<mouseX&&mouseX<posTab.x+220&&mouseTab){
                choiceTab = i;
            }
        }
    }

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
   

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
   
    ////„Çπ„ÇØ„É≠„Éº„É´Ë£úÊ≠£
    float correctionY = mouseY - Ymove;
    
    
    if(page==0||page==1){
        if(ofGetWidth()*0.2<mouseX && mouseX<ofGetWidth()*0.4 && 100<correctionY && correctionY < 145){
            //IPÂÖ•Âäõ
            page = 0;
        }
        if(ofGetWidth()*0.5<mouseX && mouseX<ofGetWidth()*0.8 && 100<correctionY && correctionY < 145){
            //„Éë„Çπ„ÉØ„Éº„ÉâÂÖ•Âäõ
            page = 1;
        }
    }
    
    if(ofGetWidth()*0.4<mouseX&&mouseX<ofGetWidth()*0.4+50&&30<correctionY&&correctionY<50){
        page = 0;
    }

    if(ofGetWidth()*0.5<mouseX && mouseX<ofGetWidth()*0.5+250&& 30<correctionY && correctionY < 50){
        //Group
        page = 2;
        while(projector.size()>Gchoice.size()){
            Gchoice.push_back(false);
        }
    }
 
    if(ofGetWidth()*0.1<mouseX && mouseX<ofGetWidth()*0.4&& 100<correctionY && correctionY < 120){
        //Group
        page_group[0]++;
        if(page_group[0]>1){
            page_group[0]=0;
        }
    }
    if(ofGetWidth()*0.6<mouseX && mouseX<ofGetWidth()*0.9&& 100<correctionY && correctionY < 120){
        //Group
        page_group[1]++;
        if(page_group[1]>1){
            page_group[1]=0;
        }

    }


    

   
    
    if(projector.size()>0&&page!=2&&page!=3){
        
        if(ofGetWidth()*0.8<mouseX && mouseX<ofGetWidth()*0.8+50 && 300<correctionY && correctionY < 360){
            projector[pro_choice].power_On();
            
           // cout <<  ofToString(pro_choice) << endl;
            
        }

        if(ofGetWidth()*0.9<mouseX && mouseX<ofGetWidth()*0.9+50 && 300<correctionY && correctionY < 360){
            projector[pro_choice].power_Off();
            
          
        }
        if(ofGetWidth()*0.8<mouseX && mouseX<ofGetWidth()*0.8+50 && 400<correctionY && correctionY < 460){
            projector[pro_choice].shutter_on();
            
         
        }

        if(ofGetWidth()*0.9<mouseX && mouseX<ofGetWidth()*0.9+50 && 400<correctionY && correctionY < 460){
            projector[pro_choice].shutter_off();
            
        }
        
        
        if(ofGetWidth()*0.8<mouseX && mouseX<ofGetWidth()*0.8+50 && 600<correctionY && correctionY<670){
            
           projector.erase(projector.begin()+pro_choice);
            
            projector.shrink_to_fit();
            if(projector.size()<=pro_choice){
                if(pro_choice!=0)pro_choice--;
            }
        }
        
        if(ofGetWidth()*0.8<mouseX && mouseX<ofGetWidth()*0.8+50&& 500<correctionY && correctionY < 570){
            projector[pro_choice].digital_INPT();
        
        }
        
        if(ofGetWidth()*0.9<mouseX && mouseX<ofGetWidth()*0.9+50&& 500<correctionY && correctionY < 570){
            projector[pro_choice].video_INPT();
            
           
        }
        

        
        for(int i =0 ;i<projector.size(); i++){
            if(38<mouseX && mouseX<52 && space*i+270<correctionY && correctionY< space*i+285){
                pro_choice = i;
            }
        }
    }
    
    
    
    if(projector.size()>0&&page==2&&page_group[0]==0){
        
        for(int i =0 ;i<projector.size(); i++){
            if(ofGetWidth()*0.05<mouseX && mouseX<ofGetWidth()*0.05+15 && space*i+288<correctionY && correctionY< space*i+305){
                Gchoice[i] = !Gchoice[i];
            }
        }
        if(ofGetWidth()*0.05-25<mouseX && mouseX<ofGetWidth()*0.05+42 && 250<correctionY && correctionY< 280){
            for(int i=0;i<projector.size();i++){
                Gchoice[i] = false;
            }
        }
    }else if(projector.size()>0&&page==2&&page_group[0]==1){
        for(int i =0 ;i<group.size(); i++){
            if(ofGetWidth()*0.05<mouseX && mouseX<ofGetWidth()*0.05+15 && space*i+288<correctionY && correctionY< space*i+305){
                groupChoice = i;
            }
        }
        
        if(ofGetWidth()*0.3<mouseX&&mouseX<ofGetWidth()*0.3+50&&300<correctionY&&correctionY<370){
            commandChoice = 0;
        }else if(ofGetWidth()*0.4<mouseX&&mouseX<ofGetWidth()*0.4+50&&300<correctionY&&correctionY<370){
            commandChoice = 1;
        }else if(ofGetWidth()*0.3<mouseX&&mouseX<ofGetWidth()*0.3+50&&400<correctionY&&correctionY<470){
            commandChoice = 2;
        }else if(ofGetWidth()*0.4<mouseX&&mouseX<ofGetWidth()*0.4+50&&400<correctionY&&correctionY<470){
            commandChoice = 3;
        }else if(ofGetWidth()*0.3<mouseX&&mouseX<ofGetWidth()*0.3+50&&500<correctionY&&correctionY<570){
            commandChoice = 4;
        }else if(ofGetWidth()*0.4<mouseX&&mouseX<ofGetWidth()*0.4+50&&500<correctionY&&correctionY<570){
            commandChoice = 5;
        }
            
    }
    
    
    
    if(projector.size()>0&&page==2&&page_group[1]==0){
        int num=0;
        
        if(isTab){
            if(posTab.x<mouseX&&mouseX<posTab.x+220&&posTab.y<correctionY&&correctionY<posTab.y+110){
                
            }else{
                isTab=false;
                
            }
            
        }

        
        for(int i= 0;i<group.size();i++){
            
            if(ofGetWidth()*0.6+group[i].groupname.size()*16<mouseX&&mouseX<ofGetWidth()*0.6+group[i].groupname.size()*16+edit.getWidth()*0.6&& 185+num*20+100*i<correctionY&&correctionY<185+num*20+100*i+edit.getHeight()*0.6){
                
                isTab = true;
                posTab = ofVec2f(ofGetWidth()*0.6+group[i].groupname.size()*16+30,80+num*20+100*i);
                GroupTabNum = i;
            }
            num+= group[i].Number.size();
        
            
            
            
        }
        
        if(mouseTab){
            for(int i=0;i<3;i++){
                if(posTab.y+10+30*i<correctionY&&correctionY<posTab.y+10+30*(i+1)  &&posTab.x<mouseX&&mouseX<posTab.x+220){
                    
                    if(i==0){
                        group.erase(group.begin()+GroupTabNum);
                        isTab=false;
                    }else if(i==1){
                        for(int i=0;i<projector.size();i++){
                            Gchoice[i] = false;
                        }
                        
                        //反映
                        group_name = group[GroupTabNum].groupname;
                        for(int j=0;j<group[GroupTabNum].Number.size();j++){
                            Gchoice[group[GroupTabNum].Number[j]] = true;
                        }
                        
                        isTab =false;
                    }else if (i==2){
                        isTab =false;
                    }
                    
                }
            }
            
        }

    }else if(projector.size()>0&&page==2&&page_group[1]==1){
      
    }
    
}

//-------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
//--------------------------------------------------------------
void ofApp::json_output(){
    char k = '"';
    string p;
    if(projector.size()==0){
        p ="{"+ofToString(k) +"Size"+ ofToString(k) +":" + ofToString(k)+ ofToString(projector.size())+ ofToString(k)+",";
    }else{
        p = "{"+ofToString(k) +"Size"+ ofToString(k) +":" + ofToString(k)+ ofToString(projector.size())+ ofToString(k) +"," +ofToString(k) + "projector" + ofToString(k) +":[{"  ;
        
        for (int i = 0; i<projector.size(); i++) {
            
            p +=  ofToString(k)+"data["+ofToString(i)+"]"+ ofToString(k) +":[{"+ ofToString(k) +"IP"+ ofToString(k) +":"+ ofToString(k) +projector[i].IP+ ofToString(k) +"},{"+ ofToString(k) +"passward"+ ofToString(k) +":"+ ofToString(k) +projector[i].password+ ofToString(k) +"},{"+ ofToString(k) +"name"+ ofToString(k) +":"+ ofToString(k) +projector[i].Name+ ofToString(k) +"},{"+ ofToString(k) +"lamptime"+ ofToString(k) +":"+ ofToString(k) +projector[i].lamptime+ ofToString(k) +"},{"+ ofToString(k) +"INPT"+ ofToString(k) +":"+ ofToString(k) +projector[i].INPT+ ofToString(k) +"},{"+ ofToString(k) +"power"+ ofToString(k) +":"+ ofToString(k) +ofToString(projector[i].Power)+ ofToString(k) +"},{"+ ofToString(k) +"shutter"+ ofToString(k) +":"+ ofToString(k) +ofToString(projector[i].Shutter)+ ofToString(k) +"}],";
            
        }
        p.erase( --p.end() );
        p+="}]}";
    }
//    if(group.size()==0){
//        p+=ofToString(k) +"Num"+ofToString(k) +":"+ofToString(k) +ofToString(group.size())+ofToString(k)+"}";
//    }else{
//        p+=ofToString(k) +"Num"+ofToString(k) +":"+ofToString(k) +ofToString(group.size())+ofToString(k) +","+ofToString(k) +"group"+ofToString(k) +":[{"  ;;
//        for(int i=0;i<group.size();i++){
////            group[i].inclock.erase(group[i].inclock.begin()+2);
////            group[i].inclock.erase(group[i].inclock.begin()+4);
////            p +=  ofToString(k)+"data["+ofToString(i)+"]"+ ofToString(k) +":[{"+ ofToString(k) +"time"+ ofToString(k) +":"+ ofToString(k) +group[i].inclock+ ofToString(k) +"},{"+ ofToString(k) +"name"+ ofToString(k) +":"+ ofToString(k) +group[i].address+ ofToString(k) +"},{"+ ofToString(k) +"num"+ ofToString(k) +":"+ ofToString(k) +ofToString(group[i].number)+ ofToString(k) +"},{"+ ofToString(k) +"pow"+ ofToString(k) +":"+ ofToString(k) +ofToString(group[i].power)+ ofToString(k)  +"}],";
////            
//            
//        }
//        p.erase( --p.end() );
//        p+="}]}";
//    }
    string fileName = "test.txt";
    ofBuffer buffer = ofBuffer( p );
    ofBufferToFile( fileName, buffer );
}
//--------------------------------------------------------------
void ofApp::json_input(){
    bool result = Input.open("test.txt");
    if(!result){
        cout << "faild to get Json data" << endl;
        
    }else{
        
        
        
        
        string letter1 = Input["Size"].asString();
        int size = stoi(letter1);
        for(int i =0;i<size;i++){
            Status x ;
            x.setup(Input["projector"][0]["data["+ofToString(i)+"]"][0]["IP"].asString(),Input["projector"][0]["data["+ofToString(i)+"]"][1]["passward"].asString());
            projector.push_back(x);
            
            
            projector[i].Name =Input["projector"][0]["data["+ofToString(i)+"]"][2]["name"].asString();
            projector[i].lamptime =Input["projector"][0]["data["+ofToString(i)+"]"][3]["lamptime"].asString();
            
            projector[i].INPT =Input["projector"][0]["data["+ofToString(i)+"]"][4]["INPT"].asString();
            
            if(Input["projector"][0]["data["+ofToString(i)+"]"][5]["power"].asString()=="0"){
                projector[i].Power = false;
            }else{
                projector[i].Power = true;
            }
            
            if(Input["projector"][0]["data["+ofToString(i)+"]"][6]["shutter"].asString()=="0"){
                projector[i].Shutter = false;
            }else{
                projector[i].Shutter = true;
            }
            
            // N.push_back(i);
            
        }
        
        
//        string letter2 = Input["Num"].asString();
//        int Num = stoi(letter2);
//        
//        for(int i =0;i<Num;i++){
//            
//            string n= Input["group"][0]["data["+ofToString(i)+"]"][2]["num"].asString();
//            int st = stoi(n);
//            bool p;
//            if(Input["group"][0]["data["+ofToString(i)+"]"][3]["pow"].asString()=="0"){
//                p= false;
//            }else{
//                p = true;
//            }
//            
        
            
//            Schedule x = Schedule(Input["group"][0]["data["+ofToString(i)+"]"][0]["time"].asString(),Input["group"][0]["data["+ofToString(i)+"]"][1]["name"].asString(),st,p);
//            group.push_back(x);
//            
//            
        

            
 //       }
    }
    

}


void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){
   
    Yscroll = scrollY;
   
    Ymove += Yscroll*3;
    if(Ymove > 0)Ymove=0;
}


void ofApp::drawGroup(int x, int y ,int i ){
    ofSetColor(100);
         Cfont3.drawString(group[i].groupname, x, y);
        for(int j=0; j<group[i].Number.size();j++){
            Mfont1.drawString(projector[group[i].Number[j]].Name, x, y+20*j+50);
            Mfont1.drawString(projector[group[i].Number[j]].IP, x+200, y+20*j+50);
        }
    ofSetColor(255,180);
    edit.draw(x+group[i].groupname.size()*16,y-13,edit.getWidth()*0.6,edit.getHeight()*0.6);

}

void ofApp::drawTimeSchedule(int x, int y ,int i){
    ofSetColor(100);
    Cfont3.drawString(group[i].groupname, x, y);
    
    for(int j=0; j<group[i].schedule.size();j++){
        ofSetColor(100);
        Mfont2.drawString(group[i].schedule[j].Sche_time, x+100, y+30*j+40);
        ofSetColor(255);
        if(group[i].schedule[j].mode==0){
            on.draw(x+50, y+30*j+20,on.getWidth()*0.4,on.getHeight()*0.4);
        }else if(group[i].schedule[j].mode==1){
            off.draw(x+50, y+30*j+20,on.getWidth()*0.4,on.getHeight()*0.4);
        }else if(group[i].schedule[j].mode==2){
            open.draw(x+50, y+30*j+20,on.getWidth()*0.4,on.getHeight()*0.4);
        }else if(group[i].schedule[j].mode==3){
            close.draw(x+50, y+30*j+20,on.getWidth()*0.4,on.getHeight()*0.4);
        }else if(group[i].schedule[j].mode==4){
            hdmi.draw(x+50, y+30*j+20,on.getWidth()*0.4,on.getHeight()*0.4);
        }else if(group[i].schedule[j].mode==5){
            dvi.draw(x+50, y+30*j+20,on.getWidth()*0.4,on.getHeight()*0.4);
        }

    }

}
