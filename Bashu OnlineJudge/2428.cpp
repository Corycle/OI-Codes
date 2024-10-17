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
const int N=25;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char a[N];
int n,m,Ans,Mod,nxt[N];
int mod(int x){return x>=Mod?x-Mod:x;}
struct Matrix{
	int a[N][N];
	void Init(){memset(a,0,sizeof(a));}
	friend Matrix operator*(Matrix A,Matrix B){
		Matrix C;C.Init();
		for(int i=0;i<m;i++){
			for(int j=0;j<m;j++){
				for(int k=0;k<m;k++){
					C.a[i][j]=mod(C.a[i][j]+1ll*A.a[i][k]*B.a[k][j]%Mod);
				}
			}
		}
		return C;
	}
};
Matrix tmp,ans;
void Solve(int t){
	for(int i=0;i<m;i++)ans.a[i][i]=1;
	while(t){
		if(t&1)ans=ans*tmp;
		tmp=tmp*tmp;
		t>>=1;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Mod=read();
	scanf("%s",a+1);
	for(int i=2,j=0;i<=m;i++){
		while(j>0&&a[i]!=a[j+1])j=nxt[j];
		if(a[i]==a[j+1])j++;
		nxt[i]=j;
	}
	for(int i=0;i<m;i++){
		for(int k=0;k<=9;k++){
			int j=i;
			while(j>0&&k+'0'!=a[j+1])j=nxt[j];
			if(k+'0'==a[j+1])j++;
			tmp.a[j][i]++;
		}
	}
	Solve(n);
	for(int i=0;i<m;i++)Ans=mod(Ans+ans.a[i][0]);
	printf("%d",Ans);
	return 0;
}