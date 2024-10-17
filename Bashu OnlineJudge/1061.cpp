#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
int main(){
	char a[1000000];
	int i,j,k=0,x=0,y=0,b=0;
	while(a[b]!='E'){
		b++;
		cin>>a[b];
	}
	for(i=1;i<b;i++){
		if(a[i]=='W')x++;
		if(a[i]=='L')y++;
		if((x>=11||y>=11)&&abs(x-y)>1){
			printf("%d:%d\n",x,y);
			x=0;y=0;
			k=0;
		}
	}
	if(((x!=0||y!=0)&&k==1)||k==0){
		printf("%d:%d\n\n",x,y);
		x=0;y=0;
	}
	k=0;
	for(i=1;i<b;i++){
		if(a[i]=='W')x++;
		else y++;
		if((x>=21||y>=21)&&abs(x-y)>1){
			printf("%d:%d\n",x,y);
			x=0;y=0;
			k=1;
		}
	}
	if(((x!=0||y!=0)&&k==1)||k==0)
	printf("%d:%d",x,y);
	return 0;
}