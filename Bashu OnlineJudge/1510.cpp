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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,num;
int p[N],cnt[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	int m=n,Ans=n+1,phi=n;
	for(int i=2;i*i<=m;i++){
		if(m%i==0){
			phi=phi/i*(i-1);
			p[++num]=i;
			while(m%i==0){
				cnt[num]++;
				m/=i;
			}
		}
	}
	if(m!=1){
		p[++num]=m;
		cnt[num]++;
		phi=phi/m*(m-1);
	}
	int Num=1;
	for(int i=1;i<=num;i++){
		Num=Num*(cnt[i]+1);
	}
	printf("%d",Ans-phi-Num);
	return 0;
}