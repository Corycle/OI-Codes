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
//如何吧一个森林转转化成一个树转化为二叉树 
int t[305][4]={0},v[305]={0},f[305][305]={0};
//t[i][0]左孩子 t[i][1]右孩子 t[i][2]该节点的最有一个孩子编号 t[i][3]存的值 
void Mtree(int n){
	int x,y;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&x,&y);
		t[i][3]=y;
		if(t[x][2]==0)t[x][0]=i;
		else t[t[x][2]][1]=i;
		t[x][2]=i;
	}
} 
void dp(int i,int j){ //f[i][j]以i为根节点选中的j门课程最大学分 
	int k,ans;
	if(f[i][j]>0)return; //剪枝 
	if(i==0||j==0)return;
	if(t[i][1]!=0)dp(t[i][1],j);
	f[i][j]=f[t[i][1]][j];
	for(int k=0;k<=j-1;k++){
		if(t[i][0]!=0)dp(t[i][0],k);
		if(t[i][1]!=0)dp(t[i][1],j-k-1);
		f[i][j]=max(f[i][j],f[t[i][0]][k]+f[t[i][1]][j-k-1]+t[i][3]);
	} 
} 
int main(){	
	int n,m;
	cin>>n>>m; 
	Mtree(n);
	dp(t[0][0],m);
	cout<<f[t[0][0]][m];
	return 0;
}