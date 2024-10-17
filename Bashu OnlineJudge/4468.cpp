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
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
long long father[20031205];
long long w1[20031205],w2[20031205];
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int find(int x){
	if(father[x]==x)return father[x];
	father[x]=find(father[x]);
	return father[x];
}
void unionn(int r1,int r2){
	father[r1]=r2;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int g,i,j,k;
	g=read();
	while(g--){
		long long n,x,y,e,tot=0,pd=0;
		n=read();
		for(i=1;i<=20031204;i++)father[i]=i;
		for(i=1;i<=n;i++){
			x=read();y=read();e=read();
			x%=20031204;y%=20031204;
			if(e==1){
				int r1=find(x);
				int r2=find(y);
				unionn(r1,r2);
			}
			else{
				w1[++tot]=x;
				w2[tot]=y;
			}
		}
		for(i=1;i<=tot;i++){
			if(find(w1[i])==find(w2[i]))pd=1;
		}
		if(pd==1)cout<<"NO"<<endl;
		else cout<<"YES"<<endl;
	}
	return 0;
}