#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define inf 0x3f3f3f3f
using namespace std;
int l[11],a[11][11],sum[11][11],ans,bjh[11][11],bjs[11][11],bjk[11][11],flag;
int lfind(int x,int y){
	if(x>=1&&x<=3&&y>=1&&y<=3)return 1;
	if(x>=1&&x<=3&&y>=4&&y<=6)return 2;
	if(x>=1&&x<=3&&y>=7&&y<=9)return 3;
	if(x>=4&&x<=6&&y>=1&&y<=3)return 4;
	if(x>=4&&x<=6&&y>=4&&y<=6)return 5;
	if(x>=4&&x<=6&&y>=7&&y<=9)return 6;
	if(x>=7&&x<=9&&y>=1&&y<=3)return 7;
	if(x>=7&&x<=9&&y>=4&&y<=6)return 8;
	if(x>=7&&x<=9&&y>=7&&y<=9)return 9;
}
void dfs(int x,int y,int tot){
//	cout<<x<<" "<<y<<endl;
//	cout<<tot<<endl;
	int t=x;
	x=l[t];
	if(t>9){
		flag=1;
		ans=max(ans,tot);
		return;
	}
	else if(a[x][y]!=0){
		if(y+1<=9)dfs(t,y+1,tot+sum[x][y]*a[x][y]);
		else dfs(t+1,1,tot+sum[x][y]*a[x][y]);
	}
	else if(a[x][y]==0){
		for(int i=1;i<=9;i++){
			int k=lfind(x,y);
			if(!bjh[x][i]&&!bjs[y][i]&&!bjk[k][i]){
				bjh[x][i]=bjs[y][i]=bjk[k][i]=1;
				a[x][y]=i;
				if(y+1<=9)dfs(t,y+1,tot+sum[x][y]*i);
				else dfs(t+1,1,tot+sum[x][y]*i);
				a[x][y]=0;
				bjh[x][i]=bjs[y][i]=bjk[k][i]=0;
			}
			
		}
	}
}
struct _{
	int h,s;
}o[15];
bool cmp(_ a,_ b){
	return a.s<b.s;
}
int main(){
	int i,j;
	int sx=1,sy=1,fx=9,fy=9;
	for(int k=6;k<=10;k++){
		for(i=sx;i<=fx;i++){
			for(j=sy;j<=fy;j++){
				sum[i][j]=k;
			}
		}
		sx++;sy++;fx--;fy--;
	}
	for(i=1;i<=9;i++){
		for(j=1;j<=9;j++){
			scanf("%d",&a[i][j]);
			bjh[i][a[i][j]]=bjs[j][a[i][j]]=bjk[lfind(i,j)][a[i][j]]=1;
		}
	}
	for(i=1;i<=9;i++){
		o[i].h=i;
		for(j=1;j<=9;j++){
			if(a[i][j]==0)o[i].s++;
		}
	}
	sort(o+1,o+10,cmp);
	for(i=1;i<=9;i++)l[i]=o[i].h;
	dfs(1,1,0);
	if(flag)printf("%d\n",ans);
	else printf("-1\n");
	return 0; 
}