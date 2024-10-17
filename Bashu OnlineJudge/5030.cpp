#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
using namespace std;
int n,m,x,y,z;
int c,k,minn,p1,p2;
long long sum=0;
inline void search(int work,int l,int w){
	if(work==0){
		p1=l;
		p2=w;
	}
	else{
		if(k==1){
			if(l+1>n-c){
				k=2;
				search(work-1,l,w+1);
			}
			else if(n-c-l<=work)search(work-(n-c-l),n-c,w);
			else search(0,l+work,w);
		}
		else if(k==2){
			if(w+1>m-c){
				k=3;
				search(work-1,l-1,w);
			}
			else if(m-c-w<=work)search(work-(m-c-w),l,m-c);
			else search(0,l,w+work);
		}
		else if(k==3){
			if(l-1<1+c){
				k=4;
				search(work-1,l,w-1);
			}
			else if(l-1-c<=work)search(work-(l-1-c),1+c,w);
			else search(0,l-work,w);
		}
		else if(k==4){
			if(w-1<2+c){
				k=1;c++;
				search(work-1,l+1,w);
			}
			else if(w-2-c<=work)search(work-(w-2-c),l,2+c);
			else search(0,l,w-work);
		}
	}
}
int main()
{
//	freopen("calc.in","r",stdin);
//	freopen("calc.out","w",stdout);
	cin>>n>>m>>x>>y>>z;
	x++;y++;
	minn=min(n,m);
	for(int i=0;i<=(minn-1)/2;i++){
		if(1+i<=x&&x<=n-i&&y==1+i){c=i;k=1;break;}
		else if(1+i<=x&&x<=n-i&&y==m-i){c=i;k=3;break;}
		else if(1+i<=y&&y<=m-i&&x==1+i){c=i;k=4;break;}
		else if(1+i<=y&&y<=m-i&&x==n-i){c=i;k=2;break;}
	}
	search(z,x,y);
	printf("%d %d",p1-1,p2-1);
	return 0;
}
