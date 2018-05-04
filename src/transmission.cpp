#include "transmission.h"

Transmission::Transmission() {

    transmittingStatus = false;
    openStatus = false;

    port = "/dev/ttyUSB0";

    openConnection();
}

Transmission::~Transmission(){
//    stopAllRobots(3);
    closeConnection();
}

void Transmission::closeConnection(){
    close(usb);
}

bool Transmission::openConnection(){

    usb = open(port.c_str(), O_RDWR | O_NOCTTY | O_SYNC);

    if (usb == -1 ){
        openStatus = false;

    } else {

        struct termios options;
        memset (&options, 0, sizeof options);

        /* Error Handling */
        if (tcgetattr(usb, &options) != 0 ) {
            //cout << "Error " << errno << " from tcgetattr: " << strerror(errno) << endl;
            openStatus = false;
        } else {
            openStatus = true;
        }

        /* Set Baud Rate */
        cfsetospeed(&options, (speed_t)B19200);
        cfsetispeed(&options, (speed_t)B19200);

        /* Setting other Port Stuff */
        options.c_cflag     &=  ~PARENB;            // Make 8n1
        options.c_cflag     &=  ~CSTOPB;
        options.c_cflag     &=  ~CSIZE;
        options.c_cflag     |=  CS8;
        options.c_cflag     &=  ~CRTSCTS;           // no flow control
        options.c_cc[VMIN]   =  1;                  // read doesn't block
        options.c_cc[VTIME]  =  5;                  // 0.5 seconds read timeout
        options.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

        /* Make raw */
        cfmakeraw(&options);

        /* Flush Port, then applies attributes */
        tcflush(usb, TCIFLUSH);

        if(tcsetattr(usb, TCSANOW, &options) != 0) {
            //cout << "Error " << errno << " from tcsetattr: " << strerror(errno) << endl;
            openStatus = false;
        } else {
            openStatus = true;
        }
    }

    return true;
}

void Transmission::send(int i, Command c){
    string comand = generateMessage(i, c);;
    serialTransmit(comand);
}

// recebe um comando e retorna a string equivalente para ser enviada
string Transmission::generateMessage(int robot, Command comand){

    short int startDelimiter = 0x7E;
    short int frameType = 0x01;
    short int frameId = 0x01;
    short int option = 0x00;

    short int address = robot;
    int lenght = 0xC;

    vector<int> hexMessage = comand.to_hex();

    int checkSum = generateCheckSum(frameType, frameId, address, option, hexMessage);

    // agrupa os parametros formando a mensagem pronta para ser enviada
    stringstream ss;
    ss << std::hex << startDelimiter;
    ss << std::hex << 0x0 << 0x0 << 0x0 << lenght;
    ss << std::hex << 0x0 << frameType;
    ss << std::hex << 0x0 << frameId;
    ss << std::hex << 0x0 << 0x0 << 0x0 << address;
    ss << std::hex << 0x0 << option;

    for(uint i=0 ; i<hexMessage.size() ; i++){
        ss << std::hex << hexMessage[i];
    }
    ss << std::hex << checkSum;

    return ss.str();
}

int Transmission::generateCheckSum(int frameType, int frameId, int address, int option, vector<int> hexMessage){

    char check = frameType + frameId + address + option;
    unsigned char sum = 0;

    for(uint i=0 ; i<hexMessage.size() ; i++){
        sum = sum + (hexMessage[i]);
    }

    int checkSum = check+sum;
    std::string binary = std::bitset<8>(checkSum).to_string();	// Pega os 8 primeiros bits do valor
    unsigned long decimal = std::bitset<8>(binary).to_ulong();	// Volta para decimal
    checkSum = 0xFF-decimal;

    return checkSum;
}

// recebe uma string para enviar
void Transmission::serialTransmit(string comand){
    const long size = comand.size();
    unsigned char sendBytes[size/2];

    // verifica o estado da conexao de 2 em 2 segundos
    /*if(clock() -lastTime > 2000){
        string out = executeCommand("ls " + port + " 2> /dev/null");

        if(out.compare("") == 0) transmittingStatus = false;
        else transmittingStatus = true;

       lastTime = timer.getTime();
    }

    if(!getConnectionStatus()){
        closeConnection();
        openConection();

    } else {*/
        for(uint i=0, cont=0 ; i<comand.size() ; i++){
            stringstream parcial;
            parcial << comand[i];
            i++;
            parcial << comand[i];
            sendBytes[cont] = stoi(parcial.str().c_str(), 0, 16);
            cont++;
        }
//        cout << sendBytes << endl;
        write(usb, sendBytes, sizeof(sendBytes));
    //}
}

bool Transmission::getConnectionStatus(){
    return transmittingStatus && openStatus;
}
