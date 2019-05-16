#include<stdio.h>
#include<stdlib.h>
#include<string.h>										
#include<ctype.h>


int fail(void);
int identify(char *);
int insert1(int,char[]);

char *token_beg=NULL, *forward=NULL;
int start,k=-100;
extern int no_act;

typedef struct node1
{
    int data;
    char str[50];
    struct node1 *next;
}node1;
node1 *head1=NULL;

int fail(void)
{
forward = token_beg;

	switch(start)
	{
		case 0:
			start = 3;
			break;
		case 3:
			start = 18;
			break;
		case 18:
			start = 113;
			break;
		case 113:
			start = 115;
			break;
		case 115:
			start = 203;
			break;
		case 203:
			start = 209;
			break;
		case 209:
			start = 214;
			break;
		case 214:
			start = 219;
			break;
		case 219:
			start = 229;
			break;
		case 229:
			start = 238;
			break;
		case 238:
			start = 247;
			break;
		case 247:
			start = 260;
			break;
		case 260:
			start = 272;
			break;
		case 272:
			start = 275;
			break;
		case 275:
			 start = 279;
			 break;
		case 279:
			start = 301;
			break;
		case 301:
			start = 305;
			break;
/*------------------change---------------------*/
		case 305:
			start = 309;
			break;
         case 309:
			start = 324;
			break;
/*-----------------change done--------------------*/
		case 201:
			start = 308;
			break;
		case 324:
			start = 201;
			break;
		default:
			printf("\nCompiler Error!");
	}

	return start;
}

int identify(char* str)
{
int state = 0;
start = 0;
char c;
char ch[50];
int i=0;
int r;
forward = token_beg = str;
c='\0';

	while(1)
	{
		switch(state)
		{
			case 0:
				c = *forward;
				forward++;

				if(c == '\n')
				{
					token_beg++;
					state = 0;
				}
				else if(c == '-')
					state = 1;
				else if(c=='?')
					state = 2;
				
				else
					state = fail();
				break;

			case 1:
				return state;
			case 2:
				return state;
			case 3:
                c = *forward;
				forward++;
				/*---------change----------*/
				if(c=='<')
                    state=4;
				else if(c=='>')
					state=5;
				else if(c=='~')
					state=6;
				/*---------change done----------*/
                else if(c == '{')
					state = 7;
				else if(c == '=')
					state = 8;
				else if(c == ';')
					state = 9;
				else if(c == '}')
					state = 10;
				else if(c == ',')
					state = 11;
				else if(c=='.')
					state=13;
				else 
					state=fail();
				break;
			/*----------change---------*/
			case 4:
				return state;
            case 5:
				return state;
			case 6:
				return state;
			/*---------change done----------*/
			case 7:
				return state;
			case 8:
				return state;
			case 9:
				return state;
			case 10:
				return state;
			case 11:
				return state;
			case 13:
				return state;
			case 18:
				c = *forward;
				forward++;

				if(c == '&')
					state = 19;
				else if(c == '|')
					state = 20;
				else
					state = fail();
				break;

			case 19:
				return state;
			case 20:
				return state;
			
			case 113:
				c = *forward;
				forward++;

				if(c == '(')
					state = 114;
				else
					state = fail();
				break;

			case 114:
				c = *forward;
				forward++;

				if(c == '\0')
					return state;
				else
					{
					state = fail();
					break;
					}

			case 115:
				c = *forward;
				forward++;

				if(c == ')')
					state = 116;
				else
					state = fail();
				break;

			case 116:
				c = *forward;
				forward++;

				if(c == '\0')
					return state;
				else
					{
					state = fail();
					break;
					}

			case 201:
				c = *forward;
				forward++;
				ch[i++]=c;

				if(isalpha(c) || isdigit(c) || c == '_')
					state = 201;
				else
					state = 202;
				break;

			case 202:
				if(c == '\0')
				{
					ch[i]='\0';
					i=0;
					r=insert1(k--,ch);
					return r;
				 }
				else
					{
					state = fail();
					break;
					}


			case 203:c=*forward;
				 forward++;
				 if(c=='a'||c=='A')
					state=204;
				else
					state=fail();
				break;
			case 204:c=*forward;
				 forward++;
				if(c=='c')
				       state=205;
				else
					state=fail();
				break;
			case 205:c=*forward;
				 forward++;
				if(c=='t')
				       state=206;
				else
					state=fail();
				break;
			case 206:c=*forward;
				 forward++;
				if(c=='o')
				       state=207;
				else
					state=fail();
				break;
			case 207:c=*forward;
				 forward++;
				if(c=='r')
				       state=208;
				else
					state=fail();
				break;
			case 208:c=*forward;
				 forward++;
				if(c=='\0')
				       return state;
				else
				{
					state=fail();
					break;
				}
			case 209:c=*forward;
				 forward++;
				if(c=='g')
				       state=210;
				else
					state=fail();
				break;
			case 210:c=*forward;
				 forward++;
				if(c=='o')
				       state=211;
				else
					state=fail();
				break;
			case 211:c=*forward;
				 forward++;
				if(c=='a')
				       state=212;
				else
					state=fail();
				break;
			case 212:c=*forward;
				 forward++;
				if(c=='l')
				       state=213;
				else
					state=fail();
				break;
			case 213:c=*forward;
				 forward++;
				if(c=='\0')
				       return state;
				else
				{
					state=fail();
					break;
				}
			case 214:c=*forward;
				 forward++;
				if(c=='t'||c=='T')
				       state=215;
				else
					state=fail();
				break;
			case 215:c=*forward;
				 forward++;
				if(c=='a')
				       state=216;
				else
					state=fail();
				break;
			case 216:c=*forward;
				 forward++;
				if(c=='s')
				       state=217;
				else
					state=fail();
				break;
			case 217:c=*forward;
				 forward++;
				if(c=='k')
				       state=218;
				else
					state=fail();
				break;
			case 218:c=*forward;
				 forward++;
				if(c=='\0')
				       return state;
				else
				{
					state=fail();
					break;
				}
		       case 219:c=*forward;
				forward++;
				if(c=='S')
				       state=220;
				else
					state=fail();
				break;
			case 220:c=*forward;
				 forward++;
				if(c=='o')
				       state=221;
				else
					state=fail();
				break;
			case 221:c=*forward;
				 forward++;
				if(c=='f')
				       state=222;
				else
					state=fail();
				break;
			case 222:c=*forward;
				 forward++;
				if(c=='t')
				       state=223;
				else
					state=fail();
				break;
			case 223:c=*forward;
				 forward++;
				if(c=='G'||c=='g')
				       state=224;
				else
					state=fail();
				break;
			case 224:c=*forward;
				 forward++;
				if(c=='o')
				       state=225;
				else
					state=fail();
				break;
			case 225:c=*forward;
				 forward++;
				if(c=='a')
				       state=226;
				else
					state=fail();
				break;
			case 226:c=*forward;
				 forward++;
				if(c=='l')
				       state=227;
				else
					state=fail();
				break;
			case 227:c=*forward;
				 forward++;
				if(c=='\0')
				       return state;
				else
				{
					state=fail();
					break;
				}
			case 229:c=*forward;
				 forward++;
				 if(c=='R'||c=='r')
				       state=230;
				else
					state=fail();
				break;
			case 230:c=*forward;
				 forward++;
				if(c=='e')
				       state=231;
				else
					state=fail();
				break;
			case 231:c=*forward;
				 forward++;
				if(c=='s')
				       state=232;
				else
					state=fail();
				break;
			case 232:c=*forward;
				 forward++;
				if(c=='o')
				       state=233;
				else
					state=fail();
				break;
			case 233:c=*forward;
				 forward++;
				 if(c=='u')
				       state=234;
				else
					state=fail();
				break;
			case 234:c=*forward;
				 forward++;
				if(c=='r')
				       state=235;
				else
					state=fail();
				break;
			case 235:c=*forward;
				 forward++;
				if(c=='c')
				       state=236;
				else
					state=fail();
				break;
			case 236:c=*forward;
				 forward++;
				if(c=='e')
				       state=237;
				else
					state=fail();
				break;
			case 237:c=*forward;
				 forward++;
				if(c=='\0')
				       return state;
				else
				{
					state=fail();
					break;
				}
			case 238:c=*forward;
				 forward++;
				 if(c=='M')
				       state=239;
				else
					state=fail();
				break;
			case 239:c=*forward;
				 forward++;
				if(c=='e')
				       state=240;
				else
					state=fail();
				break;
			case 240:c=*forward;
				 forward++;
				if(c=='a')
				       state=241;
				else
					state=fail();
				break;
			case 241:c=*forward;
				 forward++;
				if(c=='n')
				       state=242;
				else
					state=fail();
				break;
			case 242:c=*forward;
				 forward++;
				if(c=='s')
				       state=243;
				else
					state=fail();
				break;
			case 243:c=*forward;
				 forward++;
				if(c=='E')
				       state=244;
				else
					state=fail();
				break;
			case 244:c=*forward;
				 forward++;
				
				if(c=='n')
				       state=245;
				else
					state=fail();
				break;
			case 245:c=*forward;
				 forward++;
				if(c=='d')
				       state=246;
				else
					state=fail();
				break;
			case 246:c=*forward;
				 forward++;
				if(c=='\0')
				       return state;
				else
				{
					state=fail();
					break;
				}

			case 247:c=*forward;
				 forward++;
				 if(c=='d')
				       state=248;
				else
					state=fail();
				break;
			case 248:c=*forward;
				 forward++;
				if(c=='e')
				       state=249;
				else
					state=fail();
				break;
			case 249:c=*forward;
				 forward++;
				if(c=='c')
				       state=250;
				else
					state=fail();
				break;
			case 250:c=*forward;
				 forward++;
				if(c=='o')
				       state=251;
				else
					state=fail();
				break;
			case 251:c=*forward;
				 forward++;
				if(c=='m')
				       state=252;
				else
					state=fail();
				break;
			case 252:c=*forward;
				 forward++;
				if(c=='p')
				       state=253;
				else
					state=fail();
				break;
			case 253:c=*forward;
				 forward++;
				if(c=='o')
				       state=254;
				else
					state=fail();
				break;
			case 254:c=*forward;
				 forward++;
				if(c=='s')
				       state=255;
				else
					state=fail();
				break;
			case 255:c=*forward;
				 forward++;
				if(c=='e')
				       state=256;
				else
					state=fail();
				break;
			case 256:c=*forward;
				 forward++;
				if(c=='s')
				       state=257;
				else
					state=fail();
				break;
			case 257:c=*forward;
				 forward++;
				if(c=='T')
				       state=258;
				else
					state=fail();
				break;
			case 258:c=*forward;
				 forward++;
				if(c=='o')
				       state=259;
				else
					state=fail();
				break;
			case 259:c=*forward;
				 forward++;
				if(c=='\0')
				       return state;
				else
				{
					state=fail();
					break;
				}
			case 260:c=*forward;
				 forward++;
				 if(c=='d')
				       state=261;
				else
					state=fail();
				break;
			case 261:c=*forward;
				 forward++;
				if(c=='e')
				       state=262;
				else
					state=fail();
				break;
			case 262:c=*forward;
				 forward++;
				if(c=='p')
				       state=263;
				else
					state=fail();
				break;
			case 263:c=*forward;
				 forward++;
				if(c=='e')
				       state=264;
				else
					state=fail();
				break;
			case 264:c=*forward;
				 forward++;
				if(c=='n')
				       state=265;
				else
					state=fail();
				break;
			case 265:c=*forward;
				 forward++;
				if(c=='d')
				       state=266;
				else
					state=fail();
				break;
			case 266:c=*forward;
				 forward++;
				if(c=='e')
				       state=267;
				else
					state=fail();
				break;
			case 267:c=*forward;
				 forward++;
				if(c=='e' || c=='r')
				       state=268;
				else if(c=='n')
				       state=269;
				else
					state=fail();
				break;
			case 268:c=*forward;
				 forward++;
				if(c=='\0')
				       return state;
				else
				{
					state=fail();
					break;
				}
			case 269:c=*forward;
				 forward++;
				 if(c=='c')
				       state=270;
				else
					state=fail();
				break;
			case 270:c=*forward;
				 forward++;
				if(c=='y')
				       state=271;
				else
					state=fail();
				break;
			case 271:c=*forward;
				 forward++;
				if(c=='\0')
				       return state;
				else
				{
					state=fail();
					break;
				}


			case 272:c=*forward;
				 forward++;
				if(c=='A' || c=='a')
				       state=273;
				else
					state=fail();
				break;
			case 273:c=*forward;
				 forward++;
				if(c=='s')
				       state=274;
				else
					state=fail();
				break;
			case 274:c=*forward;
				 forward++;
				if(c=='\0')
				       return state;
				else
				{
					state=fail();
					break;
				}
			case 275:c=*forward;
				 forward++;
				 if(c=='g')
				       state=276;
				else
					state=fail();
				break;
			case 276:c=*forward;
				 forward++;
				  if(c=='r')
				       state=277;
				else
					state=fail();
				break;
            		case 277:c=*forward;
				 forward++;
				  if(c=='l')
				       state=278;
				else
					state=fail();
				break;
			case 278:c=*forward;
				 forward++;
				if(c=='\0')
				       return state;
				else
				{
					state=fail();
					break;
				}
			case 279:c=*forward;
				 forward++;
				  if(c=='d')
				       state=280;
				else
					state=fail();
				break;
           		case 280:c=*forward;
				 forward++;
				  if(c=='e')
				       state=281;
				else
					state=fail();
				break;
			case 281:c=*forward;
				 forward++;
				  if(c=='c')
				       state=282;
				else
					state=fail();
				break;
		   	case 282:c=*forward;
				 forward++;
				  if(c=='o')
				       state=283;
				else
					state=fail();
				break;
			case 283:c=*forward;
				 forward++;
				  if(c=='m')
				       state=284;
				else
					state=fail();
				break;
			case 284:c=*forward;
				 forward++;
				  if(c=='p')
				       state=285;
				else
					   state=fail();
				break;
			case 285:c=*forward;
				 forward++;
				  if(c=='o')
				       state=286;
				else
					   state=fail();
				break;
			case 286:c=*forward;
				 forward++;
				  if(c=='s')
				       state=287;
				else
					   state=fail();
				break;
			case 287:c=*forward;
				 forward++;
				  if(c=='i')
				       state=288;
				  else if(c=='e')
					  state=289;
				else
					state=fail();
				break;
			case 288:c=*forward;
				 forward++;
				  if(c=='t')
				       state=293;
				else
					   state=fail();
				break;
			case 289:c=*forward;
				 forward++;
				  if(c=='d')
				       state=290;
				else
					state=fail();
				break;
		
			case 290:c=*forward;
				 forward++;
				  if(c=='B'||c=='b')
				       state=291;
				else
					state=fail();
				break;
			case 291:c=*forward;
				 forward++;
				  if(c=='y')
				       state=292;
				else
					state=fail();
				break;
			
			case 292:c=*forward;
				 forward++;
				if(c=='\0')
				       return state;
				else
				{
					state=fail();
					break;
				}
			case 293:c=*forward;
				 forward++;
				  if(c=='i')
				       state=294;
				else
					state=fail();
				break;
			case 294:c=*forward;
				 forward++;
				  if(c=='o')
				       state=295;
				else
					state=fail();
				break;
			case 295:c=*forward;
				 forward++;
				  if(c=='n')
				       state=296;
				else
					state=fail();
				break;
			case 296:c=*forward;
				 forward++;
				  if(c=='T'||c=='t')
				       state=297;
				else
					state=fail();
				break;
			case 297:c=*forward;
				 forward++;
				  if(c=='y')
				       state=298;
				else
					state=fail();
				break;
			case 298:c=*forward;
				 forward++;
				  if(c=='p')
				       state=299;
				else
					state=fail();
				break;
			case 299:c=*forward;
				 forward++;
				  if(c=='e')
				       state=300;
				else
					state=fail();
				break;
			case 300:c=*forward;
				 forward++;
				if(c=='\0')
				       return state;
				else
				{
					state=fail();
					break;
				}
			case 301:c=*forward;
				 forward++;
				  if(c=='A'||c=='a')
				       state=302;
				else
					state=fail();
				break;
			case 302:c=*forward;
				 forward++;
				  if(c=='n')
				       state=303;
				else
					state=fail();
				break;
			case 303:c=*forward;
				 forward++;
				  if(c=='d')
				       state=304;
				else
					state=fail();
				break;
			case 304:c=*forward;
				 forward++;
				if(c=='\0')
				       return state;
				else
				{
					state=fail();
					break;
				}
			case 305:c=*forward;
				 forward++;
				  if(c=='O'||c=='o')
				       state=306;
				else
					state=fail();
				break;
			case 306:
				c=*forward;
				 forward++;
				  if(c=='r')
				       state=307;
				else
					state=fail();
				break;
			case 307:
				c=*forward;
				 forward++;
				if(c=='\0')
				       return state;
				else
				{
					state=fail();
					break;
				}
			case 308:
				return -1;


            /*-----------------------change-----------------------*/

			case 309:c=*forward;
				 forward++;
				if(c=='I')
				       state=310;
				else
					state=fail();
				break;
			case 310:c=*forward;
				 forward++;
				if(c=='E')
				       state=311;
				else
					state=fail();
				break;
			case 311:c=*forward;
				 forward++;
				if(c=='\0')
				       return state;
				else
				{
					state=fail();
					break;
				}
			
			/*------------------------change done----------------------*/            


			//dependsOn
			case 324:c=*forward;
				 forward++;
				 if(c=='d')
				       state=325;
				else
					state=fail();
				break;
			case 325:c=*forward;
				 forward++;
				 if(c=='e')
				       state=326;
				else
					state=fail();
				break;
			case 326:c=*forward;
				 forward++;
				if(c=='p')
				       state=327;
				else
					state=fail();
				break;
			case 327:c=*forward;
				 forward++;
				if(c=='e')
				       state=328;
				else
					state=fail();
				break;
			case 328:c=*forward;
				 forward++;
				if(c=='n')
				       state=329;
				else
					state=fail();
				break;
			case 329:c=*forward;
				 forward++;
				if(c=='d')
				       state=330;
				else
					state=fail();
				break;
			case 330:c=*forward;
				 forward++;
				if(c=='s')
				       state=331;
				else
					state=fail();
				break;
			case 331:c=*forward;
				 forward++;
				if(c=='O')
				       state=332;
				else
					state=fail();
				break;
			case 332:c=*forward;
				 forward++;
				if(c=='n')
				       state=333;
				else
					state=fail();
				break;
			case 333:c=*forward;
				 forward++;
				if(c=='\0')
				       return state;
				else
				{
					state=fail();
					break;
				}
			
		}
	}
}

int insert1(int n,char ch[])
{
      node1 *ptr,*temp,*q;
      int flag=0;
      temp=q=head1;

      ptr=(node1*)malloc(sizeof(node1));
      ptr->data=n;
      strcpy(ptr->str,ch);
      ptr->next=NULL;
      if(head1==NULL)
      {
	   head1=ptr;
	   return n;
      }
      else
      {
	  while(temp!=NULL)
	 {
	      if(strcmp(temp->str,ch)==0)
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
	      head1=ptr;
	      return n;
	 }
	 else
	     return temp->data;
     }
}

