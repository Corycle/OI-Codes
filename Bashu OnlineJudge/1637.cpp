#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
using namespace std;
struct _233{
	int renshu;
	int juli;
	char place[200];
};
int main(){
	_233 a[10000];
	int i=0,j,l,o;
	long long k,s=10000000000000;
	do{
		i++;
		cin>>a[i].renshu>>a[i].juli>>a[i].place;
	}while(a[i].juli!=0);
	for(j=1;j<=i;j++){
		k=0;
		for(l=1;l<=i;l++){
			if(l==j)continue;
			else k+=a[l].renshu*(abs(a[j].juli-a[l].juli));
		}
		if(s>k){
			o=j;s=k;
		}
	}
	cout<<a[o].place<<" "<<s;
	return 0;
}
