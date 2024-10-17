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
const int M=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int T,F,sg[N];
int SG(int n){
	if(sg[n]!=-1)return sg[n];
	if(n<F)return sg[n]=0;
	int s[M];sg[n]=0;
	memset(s,0,sizeof(s));
	for(int i=2;i<=n;i=n/(n/i)+1){
		for(int j=i;j<=min(i+1,n);j++){
			int p=0,x=n/j;
			if((n%j)&1)p^=SG(x+1);
			if((j-n%j)&1)p^=SG(x);
			s[p]=1;
		}
	}
	for(int i=0;;i++){
		if(!s[i])return sg[n]=i;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	T=read();F=read();
	memset(sg,-1,sizeof(sg));
	while(T--){
		int n=read(),Ans=0;
		for(int i=1;i<=n;i++){
			Ans^=SG(read());
		}
		printf("%d ",Ans?1:0);
	}
	return 0;
}