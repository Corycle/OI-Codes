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
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot,num,a[N];
bool cmp(int x,int y){return (x&1)>(y&1);}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){a[i]=read();num+=(a[i]&1);}
	if(m==1){
		if(n==1){printf("1\n1\n1\n");return 0;}
		else{printf("%d\n2\n1 %d",n,n-1);return 0;}
	}
	if(num>2){puts("Impossible");return 0;}
	sort(a+1,a+m+1,cmp);swap(a[2],a[m]);
	for(int i=1;i<=m;i++)printf("%d ",a[i]);puts("");
	a[1]++;a[m]--;if(!a[m])m--;printf("%d\n",m);
	for(int i=1;i<=m;i++)printf("%d ",a[i]);puts("");
	return 0;
}
