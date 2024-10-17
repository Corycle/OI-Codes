#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a[N];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	while(scanf("%d%d",&n,&m)!=EOF){
		a[0]=-1;
		for(int i=1;i<=n;i++)a[i]=read();
		if(m==1){
			printf("Nod\n");
			continue;
		}
		int sg=0,tmp=0;
		for(int i=n;i>=1;i-=2){
			sg^=(tmp=a[i]-a[i-1]-1);
		}
		if(n&1&&m==2)sg=sg^(tmp-1)^tmp;
		if(sg)printf("Nod\n");
		else printf("Nic\n");
	}
	return 0;
}