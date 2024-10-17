#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
using namespace std;
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,ans;
bool used[30005];
struct _{
	int s,e,v;
}d[5005];
bool cmp(_ x,_ y){
	return x.e<y.e;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	m=read();n=read();
	for(i=1;i<=n;i++){
		d[i].s=read();d[i].e=read();d[i].v=read();
	}
	sort(d+1,d+n+1,cmp);
	for(i=1;i<=n;i++){
		k=0;
		for(j=d[i].s;j<=d[i].e;j++){
			if(used[j])k++;
		}
		if(k>=d[i].v)continue;
		for(j=d[i].e;j>=d[i].s;j--){
			if(!used[j]){
				k++;
				ans++;
				used[j]=true;
			}
			if(k==d[i].v)break;
		}
	}
	printf("%d",ans);
	return 0;
}