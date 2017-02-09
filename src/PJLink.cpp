

#include "PJLink.h"
#include "ofMain.h"

PJLink::PJLink() {
	connected = false;
	
   
}
PJLink::PJLink(const PJLink &PJLink){
    connected = false;

  
}

PJLink::~PJLink() {

}


void PJLink::setProjectorType(int protocol) { //NEC_MODE or PJLINK_MODE
		commMode = protocol;
}

void PJLink::setup(string IP_add, string pass) {
	setProjectorIP(IP_add);
	setProjectorType(PJLINK_MODE);
	setProjectorPort(4352);
    setProjectorPassword(pass);
    timer=false;
    
}

void PJLink::setProjectorIP(string IP_add) {
	IPAddress = IP_add;
}

void PJLink::setProjectorPort(int port) {
	pjPort = port;
}

void PJLink::setProjectorPassword(string pass) {
	password = pass;
}



void PJLink::sendPJLinkCommand(string command) {
		string msgRx="";

        if(!pjClient.isConnected()) {
            pjClient.setVerbose(true);
            connected = pjClient.setup(IPAddress, pjPort,true);
            if(connected){
                ofLogNotice() << "connection established: " << IPAddress << ":" << pjPort << endl;
                string response = "";
                while (msgRx.length() < 8) {
                    msgRx = pjClient.receiveRaw();
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
		pjClient.sendRaw(authToken+command);
		msgRx = "";
		while (msgRx.length() < 8) {
			msgRx = pjClient.receiveRaw();
		}
        
        
        if(msgRx.size()>8){
            msgRx.erase( --msgRx.end());
        }
        

        presponce = msgRx;
       
        ofLogNotice() << "received response: " << msgRx << endl;
     
        
        pjClient.close();
		
        
    } else {
        ofLogError()<< "still not connected."<<endl;
        pjClient.close();
        presponce = "NOT CONEECT";
    }
}

void PJLink::sendCommand(string command){
    
        if(!pjClient.isConnected()) {
			pjClient.setVerbose(true);
			ofLogNotice() << "connecting to : " << IPAddress << ":" << pjPort << endl;
			connected = pjClient.setup(IPAddress, pjPort, true);
			ofLogNotice() << "connection state : " << connected;
           
		}
        ofLogNotice() << "sending command : " << command << endl;
        pjClient.sendRaw(command);
        ofLogNotice() << "Response length (Bytes) : " << pjClient.getNumReceivedBytes() << endl;
        msgRx = "";
        msgRx = pjClient.receiveRaw();
    
        ofLogNotice() << "received response : " << msgRx << endl;
    
        pjClient.close();
    
}


void PJLink::power_On(string IP_add, string pass) {
    setup(IP_add, pass);
	string command = "%1POWR 1\r";
    sendPJLinkCommand(command);
    
    
    
    if(presponce == "%1POWR=ERR3"){
        message = "During shutdown";
        
        timer =true;
    }
    error_view();

}

void PJLink::power_Off(string IP_add, string pass) {
    setup(IP_add, pass);
	string command = "%1POWR 0\r";
	sendPJLinkCommand(command);

    
   
    
    error_view();
}
void PJLink::pjLink_Check(string IP_add, string pass) {
    
   setup(IP_add, pass);
    string command = "%1POWR ?\r";
    sendPJLinkCommand(command);
   
    cout << pjClient.receiveRaw();
    
 
    error_view();
  
}


void PJLink::lamp(string IP_add, string pass){
    setup(IP_add, pass);
    string command = "%1LAMP ?\r";
    sendPJLinkCommand(command);
    
    if(presponce != "error"){
        for(int i =0; i < 7; i++){
            presponce.erase(presponce.begin() + 0);
        }
        
  
        
    }

}

void PJLink::name_Check(string IP_add, string pass){
    setup(IP_add, pass);
    string command = "%1NAME ?\r";
    sendPJLinkCommand(command);
    
    if(presponce != "error"){
        for(int i =0; i < 7; i++){
            presponce.erase(presponce.begin() + 0);
        }
    }


}
void PJLink::shutter_on(string IP_add, string pass){
    setup(IP_add, pass);
    string command = "%1AVMT 10\r";
    sendPJLinkCommand(command);
    

    
    error_view();
}

void PJLink::shutter_off(string IP_add, string pass){
    setup(IP_add, pass);
    string command = "%1AVMT 11\r";
    sendPJLinkCommand(command);
    

    
    error_view();
}

void PJLink::shutter_Check(string IP_add, string pass){
    setup(IP_add, pass);
    string command = "%1AVMT ?\r";
    sendPJLinkCommand(command);
    
    if(presponce != "error"){
        for(int i =0; i < 7; i++){
            presponce.erase(presponce.begin() + 0);
        }
        
    }

}


void PJLink::digital_INPT(string IP_add, string pass){
    setup(IP_add, pass);
    string command = "%1INPT 31\r";
    sendPJLinkCommand(command);
 
    error_view();
}

void PJLink::video_INPT(string IP_add, string pass){
    setup(IP_add, pass);
    string command = "%1INPT 32\r";
    sendPJLinkCommand(command);
    error_view();
}


void PJLink::INPT_Check(string IP_add, string pass){
    setup(IP_add, pass);
    string command = "%1INPT ?\r";
    sendPJLinkCommand(command);
    if(presponce != "error"){
        for(int i =0; i < 7; i++){
            presponce.erase(presponce.begin() + 0);
        }
        
    }


}

void PJLink::error_view(){
  
    if(presponce=="NOT CONEECT" || presponce=="PJLINK ERRA"){
        timer = true;
        message = presponce;
    }
    
    
    if(presponce=="ERR3"){
        timer = true;
        message = presponce;
    }
    
}

bool PJLink::getconnection(){
    return connected;
}
