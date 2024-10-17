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
int f[12][10]={0};
long long power[13];
void PreWork(){
	int i,j,k;
    power[0]=1;
    for(i=1;i<=12;i++)power[i]=power[i-1]*10;
    for(i=0;i<=9;i++)f[1][i]=1;
	for(i=2;i<=11;i++)
        for(j=0;j<=9;j++)
            for(k=0;k<=9;k++)
                if(abs(j-k)>=2)f[i][j]+=f[i-1][k];
}
int Count(int x){
	int w=0,y,i,j,pre,ans=0;
	while(power[w]<=x)w++;
	for(i=1;i<w;i++)
		for(j=1;j<=9;j++)ans+=f[i][j];
	y=x/power[w-1];
	for(j=1;j<y;j++)ans+=f[w][j];
	pre=y;
	x%=power[w-1];
	for(i=w-1;i>=1;i--){
		y=x/power[i-1];
    	for(j=0;j<y;j++)if(abs(j-pre)>=2)ans+=f[i][j];
    	if(abs(pre-y)<2)break;
    	pre=y;
    	x%=power[i-1];
	}
	return ans;
}
int main(){
	int a,b;
	cin>>a>>b;
	PreWork();
	cout<<Count(b+1)-Count(a)<<endl;
	return 0;
}
