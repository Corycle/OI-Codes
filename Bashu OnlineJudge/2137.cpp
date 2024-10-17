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
queue<int>q;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int n,a[55][55],f[55],f1[55],ans1[55],ans2[55],cut;
void clear(queue<int>&q){
    queue<int>empty;
    swap(empty,q);
}
void init(){
	int i,j,k;
	while(1){
		while(scanf("%d",&k)){
			if(k==-2)break;
			if(k==-1){
				n--;
				return;
			}
			a[n][k]=1;
		}
		n++;
	}
}
void bfs(int x){
	int i,j,k;
	clear(q);
	q.push(x);
	f[x]=1;
	while(q.size()){
		k=q.front();
		q.pop();
		for(i=0;i<=n;i++){
			if(f[i]==0&&a[k][i]==1&&i!=cut){
				f[i]=1;
				q.push(i);
			}
		}
	}
}
void slove(){
	int i,j,k;
	for(i=1;i<n;i++){//去掉图中的点,依次判断是否为必经点 
		memset(f,0,sizeof(f));
		cut=i;
		bfs(0);
		if(!f[n]){
			ans1[0]++;
			ans1[ans1[0]]=i;
		}
    }
    cut=-1;
	for(i=1;i<=ans1[0];i++){//依次判断是否为分裂点 
		memset(f,0,sizeof(f));
		cut=ans1[i];
		bfs(0);
		memcpy(f1,f,sizeof(f1));
		memset(f,0,sizeof(f));
		bfs(ans1[i]);
		for(j=0;j<=n;j++){
			if(j!=cut&&f[j]==f1[j]){
				break;
			}
		}
		if(j==n+1){
			ans2[0]++;
			ans2[ans2[0]]=ans1[i];
		}
	}
	cout<<ans1[0]<<" ";
	for(i=1;i<=ans1[0];i++)cout<<ans1[i]<<" ";
	cout<<endl<<ans2[0]<<" ";
	for(i=1;i<=ans2[0];i++)cout<<ans2[i]<<" ";
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	init();
	slove();
	return 0;
}