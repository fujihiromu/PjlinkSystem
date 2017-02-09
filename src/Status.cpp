#include "Status.h"



//Status:: Status(ofxTCPClient &pjClient):pjClient(pjClient){};


Status::Status(string address,string pass ){
    IP = address;
    password = pass;
    lamptime = "unknow";
    Name = "unknow";
    INPT = "unknow";
    Power = 0;
    Shutter = 0;
 
    setProjectorIP(address);
    setProjectorType(PJLINK_MODE);
    setProjectorPort(PJLINK_PORT);
    setProjectorPassword(pass);
    timer=false;


    
}




void Status::setProjectorType(int protocol) { //NEC_MODE or PJLINK_MODE
    commMode = protocol;
}

void Status::setup(string IP_add, string pass) {
    setProjectorIP(IP_add);
    setProjectorType(0);
    setProjectorPort(4352);
    setProjectorPassword(pass);
    timer=false;
    
}

void Status::setProjectorIP(string IP_add) {
    IP = IP_add;
}

void Status::setProjectorPort(int port) {
    pjPort = port;
}

void Status::setProjectorPassword(string pass) {
    password = pass;
}



void Status::sendPJLinkCommand(string command) {
    string msgRx="";
    
    if(!pjClient->isConnected()) {
        pjClient->setVerbose(true);
        connected = pjClient->setup(IP, pjPort,true);
        if(connected){
            ofLogNotice() << "connection established: " << IP << ":" << pjPort << endl;
            string response = "";
            while (msgRx.length() < 8) {
                msgRx = pjClient->receiveRaw();
            }
            ofLogNotice() << "received response: " << msgRx << endl;
            
            
        } else {
            ofLogError() << "faled to connect."<<endl;
            
        }
    }
    
    if(connected){
        string authToken = "";
        
        //eg. PJLINK 1 604cc14d
        if(msgRx[7] == '1') {
            ofLogNotice() << "with authentication" << endl;
            MD5Engine md5;
            md5.reset();
            string hash = msgRx.substr(9,8);
            ofLogNotice() << hash << endl;
            md5.update(hash + password);
            authToken = DigestEngine::digestToHex(md5.digest());
        }
        ofLogNotice() << "sending command: " << authToken+command << endl;
        pjClient->sendRaw(authToken+command);
        msgRx = "";
        while (msgRx.length() < 8) {
            msgRx = pjClient->receiveRaw();
        }
        
        
        if(msgRx.size()>8){
            msgRx.erase( --msgRx.end());
        }
        
        
        presponce = msgRx;
        
        ofLogNotice() << "received response: " << msgRx << endl;
        
        
        pjClient->close();
        
        
    } else {
        ofLogError()<< "still not connected."<<endl;
        pjClient->close();
        presponce = "NOT CONEECT";
    }
}

void Status::sendCommand(string command){
    
    if(!pjClient->isConnected()) {
        pjClient->setVerbose(true);
        ofLogNotice() << "connecting to : " << IP << ":" << pjPort << endl;
        connected = pjClient->setup(IP, pjPort, true);
        ofLogNotice() << "connection state : " << connected;
        
    }
    ofLogNotice() << "sending command : " << command << endl;
    pjClient->sendRaw(command);
    ofLogNotice() << "Response length (Bytes) : " << pjClient->getNumReceivedBytes() << endl;
    msgRx = "";
    msgRx = pjClient->receiveRaw();
    
    ofLogNotice() << "received response : " << msgRx << endl;
    
    pjClient->close();
    
}


void Status::power_On() {

    string command = "%1POWR 1\r";
    sendPJLinkCommand(command);
    
    if(presponce == "%1POWR=1"){
        Power = true;
    }
    
    if(presponce == "%1POWR=ERR3"){
        message = "During shutdown";
        
        timer =true;
    }
    error_view();
    
}

void Status::power_Off() {

    string command = "%1POWR 0\r";
    sendPJLinkCommand(command);

    if(presponce == "%1POWR=0"){
        Power = false;
    }

    
    error_view();
}
void Status::pjLink_Check() {
    
 
    string command = "%1POWR ?\r";
    sendPJLinkCommand(command);
    
    cout << pjClient->receiveRaw();
    
    
    if(presponce == "%1POWR=1"){
        Power = true;
    }else if(presponce == "%1POWR=0"){
        Power = false;
    }
    
    error_view();
    
}


void Status::lamp(){
  
    string command = "%1LAMP ?\r";
    sendPJLinkCommand(command);
    
    if(connected){
        for(int i =0; i < 7; i++){
            presponce.erase(presponce.begin() + 0);
        }
        
        
        lamptime = presponce;
    }
    
}

void Status::name_Check(){

    string command = "%1NAME ?\r";
    sendPJLinkCommand(command);
    
    if(connected){
        for(int i =0; i < 7; i++){
            presponce.erase(presponce.begin() + 0);
        }
        Name = presponce;
    }
    
    
}
void Status::shutter_on(){
    string command = "%1AVMT 10\r";
    sendPJLinkCommand(command);
    
    if(connected){
        Shutter = true;
    }
    
    error_view();
}

void Status::shutter_off(){
    
    string command = "%1AVMT 11\r";
    sendPJLinkCommand(command);
    
    if(connected){
        Shutter = false;
    }
    
    error_view();
}

void Status::shutter_Check(){
   
    string command = "%1AVMT ?\r";
    sendPJLinkCommand(command);
    
    if(connected){
        for(int i =0; i < 7; i++){
            presponce.erase(presponce.begin() + 0);
        }
        
    }
    
}


void Status::digital_INPT(){
    string command = "%1INPT 31\r";
    sendPJLinkCommand(command);
    
    error_view();
}

void Status::video_INPT(){
    string command = "%1INPT 32\r";
    sendPJLinkCommand(command);
    error_view();
}


void Status::INPT_Check(){
    string command = "%1INPT ?\r";
    sendPJLinkCommand(command);
    if(presponce != "error"){
        for(int i =0; i < 7; i++){
            presponce.erase(presponce.begin() + 0);
        }
        
    }
    
    
}

void Status::error_view(){
    
    if(presponce=="NOT CONEECT" || presponce=="PJLINK ERRA"){
        timer = true;
        message = presponce;
    }
    
    
    if(presponce=="ERR3"){
        timer = true;
        message = presponce;
    }
    
}

bool Status::getconnection(){
    return connected;
}


void Status::schedule_command(int mode){
    if(mode == 0){
        power_On();
    }else if(mode == 1){
        power_Off();
    }else if(mode == 2){
        shutter_on();
    }else if(mode == 3){
        shutter_off();
    }else if(mode ==4){
        digital_INPT();
    }else if(mode ==5){
        video_INPT();
    }
}
