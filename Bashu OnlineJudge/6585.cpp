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
const int Mod=998244353;
const int N=55;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,Sta,tot=1,root=1;
int ch[N][10],fail[N],flag[N],num[N];
int mod(int x){return x>=Mod?x-Mod:x;}
struct Matrix{
	int a[N][N];
	void Init(){memset(a,0,sizeof(a));}
	friend Matrix operator*(Matrix A,Matrix B){
		Matrix C;C.Init();
		for(int i=1;i<=tot;i++){
			for(int k=1;k<=tot;k++){
				if(!A.a[i][k])continue;
				for(int j=1;j<=tot;j++){
					C.a[i][j]=mod(C.a[i][j]+1ll*A.a[i][k]*B.a[k][j]%Mod);
				}
			}
		}
		return C;
	}
}F,Ans;
struct Tree{
	void Insert(int id){
		int p=root,len=strlen(s+1);
		for(int i=1;i<=len;i++){
			int x=s[i]-'0';
			if(!ch[p][x])ch[p][x]=++tot;
			p=ch[p][x];
		}
		flag[p]|=(1<<(id-1));
	}
	void Build(){
		queue<int>q;fail[1]=1;
		for(int i=0;i<=9;i++){
			if(ch[1][i]){fail[ch[1][i]]=1;q.push(ch[1][i]);}
			else ch[1][i]=1;
		}
		while(q.size()){
			int x=q.front();q.pop();
			for(int i=0;i<=9;i++){
				if(ch[x][i]){
					q.push(ch[x][i]);
					fail[ch[x][i]]=ch[fail[x]][i];
					flag[ch[x][i]]|=flag[fail[ch[x][i]]];
				}
				else ch[x][i]=ch[fail[x]][i];
			}
		}
	}
}tree;
void Solve(int t){
	Ans.Init();
	for(int i=1;i<=tot;i++)Ans.a[i][i]=1;
	while(t){if(t&1)Ans=Ans*F;F=F*F;t>>=1;}
}
int main(){
//	freopen("password.in","r",stdin);
//	freopen("password.out","w",stdout);
	m=read();n=read();
	for(int i=1;i<=m;i++){
		scanf("%s",s+1);
		tree.Insert(i);
	}
	tree.Build();
	int ans=0;Sta=(1<<m)-1;
	for(int i=1;i<=Sta;i++)num[i]=num[i>>1]+(i&1);
	for(int S=0;S<=Sta;S++){
		F.Init();
		for(int x=1;x<=tot;x++){
			if(flag[x]&S)continue;
			for(int c=0;c<=9;c++){
				int y=ch[x][c];
				if(flag[y]&S)continue;
				F.a[x][y]++;
			}
		}
		Solve(n);
		int t=num[S]&1?Mod-1:1;
		for(int x=1;x<=tot;x++)ans=mod(ans+1ll*t*Ans.a[1][x]%Mod);
	}
	printf("%d",ans);
	return 0;
}