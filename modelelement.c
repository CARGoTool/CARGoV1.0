#include <stdio.h>
#include <string.h>
#include <io.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
}node;

node *start1=NULL;

void insert_el(int);
int del_el(int);

FILE *fp,*fp1, *fp2, *fp3;

int modlroot(void)
{
    char input[100], extr[2], tokenid[6], reverse[200], filename[15];
    int num,digit,m=0,count=0,f,neg, size, i, j, k, flag, temp=0, ac_count=0;

    fp=fopen("codtoken.opm","r");
    fp1=fopen("MOD_EL.opm","w");
    fp2=fopen("Actors.opm", "w");

    filename[0]='\0';
    size = _filelength(_fileno(fp));
	//printf("size= %d",size);
	while(size>0)
	{
		/* Reading each line of Codtoken.opm*/

		/*Reading the Token Id*/
		neg=1;
		num=0;
		fread(extr, 1, 1, fp);
		size--;

		/* Checking if first character is a negative sign. If so, then setting the negative flag*/
		if(extr[0] == '-')
		{
			neg=-1;
			fread(extr, 1, 1, fp);
			size--;
		}
		/*Building the integer from string*/
		while(size>0 && extr[0]!='\t')
		{
			digit=extr[0]-48;//char to decimal
			num = num*10+digit;
			fread(extr, 1, 1, fp);
			size--;
		}
		/*Setting the appropriate sign of the number*/
		num *= neg;
		//printf("\nThe Number extracted is %d.", num);
		//getchar();
		/*Reading the Token*/
		input[0] = '\0';
		fread(extr, 1, 1, fp);
		size--;
		while(size>0 && extr[0]!='\n')
		{
			extr[1]='\0';
			strcat(input, extr);
			fread(extr, 1, 1, fp);
			size--;
		}
		if(extr[0]=='\n')
			size--;
		if(input[0]=='\0')
			continue;
		//printf("\nCodToken line read is : %d \t %s\n", num, input);	
		
        f=0;
		if(num == 208) //'Actor' keyword check
		{
			if(ac_count != 0)
				fclose(fp3);
			ac_count++;
			i=0;
			num=ac_count;
			while(num>0)
			{
				digit=num%10;
				tokenid[i]=digit+48;
				num/=10;
				i++;
			}
			tokenid[i]='\0';
			/*Reversing the tokenid string to get the correct string for integer token id*/
			k=0;
			for(j=i-1; j>=0; j--)
			{
				reverse[k] = tokenid[j];
				k++;
			}
			reverse[k] = '\0';
			strcpy(filename, "VAR");
			strcat(filename, reverse); //actors number
			strcat(filename, ".opm");
			fp3=fopen(filename, "w");

			/*Reading the Token Id*/
			neg=1;
			num=0;
			fread(extr, 1, 1, fp);
			size--;
			/* Checking if first character is a negative sign. If so, then setting the negative flag*/
			if(extr[0] == '-')
			{
				neg=-1;
				fread(extr, 1, 1, fp);
				size--;
			}
			/*Building the integer from string*/
			while(size>0 && extr[0]!='\t')
			{
				digit=extr[0]-48;
				num = num*10+digit;
				fread(extr, 1, 1, fp);
				size--;
			}
			/*Setting the appropriate sign of the number*/
			num *= neg;

			/*Reading the Token*/
			input[0] = '\0';
			fread(extr, 1, 1, fp);
			size--;
			while(size>0 && extr[0]!='\n')
			{
				strcat(input, extr);
				fread(extr, 1, 1, fp);
				size--;
			}
			if(extr[0]=='\n')
				size--;
			strcpy(reverse, "Actor");
			i=0;
			num=ac_count;
			while(num>0)
			{
				digit=num%10;
				tokenid[i]=digit+48;
				num/=10;
				i++;
			}
			tokenid[i]='\0';
			/*Reversing the tokenid string to get the correct string for integer token id*/
			k=5;
			for(j=i-1; j>=0; j--)
			{
				reverse[k] = tokenid[j];
				k++;
			}
			reverse[k] = '\0';
			strcat(reverse, "\t");
			//printf("\ninput: %s\n",input);
			strcat(reverse, input);
			strcat(reverse, "\n");
			fwrite(reverse, 1, strlen(reverse), fp2);

			//goal checking(root)
			fread(extr, 1, 1, fp);
			size--;
			while(size>0 && extr[0]!='\n')
			{
				strcat(input, extr);
				fread(extr, 1, 1, fp);
				size--;
			}
			fread(extr, 1, 1, fp);
			size--;
			count=0;
			while(count<4)
			{
				while(size>0 && extr[0]!='\n')
				{
					strcat(input, extr);
					fread(extr, 1, 1, fp);
					size--;
				}
			
				//printf("%s\n",input);
				if(extr[0]=='\n')
				size--;
				count++;
			}
			//reading the root identifier

			fread(extr, 1, 1, fp);
			size--;
			/* Checking if first character is a negative sign. If so, then setting the negative flag*/
			if(extr[0] == '-')
			{
				neg=-1;
				fread(extr, 1, 1, fp);
				size--;
			}
			/*Building the integer from string*/
			while(size>0 && extr[0]!='\t')
			{
				digit=extr[0]-48;
				num = num*10+digit;
				fread(extr, 1, 1, fp);
				size--;
			}
			
			/*Reading the Token*/
			input[0] = '\0';
			fread(extr, 1, 1, fp);
			while(extr[0]!='\n')
			{
				strcat(input, extr);
				fread(extr, 1, 1, fp);
			}
			/*Setting the appropriate sign of the number*/
			num *= neg;

			//writing root to file
			temp=num=num*(-1);
			num=temp;
			i=0;
			//printf("%d\n",num);
			while(num>0)
			{
				digit=num%10;
				tokenid[i]=digit+48;
				num/=10;
				i++;
			}

			tokenid[i]='-';
			i++;
			tokenid[i]='\0';
			//printf("%s\n",tokenid);
			/*Reversing the tokenid string to get the correct string for integer token id*/
			k=0;
			for(j=i-1; j>=0; j--)
			{
				reverse[k] = tokenid[j];
				k++;
			}
			reverse[k] = '\0';
			strcat(reverse, "\n");
			fwrite(reverse, 1, k+1, fp1);
			fwrite("V",1,1,fp3);
			
			tokenid[i-1]='\0';
			i--;
			
			k=0;
			for(j=i-1; j>=0; j--)
			{
				reverse[k] = tokenid[j];
				k++;
			}
			reverse[k] = '\0';
			strcat(reverse, "\t");
			strcat(reverse, input);
			strcat(reverse, "\n");
			fwrite(reverse, 1, strlen(reverse), fp3);
			
			//printf("%d\n",num);	//root

		}
 		else if(num==213 || num==218 || num==237)//'Goal' 'Task' 'Resource' check
        {
        	/*Reading the Token Id*/
			neg=1;
			num=0;
			fread(extr, 1, 1, fp);
			size--;
			/* Checking if first character is a negative sign. If so, then setting the negative flag*/
			if(extr[0] == '-')
			{
				neg=-1;
				fread(extr, 1, 1, fp);
				size--;
			}
			/*Building the integer from string*/
			while(size>0 && extr[0]!='\t')
			{
				digit=extr[0]-48;
				num = num*10+digit;
				fread(extr, 1, 1, fp);
				size--;
			}
			/*Setting the appropriate sign of the number*/
			num *= neg;

			/*Reading the Token*/
			input[0] = '\0';
			fread(extr, 1, 1, fp);
			size--;
			while(size>0 && extr[0]!='\n')
			{
				strcat(input, extr);
				fread(extr, 1, 1, fp);
				size--;
			}
			if(extr[0]=='\n')
				size--;
			//printf("\nCodToken line read is : %d \t %s", num, input);
			//getchar();
			if(num<0)
			{
				f=del_el(num);
				i=0;
				flag=1;
				temp=num=num*(-1);
				
				while(num>0)
				{
					digit=num%10;
					tokenid[i]=digit+48;
					num/=10;
					i++;
				}
				if(flag == 1)
				{
					tokenid[i]='V';
					i++;
				}
				tokenid[i]='\0';
				/*Reversing the tokenid string to get the correct string for integer token id*/
				k=0;
				for(j=i-1; j>=0; j--)
				{
					reverse[k] = tokenid[j];
					k++;
				}
				reverse[k] = '\0';
				strcat(reverse, "\t");
				strcat(reverse, input);
				strcat(reverse, "\n");
				fwrite(reverse, 1, strlen(reverse), fp3);
			}

			if(!f)
			{
				/*Converting the token id from integer to string in reverse order*/
				i=0;
				flag=0;
				num=temp;
				
				while(num>0)
				{
					digit=num%10;
					tokenid[i]=digit+48;
					num/=10;
					i++;
				}
				tokenid[i]='-';
				i++;
				tokenid[i]='\0';
				/*Reversing the tokenid string to get the correct string for integer token id*/
				k=0;
				for(j=i-1; j>=0; j--)
				{
					reverse[k] = tokenid[j];
					k++;
				}
				reverse[k] = '\0';
				strcat(reverse, "\n");
				//fwrite(reverse, 1, k+1, fp1);
			}
		}
		else if(num==246 || num==259)//'MeansEnd' 'DecomposesTo' check
		{
			do
			{
				/*Reading the Token Id*/
				neg=1;
				num=0;
				fread(extr, 1, 1, fp);
				size--;
				/* Checking if first character is a negative sign. If so, then setting the negative flag*/
				if(extr[0] == '-')
				{
					neg=-1;
					fread(extr, 1, 1, fp);
					size--;
				}
				/*Building the integer from string*/
				while(size>0 && extr[0]!='\t')
				{
					digit=extr[0]-48;
					num = num*10+digit;
					fread(extr, 1, 1, fp);
					size--;
				}
				/*Setting the appropriate sign of the number*/
				num *= neg;

				/*Reading the Token*/
				input[0] = '\0';
				fread(extr, 1, 1, fp);
				size--;
				while(size>0 && extr[0]!='\n')
				{
					strcat(input, extr);
					fread(extr, 1, 1, fp);
					size--;
				}
				if(extr[0]=='\n')
					size--;
				if(num<0)
					m=num;
				else if(num==114 || num==116)
					count++;
				if(count==2)
				{
					count=0;
					insert_el(m);
					//printf("%d",m);
				}
			}while(num!=2);
		}
	}
    fclose(fp);
    fclose(fp1);
	fclose(fp2);
	fclose(fp3);   

        printf("\n\nALL ACTORS ARE IDENTIFIED.\nSEE 'Actors.opm'");
	    printf("\nROOT OF THE TREE UNDER EACH ACTOR IS IDENTIFIED.\nSEE 'MOD_EL.opm'");
	    printf("\nNODES OF THE TREE UNDER EACH ACTOR IS STORED IN SEPARATE FILES.");
        
	return ac_count;
}

void insert_el(int n)
{
      node *ptr,*temp,*q;
      int flag=0;
      temp=q=start1;
      ptr=(node*)malloc(sizeof(node));
      ptr->data=n;
      ptr->next=NULL;
      if(start1==NULL)
      {
	   start1=ptr;
	   //printf("\n %d is inserted in the list\n",n);
      }
      else
      {
	  	while(temp!=NULL)
	 	{
		 	if(temp->data==n)
	      	{
		   		flag=1;
		   		break;
	      	}
	      	else
		 		temp=temp->next;
	 	}
	 	if(flag==0)
	 	{
		 	ptr->next=q;
	      	start1=ptr;
	      	//printf("\n %d is inserted in the list\n",n);
	 	}
     }
     temp=start1;
     while(temp!=NULL)
     {
	   //printf("%5d",temp->data);
	   temp=temp->next;
     }
}
int del_el(int n)
{
	  node *p,*q;
	  p=start1;
	 if(start1==NULL)
	       return 0;
	 else if(p->data==n)
	 {
	     start1=p->next;
	      p->next=NULL;
	      free(p);
	      //printf("\n %d is deleted from the list\n",n);
	      return 1;
	 }
	 else
	 {
	      while(p->next!=NULL)
	      {
		     if(p->next->data==n)
		     {
			   q=p->next;
			   p->next=q->next;
			   q->next=NULL;

			   free(q);
			   //printf("\n %d is deleted from the list\n",n);
			   return 1;
		     }
		     p=p->next;
	       }
	  }     
		
	    if(p->next==NULL)
	       return 0;
	  

}


