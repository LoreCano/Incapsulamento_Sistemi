#include<iostream>
#include<fstream>
#include<string>
#include "funzioni.h"

using namespace std;

int main(){
    
    //inizializzo la struct Datagram presente in funzioni.h
    Datagram ip;

    Frame ethernet;
    
    //riempio tutti i campi della struct Datagram
    setDatagram(ip);

    //riempo tutti i campi della struct Frame
    setFrame(ethernet, datagramToBin(ip));
	
    //scrivo tutto il frame in binario nel file frame.txt
    writeFile(frameToBin(ethernet), "frame.txt");
    
    cout<<ethernet.sfd;

	return 0;
}
