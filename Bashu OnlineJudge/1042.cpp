#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
using namespace std;
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
string name[101],dos;
queue<int>fr,en;
int n;
bool sa[101];
int main(){
    cin>>n;
	for(int i=1;i<=n;i++){
        cin>>name[i]>>dos;
        if(dos=="UP")en.push(i);
        if(dos=="DOWN")fr.push(i);
        if(dos=="SAME")sa[i]=1;
    }
    for(int i=1;i<=n;i++){
        if(sa[i]==1)cout<<name[i]<<endl;
        else{
        	if(!fr.empty()){
				cout<<name[fr.front()]<<endl;
				fr.pop();
			}
        	else if(!en.empty()){
				cout<<name[en.front()]<<endl;
				en.pop();
			}
        }
    }
    return 0;
}