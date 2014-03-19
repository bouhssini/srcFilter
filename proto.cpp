#include "you.h"

void Protocole_BYF(Clients& sck,string txt)
{
    unsigned int MyLn = 46;
    unsigned int id_len = 0;

    string Buut,St;
    St = txt;
    int ln = sck.sByte.length();
    dub:
    if (sck.sWait == false)
    {
        if (St.length() < MyLn){
            sck.sWait = true;
            sck.sByte = St;
            return;
        }else if(St.length() == MyLn){
            sck.sByte = St;
            goto aa;
        }else{
            sck.sWait = true;
            sck.sByte = St;
            goto aa;
        }
    }else{
        sck.sByte.append(St.data(),St.length());
        if (sck.sByte.length() < MyLn) return;
    }
    aa:
    string My;

    My = sck.sByte.substr(0,MyLn);
    if (My.substr(6,8)!=("YB.PALAR"))
    {
        sck.sWait = false;
        sck.sByte.clear();
        sck.state = 9;        
        CloseSocket(sck);
        return;
    }
    id_len = cti((unsigned char*)My.substr(2,4).data());
    if (id_len > 0)
    {
        if (sck.sByte.length() < (id_len+MyLn))
            sck.sWait = true;
        else
            sck.sWait = false;
    }else{
        sck.sWait = false;
    }

    if(sck.sWait) return;
    Buut = sck.sByte.substr(MyLn,sck.sByte.length()-MyLn);
    Buut = Buut.substr(0,id_len);
    sck.sByte = sck.sByte.substr(id_len+MyLn);
    ln=sck.sByte.length();
    ExtractCmd(My, Buut, sck);
    if (sck.sByte.length() != 0)
    {
        St = sck.sByte;
        sck.sByte.clear();
        sck.sWait = true;
        goto dub;
    }
}
void ExtractCmd(string My, string txt,Clients& sck)
{
    int ID=0,id_len=0;
    string w_sing,wr_cmd;

    //sck.sCon=true;
    ID = cts((unsigned char*)My.substr(0,2).data());
    id_len = cti((unsigned char*)My.substr(2,4).data());
    w_sing = Trim((char*)My.substr(6,8).data());
    wr_cmd = Trim((char*)My.substr(14,46).data());
    try{
       switch(ID)
       {
       case -3:     /*معرفة الاصدارة البرنامج*/
           sck.sCon=true;
           sVersion(sck,wr_cmd);
           break;
       case -1:     /*التسجيل*/
           sck.sCon=true;
           REG_USER(sck,txt);
           break;
       default:
           break;
       }

   }catch(char* str){
       cerr<<"Error : "<<str<<endl;
   }

}
void CloseConnexion(string ky)
{
    ListClients(FindClient(ky)).sByte.clear();
    ListClients(FindClient(ky)).UserID = 0;
    ListClients(FindClient(ky)).nickname.clear();
    ListClients(FindClient(ky)).sCon = false;
    ListClients(FindClient(ky)).state = 0;
    close(ListClients(FindClient(ky)).id);ListClients(FindClient(ky)).id=-1;
}
