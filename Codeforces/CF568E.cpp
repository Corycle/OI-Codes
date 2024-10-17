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
int n,m,a[N],b[N],c[N],f[N],pos[N],lst[N],vis[N],Ans[N];
void GetVal(int x,int k,int &val){
	int tmp=lower_bound(b+1,b+m+1,k)-b-1;
	vis[tmp]=1;val=Ans[x]=b[tmp];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();a[++n]=inf;
	for(int i=1;i<=n;i++)c[i]=inf;
	m=read();
	for(int i=1;i<=m;i++)b[i]=read();
	sort(b+1,b+m+1);
	for(int i=1;i<=n;i++){
		if(a[i]!=-1){
			int j=lower_bound(c+1,c+n+1,a[i])-c-1;
			f[i]=j+1;lst[i]=pos[j];c[j+1]=a[i];pos[j+1]=i;
		}
		else{
			int j=n;
			for(int k=m;k>=1;k--){
				while(c[j]>=b[k])j--;
				c[j+1]=b[k];pos[j+1]=i;
			}
		}
	}
	int x=n,len=f[n],val=a[n];
	while(len--){
		if(a[x]!=-1){
			if(a[lst[x]]!=-1)val=a[lst[x]];
			else GetVal(lst[x],a[x],val);
			x=lst[x];
		}
		else{
			bool flag=false;
			for(int k=x-1;k>=1;k--)if(a[k]!=-1&&f[k]==len&&a[k]<val){x=k;val=a[x];flag=true;break;}
			if(flag)continue;
			for(int k=x-1;k>=1;k--)if(a[k]==-1){GetVal(k,val,val);x=k;break;}
		}
	}
	int p=1;
	for(int i=1;i<=n;i++)if(a[i]!=-1)Ans[i]=a[i];
	for(int i=1;i<=n;i++)if(!Ans[i]){while(vis[p])p++;vis[p]=1;Ans[i]=b[p];}
	for(int i=1;i<n;i++)printf("%d ",Ans[i]);
	return 0;
}
