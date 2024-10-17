#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=400005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
struct Dancing_Links_X{
	int n,m,tot,ans;
	int belong_row[N],belong_col[N];
	int down[N],up[N],R[N],L[N],row[N],col[N];
	void Prepare(){
		ans=inf;
		for(int i=0;i<=m;i++){
			down[i]=up[i]=i;
			R[i]=i-1;L[i]=i+1;
		}
		R[0]=m;L[m]=0;tot=m;
		for(int i=1;i<=n;i++)row[i]=-1;
	}
	void Insert(int x,int y){
		col[y]++;tot++;
		belong_row[tot]=x;
		belong_col[tot]=y;
		up[tot]=up[y];
		down[up[y]]=tot;
		down[tot]=y;up[y]=tot;
		if(row[x]==-1)row[x]=R[tot]=L[tot]=tot;
		else{
			L[tot]=L[row[x]];
			R[L[row[x]]]=tot;
			R[tot]=row[x];
			L[row[x]]=tot;
		}
	}
	void Remove(int c){//删除行 
		R[L[c]]=R[c];
		L[R[c]]=L[c];
		for(int i=up[c];i!=c;i=up[i]){
			for(int j=L[i];j!=i;j=L[j]){
				down[up[j]]=down[j];
				up[down[j]]=up[j];
				col[belong_col[j]]--;
			}
		}
	}
	void Resume(int c){//恢复行 
		R[L[c]]=c;
		L[R[c]]=c;
		for(int i=down[c];i!=c;i=down[i]){
			for(int j=L[i];j!=i;j=L[j]){
				down[up[j]]=j;
				up[down[j]]=j;
				col[belong_col[j]]++;
			}
		}
	}
	void Dance(int depth){
		if(L[0]==0){
			ans=min(ans,depth-1);
			return;
		}
		int c=L[0];
		for(int i=L[0];i!=0;i=L[i]){
			if(col[i]<col[c])c=i;
		}
		Remove(c);
		for(int i=up[c];i!=c;i=up[i]){
			for(int j=L[i];j!=i;j=L[j]){
				Remove(belong_col[j]);
			}
			Dance(depth+1);
			for(int j=R[i];j!=i;j=R[j]){
				Resume(belong_col[j]);
			}
		}
		Resume(c);
	}
}DLX;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	DLX.n=read();
	DLX.m=read();
	DLX.Prepare();
	for(int i=1;i<=DLX.n;i++){
		for(int j=1;j<=DLX.m;j++){
			int x=read();
			if(x==1)DLX.Insert(i,j);
		}
	}
	DLX.Dance(1);
	if(DLX.ans==inf)DLX.ans=-1;
	printf("%d",DLX.ans);
	return 0;
}