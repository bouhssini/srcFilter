#include "you.h"

void sVersion(Clients& sck,string wr_cmd)
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    string SQL,sV,Pat,St;
    string sBuf;
    bool Bconn=true;

    if (HandleDB()==NULL) Bconn = ConnetMySql();
    if(!Bconn) throw (char*)"ConnetMySql sVersion";

    SQL ="SELECT * FROM pal_version;";
    result = Exec_query(SQL);
    /*
    if (mysql_query(HandleDB(), SQL.data()) != 0)
    {
        cout<<"Error "<<mysql_errno(HandleDB())<<": "<<mysql_error(HandleDB())<<endl;
        CloseDB();
        ConnetMySql();
        if (mysql_query(HandleDB(), SQL.data()) != 0)  throw (char*)"mysql_query (1) sVersion";
    }
    result = mysql_store_result(HandleDB());
    */
    row = mysql_fetch_row(result);
    sV = Row(result,row,"number");
    Pat = Row(result,row,"path");
    mysql_free_result(result);

    St = sV+"|"+Pat+"|"+"localhost:"+itostr(GETPort());
    sBuf =stc(-6)+itc(St.length())+"YB.PALAR"+Trim(wr_cmd)+String(32 - Trim(wr_cmd).length(), ' ');
    sBuf +=St.data();
    SendData(sck.skey,sBuf);
    //CloseDB();
}
void REG_USER(Clients& sck,string txt)
{
    string St,nickname,password,zip,sex,qustion,first,last,email,pays,sBuf,tx,SQL,liste;
    vector<string> arr,arr2;
    MYSQL_RES *result;
    CloseDB();
    ConnetMySql();

    tx = txt;
    tx = ICONV(txt,"CP1256","UTF-8");
    arr=Split(tx,"|");
    for (Uint i=0;i<arr.size();i++)
    {
        arr2 = Split(arr[i],":");
            if (LCASE(arr2[0]) == "nickname") nickname = arr2[1];
        else if(LCASE(arr2[0]) == "password") password = arr2[1];
        else if(LCASE(arr2[0]) == "liste") liste = arr2[1];
        else if(LCASE(arr2[0]) == "qustion") qustion = arr2[1];
        else if(LCASE(arr2[0]) == "first") first = arr2[1];
        else if(LCASE(arr2[0]) == "last") last = arr2[1];
        else if(LCASE(arr2[0]) == "email") email = arr2[1];
        else if(LCASE(arr2[0]) == "sex" || LCASE(arr2[0]) == "rajole") sex = arr2[1];
        else if(LCASE(arr2[0]) == "pays") pays = arr2[1];
    }
    result = Exec_query("SELECT * FROM pal_user WHERE Email ='"+email+"'; ");
    if(mysql_num_rows(result)>0){
        sBuf =stc(-2)+itc(0)+"YB.PALAR"+"deja_email"+String(22, ' ');
        SendData(sck.skey,sBuf);
        sck.sCon = false;
        mysql_free_result(result); result = NULL;
        return;
    }
    mysql_free_result(result); result = NULL;

    if (strtoi(nickname)!=0){
        sBuf =stc(-4)+itc(0)+"YB.PALAR"+"non"+String(29, ' ');
        SendData(sck.skey,sBuf);
        return;
    }

    result = Exec_query("SELECT * FROM pal_user WHERE nickname ='"+nickname+"'; ");
    if(mysql_num_rows(result)>0){
        sBuf =stc(-2)+itc(0)+"YB.PALAR"+"non"+String(29, ' ');
        SendData(sck.skey,sBuf);
        sck.sCon = false;
        mysql_free_result(result); result = NULL;
        return;
    }else{
        mysql_free_result(result); result = NULL;
        SQL = "INSERT INTO pal_user " \
              "(`id`  , `nickname` , `password` , `First` , `Last` , `Email` , `sex` , `Pays` , " \
              "`user_type` , `Qustion_list` , `Qustion` , `Date` , `Group`) VALUES " \
              "(NULL, '"+nickname+"', '"+MD5(password)+"', '"+first+"', '"+last+"', '"+email+"', '"+sex+"', " \
              "'"+pays+"', '1', '"+liste+"', '"+qustion+"', '"+datetime()+"', '3'); ";

        if (mysql_query(HandleDB(), SQL.data()) != 0){
            sBuf =stc(-4)+itc(0)+"YB.PALAR"+"non"+String(29, ' ');
            SendData(sck.skey,sBuf);
        }else{
            nickname = ICONV(nickname,"UTF-8","CP1256");
            password = ICONV(password,"UTF-8","CP1256");
            St = nickname+"|"+password;
            sBuf = stc(-1)+itc(St.length())+"YB.PALAR"+"ok"+String(30, ' ');
            sBuf += St;
            SendData(sck.skey,sBuf);
        }
        mysql_free_result(result); result = NULL;
    }
   CloseDB();
}
