#include<iostream>
#include<iomanip>
#include<cstdio>
#include<queue>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int n,d[100005],x,maxx,ans;
bool vis[100005];
struct que
{
	int x,d;
	friend bool operator <(const que &a,const que &b)
	{
		return a.d>b.d;
	}
};
priority_queue<que> q;
void bfs(int x,int op)
{
	if(op==0)
	{
		vector<int> a;
		while(x)
		{
			a.push_back(x%10);
			x/=10;
		}
		int l=a.size();
		for(int i=0;i<l;i++)
		{
			for(int j=i+1;j<l;j++)
			{
				swap(a[i],a[j]);
				int y=0;
				for(int k=l-1;k>=0;k--)
				{
					y=y*10+a[k];
				}
				swap(a[i],a[j]);
				if(vis[y]) continue;
				if(d[y]>((a[i]&a[j])+(a[i]^a[j]))*2)
				{
					d[y]=((a[i]&a[j])+(a[i]^a[j]))*2;
					q.push((que){y,d[y]});
//					cout<<y<<endl;
				}
			}
		}
	}
	else if(op==1)
	{
		if((int)log10(x)+2>maxx) return;
		vector<int> a;
		while(x)
		{
			a.push_back(x%10);
			x/=10;
		}
		int l=a.size();
		for(int i=0;i<l-1;i++)
		{
			if(a[i]>=a[i+1])
			{
				int y=0;
				for(int j=l-1;j>=i+1;j--)
				{
					y=y*10+a[j];
				}
				for(int j=a[i+1];j<=a[i];j++)
				{
					int sy=y*10+j;
					for(int k=i;k>=0;k--)
					{
						sy=sy*10+a[k];
					}
					if(vis[sy]) continue;
					if(d[sy]>j+(a[i]&a[i+1])+(a[i]^a[i+1]))
					{
						d[sy]=j+(a[i]&a[i+1])+(a[i]^a[i+1]);
						q.push((que){sy,d[sy]});
//						cout<<sy<<endl;
					}
				}
			}
		}
		if(a[l-1]>=a[0])
		{
			int y=0;
			for(int i=l-1;i>=0;i--)
			{
				y=y*10+a[i];
			}
			for(int j=a[0];j<=a[l-1];j++)
			{
				int sy=y*10+j;
				if(vis[sy]) continue;
				if(d[sy]>j+(a[0]&a[l-1])+(a[0]^a[l-1]))
				{
					d[sy]=j+(a[0]&a[l-1])+(a[0]^a[l-1]);
					q.push((que){sy,d[sy]});
//					cout<<sy<<endl;
				}
			}
			int sy;
			for(int j=a[0];j<=a[l-1];j++)
			{
				sy=j;
				for(int k=0;k<l;k++)
				{
					sy*=10;
				}
				sy+=y;
				if(vis[sy]) continue;
				if(d[sy]>j+(a[0]&a[l-1])+(a[0]^a[l-1]))
				{
					d[sy]=j+(a[0]&a[l-1])+(a[0]^a[l-1]);
					q.push((que){sy,d[sy]});
//					cout<<sy<<endl;
				}
			}
		}
	}
	else
	{
		if(x/10==0) return;
		vector<int> a;
		while(x)
		{
			a.push_back(x%10);
			x/=10;
		}
		int l=a.size();
		for(int i=1;i<l-1;i++)
		{
			if(a[i]>=a[i+1]&&a[i]<=a[i-1])
			{
				int y=0;
				for(int k=l-1;k>=i+1;k--)
				{
					y=y*10+a[k];
				}
				for(int k=i-1;k>=0;k--)
				{
					y=y*10+a[k];
				}
				if(vis[y]) continue;
				if(d[y]>a[i]+(a[i-1]&a[i+1])+(a[i-1]^a[i+1]))
				{
					d[y]=a[i]+(a[i-1]&a[i+1])+(a[i-1]^a[i+1]);
					q.push((que){y,d[y]});
				}
			}
		}
		if(a[0]>=a[1]&&a[0]<=a[l-1])
		{
			int y=0;
			bool flag=0;
			for(int k=l-1;k>=1;k--)
			{
				y=y*10+a[k];
			}
			if(vis[y]) flag=1;
			if(!flag)
			if(d[y]>a[0]+(a[1]&a[l-1])+(a[1]^a[l-1]))
			{
				d[y]=a[0]+(a[1]&a[l-1])+(a[1]^a[l-1]);
				q.push((que){y,d[y]});
			}
		}
		if(a[l-1]>=a[0]&&a[l-1]<=a[l-2])
		{
			int y=0;
			bool flag=0;
			for(int k=l-2;k>=0;k--)
			{
				y=y*10+a[k];
			}
			if(vis[y]) flag=1;
			if(!flag)
			if(d[y]>a[l-1]+(a[0]&a[l-2])+(a[0]^a[l-2]))
			{
				d[y]=a[l-1]+(a[0]&a[l-2])+(a[0]^a[l-2]);
				q.push((que){y,d[y]});
			}
		}
	}
}
int main()
{
	scanf("%d",&n);
	memset(d,0x3f,sizeof(d));
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		q.push((que){x,0});
		maxx=max((int)log10(x)+1,maxx);
	}
	while(!q.empty())
	{
		que u=q.top();
		q.pop();
		if(vis[u.x]) continue;
//		cout<<u.x<<" "<<u.d<<endl;
		vis[u.x]=1;
		ans+=u.d;
		for(int i=0;i<3;i++)
		{
			bfs(u.x,i);
		}
	}
//	for(int i=1;i<=100000;i++){
//		if(d[i]!=0x3f3f3f3f){
//			cout<<i<<" "<<d[i]<<endl;
//		}
//	}
	printf("%d",ans);
}