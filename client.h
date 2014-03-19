#ifndef CLIENT_H
#define CLIENT_H
#include <iostream>
using namespace std;

class Clients
{
public:
        int id;

        int sThead;
        bool sWait;    //خاص بالبروتوكول
        bool sCon;     //خاص بالبروتوكول
        int UserID;
        int state;
        int sNet;
        int sPort;
        int RemotePort;
        string skey;
        string sPath;
        string RemoteIP;
        string addressIP;
        string nickname;
        string sByte;
        //string sByte;     //خاص بالبروتوكول

        Clients();

        //friend std::ostream& operator << (Clients& p,Clients& s);
        Clients& operator << (Clients& s);
        Clients& operator + (string byte);
};

#endif // CLIENT_H
