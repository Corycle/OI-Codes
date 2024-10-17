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
const int Mod=1e9+7;
const int N=2e3+5;
const int M=55;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N],X[M],Y[M];
int n,m,a[N],f[M][N][M/2][2];
int mod(int x){return x>=Mod?x-Mod:x;}
struct SAM{
	int tot=1,lst=1,root=1;
	int ch[N][10],fa[N],len[N];
	void Insert(int num){
		int x=lst,fx=++tot;len[fx]=len[x]+1;
		while(x&&!ch[x][num]){ch[x][num]=fx;x=fa[x];}
		if(!x)fa[fx]=root;
		else{
			int y=ch[x][num];
			if(len[y]==len[x]+1)fa[fx]=y;
			else{
				int fy=++tot;len[fy]=len[x]+1;
				fa[fy]=fa[y];fa[y]=fa[fx]=fy;
				memcpy(ch[fy],ch[y],sizeof(ch[fy]));
				while(x&&ch[x][num]==y){ch[x][num]=fy;x=fa[x];}
			}
		}
		lst=fx;
	}
}sam;
void Next(int &p,int &Len,int c){
	if(sam.ch[p][c]){p=sam.ch[p][c];Len++;}
	else{
		while(p&&!sam.ch[p][c]){p=sam.fa[p];Len=sam.len[p];}
		if(p){p=sam.ch[p][c];Len++;}
		else {p=1;Len=0;}
	}
	Len=min(Len,m/2);
}
int DFS(int x,int p,int num,int c,int flag){
	if(!x)return c;
	if(!flag&&f[x][p][num][c]!=-1)return f[x][p][num][c];
	int k=flag?a[x]:9,ans=0;
	for(int i=0;i<=k;i++){
		int fp=p,fnum=num;Next(fp,fnum,i);
		ans=mod(ans+DFS(x-1,fp,fnum,c|(fnum==m/2),flag&(i==k)));
	}
	if(!flag)f[x][p][num][c]=ans;
	return ans;
}
int Query(char Num[]){
	a[0]=0;memset(f,-1,sizeof(f));
	for(int i=m;i>=1;i--)a[++a[0]]=Num[i]-'0';
	return DFS(m,1,0,0,1);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	scanf("%s%s%s",s+1,X+1,Y+1);
	n=strlen(s+1);m=strlen(X+1);
	for(int i=1;i<=n;i++)sam.Insert(s[i]-'0');
	for(int i=m;i>=1;i--){
		if(X[i]=='0')X[i]='9';
		else{X[i]--;break;}
	}
	printf("%d",mod(Query(Y)-Query(X)+Mod));
	return 0;
}
