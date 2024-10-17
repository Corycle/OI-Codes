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
int a[205][205],f[205],n,m;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++){
		scanf("%d%d",&j,&k);
		a[j][k]=a[k][j]=1;
	}
	scanf("%d",&k);
	q.push(k);
	f[k]=1;
	int p;
	while(q.size()!=0){
		p=q.front();
		printf("%d ",p);
		q.pop();
		for(i=1;i<=n;i++){
			if(a[p][i]&&f[i]==0){
				f[i]=1;
				q.push(i);
			}
		}
	}
	return 0;
}