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
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
struct Node{int x1,y1,x2,y2;}P[N];
namespace Task1{
	int Ansx,Ansy;
	void Main(){
		Ansx=Ansy=-inf;
		for(int i=1;i<=n;i++){
			Ansx=max(Ansx,P[i].x1);
			Ansy=max(Ansy,P[i].y1);
		}
		printf("%d %d\n",Ansx,Ansy);
	}
}
int main(){
//	freopen("hamburg.in","r",stdin);
//	freopen("hamburg.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		P[i].x1=read();P[i].y1=read();
		P[i].x2=read();P[i].y2=read();
	}
	if(m==1)Task1::Main();
	return 0;
}
