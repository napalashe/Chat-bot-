// Assignment4.cpp : Chat app
// Copyright (c) Christopher Mireles 12/04/2023
// 
// 
//


#include <iostream>
#include <string>
#include <thread>
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include<iomanip>


#pragma comment(lib,"ws2_32.lib")

using namespace std;

const int PORT_TO_SEND =3514;

void sendMessage(const char* destinationIP) {


    WSAData dataInformation;
    WSAStartup(MAKEWORD(2, 2),&dataInformation);

    cout << "ENTER Q TO QUIT" << endl << endl;
    cout << "CSUF CHATROOM" << endl <<"=============================" << endl;


    while (true) {


        string message;
        cout << "Enter message to send: ";

        getline(cin,message);

        if (message == "q") 
        {
            break;
        }


        sockaddr_in destination;
        destination.sin_family = AF_INET;




        destination.sin_port =htons(PORT_TO_SEND);

        inet_pton(AF_INET,destinationIP,&destination.sin_addr.s_addr);

        SOCKET s =socket(AF_INET, SOCK_DGRAM,IPPROTO_UDP);

        sendto(s,message.c_str(), message.length(), 0,(sockaddr*)&destination, sizeof(destination));


        closesocket(s);
    }

    WSACleanup();
}

int main() {

    const char* destIP = "127.0.0.1";


    sendMessage(destIP);

    return 0;
}