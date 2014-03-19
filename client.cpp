#include "client.h"

Clients::Clients()
{
    id = -1;
    skey.clear();
    sThead = 0;
    sWait = false;
    sCon = false;
    state = -1;
    sNet = 0;
    sPort = 0;
    RemotePort = 0;
    sPath.clear();
    RemoteIP.clear();
    addressIP.clear();
    nickname.clear();
    sByte.clear();
    UserID = -1;
}
Clients& Clients::operator +(string byte)
{
    sByte += byte;
    return *this;
}
Clients& Clients::operator << (Clients& s)
{
    id = s.id;

    sThead = s.sThead;
    sWait = s.sWait;
    sCon = s.sCon;
    state = s.state;
    sNet = s.sNet;
    sPort = s.sPort;
    RemotePort = s.RemotePort;
    skey = s.skey;
    sPath = s.sPath;
    RemoteIP = s.RemoteIP;
    addressIP = s.addressIP;
    sByte = s.sByte;
    UserID = s.UserID;
    nickname = s.nickname;
    return *this;
}
