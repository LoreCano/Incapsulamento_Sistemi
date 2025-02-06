
#include<iostream>
#include<string>
#include<fstream>
#include "funzioni.h"

using namespace std;

//funzione per leggere da file
string readFile(string file){

    //dichiaro la variabile mess che conterrà il messaggio
	string mess;

    //apro e controllo il canale di comunicazione con il file
	ifstream fin (file);
	if(!fin){
		cerr<<"Errore nell'apertura del file\n";
		exit(1);
	}

    //prendo in input la riga del file la salvo nella variabile mess
	getline(fin, mess);

    //chiudo il canale di comunicazione
	fin.close();
	
    //restituisco la riga presa in input
    return mess;
}


//procedura per scrivere su file
void writeFile(string mess, string file){

    //apro e controllo il canale di comunicazione con il file
	ofstream fout (file);
	if(!fout){
		cerr<<"Errore nell'apertura del file\n";
		exit(1);
	}

    //stampo nel file la stringa mess
	fout<<mess;

    //chiudo il canale di comunicazione
    fout.close();
}


//funzione per convertire da char a binario
string charToBin(char c){
    
    //dichiaro e inizializzo la variabile bin che conterra' la sequenza binaria
	string bin = "";

    //dichiaro la variabile ris che conterrà ogni volta il singolo bit
	int ris;

    //utilizzando le operazioni di modulo, divisione e concatenazione tra stringhe contruisco la sequenza binaria
	for(int i = 0; i < 8; i++){
		ris = c%2;
		bin = char (ris + '0') + bin;
		c/=2;
	}

    //restituisco la sequenza binaria
	return bin;
}


//funzione per convertire da stringa a binario
string stringToBin(string s){

    //dichiaro e inizializzo la variabile bin che conterra' la sequenza binaria
	string bin = "";

    //scorro tutta la stringa, converto in binario carattere per carattere e concateno le sequenze binarie nella variabile bin
	for(int i = 0; i < s.size(); i++){
		bin += charToBin(s[i]);
	}

    //restituisco la sequenza binaria corrispondente all'intera stringa
	return bin;
}


//funzione per convertire una sequenza di bit in un intero
int binToInt(string s){

    //dichiaro e inizializzo la variabile num che conterra' il numero finale
    int num = 0;

    //moltiplico ogni carattere della stringa per la potenza di due che corrisponde alla sua posizione e la sommo a num
    for(int i = 0; i < s.size(); i++){
        num += (int(s[i]-'0') << (s.size()-i-1));
    }

    //restituisco il numero finale
    return num;
}


//funzione per convertire un intero in una sequenza di bit 
string intToBin(int n, int dim){

    //dichiaro e inizializzo le variabili bin(stringa binaria) e zero(0 da aggiungere per raggiungere la lunghezza dim) 
    string bin = "", zero = "";

    //tramite lo stesso principio usato in precedenza converto il numero in binario e lo salvo in bin
    while(n != 0){
        bin += char(n%2 +'0');
        n /= 2;
        dim--;
    }

    //salvo in zero il numero di 0 che andranno posti a sinistra di bin per ottenere la lunghezza della sequenza binaria richiesta
    while(dim > 0){
        zero += '0';
        dim--;
    }

    //restituisco la conversione in binario del numero su dim bit
    return zero + bin;
}


//funzione per calcolcolare l'header checksum
string calculateHc(Datagram ip) {

    //dichiaro e inizializzo la variabile sum
    unsigned long sum = 0;

    //sommo tutti i campi dell'header IP (non considero header checksum perche' settato a 0)
    sum = binToInt(ip.version) + 
          binToInt(ip.hlen) + 
          binToInt(ip.tos) + 
          binToInt(ip.tl) + 
          binToInt(ip.id) + 
          binToInt(ip.flags) + 
          binToInt(ip.fo) + 
          binToInt(ip.ttl) + 
          binToInt(ip.protocol) + 
          binToInt(ip.sia.substr(0, 16)) + binToInt(ip.sia.substr(16, 16)) + 
          binToInt(ip.dia.substr(0, 16)) + binToInt(ip.dia.substr(16, 16));

    //correggo l'overflow a 16 bit
    while (sum > 0xFFFF) {
        sum = (sum & 0xFFFF) + (sum >> 16);
    }

    //restituisco il complemento a 1 di sum su 16 bit
    return intToBin(~sum & 0xFFFF, 16);
}


//funzione per definire il type of service
string getTos(){

    //dichiaro e inizializzo le variabili tos, prec e scelta
    string tos = "";
    int prec;
    char scelta;

    cout<<"Set Type Of Service:\n\n";

    //prendo in input il numero di precedenza
    do{
        cout<<"Select a precedence writing a number between 0 and 7: ";
        cin>>prec;
        if(prec < 0 || prec > 7){
            cerr<<"Wrong number\n";
        }
    }while(prec < 0 || prec > 7);
    
    //concateno il binario del numero a tos
    tos += intToBin(prec, 3);
    
    //setto il flag delay
    do{
        cout<<"Do you want to set the delay flag? (y/n): ";
        cin>>scelta;
        if(scelta != 'y' && scelta != 'n' && scelta != 'N' && scelta != 'Y'){
            cerr<<"Wrong choise\n";
        }
    }while(scelta != 'y' && scelta != 'n' && scelta != 'N' && scelta != 'Y');
    
    //in base alla scelta concateno 1 o 0 a tos
    if(scelta == 'y' || scelta == 'Y') tos += '1';
    if(scelta == 'n' || scelta == 'N') tos += '0';
    
    //setto il flag troughput
    do{
        cout<<"Do you want to set the troughput flag? (y/n): ";
        cin>>scelta;
        if(scelta != 'y' && scelta != 'n' && scelta != 'N' && scelta != 'Y'){
            cerr<<"Wrong choise\n";
        }
    }while(scelta != 'y' && scelta != 'n' && scelta != 'N' && scelta != 'Y');
    
    //in base alla scelta concateno 1 o 0 a tos
    if(scelta == 'y' || scelta == 'Y') tos += '1';
    if(scelta == 'n' || scelta == 'N') tos += '0';
    
    //setto il flag reliability
    do{
        cout<<"Do you want to set the reliability flag? (y/n): ";
        cin>>scelta;
        if(scelta != 'y' && scelta != 'n' && scelta != 'N' && scelta != 'Y'){
            cerr<<"Wrong choise\n";
        }
    }while(scelta != 'y' && scelta != 'n' && scelta != 'N' && scelta != 'Y');
    
    //in base alla scelta concateno 1 o 0 a tos
    if(scelta == 'y' || scelta == 'Y') tos += '1';
    if(scelta == 'n' || scelta == 'N') tos += '0';
    
    //setto il flag monetary cost
    do{
        cout<<"Do you want to set the monetary cost flag? (y/n): ";
        cin>>scelta;
        if(scelta != 'y' && scelta != 'n' && scelta != 'N' && scelta != 'Y'){
            cerr<<"Wrong choise\n";
        }
    }while(scelta != 'y' && scelta != 'n' && scelta != 'N' && scelta != 'Y');
    
    //in base alla scelta concateno 1 o 0 a tos
    if(scelta == 'y' || scelta == 'Y') tos += '1';
    if(scelta == 'n' || scelta == 'N') tos += '0';
    
    //concateno 0 a tos perche' l'ultimo bit e' inutilizzato
    tos += '0';
    
    //restituisco la stringa binaria di type of service
    return tos;
}

//funzione per impostare il datagram
void setDatagram(Datagram &  ip){
    
    //apro e controllo il canale di comunicazione con il file di configurazione
    ifstream fin("configuration.txt");
    if (!fin) {
        cerr << "Errore nell'apertura del file di configurazione\n";
        exit(1);
    }
    
    //dichiaro le variabili str(riga del file), bin(stringa binaria) e field(nome del campo)
    string str, bin , field ;

    //dichiaro una variabile booleana
    bool boolean ;
    
    //prendo in input tutte le righe del file
    while(getline(fin, str)){

        //pulisco le variabili boolean field e bin
        boolean = 0;
        field = "";
        bin = "";

        //per ogni riga separo il nome del campo dalla corrispettiva stringa binaria tramite il separatore(:)
        for(int j = 0; j < str.size(); j++){

            if(str[j] == ':'){
                boolean = 1;
                j++;
            }

            if(!boolean){
                field += str[j];
            } else {
                if(str[j] != '\r' && str[j] != '\n'){
                    bin += str[j];
                }
            }
        }
        
        //in base a com'è field riempo il campo della struct corrispondente
        if (field == "version") ip.version = bin;
        else if (field == "hlen") ip.hlen = bin;
        else if (field == "tl") ip.tl = bin;
        else if (field == "id") ip.id = bin;
        else if (field == "flags") ip.flags = bin;
        else if (field == "fo") ip.fo = bin;
        else if (field == "ttl") ip.ttl = bin;
        else if (field == "protocol") ip.protocol = bin;
        else if (field == "sia") ip.sia = bin;
        else if (field == "dia") ip.dia = bin;             
    }
    
    //riempio i restanti campi della struct che non posso riempire con il file di configurazione
    ip.tos = getTos();
    ip.hc = calculateHc(ip);
    ip.message = stringToBin(readFile("msg.txt"));

    //chiudo il canale di comunicazione
    fin.close();
}

//funzione per convertire il datagramma in binario
string datagramToBin(Datagram ip){

    //dichiaro e inizializzo la variabile str
    string str = "";

    //concateno a str tutti i campi della struct
    str = ip.version + 
          ip.hlen + 
          ip.tos + 
          ip.tl + 
          ip.id + 
          ip.flags + 
          ip.fo + 
          ip.ttl + 
          ip.protocol + 
          ip.hc + 
          ip.sia + 
          ip.dia +
          ip.message;

    //restituisco la stringa binaria del datagramma
    return str;
}