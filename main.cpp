/********************************************************************
*
*   AUTORI: Canocchi, Polini, Falzetta
********************************************************************/

#include<iostream>
#include<fstream>
#include<string>
#include "funzioni.h"

using namespace std;

int main(){
    
    //inizializzo la struct Datagram presente in funzioni.h
    Datagram ip;

    //riempio tutti i campi della struct
    setDatagram( ip);

    //scrivo tutto il datagramma in binario nel file frame.txt
    writeFile(datagramToBin(ip), "frame.txt");

	return 0;
}
