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
const int N=105;
const int M=30;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,Ans,a[N];
void DFS(int depth,int sum){
//	cout<<"DFS: "<<depth<<" "<<sum<<endl;
	if(sum>Ans)return;
	if(depth==-1){Ans=sum;return;}
	int tmp=0,Min=inf,id=0;
	for(int i=1;i<=n;i++)tmp+=((a[i]>>depth)&1);
	if(!(tmp&1)){DFS(depth-1,sum);return;}
	for(int i=1;i<=n;i++){
		if((a[i]>>depth)&1){
			int dlt=(a[i]&((1<<depth)-1))+1;
			if(dlt<Min){Min=dlt;id=i;}
		}
	}
	if(id){tmp=a[id];a[id]=(1<<depth)-1;DFS(depth-1,sum+Min);a[id]=tmp;}
	Min=inf;id=0;
	for(int i=1;i<=n;i++){
		if(!((a[i]>>depth)&1)){
			int dlt=(1<<depth)-(a[i]&((1<<depth)-1));
			if(dlt<Min){Min=dlt;id=i;}
		}
	}
	if(id){tmp=a[id];a[id]=(1<<depth);DFS(depth-1,sum+Min);a[id]=tmp;}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		n=read();
		for(int i=1;i<=n;i++)a[i]=read();
		if(n==2)printf("%d\n",abs(a[1]-a[2]));
		else{Ans=inf;DFS(M,0);printf("%d\n",Ans);}
	}
	return 0;
}