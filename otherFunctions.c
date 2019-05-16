#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "structure.h"
char* filename(char cf[],int c)
  {
    static char cfn[25];
	strcpy(cfn,cf);
   // printf("%s",cfn);
	cfn[strlen(cfn)]='\0';
	int fl=strlen(cfn),rn=0;
	//printf("%d",fl);
	while(c!=0)
	 {
       rn=rn*10+c%10;
       c/=10;
     }
    while(rn!=0)
	 {
       cfn[fl++]=rn%10+48;
       rn/=10;
     }
    cfn[fl++]='\0';
    strcat(cfn,".opm");
    cfn[fl+4]='\0';
	//printf("file=%s",cfn);
	return cfn;
  }



int IsSame(int c) //file comparison
{
	FILE *fp1,*fp2;
	char c1,c2,f1[25],f2[25];
    strcpy(f1,filename("Conflict_V",c));
    strcpy(f2,filename("Conflict_V",c-3));
	fp1=fopen(f1,"r");
	fp2=fopen(f2,"r");
	//printf("%s------------%s",f1,f2);
	//if(fp1==NULL ||fp2==NULL) printf("\t\t%s and %s   NOTFOUND",f1,f2);
	while((c1=fgetc(fp1))!=EOF && (c2=fgetc(fp2))!=EOF )
	{
		//printf("%c--%c  ",c1,c2);
		if(c1!=c2)
			return 0;
	}
	fprintf(flog,"\n\nSame conflict-files are generated for last 2 iterations...conflicts are not being resolved.....\n");
	return 1;
}
