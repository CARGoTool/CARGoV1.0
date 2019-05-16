#include <stdio.h>
#include <string.h>
#include <io.h>
#include <stdlib.h>
#include "structure.h"
void trav(struct tree_node *t,char *notvar)
{
	if(t==NULL)   return;
	else
		{
			printf("\ntree node:  %s",t->str);
			struct IE_node *tempi=t->ie,*previ=t->ie;
			while(tempi!=NULL)
			{  printf("\n##%s##\n",tempi->var);
				if(strcmp(notvar,tempi->var)==0)
				{
				    fprintf(flog,"<%s> from IE set of %s is removed\n",tempi->var,t->str);
					if(previ==tempi)
						t->ie=tempi->next;
					else
						previ->next=tempi->next;
					break;
				}
				previ=tempi;
				tempi=tempi->next;
			}

		    struct child_queue_node *chq=t->children;
			while(chq!=NULL)
			{
			    trav(chq->ptrc,notvar);
				chq=chq->next;
			}
		}
}
void hc_resolution(struct conflict* chead)
{
	struct conflict *cptr=chead;
	while(cptr!=NULL)
	{
		if(cptr->con_flag==1)		//HIERARCHICAL CONSISTENCY CONFLICT
		{
            fprintf(flog,"\nDue to HIERARCHICAL CONSISTENCY CONFLICT, ");
			struct IE_node *tempie=cptr->conflicting_pnode->ie;
			//strcat(cptr->conflicting_cnode->ptrc->str,"temp");
			//printf("%s************\n",cptr->conflicting_cnode->ptrc->str);
			while(tempie!=NULL) 
			{
				char notvar[3];//notvar contains ~IE
				if(tempie->var[0]=='~')
				{
					notvar[0]=tempie->var[1];
					notvar[1]=tempie->var[2];
					notvar[2]='\0';
				}
				else
				{
					notvar[0]='~';
					notvar[1]=tempie->var[0];
					notvar[2]=tempie->var[1];
				}
			
				//printf("\n\t\tRemoving %s from the following:---------------------",notvar);
				trav(cptr->conflicting_cnode->ptrc,notvar);
				//printf("end %s",cptr->conflicting_cnode->ptrc->str);
				tempie=tempie->next;
			}
		}
		cptr=cptr->next_conflict;
		//printf("*******");
	}
}
void sc_resolution(struct conflict* chead)
{
	struct conflict *cptr=chead;
	while(cptr!=NULL)
	{
		if(cptr->con_flag==2)		//SIBLING CONSISTENCY CONFLICT
		{
			    fprintf(flog,"\nDue to SIBLING CONSISTENCY CONFLICT, ");
				//strcat(cptr->conflicting_cnode->ptrc->str,"temp");
				struct child_queue_node *childqn=cptr->conflicting_cnode->next;
				while(childqn!=NULL)
				{
						struct CE_node *tempce1=cptr->conflicting_cnode->ptrc->ce,*prevce1=cptr->conflicting_cnode->ptrc->ce;
						//printf("%s************\n",cptr->conflicting_cnode->ptrc->str);
						while(tempce1!=NULL) 
						{
							char notvar[3];//notvar contains ~CE
							if(tempce1->var[0]=='~')
							{
								notvar[0]=tempce1->var[1];
								notvar[1]=tempce1->var[2];
								notvar[2]='\0';
							}
							else
							{
								notvar[0]='~';
								notvar[1]=tempce1->var[0];
								notvar[2]=tempce1->var[1];
							}
							
							int flag=0;
							struct CE_node *tempce=childqn->ptrc->ce;
							while(tempce!=NULL)
							{
								flag=0;
								if(strcmp(notvar,tempce->var)==0)
								{
									if(prevce1==tempce1)
										cptr->conflicting_cnode->ptrc->ce=tempce1->next;
									else
										prevce1->next=tempce1->next;
									flag=1;
									
									struct IE_node *tempi=cptr->conflicting_cnode->ptrc->ie,*previ=cptr->conflicting_cnode->ptrc->ie;
									while(tempi!=NULL)
									{
										if(strcmp(tempce1->var,tempi->var)==0)
										{
									        fprintf(flog,"<%s> from IE set of %s is removed\n",tempi->var,cptr->conflicting_cnode->ptrc->str);
											if(previ==tempi)
												cptr->conflicting_cnode->ptrc->ie=tempi->next;
											else
												previ->next=tempi->next;
																		
											break;
										}
										previ=tempi;
										tempi=tempi->next;
									}
							        //printf("\n%s to be deleted from %s",tempce1->var,cptr->conflicting_cnode->ptrc->str);
							        //int ghhf;scanf("%d",&ghhf);
									trav(cptr->conflicting_cnode->ptrc,tempce1->var);/*CHANGE*/
									break;
								}
								tempce=tempce->next;
							}
					        if(!flag)
								prevce1=tempce1;
							tempce1=tempce1->next;
						}

						childqn=childqn->next;
				}
		}
		cptr=cptr->next_conflict;
	}
}
