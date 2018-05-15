#include <iostream>
#include<vector>
#include<string>
#include<fstream>

using namespace std;

ifstream file1;

vector <int> adj(int x)         ///create a list of indices of adjacent letters
{
    vector<int> adj_list; ///list of adj letters indexes
    int y;
    for (int i=-5;i<=5;i++)
    {
        if(x%4==0)
        {
            switch(i)
            {
            case(1):
            case(4):
            case(-3):
            case(-4):
            case(5):
                y=x+i;
                if (y<=15 && y>=0)
                    adj_list.push_back(y);
            }
        }
            else if(x%4==3)
            {
            switch(i){
            case(-1):
            case(3):
            case(4):
            case(-4):
            case(-5):
                y=x+i;
                if (y<=15 && y>=0)
                    adj_list.push_back(y);
            }
            }
            else
            {
            switch(i){
            case(1):
            case(-1):
            case(3):
            case(-3):
            case(4):
            case(-4):
            case(5):
            case(-5):
                y=x+i;
                if (y<=15 && y>=0)
                    adj_list.push_back(y);
                    }
            }
    }
    return adj_list;
}

void wordcheck(string str2)      ///check whether word is correct or not and print if correct
{
    file1.clear();
    file1.seekg(0, ios::beg);
    string data;
    while(true)
    {
        file1>>data;
        if  (str2[0]==data[0])
        {
            if(str2[1]==data[1])
            {
                if(str2[2]==data[2])
                {
                    if(str2==data)
                    {
                        cout<<str2<<endl;
                        break;
                    }
                }
            }
        }
        else if (data=="zyzzyvas")
            break;
    }

}

void func(string word,vector<int> adlist,char grid[16],bool selchk[16],int k)
{                                               ///recursive function for word making

    for (vector<int>::iterator i=adlist.begin(); i!=adlist.end(); ++i)
    {   if(selchk[*i]==0)
                    {   string vord=word;
                        selchk[*i]=1;
                        char a=grid[*i];
                        vord+=a;
                        //cout<<vord<<endl;
                        wordcheck(vord);            ///print correct word
                        vector<int> adlistf;
                        adlistf=adj(*i);
                        if (vord.size()<k)
                            func(vord,adlistf,grid,selchk,k);
                    }
        selchk[*i]=0;
    }
}

int main()
{   int p=0;
    char grid[16];
    cout<<"enter letters one after another"<<endl;
    for (int i=0;i<16;i++)    ///input grid
    {
        cin>>grid[i];
    }
    for (int ii=0;ii<4;ii++)    ///output grid
    {
        for(int jj=0;jj<4;jj++)
        {
            cout<<grid[p]<<"\t";
            p=p+1;
        }
        cout<<endl;
    }

    file1.open("C:\\Users\\Tanujdeep\\Desktop\\C,C++\\wordswipe\\wordsEn.txt",ios::in);

    int k;
    cout<<"enter no. of maximum letters in a word \t";
    cin>>k;
    //for(int k=4;k<=o;k++)
    //{


    for(int i1=0;i1<=15;i1++)
    {
        bool selchk[16];                   ///array which has '1' for every letter index that was chosen and '0' for not
        selchk[i1]=1;                      /// 1 for selected
        char a1=grid[i1];                  /// 1st letter of the word
        vector<int> adlist1;
        adlist1=adj(i1);                    ///list of adjacent letters indices
        for (vector<int>::iterator i2 = adlist1.begin(); i2 != adlist1.end(); ++i2)     ///for each of the adjacent letter
        {   if (selchk[*i2]==0)                 ///IF THAT LETTER WAS NOT SELECTED PRIOR
            {
                selchk[*i2]=1;                  ///do '1' for selected
                char a2=grid[*i2];              ///2nd letter of the word
                vector<int> adlist2;            ///list of adjacent letters' indices for 2nd letter
                adlist2=adj(*i2);
                for (vector<int>::iterator i3=adlist2.begin(); i3!=adlist2.end(); ++i3)
                {   if(selchk[*i3]==0)
                    {   string word;
                        selchk[*i3]=1;
                        char a3=grid[*i3];              ///3rd letter
                        word+=a1;word+=a2;word+=a3;         ///word
                        //cout<<word<<endl;
                        wordcheck(word);                    ///check if word exists
                        vector<int> adlist3;
                        adlist3=adj(*i3);
                        func(word,adlist3,grid,selchk,k);       ///repeat these steps until desired lenght of word
                    }
                selchk[*i3]=0;                          ///de-select letters from checked words
                }
            }
        selchk[*i2]=0;                                  /// ^^^^^^
        }
    selchk[i1]=0;                                       /// ^^^^^^
    }
    //}
    file1.close();
    getchar();
    return 0;
}




