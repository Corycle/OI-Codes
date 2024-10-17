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
const int N=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot;
int f[N],a[N][N],ans[N];
void Print(int l,int r){
	int num=r-l;
	for(int i=l;i<=r;i++){
		int sum=num;
		for(int j=i+1;j<=m;j++){
			if(sum)printf("1 ");
			else printf("0 ");
			if(sum)sum--;
		}
		printf("\n");
		num--;
	}
}
int main(){
//	freopen("graph.in","r",stdin);
//	freopen("graph.out","w",stdout);
	n=read();
	while(1){
		tot++;
		f[tot]=f[tot-1]+(tot-2)*(tot-1)/2;
		if(f[tot]>=n)break;
	}
	for(int i=tot;i>=3;i--){
		ans[i]+=n/f[i];
		n-=ans[i]*f[i];
		m+=ans[i]*i;
	}
	int sum=0;
	printf("%d\n",m);
	for(int i=1;i<=tot;i++){
		while(ans[i]){
			Print(sum+1,sum+i);
			sum+=i;ans[i]--;
		}
	}
	return 0;
}