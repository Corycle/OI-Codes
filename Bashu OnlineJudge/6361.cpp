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
#include<set>
#define ll long long
#define multi_it multiset<int>::iterator
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
multiset<int>F;
int n,a[N],b[N],c[N],t1[N],t2[N],Ans[N];
bool cmp(int x,int y){return a[x]<a[y];}
int Solve(){
//	sort(t1+1,t1+t1[0]+1);
//	sort(t2+1,t2+t2[0]+1);
	int pos1=1,pos2=1,ans=0;
	while(pos1<=t1[0]&&pos2<=t2[0]){
		if(t2[pos2]>t1[pos1]){
			ans++;pos1++;
		}
		pos2++;
	}
	return ans;
}
int main(){
//	freopen("card.in","r",stdin);
//	freopen("card.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)c[i]=i;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=n;i++)F.insert(b[i]);
	for(int i=1;i<=n;i++)t1[++t1[0]]=a[i];
	for(int i=1;i<=n;i++)t2[++t2[0]]=b[i];
	sort(t1+1,t1+t1[0]+1);sort(t2+1,t2+t2[0]+1);
	int Sum=Solve(),sum=0;sort(c+1,c+n+1,cmp);
	for(int i=1;i<=n;i++){
		int ans=0;
		multi_it it=F.end();it--;
		if((*it)>a[i]){
			int l=*F.upper_bound(a[i]),r=1e9;
			while(l<=r){
				int mid=(l+r)>>1;
				it=F.upper_bound(mid);it--;
				int x=*it;multi_it tmp=it;t1[0]=t2[0]=0;
				for(it=F.begin();it!=F.end();it++){
					if(it!=tmp)t2[++t2[0]]=*it;
				}
				for(int j=1;j<=n;j++){
					if(c[j]>i)t1[++t1[0]]=a[c[j]];
				}
				if(Solve()+sum+1==Sum){ans=x;l=mid+1;}
				else r=mid-1;
			}
		}
		if(!ans){
			int l=1,r=a[i];
			while(l<=r){
				int mid=(l+r)>>1;
				it=F.upper_bound(mid);it--;
				int x=*it;multi_it tmp=it;t1[0]=t2[0]=0;
				for(it=F.begin();it!=F.end();it++){
					if(it!=tmp)t2[++t2[0]]=*it;
				}
				for(int j=1;j<=n;j++){
					if(c[j]>i)t1[++t1[0]]=a[c[j]];
				}
				if(Solve()+sum==Sum){ans=x;l=mid+1;}
				else r=mid-1;
			}
		}
		Ans[i]=ans;if(Ans[i]>a[i])sum++;
		it=F.lower_bound(ans);F.erase(it);
	}
	for(int i=1;i<=n;i++)printf("%d ",Ans[i]);
	return 0;
}