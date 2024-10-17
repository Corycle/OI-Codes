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
const int M=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int vis[N];
char a[M][M];
int id1(int x,int y){return (x-1)*9+y;}//每一个格子刚好出现一个数
int id2(int x,int y){return 81+(x-1)*9+y;}//每一行刚好出现1~9
int id3(int x,int y){return 162+(x-1)*9+y;}//每一列刚好出现1~9
int id4(int x,int y,int k){//每一宫刚好出现1~9
	return 243+((x-1)/3*3+(y-1)/3)*9+k;
}
int Num(int x,int y,int z){
	return (x-1)*81+(y-1)*9+(z-1)+1;
}
struct Dancing_Links_X{
	int n,m,tot;
	int belong_row[N],belong_col[N],data[N];
	int down[N],up[N],L[N],R[N],row[N],col[N];
	void Prepare(){
		for(int i=0;i<=m;i++){
			down[i]=up[i]=i;
			L[i]=i-1;R[i]=i+1;
		}
		L[0]=m;R[m]=0;tot=m;
		for(int i=1;i<=n;i++)row[i]=-1;
	}
	void Insert(int x,int y){
		col[y]++;
		data[++tot]=y;
		belong_row[tot]=x;
		belong_col[tot]=y;
		up[tot]=up[y];
		down[up[y]]=tot;
		down[tot]=y;
		up[y]=tot;
		if(row[x]==-1)row[x]=L[tot]=R[tot]=tot;
		else{
			R[tot]=R[row[x]];
			L[R[row[x]]]=tot;
			L[tot]=row[x];
			R[row[x]]=tot;
		}
	}
	void Remove(int c){//删除行 
		L[R[c]]=L[c];
		R[L[c]]=R[c];
		for(int i=up[c];i!=c;i=up[i]){
			for(int j=R[i];j!=i;j=R[j]){
				down[up[j]]=down[j];
				up[down[j]]=up[j];
				col[belong_col[j]]--;
			}
		}
	}
	void Resume(int c){//恢复行 
		L[R[c]]=c;
		R[L[c]]=c;
		for(int i=down[c];i!=c;i=down[i]){
			for(int j=R[i];j!=i;j=R[j]){
				down[up[j]]=j;
				up[down[j]]=j;
				col[belong_col[j]]++;
			}
		}
	}
	void Dance(int depth){
		if(R[0]==0){
			for(int i=1;i<=9;i++){
				for(int j=1;j<=9;j++){
					for(int k=1;k<=9;k++){
						if(vis[Num(i,j,k)]){
							printf("%d",k);
						}
					}
				}
				printf("\n");
			}
			exit(0);
		}
		int c=R[0];
		for(int i=R[0];i!=0;i=R[i]){
			if(col[i]<col[c])c=i;
		}
		Remove(c);
		for(int i=up[c];i!=c;i=up[i]){
			vis[belong_row[i]]=1;
			for(int j=R[i];j!=i;j=R[j]){
				Remove(belong_col[j]);
			}
			Dance(depth+1);
			for(int j=L[i];j!=i;j=L[j]){
				Resume(belong_col[j]);
			}
			vis[belong_row[i]]=0;
		}
		Resume(c);
	}
}DLX;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	DLX.n=729;DLX.m=324;DLX.Prepare();
	for(int i=1;i<=9;i++)scanf("%s",a[i]+1);
	for(int i=1;i<=9;i++){
		for(int j=1;j<=9;j++){
			for(int k=1;k<=9;k++){
				if(a[i][j]=='?'||a[i][j]-'0'==k){
					int num=Num(i,j,k);
					DLX.Insert(num,id1(i,j));
					DLX.Insert(num,id2(i,k));
					DLX.Insert(num,id3(j,k));
					DLX.Insert(num,id4(i,j,k));
				}
			}
		}
	}
	DLX.Dance(1);
	return 0;
}