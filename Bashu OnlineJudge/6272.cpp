/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=7005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,mod,b[N],sum[N][N];
struct Point{int x,y;}P[N];
bool cmp(Point A,Point B){return A.y>B.y;}
int Mod(int x){return x>=mod?x-mod:x;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();mod=read();
	for(int i=1;i<=n;i++){
		P[i].x=read();
		P[i].y=read();
		b[++b[0]]=P[i].x;
	}
	sort(b+1,b+b[0]+1);
	sort(P+1,P+n+1,cmp);
	b[0]=unique(b+1,b+b[0]+1)-b-1;
	for(int i=1;i<=n;i++){
		P[i].x=lower_bound(b+1,b+b[0]+1,P[i].x)-b;
	}
	int Ans=n,t=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++){
			//t=f[i][j],P[j].y>P[i].y
			if(P[j].x>P[i].x)t=sum[j][P[i].x-1];
			else t=Mod(sum[j][n]-sum[j][P[i].x]+mod);
			sum[i][P[j].x]=Mod(t+1);Ans=Mod(Ans+t+1);
		}
		for(int j=1;j<=n;j++){
			sum[i][j]=Mod(sum[i][j]+sum[i][j-1]);
		}
	}
	printf("%d",Ans);
	return 0;
}