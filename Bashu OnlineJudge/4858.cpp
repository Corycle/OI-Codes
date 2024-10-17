/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<cstring>
#include<complex>
#include<bitset>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
#define Bitset bitset<N>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n;
ll Ans;
char s[N];
Bitset a[N];
int main(){
//	freopen("tour.in","r",stdin);
//	freopen("tour.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=n;j++)a[i][j]=s[j]-'0';
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j)continue;
			Bitset t1=(a[i]&a[j]);
			Bitset t2=a[j];
			int num1=t1.count();
			int num2=t2.count();
			Ans+=1ll*num1*(num2-1-a[j][i]);
		}
	}
	printf("%lld\n",Ans);
	return 0;
}