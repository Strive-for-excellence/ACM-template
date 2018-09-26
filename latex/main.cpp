#include<bits/stdc++.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
using namespace std;
string config = "/config";
const char* cf = "/config";
const char* tf = "template.tex";
const char* head = "head";
const char* tail = "tail";
#define MAXL 200
char temp[200];
typedef pair<string,string> P;
FILE* tex = NULL;
void file(const char* filename)
{
    FILE* fp = fopen(filename, "r");
    while (fgets(temp, MAXL, fp) != NULL) fprintf(tex, temp);
    fclose(fp);
}
void Section(char *path);
void Subsection(char * path);
void Subsubsetion(char *path,vector<P> &vec);
bool cmp(const struct dirent    *a,const struct dirent    *b)
{
    return strcmp(a->d_name,b->d_name) < 0;
}
int main(int argc,char *argv[])
{
    tex = fopen(tf, "w+");
    file(head);
    char link[100];
    char path[100];

    sprintf( link, "/proc/%d/exe", getpid() );

    int i = readlink( link, path, sizeof( path ) );
    path[i] = '\0';
    string s = path;
    //for(int i = 0; path[i]; ++i)
    s = s.substr(0,s.find_last_of('/'));
    s = s.substr(0,s.find_last_of('/'));
    path[s.size()] = 0;
    cout<<path<<endl;
    Section(path);// setion 大类
    file(tail);
    fclose(tex);
    return 0;
}
void Section(char *path)
{
    DIR              *pDir ;
    struct dirent    *ent  ;
//    int               i=0  ;
    char              childpath[1000];

    pDir=opendir(path);
    if(pDir == NULL)
    {
        // cout<<path<<"1 wrong"<<endl;
        return ;
    }
    memset(childpath,0,sizeof(childpath));

    vector<dirent*> vec;
    while((ent=readdir(pDir))!=NULL)
    {
        if(strcmp(ent->d_name,"latex")==0) continue;
        if(strcmp(ent->d_name,".")==0 || strcmp(ent->d_name,"..")==0 || strchr(ent->d_name,'.') != NULL)
            continue;
        vec.push_back(ent);

    }
    sort(vec.begin(),vec.end(),cmp);
    for(int i = 0; i < vec.size(); ++i)
    {
        ent = vec[i];
        if(ent->d_type == DT_DIR)
        {
            sprintf(childpath,"%s/%s",path,ent->d_name);
            printf("path:%s\n",childpath);

            Subsection(childpath);

        }
    }

}
void Subsection(char * path)
{
    if(string(path).find(".git") != string::npos) return ;
    vector<vector<P> > vec;
    DIR              *pDir ;
    struct dirent    *ent  ;
    char              childpath[1000];

    pDir=opendir(path);
    if(pDir == NULL)
    {
        // cout<<path<<"2 wrong"<<endl;
        return ;
    }
    memset(childpath,0,sizeof(childpath));
    while((ent=readdir(pDir))!=NULL)
    {
        if(strcmp(ent->d_name,".")==0 || strcmp(ent->d_name,"..")==0)
            continue;
        if(ent->d_type == DT_DIR)
        {
            sprintf(childpath,"%s/%s",path,ent->d_name);
            vector<P> v;
            Subsubsetion(childpath,v);
            if(v.size() >= 1)
                vec.push_back(v);
        }
        else if(ent->d_type==DT_REG)
        {

            string s = ent->d_name;
            vector<P> v;
            if(s.find(".cpp") != string::npos)
                v.push_back(P(string(path)+"/"+ent->d_name,ent->d_name));
            vec.push_back(v);
            //cout<<ent->d_name<<endl;
        }
    }
    /// ofstream out;


    if(vec.empty()) return;
    const string s = string(path)+"/config";
    //FILE *file = fopen(s.c_str(),"w+");
    // out.open(s.c_str(),ofstream:out);
    string tmp = path;
    string ss = tmp.substr(tmp.find_last_of('/')+1);
    fprintf(tex, "\\section{%s}\n", ss.c_str());
    sort(vec.begin(),vec.end());
    for(int i = 0; i < vec.size(); ++i)
    {
        if(vec[i].size() == 1)
        {
            fprintf(tex, "\\subsection{%s}\n",vec[i][0].second.c_str());
            fprintf(tex, "\\inputminted{c++}{%s}\n",vec[i][0].first.c_str());
        }
        else
        {
            if(vec[i].empty()) continue;
            string t = vec[i][0].first;
            t = t.substr(0,t.find_last_of('/'));

            t = t.substr(t.find_last_of('/')+1);
            cout<<t<<endl;
            fprintf(tex, "\\subsection{%s}\n",t.c_str());
            for(int j = 0; j < vec[i].size(); ++j)
            {
                fprintf(tex, "\\subsubsection{%s}\n",vec[i][j].second.c_str());
                fprintf(tex, "\\inputminted{c++}{%s}\n",vec[i][j].first.c_str());
            }
        }
        //out<<vec[i].second<<" "<<vec[i].first<<endl;

        //   fprintf(file,"<%s>\t\t<%s>\n",vec[i].second.c_str(),vec[i].first.c_str());
        //   printf("<%s>\t\t<%s>\n",vec[i].second.c_str(),vec[i].first.c_str());
    }
    // cout<<"debug"<<endl;
    // fclose(file);
}
void Subsubsetion(char *path,vector<P> &vec)
{
    DIR              *pDir ;
    struct dirent    *ent  ;
    char              childpath[1000];

    pDir=opendir(path);
    if(pDir == NULL)
    {
        // cout<<path<<"3 wrong"<<endl;
        return ;
    }
    memset(childpath,0,sizeof(childpath));
    while((ent=readdir(pDir))!=NULL)
    {
        if(strcmp(ent->d_name,".")==0 || strcmp(ent->d_name,"..")==0)
            continue;
        if(ent->d_type==DT_REG)
        {
            string s = ent->d_name;
            if(s.size() > 4 && s.substr(s.size()-4) == ".cpp"){
                 string tmp(ent->d_name);
                 vec.push_back(P(string(path)+"/"+ent->d_name,tmp.substr(0,tmp.size()-4)));
            }

        }
    }
    sort(vec.begin(),vec.end());
}


