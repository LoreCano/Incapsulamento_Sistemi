#ifndef FUNZIONI_h
#define FUNZIONI_h

#include<string>

using namespace std;

//Max Lenght: 60B, Min Lenght: 20B
struct Datagram {
	string version; // 4b
	string hlen; // 4b
	string tos; // 1B Type of service
	string tl; //2B Total lenght
	string id; //2B Identification
	string flags; //3b
	string fo; //13b Fragment ofset
	string ttl; //1B Time to live
	string protocol; //1B
	string hc; //2B Header checksum
	string sia; //4B Source Ip address
	string dia; //4B Destination Ip address
	string option; //Variable Length
	//string padding; //Variable Length
	string message; //Variable Length
};

//Max Lenght: 1500B, Min Lenght: 64B
struct Frame {
	string preamble; // 7B
	string sfd; // 1B
	string dst; // 6B
	string src; // 6B
	string type; //2B
	string datagram; // Variable Length
	string fcs; // 4B
};



//funzione per leggere da file
string readFile(string file);

//procedura per scrivere su file
void writeFile(string mess, string file);

//funzione per convertire da char a binario
string charToBin(char c);

//funzione per convertire da stringa a binario
string stringToBin(string s);

//funzione per convertire una sequenza di bit in un intero
int binToInt(string s);

//funzione per convertire un intero in una sequenza di bit
string intToBin(int n, int dim);

//funzione per calcolcolare l'header checksum
string calculateHc(Datagram ip);

//funzione per impostare il datagram
void setDatagram(Datagram & ip);

//funzione per convertire il datagramma in binario
string datagramToBin(Datagram ip);

//funzione per calcolare il CRC
string calculateCRC(Datagram ip);

//funzione per impostare il frame 
void setFrame(Frame & ethernet, string ip);

//funzione per convertire il frame in binario
string frameToBin(Frame ethernet);


#endif
