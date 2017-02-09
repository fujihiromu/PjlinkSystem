

#ifndef OFXPJCONTROL_H
#define OFXPJCONTROL_H

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


class PJLink{
public:
	PJLink();
	~PJLink();

    explicit PJLink(const PJLink &PJLink);
    
	//methods
	
	void sendPJLinkCommand(string command); //send any PJLink command to the projector
	void setup(string IP_add, string pass); //default
	void setProjectorType(int protocol); //NEC_MODE or PJLINK_MODE
	void setProjectorIP(string IP_add); //the network IP of the projector
    void setProjectorPassword(string pass); //password for PJLink authentication
		void setProjectorPort(int port); //the network port of the projector
	void sendCommand(string command); //send any string command to the projector without password authentication
    string presponce;
    

	void power_On(string IP_add, string pass);
	void power_Off(string IP_add, string pass);
    
    bool getconnection();

   
    void shutter_on(string IP_add, string pass);
    void shutter_off(string IP_add, string pass);
    void pjLink_Check(string IP_add, string pass);
    void shutter_Check(string IP_add, string pass);
    
    void lamp(string IP_add, string pass);
    void name_Check(string IP_add, string pass);
    
    void INPT_Check(string IP_add, string pass);
    void digital_INPT(string IP_add, string pass);
    void video_INPT(string IP_add, string pass);
    void error_view();

	
    
private:
    
	ofxTCPClient pjClient;
    
    
	string IPAddress;
    string password;
	int pjPort;
	int commMode;
	string msgRx;
	bool connected;

    bool timer;
    string message;
    


};

#endif

