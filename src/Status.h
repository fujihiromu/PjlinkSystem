#include "ofMain.h"
#include "ofxNetwork.h"
#include "Poco/MD5Engine.h"
#include "Poco/DigestStream.h"
#include "Poco/StreamCopier.h"

using Poco::DigestEngine;
using Poco::MD5Engine;
using Poco::DigestOutputStream;
using Poco::StreamCopier;

const int NEC_PORT = 7142; //NEC projector port
const int PJLINK_PORT = 4352; //PJLink projector protocol port
const int CHRISTIE_PORT = 3002; //CHRISTIE projector protocol port
const int SANYO_PORT = 100; //SANYO projector protocol port
const int PJDESIGN_PORT = 1025; //Projectino Design projector protocol port

const int PJLINK_MODE = 0;
const int NEC_MODE = 1;
const int CHRISTIE_MODE = 2;
const int SANYO_MODE = 3;
const int PJDESIGN_MODE = 4;

class Status{
public:
    Status(){};
    Status(string address,string pass);
  
   // Status(ofxTCPClient &pjClient):pjClient(pjClient){};
    
    string IP;
    string password;
    string Name;
    string lamptime;
    string INPT;
    
    bool Power;
    bool Shutter;
    
    
    
    
    void sendPJLinkCommand(string command); //send any PJLink command to the projector
    void setup(string IP_add, string pass); //default
    void setProjectorType(int protocol); //NEC_MODE or PJLINK_MODE
    void setProjectorIP(string IP_add); //the network IP of the projector
    void setProjectorPassword(string pass); //password for PJLink authentication
    void setProjectorPort(int port); //the network port of the projector
    void sendCommand(string command); //send any string command to the projector without password authentication
    string presponce;
    
    
    void power_On();
    void power_Off();
    
    bool getconnection();
    
    
    void shutter_on();
    void shutter_off();
    void pjLink_Check();
    void shutter_Check();
    
    void lamp();
    void name_Check();
    void INPT_Check();
    void digital_INPT();
    void video_INPT();
    void error_view();
    
    void schedule_command(int mode);
    
  //  ofxTCPClient pjClient;
    ofxTCPClient *pjClient = new ofxTCPClient;
  

    int pjPort;
    int commMode;
    string msgRx;
    bool connected;
    
    bool timer;
    string message;
    

   
};
