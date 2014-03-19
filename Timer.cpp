#include "you.h"
void starttimer(int tm)
{
    pthread_t Begin_th;
    if (pthread_create(&Begin_th, NULL,(void*(*)(void*))&timetread,(int*)tm))
    {
            perror("pthread_create");
            exit(EXIT_FAILURE);
    }
}
void timetread(int arg)
{
    pthread_detach(pthread_self());

    int tm=arg;//(int)arg;
    while(1)
    {      
        usleep(1000000*tm);
        timeout();
    }
    pthread_exit(NULL);
}
void timeout()
{
    sembuf op;op.sem_num =0;op.sem_flg =0;
    /*_________________________sem______________________________*/
    op.sem_op = -1;semop(sem_ID(),&op,1);
    /*__________________________________________________________*/
    CloseDB();
    ConnetMySql();
    //WaitClient(true);
    aa:
    for (Uint i=0;i<ListClients().size();i++)
    {
      if (ListClients(i).state != 7)
      {
          CloseConnexion(ListClients(i).skey);
          ListClientsRomove(i);
          goto aa;
      }
    }

    bb:
    for (Uint i=0;i<ListClients().size();i++)
    {
      if (ListClients(i).sCon == false && ListClients(i).sNet == PF_INET)
      {
          CloseConnexion(ListClients(i).skey);
          ListClientsRomove(i);
          goto bb;
      }
    }
    //WaitClient(false);
    /*_________________________sem______________________________*/
    op.sem_op = 1;semop(sem_ID(),&op,1);
    /*__________________________________________________________*/
}
