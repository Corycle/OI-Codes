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
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int read(){
	int s=0,fl=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')fl=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*fl;
}
int n,l[100005],r[100005],f[100005],m;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();
	f[1]=1;
	for(i=2;i<=n;i++){
		j=read();k=read();
		if(!f[j])continue;
		if(k==0){
			r[l[j]]=i;
			l[i]=l[j];
			l[j]=i;
			r[i]=j;
		}
		else{
			l[r[j]]=i;
			r[i]=r[j];
			r[j]=i;
			l[i]=j;
		}
		f[i]=1;
//		for(k=1;k<=n;k++){
//		if(f[k]){
//			while(f[l[k]])k=l[k];
//			while(f[r[k]]){
//				printf("%d ",k);
//				k=r[k];
//			}
//			printf("%d \n",k);
//			break;
//		}
//	}
	}
	m=read();
	for(i=1;i<=m;i++){
		j=read();
		if(!f[j])continue;
		l[r[j]]=l[j];
		r[l[j]]=r[j];
		f[j]=0;
	}
	for(i=1;i<=n;i++){
		if(f[i]){
			while(f[l[i]])i=l[i];
			while(f[r[i]]){
				printf("%d ",i);
				i=r[i];
			}
			printf("%d\n",i);
			break;
		}
	}
	return 0;
}