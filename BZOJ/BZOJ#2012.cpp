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
const int Mul=200;
const int N=5e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N][10];
map<ll,int>Num;
int n,m,D,num[N];
ll Ans[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();D=read();
	for(int i=1;i<=n;i++)scanf("%s",s[i]);
	for(int S=0;S<(1<<4);S++){
		ll sum=0;Num.clear();
		num[S]=num[S>>1]+(S&1);
		for(int i=1;i<=n;i++){
			ll Hash=0;
			for(int j=0;j<4;j++)if((S>>j)&1)Hash=Hash*Mul+s[i][j];
			sum+=Num[Hash];Num[Hash]++;
		}
		Ans[num[S]]+=sum;
	}
	Ans[3]-=Ans[4]*4;
	Ans[2]-=Ans[4]*6+Ans[3]*3;
	Ans[1]-=Ans[4]*4+Ans[3]*3+Ans[2]*2;
	Ans[0]-=Ans[4]*1+Ans[3]*1+Ans[2]*1+Ans[1]*1;
	printf("%lld",Ans[4-D]);
	return 0;
}
