#include<iostream>
using namespace std;
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
long long dy[4]={2,1,2,1},dx[4]={1,2,-1,-2},xx[10005],yy[10005],js=1,bj=1;
long long q,m,n,x1,y1,x2,y2,dp[55][55],p[55][55];
void did_dp()
{
	cin>>x1>>y1>>x2>>y2;
	dp[x1][y1]=1;
	int i,j;
    for(i=x1+1;i<=n;i++) 
    for(j=1;j<=m;j++) 
    {
        if(i-2>0&&j-1>0)dp[i][j]+=dp[i-2][j-1];
        if(i-2>0&&j+1<=m)dp[i][j]+=dp[i-2][j+1];
        if(i-1>0&&j-2>0)dp[i][j]+=dp[i-1][j-2];
        if(i-1>0&&j+2<=m)dp[i][j]+=dp[i-1][j+2];
    }
    cout<<dp[x2][y2];
}
void printf()
{
    int i,j; 
	for(i=0;i<js-1;i++)
	cout<<"("<<xx[i]<<","<<yy[i]<<")->";
	cout<<"("<<xx[js-1]<<","<<yy[js-1]<<")";
}
void dfs(int x,int y)
{
	int i,j;
	if(bj)
	if(x==m&&y==n)
	{
		bj=0;
		printf();
	}	
	else
	{
		for(i=0;i<=3;i++)
		{
			int nowx=x+dx[i],nowy=y+dy[i];
			if(nowx>=1&&nowx<=m&&nowy>=1&&nowy<=n&&p[nowx][nowy]==0)
			{
				p[nowx][nowy]=1;
				xx[js]=nowx;yy[js]=nowy;
				js++;
				dfs(nowx,nowy);
				p[nowx][nowy]=0;
				xx[js]=0;yy[js]=0;
				js--;
			}
		}
	}
	else return;
}
int main() 
{
	cin>>q>>m>>n;
	p[1][1]=1;xx[0]=1;yy[0]=1;
	if(q==1) dfs(1,1);
	else did_dp();
}