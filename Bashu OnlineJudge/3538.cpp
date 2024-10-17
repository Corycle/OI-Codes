#include<iostream>
#include<cstring>
using namespace std;
bool ec[105][105];
int mp[105][105],ct[105],study[105],dis[105];
int n,k,m,bg,ed,flag;
bool pd(int x){
    for(int i=1;i<=k;i++){
        if(study[i]&&ec[ct[x]][i])return 0;
    }
    return 1;
}
int search(int x){
	int i,j;
    flag=0;
    if(!study[ct[x]]){
		flag=1;
		study[ct[x]]=1;
	}
    for(i=1;i<=n;i++){
        if(mp[x][i]+dis[x]<dis[i]&&pd(i)){dis[i]=mp[x][i]+dis[x];search(i);}
    }
    if(flag==1)study[ct[x]]=0;
}
int main(){
	int i,j;
    cin>>n>>k>>m>>bg>>ed;
    for(i=1;i<=n;i++)cin>>ct[i];
    for(i=1;i<=k;i++)
		for(j=1;j<=k;j++)
			cin>>ec[i][j];
    memset(mp,0x3f,sizeof(mp));
    for(int i=1;i<=n;i++)dis[i]=0x3f3f3f3f;
    for(int i=1;i<=m;i++){
        int x,y,v;
        cin>>x>>y>>v;
        mp[x][y]=mp[y][x]=v;
    }
    dis[bg]=0;
    search(bg);
    if(dis[ed]!=0x3f3f3f3f)cout<<dis[ed];
    else cout<<-1;
    return 0;
}