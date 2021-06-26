# include<stdio.h>
int judgeyear(int year)
{
	if (year%4==0){
	
	if (year%100==0&&year%400!=0) return 0;
	else return 1;
	}
	return 0;
}
int main(){
	int n,i,j,a;
	int second1,minute1,hour1,day1,month1,year1;
	int second2,minute2,hour2,day2,month2,year2;
	int month[2][13]={0,31,28,31,30,31,30,31,31,30,31,30,31,
	                  0,31,29,31,30,31,30,31,31,30,31,30,31};
	int daysum;int secondsum;
	
	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf("%d:%d:%d %d.%d.%d",&hour1,&minute1,&second1,&day1,&month1,&year1);
		
		daysum=(year1-2000)*365+(year1-1-1996)/4-(year1-1-1900)/100
		+(year1-1-1600)/400;    //先计算前几年的天数 
		
		a=judgeyear(year1);
		for(j=0;j<month1;j++) daysum+=month[a][j];
		daysum+=day1;
		secondsum=(hour1*60+minute1)*60+second1;
		day2=daysum%100;
		if(day2==0) {
		day2=100;daysum-=100;}
		daysum=daysum/100;
		month2=daysum%10;month2+=1;
		daysum=daysum/10;
		year2=daysum;
		
		secondsum=secondsum*1000;
	    secondsum=secondsum/864;
		secondsum=secondsum;
	    second2=secondsum%100;
	    secondsum=secondsum/100;
	    minute2=secondsum%100;
	    secondsum=secondsum/100;
	    hour2=secondsum%10;
		printf("%d:%d:%d %d.%d.%d\n",hour2,minute2,second2,day2,month2,year2);
	}
	return 0;
}
