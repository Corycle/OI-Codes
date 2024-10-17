/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
const int M=10005;
const int B=400;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot;
int st[N],ed[N],pos[N],a[N],b[B][M],c[B][M];
void Prepare(){
	while(ed[tot]<n){
		tot++;
		st[tot]=ed[tot-1]+1;
		ed[tot]=min(ed[tot-1]+B,n);
	}
	for(int i=1;i<=tot;i++){
		for(int j=1;j<M;j++){
			b[i][j]=b[i-1][j];
			c[i][j]=c[i-1][j];
		}
		for(int j=st[i];j<=ed[i];j++){
			pos[j]=i;
			b[i][a[j]]++;
			c[i][b[i][a[j]]]++;
		}
	}
}
void Change(int x,int data){
	for(int i=pos[x];i<=tot;i++){
		c[i][b[i][a[x]]]--;
		b[i][a[x]]--;
		b[i][data]++;
		c[i][b[i][data]]++;
	}
	a[x]=data;
}
int Query(int x,int y){
	if(x==1)return a[y];
	if(y==ed[pos[y]]){
		int t=pos[y];
		int Ans=(x&1)?c[t][b[t][a[y]]]:b[t][a[y]];
		return Ans;
	}
	int t=pos[y]-1;
	for(int i=st[t+1];i<=y;i++){
		b[t][a[i]]++;
		c[t][b[t][a[i]]]++;
	}
	int Ans=(x&1)?c[t][b[t][a[y]]]:b[t][a[y]];
	for(int i=y;i>=st[t+1];i--){
		c[t][b[t][a[i]]]--;
		b[t][a[i]]--;
	}
	return Ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	Prepare();
	m=read();
	while(m--){
		int op=read(),x=read(),y=read();
		if(op==1)Change(y,x);
		if(op==2)printf("%d\n",Query(x,y));
	}
	return 0;
}