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
const int M=(1<<8)+5;
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K,tot;
int id[10],f[N][M],num[M];
struct Node{int x,f,id;}P[N];
bool cmp(Node A,Node B){return A.x!=B.x?A.x<B.x:A.f<B.f;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();K=read();
	for(int i=1;i<=n;i++){P[++tot]=(Node){read(),1,i};P[++tot]=(Node){read()+1,-1,i};}
	sort(P+1,P+tot+1,cmp);memset(f,-0x3f,sizeof(f));f[0][0]=0;
	for(int i=1;i<=K;i++)id[i]=0;
	int Sta=0;
	for(int S=1;S<M;S++)num[S]=num[S>>1]+(S&1);
	for(int i=1;i<=tot;i++){
		if(P[i].f==1){
			int pos=0;
			for(int j=1;j<=K;j++)if(!id[j]){pos=j;id[j]=P[i].id;break;}
			int T=(1<<(pos-1));
			for(int S=Sta;;S=(S-1)&Sta){
				f[i][S]=max(f[i][S],f[i-1][S]+(num[S]&1)*(P[i].x-P[i-1].x));
				f[i][S|T]=max(f[i][S|T],f[i-1][S]+(num[S]&1)*(P[i].x-P[i-1].x-1)+(num[S|T]&1));
				if(!S)break;
			}
			Sta^=T;
		}
		if(P[i].f==-1){
			int pos=0;
			for(int j=1;j<=K;j++)if(id[j]==P[i].id){pos=j;id[j]=0;break;}
			int T=(1<<(pos-1));
			Sta^=T;
			for(int S=Sta;;S=(S-1)&Sta){
				f[i][S]=max(f[i][S],f[i-1][S]+(num[S]&1)*(P[i].x-P[i-1].x));
				f[i][S]=max(f[i][S],f[i-1][S|T]+(num[S|T]&1)*(P[i].x-P[i-1].x-1)+(num[S]&1));
				if(!S)break;
			}
		}
	}
	printf("%d\n",f[tot][Sta]);
	return 0;
}
