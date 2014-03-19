#include "you.h"

int FindClientNickname(const string Nickname)
{
    for (Uint i=0;i<ListClients().size();i++)
      if (ListClients(i).nickname==Nickname) return i;

    return -1;
}
int FindClient(const string key)
{
    for (Uint i=0;i<ListClients().size();i++)
      if (ListClients(i).skey==key) return i;

    return -1;
}
int FindClientUser(int id)
{
    for (Uint i=0;i<ListClients().size();i++)
      if (ListClients(i).UserID==id) return i;

    return -1;
}
void CloseSocket(Clients& sck)
{
    //sembuf op;op.sem_num =0;op.sem_flg =0;
    /*_________________________sem______________________________*/
    //op.sem_op = -1;semop(sem_ID(),&op,1);
    /*__________________________________________________________*/
    int index;
    index = FindClient(sck.skey);if (index == -1) return;

    if (sck.sNet != AF_LOCAL)
            CloseConnexion(sck.skey);
    else
        close(sck.id);
    /*_________________________sem______________________________*/
    //op.sem_op = 1;semop(sem_ID(),&op,1);
    /*__________________________________________________________*/
}
void SendData(const string key,string by)
{
    /*aa:
    if (WaitClient())
    {
        usleep(100);
        goto aa;
    }*/
    int i = FindClient(key);
    if (i != -1)
    {
        if (ListClients(i).state == 7)
        {
            int ln;
            ln=send(ListClients(i).id,by.data(),by.length(),0);
            if (ln <= 0) ListClients(i).state=9;
        }
    }
}
void ReadData(const string key,string by)
{
    /*aa:
    if (WaitClient())
    {
        usleep(200);
        goto aa;
    }*/
    int i = FindClient(key);
    if (i != -1)
    {
        if (ListClients(i).state == 7)
        {
            Protocole_BYF(ListClients(i),by);
        }
    }
}
void ReadDataLocal(Clients& sck,string by)
{
    /*aa:
    if (WaitClient())
    {
        usleep(200);
        goto aa;
    }*/
    if (sck.state == 7)
    {
        Protocole_BYF(sck,by);
    }
}
void connectsocket(Clients& arg)
{
    Clients new_socket ;
    new_socket = arg;
    pthread_detach(pthread_self());

    sembuf op;op.sem_num = 0;op.sem_flg =0;

    if (new_socket.sNet == AF_INET)
    {
        int i=FindClient(new_socket.skey);
        if (i!=-1) new_socket=ListClients(i);
    }
    char buffer[bufsize];
    int n;
    string by;
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    do
    {
        memset(&buffer,'\0',sizeof(buffer));
        n=recv(new_socket.id,buffer,bufsize,0);

        if (n>0)
        {
            /*_________________________sem______________________________*/
            op.sem_op = -1; semop(sem_ID(),&op,1);
            /*__________________________________________________________*/
            by.clear();
            by.append(buffer,n);
            if (new_socket.sNet == AF_INET){
                ReadData(new_socket.skey,by);
                if (new_socket.state!=7) {op.sem_op = 1; semop(sem_ID(),&op,1);goto fin;}
            }else{
                ReadDataLocal(new_socket,by);
            }
            /*__________________________sem_____________________________*/
            op.sem_op = 1; semop(sem_ID(),&op,1);
            /*__________________________________________________________*/
        }
        if (n<0)
        {
            break;
        }
        pthread_testcancel();
        usleep(100);
    }while(!(n==0));
    fin:
    close(new_socket.id);new_socket.id=-1;
    CloseSocket(new_socket);
    pthread_exit(NULL);
}
void LisnServer(int Port)
{
    int create_socket,new_socket,addrlen;
    struct sockaddr_in address;
    socklen_t scklen;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(Port);
    sembuf op;op.sem_num =0;op.sem_flg =0;

    create_socket = socket(AF_INET,SOCK_STREAM,0);
    if (bind(create_socket,(struct sockaddr *)&address,sizeof(address)) < 0)
    {
                 perror("error listen\n");
                 exit(-1);
    }

    if (listen(create_socket,0)==0)  cout<<"Listen :"<<Port<<endl;
    addrlen = sizeof(struct sockaddr_in);

     while(1)
     {
             scklen = addrlen;
             new_socket = accept(create_socket,(struct sockaddr *)&address,&scklen);
             /*_________________________sem______________________________*/
             op.sem_op = -1;semop(sem_ID(),&op,1);
             /*__________________________________________________________*/
             if (new_socket > -1)
             {
               /*if (WaitClient())
                 {
                     close(new_socket);
                 }else{*/
                     pthread_t Begin_th;
                     Clients opj;
                     opj.sThead = (int)Begin_th;
                     opj.id = new_socket;
                     opj.addressIP = inet_ntoa(address.sin_addr);
                     opj.sPort = address.sin_port;
                     opj.skey = opj.addressIP+":"+itostr(opj.sPort);
                     opj.state = 7;
                     opj.sNet = PF_INET;
                     opj.RemoteIP = "0.0.0.0";
                     opj.RemotePort = Port;
                     ListClientsAdd(opj);
                     usleep(100);
                     if (pthread_create(&Begin_th, NULL,(void*(*)(void*))&connectsocket,&opj))
                     {
                          perror("pthread_create");
                          exit(EXIT_FAILURE);
                     }
               /*}*/
             }else{
                 close(new_socket);
             }
             /*_________________________sem______________________________*/
             op.sem_op = 1;semop(sem_ID(),&op,1);
             /*__________________________________________________________*/
         }
    close(create_socket);
}
void ConnectLocal(string PATH,string DATA)
{
    int connfd;
    struct sockaddr_un	servaddr;

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family = AF_LOCAL;
    strcpy(servaddr.sun_path, PATH.data());

    if ((connfd = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0)
    {
        cerr<<"Error Socket Local : "<<PATH<<endl;
        return;
    }
    usleep(100);
    if (connect(connfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
    {
        cerr<<"Error Connect Local : "<<PATH<<endl;
        return;
    }
    usleep(100);
    if(send(connfd,DATA.data(),DATA.length(),0)<=0)
        if (connect(connfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
        {
            cerr<<"Error Send Local : "<<PATH<<endl;
            return;
        }

    if (close(connfd) != 0)
    {
        cerr<<"Error close Local : "<<PATH<<endl;
        return;
    }
}
void StartLocal(char *p)
{
    pthread_t Begin_th;
    if (pthread_create(&Begin_th, NULL,(void*(*)(void*))&ListenLocal,(char*)p))
    {
            perror("pthread_create");
            exit(EXIT_FAILURE);
    }
}
void ListenLocal(char *arg)
{
    string PATH;
    PATH = arg;

    int listenfd, connfd;
    struct sockaddr_un	servaddr;
    pthread_detach(pthread_self());

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family = AF_LOCAL;
    strcpy(servaddr.sun_path, PATH.data());

    unlink(PATH.data());

    if ((listenfd = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0) errx(1, "parent: socket error: %d", errno);
    if (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) errx(1, "parent: bind error: %d", errno);
    if (listen(listenfd, 1024) < 0) errx(1, "parent: listen error: %d", errno);

    while(1)
    {
        if ((connfd = accept(listenfd, (struct sockaddr *) NULL, NULL)) < 0)  errx(1, "parent: accept error: %d", errno);
        pthread_t Begin_th;
        Clients opj;
        opj.sThead = (int)Begin_th;
        opj.id = connfd;
        opj.sPort = 0;
        opj.state = 7;
        opj.sNet = PF_LOCAL;
        opj.sPath = PATH;
        opj.RemotePort = 0;
        //ListClientsAdd(opj);
        
        if (pthread_create(&Begin_th, 0,(void*(*)(void*))&connectsocket,&opj))
        {
                perror("pthread_create");
                exit(EXIT_FAILURE);
        }
    }
    close(listenfd);
    pthread_exit(NULL);
}
bool TestListen(int Port)
{
        int create_socket;
        struct sockaddr_in address;

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(Port);

        create_socket = socket(AF_INET,SOCK_STREAM,0);
        if (bind(create_socket,(struct sockaddr *)&address,sizeof(address)) < 0)
        {
            close(create_socket);
            return true;
        }
        close(create_socket);
        return false;
}
