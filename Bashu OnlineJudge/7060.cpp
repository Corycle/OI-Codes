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
const int N=5e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,top,tot,Max;
int a[N],b[N],L[N],R[N],st[N],Ans[N];
int gcd(int x,int y){return !y?x:gcd(y,x%y);}
int main(){
//	freopen("multiple.in","r",stdin);
//	freopen("multiple.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++){
		int num=0;top++;st[top]=i;b[top]=a[i];
		for(int j=1;j<=top;j++)b[j]=gcd(b[j],a[i]);
		for(int j=1;j<=top;j++)if(b[j]!=b[j-1]){num++;st[num]=st[j];b[num]=b[j];}
		top=num;
		for(int j=1;j<=top;j++)if(b[j]%a[i]==0){L[i]=st[j];break;}
	}
	top=0;
	for(int i=n;i>=1;i--){
		int num=0;top++;st[top]=i;b[top]=a[i];
		for(int j=1;j<=top;j++)b[j]=gcd(b[j],a[i]);
		for(int j=1;j<=top;j++)if(b[j]!=b[j-1]){num++;st[num]=st[j];b[num]=b[j];}
		top=num;
		for(int j=1;j<=top;j++)if(b[j]%a[i]==0){R[i]=st[j];break;}
	}
	Max=-1;
	for(int i=1;i<=n;i++){
		if(Max<R[i]-L[i]){Max=R[i]-L[i];tot=1;Ans[tot]=L[i];}
		else if(Max==R[i]-L[i])Ans[++tot]=L[i];
	}
	sort(Ans+1,Ans+tot+1);tot=unique(Ans+1,Ans+tot+1)-Ans-1;
	printf("%d %d\n",tot,Max);
	for(int i=1;i<=tot;i++)printf("%d ",Ans[i]);
	return 0;
}