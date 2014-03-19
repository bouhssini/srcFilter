#ifndef YOU_H
#define YOU_H
#include "TitreCmd.h"

extern string db_conf;

//typedef basic_string<unsigned char> ByteArry;
typedef unsigned int Uint;

const int bufsize = 8192;
extern short cts(unsigned char * ch);
extern int cti(unsigned char * ch);
extern string stc(short i);
extern string itc(int i);
extern string convertInt(int value);
extern string itostr(int value);
extern int strtoi(string s);

extern string Replace(string txt,string str,string chstr);
extern string Trim(string txt);
extern string String(int Ln,char c);
extern string ICONV(string txt,const char fromcode[],const char tocode[]);
extern vector<string> Split(string txt,string str);
extern string UCASE(string txt);
extern string LCASE(string txt);
extern string MD5(string txt);

extern void ConnectSQLite();

extern void CloseDB();
extern bool ConnetMySql();
extern string Row(MYSQL_RES *result,MYSQL_ROW row ,string name);
extern bool ExistTable(string tb);
extern void CreateTables();
extern MYSQL_RES * Exec_query(string SQL);
extern MYSQL_RES *Find_query(string table,string arg);
extern MYSQL * HandleDB();
extern void HandleDB(MYSQL *hlDB);

extern void Protocole_BYF(Clients& sck,string txt);
extern void ExtractCmd(string My, string txt,Clients& sck);
extern void CloseConnexion(string ky);

extern bool WaitClient();
extern void WaitClient(bool b);

extern void sem_ID(int b);
extern int sem_ID();
extern void GETPort(int b);
extern int GETPort();

extern vector<Clients>& ListClients();
extern Clients& ListClients(int i);
extern void ListClientsRomove(int i);
extern void ListClientsAdd(Clients& cl);

extern int FindClient(const string key);
extern int FindClientUser(int id);
extern int FindClientNickname(const string Nickname);

extern void starttimer(int tm);
extern void timetread(int arg);
extern void timeout();

extern void StartLocal(char *p);
extern void ListenLocal(char *arg);

extern void ReadDataLocal(Clients& sck,string by);
extern void ReadData(const string key,string by);
extern void SendData(const string key,string by);
extern void CloseSocket(Clients& sck);
extern void connectsocket(Clients& arg);
extern void LisnServer(int Port);
extern void ConnectLocal(string PATH,string DATA);
extern bool TestListen(int Port);

/* Function File */
extern bool ExistsFile(string filename);
extern string ReadAllFile(string filename);
extern void WriteFile(string filename,string txt);
/* Exec File */
extern string EXEC(string path);
/* Function DateTime */
extern string datetime();
extern int Year(const char *date);
extern int Month(const char *date);
extern int Day(const char *date);
extern int Hour(const char *date);
extern int Minute(const char *date);
extern int Second(const char *date);
extern int DateDiff(const char * str1,const char * str2,const char Format);
extern time_t ChangeStrToTime(const char * str1);

#endif // YOU_H
