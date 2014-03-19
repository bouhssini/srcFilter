//INCPATH  = `mysql_config --cflags`  LIBS = $(SUBLIBS)  -lsqlite3 `mysql_config --libs`
#include "you.h"
#include <stdio.h>
#define ID 125

string db_conf;

int main(int argc, char *argv[])
{    
/**/
    string exe,path,ss;
    exe = Split(argv[0],"/")[Split(argv[0],"/").size()-1];
    path  = Split(EXEC("pwd 2>/dev/null"),"\n")[0];


    key_t KEY;
    ss = path+"/"+exe;
    KEY = ftok(ss.c_str(),ID);

    int semID=0;

    semID = semget(KEY,1,IPC_EXCL | 0600);
    if (semID != -1) semctl(semID, 0, IPC_RMID, 0);
    semID = semget(KEY,1,IPC_CREAT | IPC_EXCL | 0600);
    semctl(semID,0,SETVAL,1);

    sem_ID(semID);

    int Port,Port2;


    Port = (argc > 1)?atoi(argv[1]):5001;
    Port2 = (argc > 2)?atoi(argv[2]):10000;
    db_conf = (argc > 3)?argv[3]:"/etc/palarabic.conf";

    if (TestListen(Port))
    {
        perror("Port Deja Open");
        exit(-1);
    }



    if (TestListen(Port2))
    {
        perror("Port2 Deja Open");
    }
    GETPort(Port2);

    if (!ConnetMySql()){ cerr<<"Error Config MySQl"<<endl;exit(-1);}

    starttimer(30);

    usleep(1000);

    LisnServer(Port);

    semctl(semID, 0, IPC_RMID, 0);
    return 0;
}
