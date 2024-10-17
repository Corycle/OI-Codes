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
const int N=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n;
string s,a1[N],a2[N];
string A[N][N],B[N][N];
map<string,int>id1,id2;
int p1[N],p2[N],num[N];
int m1[N][N],m2[N][N],q[N][N];
void Solve(){
	for(int i=1;i<=n;i++){
		p1[i]=p2[i]=num[i]=0;
	}
	int Num=0;
	while(Num<n){
		for(int i=1;i<=n;i++)q[i][0]=0;
		for(int i=1;i<=n;i++){
			if(!p1[i]){
				int x=m1[i][++num[i]];
				q[x][++q[x][0]]=i;
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=q[i][0];j++){
				if(!p2[i]){
					p1[q[i][j]]=i;
					p2[i]=q[i][j];
					Num++;
				}
				else if(m2[i][q[i][j]]<m2[i][p2[i]]){
					p1[p2[i]]=0;
					p1[q[i][j]]=i;
					p2[i]=q[i][j];
				}
			}
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	while(scanf("%d",&n)!=EOF){
		for(int i=1;i<=n;i++){
			cin>>a1[i];id1[a1[i]]=i;
			for(int j=1;j<=n;j++){
				cin>>A[i][j];
			}
		}
		for(int i=1;i<=n;i++){
			cin>>a2[i];id2[a2[i]]=i;
			for(int j=1;j<=n;j++){
				cin>>B[i][j];
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				m1[i][j]=id2[A[i][j]];
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				m2[i][id1[B[i][j]]]=j;
			}
		}
		Solve();
		for(int i=1;i<=n;i++){
			cout<<a1[i]<<" "<<a2[p1[i]]<<endl;
		}
	}
	return 0;
}