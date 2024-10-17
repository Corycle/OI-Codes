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
#include<set>
#define ll long long
#define ull unsigned ll
using namespace std;
const int inf=0x3f3f3f3f;
const ull Mul=13131;
const int N=2e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
ull f[N];
char s[N];
map<ull,int>F;
int n,m,nxt[N];
ull GetHash(int x){
	ull ans=0;
	for(int i=1;i<=x;i++)ans=ans*Mul+s[i];
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int t=1;t<=n;t++){
		m=read();scanf("%s",s+1);
		for(int i=2,j=0;i<=m;i++){
			while(j!=0&&s[i]!=s[j+1])j=nxt[j];
			if(s[i]==s[j+1])j++;nxt[i]=j;
		}
		f[t]=(m%(m-nxt[m])==0)?GetHash(m-nxt[m]):GetHash(m);
		F[f[t]]++;
	}
	for(int i=1;i<=n;i++)if(f[i])Ans+=F[f[i]];
	printf("%lld\n",Ans);
	return 0;
}
