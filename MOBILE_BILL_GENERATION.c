#include<stdio.h>
int main()
{
	int n,noc,a,bill;
	printf("\n enter the month:");
	scanf("%d",&n);
	if((n==1)||(n==3)||(n==5)||(n==7)||(n==8)||(n==10)||(n==12))	
	{
		printf("\n enter number of calls for that month:");
		scanf("%d",&a);
		noc=31*a;
	}
	 if((n==4)||(n==6)||(n==9)||(n==11))
	{
		printf("\n enter number of calls for that month:");
		scanf ("%d",&a);
		noc=30*a;
	}
	 if (n==2)
	{
		printf("\n enter number of calls for that month");
		scanf("%d",&a);
		noc=28*a;
	}
	 if (n==13)
	{
		printf ("\n enter number of calls for that month:");
		scanf("%d",&a);
		noc=29*a;
	}
	printf("\n numbers of calls is %d",noc);
	printf("\n enter number of calls:");
	scanf("%d",&noc);
	if(noc<=280)
	{
		bill=noc*0.10;
	}
	else if(noc<=500)
	{
		bill=noc*0.15;
	}
	else if(noc<=750)
	{
		bill=noc*0.20;
	}
	else
	{
		bill=noc*0.25;
	}
	printf("\n the bill is %d",bill);
	
}
