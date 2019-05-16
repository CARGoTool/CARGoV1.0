#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<io.h>
#include "lex.h"


/* entry point */

int hnum; /*CHANGE*/

int recognize_func(void)
{
	FILE *fpt, *fpk, *fps, *fpc;
	char copy[700], input[700], tokenid[6], reverse[6], extr[2], insert[700], keyword[100], uservar[100];
	int id, check, num, i, j, k, countk, countu, flag, size, digit, len_ins, sizeK, sizeU;
	countk = countu = 0;
	
	fpt = fopen("tokenize.opm", "r");	
	size = _filelength(_fileno(fpt));

	while(size != 0)
	{
		input[0] = '\0';
		fread(extr, 1, 1, fpt);
		size--;
		while(size>0 && extr[0]!='\n')
		{
			strcat(input, extr);
			fread(extr, 1, 1, fpt);
			size--;
		}

		if(input[0]=='\0')
			continue;
				
		strcpy(copy, input);
		num = id = identify(input);

		//*Creating Codtoken.opm*
		fpc = fopen("codtoken.opm", "a");

		//*Converting the token id from integer to string in reverse order*
		i=0;
		flag=0;
		if(num<0)
		{
			flag=1;
			num=num*(-1);
		}
		while(num>0)
		{
			digit=num%10;
			tokenid[i]=digit+48; //since 0 in char is equivalent to 48 in decimal
			num/=10;
			i++;
		}
		if(flag == 1)
		{
			tokenid[i]='-';
			i++;
			
		}
		tokenid[i]='\0';
		//*Reversing the tokenid string to get the correct string for integer token id*
		k=0;
		for(j=i-1; j>=0; j--)
		{
			reverse[k] = tokenid[j];
			k++;
		}
		reverse[k] = '\0';
		
		//*Creating the "Token_id \t Token \n" line for Codetoken*
		strcpy(insert, reverse);
		strcat(insert, "\t");
		strcat(insert, copy);
		strcat(insert, "\n");
		len_ins = strlen(reverse) + strlen(copy) + 2;

		fwrite(insert, 1, len_ins, fpc);
		fclose(fpc);

		if(id>0)
		{
			check = 0;
			if(countk == 1)
			{
				//*Checking keywords.opm for existing keywords*
				fpk = fopen("keywords.opm", "r");
				sizeK = _filelength(_fileno(fpk));
				while(sizeK != 0)
				{
					keyword[0] = '\0';
					fread(extr, 1, 1, fpk);
					sizeK--;
					while(sizeK>0 && extr[0]!='\n')
					{
						strcat(keyword, extr);
						fread(extr, 1, 1, fpk);
						sizeK--;
					}

					if(strcmp(keyword, copy) == 0)
					{
						check = 1;
						break;
					}
				}
				fclose(fpk);
			}
			//*Writing new keyword into keywords.opm*
			if(check == 0)
			{
				fpk = fopen("keywords.opm", "a");
				strcpy(insert, copy);
				strcat(insert, "\n");
				fwrite(insert, 1, strlen(insert), fpk);
				countk=1;
				fclose(fpk);
			}				
		}

		else if(id < 0)
		{
			check=0;
			if(countu==1)
			{
				fps = fopen("userid.opm", "r");
				sizeU = _filelength(_fileno(fps));
				while(sizeU != 0)
				{
					uservar[0] = '\0';
					fread(extr, 1, 1, fps);
					sizeU--;
					while(sizeU>0 && extr[0]!='\n')
					{
						strcat(uservar, extr);
						fread(extr, 1, 1, fps);
						sizeU--;
					}

					if(strcmp(uservar, copy) == 0)
					{
						check = 1;
						break;
					}
				}
				fclose(fps);
			}

			if(check == 0)
			{
				fps = fopen("userid.opm", "a");
				strcpy(insert, copy);
				strcat(insert, "\n");
				fwrite(insert, 1, strlen(insert), fps);
				countu=1;				
				fclose(fps);
			}
			hnum=id;/*CHANGE*/			
		}	
    		
	}
	
	fclose(fpt);
	printf("\n\nAN UNIQUE CODE-NUMBER IS GIVEN TO EACH TOKEN.\nSEE 'codtoken.opm' ");
    printf("\nALL KEYWORDS ARE IDENTIFIED.\nSEE 'keywords.opm'");
	printf("\nALL VARIABLES ARE IDENTIFIED.\nSEE 'userid.opm'");
	return hnum;/*CHANGE*/
}

