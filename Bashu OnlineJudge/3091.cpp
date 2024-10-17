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
long long read(){
	long long s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
const long long inf=0x7f7f7f7f7f7f7f7f;
long long n,m,h[205],dis[205][205],vis[205][205];
queue<long long>q,s;
long long Find(long long x){
	long long l=1,r=n;
	while(l<=r){
		int mid=(l+r)/2;
		if(h[mid]<=x)l=mid+1;
		else r=mid-1;
	}
	return r;
}
void spfa(){
	long long i,j,k;
	memset(dis,0x7f,sizeof(dis));
	dis[1][0]=0;
	q.push(1);s.push(0);
	while(q.size()){
		long long x=q.front(),num=s.front();
		q.pop();s.pop();
//		cout<<x<<" "<<num<<" "<<dis[x][num]<<endl;
		vis[x][num]=0;
//		if(x!=n&&dis[x][num]+1<dis[x+1][0]){
//			dis[x+1][0]=dis[x][num]+1;
//			if(!vis[x+1][0]){
//				vis[x+1][0]=1;
//				q.push(x+1);s.push(0);
//			}
//		}
		if(x!=1&&dis[x][num]+1<dis[x-1][num+1]){
			dis[x-1][num+1]=dis[x][num]+1;
			if(!vis[x-1][num+1]){
				vis[x-1][num+1]=1;
				q.push(x-1);s.push(num+1);
			}
		}
		long long p=min((long long)(h[x]+pow(2,num)),h[n]);
//		cout<<p<<" "<<Find(p)<<endl;
//		system("pause");
		for(i=Find(p);i>x;i--){
			long long y=i;
			if(dis[x][num]+1<dis[y][0]){
				dis[y][0]=dis[x][num]+1;
				if(!vis[y][0]){
					vis[y][0]=1;
					q.push(y);s.push(0);
				}
			}
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	long long i,j,k;
	n=read();
	for(i=1;i<=n;i++){
		h[i]=read();
	}
	spfa();
	printf("%lld",dis[n][0]==inf?-1:dis[n][0]);
	return 0;
}