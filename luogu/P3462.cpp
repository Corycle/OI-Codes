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
int n,m,tot,Ans,a[N],b[N],c[N],num[N],sum[N];
void Update(int pos){
	if(!sum[pos]){
		int p=0;
		for(int i=pos+1;i<=tot;i++)if(sum[i]){p=i;break;}
		if(!p)return;
		sum[p]--;
		for(int i=p-1;i>=pos;i--)sum[i]+=b[i+1]/b[i];
	}
	sum[pos]--;Ans++;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	m=read();n=read();
	for(int i=1;i<=m;i++)c[i]=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)b[i]=a[i];
	tot=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++)num[lower_bound(b+1,b+tot+1,a[i])-b]++;
	for(int i=1;i<=m;i++){
		for(int j=tot;j>=1;j--){sum[j]+=c[i]/b[j];c[i]%=b[j];}
	}
	for(int i=1;i<=tot;i++)while(num[i]--)Update(i);
	printf("%d\n",Ans);
	return 0;
}
