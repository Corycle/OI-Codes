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
//stack<_>_;
//queue<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
char c[1000005];
int a[100005];
bool b[100005];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,n,s,j,m,x,k,lc,ans=0,inc=0,t;
    gets(c);
    lc=strlen(c);
    for(i=0;i<lc;i++){
        if(c[i]=='+'||c[i]=='*'){
            if(c[i]=='*')b[inc++]=1;
            else b[inc++]=0;
        }
        else if(c[i]>='0'&&c[i]<='9'){
            a[inc]=(a[inc]*10+((c[i])-48))%10000;
        }        
    }
    for(i=0;i<=inc;i++){
        if(b[i]==1){
        	a[i+1]=(a[i]*a[i+1])%10000;
        }
    }
    for(i=0;i<=inc;i++){
        t=0;
        if(b[i]==0){
        	t=i;
        	while(b[t+1]==1)t++;
        	a[t+1]=(a[i]+a[t+1])%10000;
        }
    }
    printf("%d",(a[inc+1])%10000);
	return 0;
}