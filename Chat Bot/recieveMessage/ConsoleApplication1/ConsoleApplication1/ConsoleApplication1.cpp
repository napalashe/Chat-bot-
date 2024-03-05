// Assignment4.cpp : Chat app
// Copyright (c) Christopher Mireles 12/04/2023
// 
// 
//
#include<iostream>
#include<string>
#include<iomanip>
#include<thread>
#include<WinSock2.h>
#include<Ws2tcpip.h>

#pragma comment(lib,"ws2_32.lib")

using namespace std;
const int PORT_TO_RECEIVE =3514;



void receiveMessages() {

    WSAData dataInformation;
    WSAStartup(MAKEWORD(2,2),&dataInformation);

    SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    sockaddr_in localAddr;

    localAddr.sin_family = AF_INET;
    localAddr.sin_port =htons(PORT_TO_RECEIVE);

    localAddr.sin_addr.s_addr = INADDR_ANY;



    bind(s, (sockaddr*)&localAddr, sizeof(localAddr));
    //waits for message
    cout <<"CSUF CHATROOM" <<endl;
    cout << "==========================" <<endl << "Waiting...";
    cout <<endl;

    sockaddr_in senderAddr;

    int senderSize = sizeof(senderAddr);

    char receivedBuffer[1024];

    while (true) {

        int bytesReceived = recvfrom(s,receivedBuffer,sizeof(receivedBuffer), 0,(sockaddr*)&senderAddr, &senderSize);

        if (bytesReceived >0) {


            receivedBuffer[bytesReceived] = '\0';


            cout << "Received Message: " << receivedBuffer << endl;

        }
    }

    closesocket(s);
    WSACleanup();
}

int main() {

    receiveMessages();

    return 0;


}