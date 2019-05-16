#include <stdio.h>
#include <string.h>
#include <io.h>

/* entry point */

int filtoken_func(int argc,char *argv[])
{

 	char input[700], temp[700], extr[2], insert[3];
	char *sepr = "+-*/%^#&|~<>=()[]{}\" ,;'$\n?.";
	
	char *p, *q, *org;
	FILE *fp1, *fp2;
	int count, lenq, len, size, sizeI;

	if(argc==2)
    {	
		fp1 = fopen(argv[1], "r");
		fp2 = fopen("tokenize.opm", "w");
		sizeI = size = _filelength(_fileno(fp1));
			
		while(size > 0)
		{
			input[0] = '\0';
			fseek(fp1, sizeI-size ,0);//reset the write pointer at (sizeI-size)th position from begining 
			fread(extr, 1, 1,fp1);//read 1 element of 1 byte i.e. 1 character at a time from input file into extr(the buffer)
			size--;
			while(size>=0 && extr[0]!=' ' && extr[0]!='\t' && extr[0]!='\n')
			{
				strcat(input, extr);
				fread(extr, 1, 1, fp1);
				size--;  
			}

			if(input[0]=='\0')
				continue;

			//printf("\n%s", input);//show			
			strcpy(temp, input);
			org = temp;
			p = input;
			count = 0;
			len = strlen(input);
			q = strtok(input, sepr);// break the content of input into tokens separated by delimiters(contained in the string sepr)
		
			if(q)//if input array is not empty
			{
				count = lenq = strlen(q);
				while(p<q)//the string before the separator
				{					
					insert[0] = *org;
					insert[1] = '\n';
					insert[2] = '\0';
					fwrite(insert, 1, 2, fp2);
					org = org+1;
					p = p+1;
				}
				strcat(q, "\n");
				fwrite(q, 1, lenq+1, fp2);
				p = q + lenq;
				org += lenq;	
			}
			else
			{
				while(*org != '\0')
				{
					insert[0] = *org;
					insert[1] = '\n';
					insert[2] = '\0';
					fwrite(insert, 1, 2, fp2);
					org = org + 1;
				}
			}
			while(count < len)
			{
				q = strtok(NULL, sepr);			
				if(q)
				{
					lenq = strlen(q);
					while(p<q)
					{
						insert[0] = *org;
						insert[1] = '\n';
						insert[2] = '\0';
						fwrite(insert, 1, 2, fp2);
						org = org+1;
						p = p+1;
					}
					strcat(q, "\n");
					fwrite(q, 1, lenq+1, fp2);
					p = q + lenq;
					org += lenq;
					count += lenq;
				}
				else
					break;
			}
			while(*org != '\0')
			{		
				strcpy(input, org);				
			//	printf("\norg(to be tokenised): %s", input);//show							
				strcpy(temp, input);
				org = temp;
				p = input;
				count = 0;
				len = strlen(input);
				q = strtok(input, sepr);
				
				if(q)
				{
					count = lenq = strlen(q);
					while(p<q)
					{
					
						insert[0] = *org;
						insert[1] = '\n';
						insert[2] = '\0';
						fwrite(insert, 1, 2, fp2);
						org = org+1;
						p = p+1;
					}
					strcat(q, "\n");
					fwrite(q, 1, lenq+1, fp2);
					p = q + lenq;
					org += lenq;
				}
				else
				{
					while(*org != '\0')
					{					
						insert[0] = *org;
						insert[1] = '\n';
						insert[2] = '\0';
						fwrite(insert, 1, 2, fp2);
						org = org + 1;
					}
				}
				
				while(count < len)
				{
					q = strtok(NULL, sepr);
					//printf("\nThe extracted token is : %s", q);	//show				
					if(q) //when??
					{
						lenq = strlen(q);
						while(p<q)
						{
							insert[0] = *org;
							insert[1] = '\n';
							insert[2] = '\0';
							fwrite(insert, 1, 2, fp2);
							org = org+1;
							p = p+1;
						}
						strcat(q, "\n");
						fwrite(q, 1, lenq+1, fp2);
						p = q + lenq;
						org += lenq;
						count += lenq;
					}
					else
						break;
				}
			}
		}
		fclose(fp1);
		fclose(fp2);
		printf("\nTHE CONTENT OF THE INPUT FILE IS SEPARATED INTO TOKENS.\nSEE 'tokenize.opm'");
	}
	else
		printf("Invalid arguments!!!!");
	return 0;
}

