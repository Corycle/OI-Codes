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
#define inf 0x7f7f7f7f7f7f7f7f
using namespace std;
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
long long read(){
	long long s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
bool p[555][555];
long long f[10][555][105],num[555],n,m,maxx,ans;
void dfs(int x,int y,int l,int k,int a,int b){
	if(l>n){
//		cout<<x<<" "<<y<<endl;
		p[x][y]=p[y][x]=true;
		num[x]=a;num[y]=b;
		return;
	}
	dfs(x<<1,y<<1,l+1,0,a,b);
	if(k==0){
		dfs(x<<1|1,y<<1,l+1,1,a+1,b);
		dfs(x<<1,y<<1|1,l+1,1,a,b+1);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	maxx=(1<<n)-1;
	dfs(0,0,1,0,0,0);
	for(i=0;i<=maxx;i++)f[1][i][num[i]]=1;
	for(i=1;i<=n;i++){
		for(j=0;j<=maxx;j++){
			for(k=0;k<=maxx;k++){
				if(!p[j][k])continue;
				for(int sum=num[k];sum<=m;sum++){
					if(sum+num[j]>m)continue;
					f[i][j][sum+num[j]]+=f[i-1][k][sum];
				}
			}
			if(i==n)ans+=f[i][j][m];
		}
	}
	printf("%lld",ans);
	return 0;
}