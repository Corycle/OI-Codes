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
const double eps=1e-8;
const int N=105;
const int M=15;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,len,pos[N];
double P[M],f[N],a[N][N];
struct AC_Tree{
	int Root=1,tot=1,ch[N][M],fail[N],flag[N];
	int Insert(){
		int p=Root;
		for(int i=1;i<=len;i++){
			int x=s[i]-'A';
			if(!ch[p][x])ch[p][x]=++tot;
			p=ch[p][x];
		}
		flag[p]=1;
		return p;
	}
	void Build(){
		queue<int>q;
		fail[1]=1;
		for(int i=0;i<m;i++){
			if(ch[1][i]){q.push(ch[1][i]);fail[ch[1][i]]=1;}
			else ch[1][i]=1;
		}
		while(q.size()){
			int x=q.front();q.pop();
			for(int i=0;i<m;i++){
				if(ch[x][i]){
					q.push(ch[x][i]);
					fail[ch[x][i]]=ch[fail[x]][i];
				}
				else ch[x][i]=ch[fail[x]][i];
			}
		}
		for(int i=1;i<=tot;i++){
			a[i][i]=1;
			if(flag[i])continue;
			for(int j=0;j<m;j++)a[ch[i][j]][i]-=P[j];
		}
		for(int i=1;i<=tot;i++)a[1][i]=flag[i];
		a[1][tot+1]=1;
	}
}tree;
void Gauss(int n){
	for(int i=1;i<=n;i++){
		int t=i;
		for(int j=i;j<=n;j++)if(fabs(a[t][i])<fabs(a[j][i]))t=j;
		if(t!=i)swap(a[i],a[t]);
		for(int j=i+1;j<=n;j++){
			double dlt=a[j][i]/a[i][i];
			for(int k=i;k<=n+1;k++)a[j][k]-=a[i][k]*dlt;
		}
	}
	for(int i=n;i>=1;i--){
		for(int j=i+1;j<=n;j++)a[i][n+1]-=a[i][j]*f[j];
		if(fabs(a[i][i])>eps)f[i]=a[i][n+1]/a[i][i];
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();len=read();m=read();
	for(int i=0;i<m;i++){int p=read(),q=read();P[i]=1.0*p/q;}
	for(int i=1;i<=n;i++){scanf("%s",s+1);pos[i]=tree.Insert();}
	tree.Build();Gauss(tree.tot);
	for(int i=1;i<=n;i++)printf("%.2lf\n",f[pos[i]]);
	return 0;
}