#include "you.h"
bool waitSocket;
int semID;
int sPORT;

vector<Clients> ListClient;

int sem_ID()
{
    return semID;
}
void sem_ID(int b)
{
    semID = b;
}

int GETPort()
{
    return sPORT;
}
void GETPort(int b)
{
    sPORT = b;
}

vector<Clients>& ListClients()
{
    return ListClient;
}
Clients& ListClients(int i)
{
    return ListClient[i];
}
void ListClientsRomove(int i)
{
    ListClient.erase(ListClient.begin()+i);
}
void ListClientsAdd(Clients& cl)
{
    ListClient.push_back(cl);
}
bool WaitClient()
{
    return waitSocket;
}
void WaitClient(bool b)
{
    waitSocket = b;
}
