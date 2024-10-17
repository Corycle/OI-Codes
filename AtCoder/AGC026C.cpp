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
#include<unordered_map>
#define ll long long
#define ull unsigned ll
using namespace std;
const int inf=0x3f3f3f3f;
const int Mul=13131;
const int N=40;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
char s[N];
int n,m,a[N];
unordered_map<ull,int>F[N];
void Update(){
	int num=0;ull Hash=0;
	for(int i=1;i<=n;i++)if(a[i]==0){Hash=Hash*Mul+s[i];num++;}
	for(int i=1;i<=n;i++)if(a[i]==1)Hash=Hash*Mul+s[i];
	F[num][Hash]++;
}
void Query(){
	int num=0;ull Hash=0;
	for(int i=n*2;i>n;i--)if(a[i]==1){Hash=Hash*Mul+s[i];num++;}
	for(int i=n*2;i>n;i--)if(a[i]==0)Hash=Hash*Mul+s[i];
	Ans+=F[num][Hash];
}
void DFS(int x,int Max){
	if(x==Max+1){Max==n?Update():Query();return;}
	a[x]=0;DFS(x+1,Max);a[x]=1;DFS(x+1,Max);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();scanf("%s",s+1);DFS(1,n);DFS(n+1,n*2);printf("%lld\n",Ans);
	return 0;
}
