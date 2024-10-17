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
const int N=1e5+5;
const int M=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,t,d,tot;
int t1[N],t2[N],nxt[M],sum[M][10];
struct List{int l,r,id;char c;}L[M];
void Link(int x,int y){
	L[x].r=y;L[y].l=x;
}
void Erase(int x){
	L[L[x].l].r=L[x].r;
	L[L[x].r].l=L[x].l;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	scanf("%s",s+1);
	for(int i=1;i<=n;i++){
		L[++tot].c='>';
		Link(tot-1,tot);
		nxt[tot]=tot+1;
	}
	int x=tot,p=tot+1;
	for(int i=1;i<=n;i++){
		L[++tot].c=s[i];
		Link(tot-1,tot);
		nxt[tot]=tot+1;
		L[tot].id=i;
	}
	L[++tot].c='>';
	Link(tot-1,tot);
	nxt[tot]=tot+1;
	L[tot].id=n+1;
	t1[0]=1;
	while(p){
		t++;
		for(int i=0;i<=9;i++)sum[t][i]=sum[t-1][i];
		if(!t1[L[p].id])t1[L[p].id]=t;
		for(int i=nxt[p];i&&i<=L[p].r&&t1[L[i].id];i=nxt[i]){
			t2[L[i].id]=t;nxt[p]=nxt[i];
		}
		if('0'<=L[p].c&&L[p].c<='9'){
			sum[t][L[p].c-'0']++;
			if(L[p].c=='0')Erase(p);
			else L[p].c--;
		}
		else{
			if(!('0'<=L[x].c&&L[x].c<='9'))Erase(x);
		}
		x=p;p=(d?L[p].l:L[p].r);
		if(!('0'<=L[p].c&&L[p].c<='9'))d=(L[p].c=='<');
	}
	for(int i=0;i<=n;i++)if(!t2[i])t2[i]=t;
	while(m--){
		int l=read(),r=read();
		int S=t1[l]-1,T=min(t2[l],t1[r+1])-1;
		for(int i=0;i<=9;i++)printf("%d ",sum[T][i]-sum[S][i]);
		printf("\n");
	}
	return 0;
}