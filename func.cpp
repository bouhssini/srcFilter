#include "you.h"

short cts(unsigned char * ch)
{
        short i;
        unsigned char ptr[2];
        ptr[0]=ch[0];
        ptr[1]=ch[1];
        memcpy(&i,&ptr,sizeof(short));
        return i;
}
string convertInt(int value) {
  std::ostringstream o;
  if (!(o << value))
    return "";
  return o.str();
}

string itostr(int value)
{
  std::ostringstream o;
  if (!(o << value))
    return "";
  return o.str();
}
int strtoi(string s)
{
    return atoi(s.c_str());
}

string stc(short i)
{
    string s;
        char ptr[2];
        memcpy(&ptr,&i,sizeof(short));
        s.append(ptr,2);
        return s;
}
string itc(int i)
{
        string s;
        char ptr[4];
        memcpy(&ptr,&i,sizeof(int));
        s.append(ptr,4);
        return s;
}
int cti(unsigned char * ch)
{
        int i;
        unsigned char ptr[4];
        ptr[0]=ch[0];
        ptr[1]=ch[1];
        ptr[2]=ch[2];
        ptr[3]=ch[3];
        memcpy(&i,&ptr,sizeof(int));
        return i;
}

string Replace(string txt,string str,string chstr)
{
    int pos=0,ln=0;
    if (str == chstr)
        return txt;
    if (str == "")
        return txt;

    while((pos = txt.find(str,ln))!=-1)
    {
        txt.replace(pos,str.length(),chstr);
        ln=pos+chstr.length()-str.length()+1;
    }
    return txt;
}
string Trim(string txt)
{
    char sp=' ';
    unsigned int i=0;
    string tx2;
    for (i=0;i<txt.length();i++)
          if (txt.data()[i] != sp)  break;

    tx2 = txt.substr(i,txt.length());

    for (i=1;i<tx2.length();i++)
          if (tx2.data()[tx2.length()-i] != sp)  break;

    tx2 = tx2.substr(0,tx2.length()-i+1);
    return tx2;
}
string String(int Ln,char c)
{
    char s[Ln];
    string s2;
    for(int i=0;i<Ln;i++)
        s[i] = c;
    s2.append(s,Ln);
    return s2;
}
string ICONV(string txt,const char fromcode[],const char tocode[])
{
    iconv_t      cd;
    size_t       in_size = txt.length();
    char         *inptr = (char*)txt.c_str();
    char         out[in_size*3];
    size_t       out_size = sizeof(out);
    char         *outptr = out;

    string s;
    s.clear();

    if ((iconv_t)(-1) == (cd = iconv_open(tocode, fromcode))) {
       goto fin;
    }
    if ((size_t)(-1) == iconv(cd, &inptr, &in_size, &outptr, &out_size)) {
       goto fin;
    }
    *outptr = '\0';
    if (-1 == iconv_close(cd)) {
       goto fin;
    }
    s.append(out,strlen(out));
    fin:
    return s;
}
vector<string> Split(string txt,string str)
{
    vector<string> l;
    int pos=0,ln=0,ps=0,i=0;
    string tx;
    if (str == "")
    {
        l.push_back(txt);
        return l;
    }

    while((pos = txt.find(str,ln))!=-1)
    {
        tx = txt.substr(ps,pos-ps);
        l.push_back(tx);
        //ln=pos+str.length()+1;
        ps=pos+str.length();
        ln = ps;
        i++;
    }

    if (i == 0)
    {
        l.push_back(txt);
    }else{
        tx = txt.substr(ps,txt.length()-ps);
        l.push_back(tx);
    }
    return l;
}
string MD5(string txt)
{
    return md5(txt);
}
string UCASE(string str)
{
    int leng=str.length();
    for(int i=0; i<leng; i++)
        if (97<=str[i]&&str[i]<=122)//a-z
            str[i]-=32;
    return str;
}
string LCASE(string str)
{
    int leng=str.length();
    for(int i=0; i<leng; i++)
        if (65<=str[i]&&str[i]<=90)//A-Z
            str[i]+=32;
    return str;
}
/* Function File */
bool ExistsFile(string filename){
    FILE *f;
    f= fopen(filename.c_str(),"r");
    if (f == NULL){
        return false;
    }else{
        fclose(f);
        return true;
    }
}
string ReadAllFile(string filename)
{
    FILE *f;
    char * buffer;
    long l,result;
    string s;

    if (!ExistsFile(filename)) return "";
    f = fopen(filename.c_str(),"rb");
    fseek (f , 0 , SEEK_END);
    l = ftell (f);
    rewind (f);
    buffer = (char*) malloc (sizeof(char)*l);
    result = fread (buffer,1,l,f);
    fclose(f);
    s.append(buffer,l);
    free (buffer);
    if (result != l) return "";

    return s;
}
void WriteFile(string filename,string txt){
    FILE *f;
    f = fopen(filename.c_str(),"a+");
    if (f != NULL){
        fwrite (txt.c_str() , 1 , txt.length() , f);
        fclose(f);
    }
}
/* Exec File */
string EXEC(string path)
{
    FILE *f;
    char line[256];
    string st;
    if ( !(f = popen(path.c_str(),"r")) )
    {
       perror("Problems with pipe");
       return "";
    }

    while ( fgets(line, sizeof line, f))
    {
        st.append(line);
    }
    pclose(f);
    return st;
}
/* Function DateTime */
string datetime()
{
    time_t Seconds;
    string yyyy,MM,dd,hh,mm,ss;
    struct tm* Time;
    time(&Seconds);
    Time =  localtime(&Seconds);
    yyyy =  convertInt(Time->tm_year+1900);
    MM   =  convertInt(Time->tm_mon+1);if (MM.size()==1) MM ="0"+MM;
    dd   =  convertInt(Time->tm_mday);if (dd.size()==1) dd ="0"+dd;
    hh   =  convertInt(Time->tm_hour);if (hh.size()==1) hh ="0"+hh;
    mm   =  convertInt(Time->tm_min);if (mm.size()==1) mm ="0"+mm;
    ss   =  convertInt(Time->tm_sec);if (ss.size()==1) ss ="0"+ss;
    return yyyy+"-"+MM+"-"+dd+" "+hh+":"+mm+":"+ss;
}
int Year(const char *date)
{
    string dt = date;
    return atoi(dt.substr(0,4).data());
}
int Month(const char *date)
{
    string dt = date;
    return atoi(dt.substr(5,2).data());
}
int Day(const char *date)
{
    string dt = date;
    return atoi(dt.substr(8,2).data());
}
int Hour(const char *date)
{
    string dt = date;
    return atoi(dt.substr(11,2).data());
}
int Minute(const char *date)
{
    string dt = date;
    return atoi(dt.substr(14,2).data());
}
int Second(const char *date)
{
    string dt = date;
    return atoi(dt.substr(17,2).data());
}

time_t ChangeStrToTime(const char * str1)
{
    int yyyy,MM,dd,hh,mm,ss;
    time_t t1;
    struct tm * tm1;

    yyyy =Year(str1);
    MM=Month(str1);
    dd=Day(str1);
    hh=Hour(str1);
    mm=Minute(str1);
    ss=Second(str1);
    time(&t1);
    tm1 = localtime(&t1);
    tm1->tm_year = yyyy - 1900;
    tm1->tm_mon = MM - 1;
    tm1->tm_mday = dd;
    tm1->tm_hour = hh;
    tm1->tm_min = mm;
    tm1->tm_sec = ss;
    t1=mktime(tm1);
    return t1;
}
int DateDiff(const char * str1,const char * str2,const char Format)
{
    int diff;
    time_t t1,t2;
    t1 = ChangeStrToTime(str1);
    t2 = ChangeStrToTime(str2);


    diff = difftime(t2,t1);
    switch (Format)
    {
    case 'd':
        diff = diff / (3600*24); break;
    case 'h':
        diff = diff / 3600; break;
    case 'm':
        diff = diff / 60; break;
    case 's':
        break;
    }
    return diff;
}
