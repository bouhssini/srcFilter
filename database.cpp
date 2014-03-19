#include "you.h"

MYSQL *conn;
sqlite3 *condb3;

MYSQL *HandleDB()
 {
     return conn;
 }
void HandleDB(MYSQL *hlDB)
 {
     conn = hlDB;
 }
void CloseDB()
{
    mysql_close(conn);
    conn = NULL;
}
MYSQL_RES *Exec_query(string SQL)
{
    MYSQL_RES *result;
    string sqlerr;
    sqlerr = " Error Exec_query: "+SQL;
    if (mysql_query(HandleDB(), SQL.data()) != 0) throw (char*)sqlerr.c_str();
    result = mysql_store_result(HandleDB());
    return result;
}
MYSQL_RES *Find_query(string table,string arg)
{
    MYSQL_RES *result;
    string SQL,sqlerr;
    SQL = "SELECT * FROM `"+table+"` WHERE "+arg+";";
    sqlerr = " Error Find_query: "+SQL;
    if (mysql_query(HandleDB(), SQL.data()) != 0) throw (char*)sqlerr.c_str();
    result = mysql_store_result(HandleDB());
    return result;
}
bool ConnetMySql()
 {
     string Host,Login,Password,db,St,filename,ty;
     unsigned int Port=0;
     filename = db_conf;//"/etc/palarabic.conf";

     if(ExistsFile(filename)){
         vector<string> arr,arr2;
         St = ReadAllFile(filename);
         arr = Split(St,"\n");
         if ((int)arr[0].find("File Config DataBase (Bouhssini)")== -1) goto aa;
         for (Uint i=2;i<arr.size();i++)
         {
             arr2 = Split(arr[i],"=");
                  if ((int)LCASE(arr2[0]).find("host")!=-1) Host = Trim(arr2[1]);
             else if ((int)LCASE(arr2[0]).find("port")!=-1) Port = atoi(Trim(arr2[1]).c_str());
             else if ((int)LCASE(arr2[0]).find("login")!=-1) Login = Trim(arr2[1]).c_str();
             else if ((int)LCASE(arr2[0]).find("password")!=-1) Password = Trim(arr2[1]).c_str();
             else if ((int)LCASE(arr2[0]).find("db")!=-1) db = Trim(arr2[1]).c_str();
             else if ((int)LCASE(arr2[0]).find("type")!=-1) ty = Trim(arr2[1]).c_str();
         }
         if (LCASE(ty)!="mysql") goto Err;
     }else{
         Host     = "localhost";
         Port     = 3306;
         Login    = "root";
         Password = "123456";
         db       = "maahad_hakiba";
         ty       = "MySQL" ;

         WriteFile(filename,"##  File Config DataBase (Bouhssini) ##\n");
         WriteFile(filename,"#######################################\n");
         WriteFile(filename,"\n");
         WriteFile(filename,"Host       = "+Host+"\n");
         WriteFile(filename,"Port       = "+convertInt(Port)+"\n");
         WriteFile(filename,"Login      = "+Login+"\n");
         WriteFile(filename,"Password   = "+Password+"\n");
         WriteFile(filename,"DB         = "+db+"\n");
         WriteFile(filename,"Type       = "+ty+"\n");
     }
     aa:
     conn = mysql_init(NULL);
     if (conn == NULL) goto Err;
     if (mysql_real_connect(conn, Host.c_str(), Login.c_str(), Password.c_str(), db.c_str(), Port, NULL, 0)==NULL) goto Err;
     mysql_query(conn, "SET CHARACTER SET utf8");
     mysql_query(conn, "SET NAMES utf8");
         return true;
     Err:
         conn = NULL;
         return false;
 }
string Row(MYSQL_RES *result,MYSQL_ROW row ,string name)
 {
     int num_fields,i;
     string s;
     num_fields = mysql_num_fields(result);
     for(i = 0; i < num_fields; i++){
         if(LCASE(name) ==  LCASE(mysql_fetch_fields(result)[i].name)){
             if (row[i]==NULL) return s;
             else return row[i];
         }
     }
     return s;
 }
bool ExistTable(string tb)
 {
     MYSQL_RES *result;
     MYSQL_ROW row;

     mysql_query(conn, "SHOW TABLES;");
     result = mysql_store_result(conn);

       while ((row = mysql_fetch_row(result)))
       {
           if (tb == row[0]){
               mysql_free_result(result);
               return true;
           }
       }
       mysql_free_result(result);
       return false;
 }
void ConnectSQLite()
 {
     int rc;
     sqlite3_stmt* stmt;

     rc = sqlite3_open("db.sqlite",&condb3);
     string SQL,rw;
     SQL = "CREATE TABLE IF NOT EXISTS `pal_admin` (" \
         "  `user_id` int(11) NOT NULL default '0'," \
         "  `room_id` int(11) NOT NULL default '0'," \
         "  `room_type` int(11) NOT NULL default '0'" \
         ");";
     rc = sqlite3_prepare_v2(condb3, SQL.data(), -1, &stmt, 0);
     rc = sqlite3_step(stmt);

     SQL = "INSERT INTO `pal_admin` (user_id,room_id,room_type) VALUES(11,20,23)";
     rc = sqlite3_prepare_v2(condb3, SQL.data(), -1, &stmt, 0);
     rc = sqlite3_step(stmt);

     SQL = "SELECT * FROM `pal_admin`;";
     if(sqlite3_prepare_v2(condb3, SQL.data(), -1, &stmt, 0) != SQLITE_OK )
     {
         cout<<sqlite3_errmsg(condb3)<<endl;
     }

     while(sqlite3_step(stmt)==SQLITE_ROW)
     {
         rw = (char*)sqlite3_column_text(stmt,0) ;
     }

     sqlite3_finalize(stmt);
     sqlite3_close(condb3);
 }
