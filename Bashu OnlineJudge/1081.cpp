#include<iostream>
#include<cstring>
using namespace std;
int main()
{
	string n;
	cin>>n;
	switch(n[n.length()-1])
	{
		case'1':cout<<6;break;
		case'2':cout<<6;break;
		case'3':cout<<6;break;
		case'4':cout<<6;break;
		case'5':cout<<6;break;
		case'6':cout<<8;break;
		case'7':cout<<6;break;
		case'8':cout<<6;break;
		case'9':cout<<6;break;
		case'0':cout<<8;break;
	}
	return 0;
}