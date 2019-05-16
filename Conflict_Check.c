#include <stdio.h>
#include <string.h>
#include <io.h>
#include <stdlib.h>
#include "structure.h"

#define new_conflict (struct conflict*)malloc(sizeof(struct conflict))
#define new_child_queue_node (struct child_queue_node*)malloc(sizeof(struct child_queue_node))
	 
struct conflict* conflict_check(struct actor_node *head)
{
  //  printf("\nConflict checking --------------START--------------------\n\n");
	struct conflict *conhead=NULL,*conptr=NULL;
	struct actor_node *p=head;

	while(p!=NULL)//each actor
	{
		//printf("\n\n\n--------------inside %s------------",p->str);
		struct tree_node *t=p->next;
		while(t!=NULL)//each tree
		{
			int e=0,c=0;
			//printf("\nTREE %s\n\n",t->str);			
			int flag1;
			/******************AND decomp Entailment******************/
				struct IE_node *tempie=t->ie;
				int cntr=0,NoCE=0,NoIE=0;
				while(tempie!=NULL)	
					{
						NoIE++;
						tempie=tempie->next;
					}
				//printf("\n\nNoIE=%d, type=%d",NoIE,t->type);
				tempie=t->ie;
				if(t->type==1&&tempie!=NULL)
				{					
					struct CE_node *oce=t->ce,*ice=t->ce;		
					while(oce!=NULL)//each CE element
					{
					    NoCE++;
						tempie=t->ie;
					    int found=0,matched=0;
						//printf("from %s :-\n",oce->var);
						while(tempie!=NULL)//checking for each IE
						{
						    ice=oce;
							found=0;
							//printf("%s-----\n",tempie->var);
							while(ice!=NULL && strcmp(ice->var,",")!=0)//CE element
							{
								//printf("***%s***",ice->var);
								if(strcmp(tempie->var,ice->var)==0)
									{	found=1;	 	break;	}
								ice=ice->next;
							}
							if(found)
								{	
									matched++;
								}
							tempie=tempie->next;
						}
						if(matched!=NoIE)	
						{

								//printf("\nConflict node or E created");
								struct conflict *new=new_conflict;
								new->conflicting_pnode=t;
								new->conflicting_cnode=NULL;
								if(matched!=0)
									new->con_flag=4;   //partial entailment
								else
									new->con_flag=3;	//full entailment
								new->el_no=NoCE;
								new->next_conflict=NULL;
								if (conhead==NULL)
									conhead=conptr=new;
								else
								{
									conptr->next_conflict=new;
									conptr=conptr->next_conflict;
								}
								 //printf("\n+++++++++++++++ALL FOUND+++++++++++++++++++");
						}
						//printf("(%s)",ice->var);
						if(ice==NULL)
							{	
						      //printf("ENDing------");
                              break;
                        	}
						else
						{
						
							//printf("\nice  not  null\n");
							while(strcmp(oce->var,",")!=0)
							{	
								//printf("%s%%%\n",oce->var);
								oce=oce->next;
								if(oce==NULL)	
									break;
							}
					
							if(oce!=NULL)	
								oce=oce->next;
							else 
								break;
						}
					}
					//printf("\n\t--------------------------cntr=%d     noCE=%d\n",cntr,NoCE);
				}
							
				/******************AND decomp Entailment******************/

				/******************OR decomp Entailment******************/
				tempie=t->ie;
				if(t->type==0&&tempie!=NULL)
				{					
					struct child_queue_node *childqnd = t->children;
					while(childqnd!=NULL)//each child
					{
						struct CE_node *oce=childqnd->ptrc->ce,*ice=childqnd->ptrc->ce;cntr=0;NoCE=0;		
						while(oce!=NULL)//each CE element
						{
						    NoCE++;
							tempie=t->ie;
						    int found=0,matched=0;
							//printf("from %s :-\n",oce->var);
							while(tempie!=NULL)//checking for each IE
							{
							    ice=oce;
								found=0;
								//printf("%s-----\n",tempie->var);
								while(ice!=NULL && strcmp(ice->var,",")!=0)//CE element
								{
									//printf("***%s***",ice->var);
									if(strcmp(tempie->var,ice->var)==0)
										{	found=1;	 	break;	}
									ice=ice->next;
								}
								if(found)
								{	
									matched++;
								}
								tempie=tempie->next;
							}
							if(matched!=NoIE)	
							{

								//printf("\nConflict node or E created");
								struct conflict *new=new_conflict;
								new->conflicting_pnode=t;
								new->conflicting_cnode=childqnd;
								if(matched!=0)
									new->con_flag=4;   //partial entailment
								else
									new->con_flag=3;	//full entailment
								new->el_no=NoCE;
								new->next_conflict=NULL;
								if (conhead==NULL)
									conhead=conptr=new;
								else
								{
									conptr->next_conflict=new;
									conptr=conptr->next_conflict;
								}
								 //printf("\n+++++++++++++++ALL FOUND+++++++++++++++++++");
							}
							//printf("(%s)",ice->var);
							if(ice==NULL)
								{	
							     //printf("ENDing------");
                         		 break;
                            	}
							else
							{
								//printf("\nice  not  null\n");
								while(strcmp(oce->var,",")!=0)
								{	
									//printf("%s%%%\n",oce->var);
									oce=oce->next;
									if(oce==NULL)	
										break;
								}
								if(oce!=NULL)	
									oce=oce->next;
								else 
									break;
							}
						}
						//printf("\n\t--------------------------cntr=%d     noCE=%d\n",cntr,NoCE);
						childqnd=childqnd->next;
					}
				}
							
				/******************OR decomp Entailment******************/



			/**************************Hierarchical Consis********************************/
			
				struct child_queue_node *ch=t->children,*ch1,*chlist=NULL,*chhead=NULL;
				while(ch!=NULL)
				{
					tempie=t->ie;
					if(tempie!=NULL)
					{
						e=c=0;
						//printf("\n %s",ch->ptrc->str);
						
						while(tempie!=NULL) 
						{
							//printf("\n%s---findingie---\n",tempie->var);
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
						
							//flag=0;
							flag1=0;
							
							struct CE_node *tempce=ch->ptrc->ce;
							while(tempce!=NULL)
							{
								//printf("*ce*%s\t",tempce->var);
							/*	if(t->type!=1 && strcmp(tempie->var,tempce->var)==0)
									{ flag=1;
							//printf("------------------------------------%s found",tempie->var);
							}*/
								if(strcmp(notvar,tempce->var)==0)
									{ flag1=1;}
								tempce=tempce->next;
							}
							/*if(t->type!=1 && flag==0)
							{
								//printf("\n%s --------- %s has entailment conflict with %s ",t->str,ch->ptrc->str,tempie->var); 
								e=1;
							}*/
							if(flag1==1)
							{
								//printf("\n%s --------- %s has consistency conflict with %s ",t->str,ch->ptrc->str,tempie->var); 
								c=1;
							}			

							tempie=tempie->next;
						}
					}
			/**************************Hierarchical inconsistency********************************/

				/***************************sibling inconsistency*****************************/
					//printf("-----------------sibling inconsis finding-------------------");
					struct child_queue_node *newch=new_child_queue_node;
				    newch->ptrc=ch->ptrc;
					newch->next=NULL;
					chlist=chhead=newch;
					int f=0;
				    struct CE_node *tempce=ch->ptrc->ce;
					while(tempce!=NULL)
					{
					    //printf("\n\t%s finding \t\n",tempce->var);
						char notvar[3];
						if(tempce->var[0]=='~')
						{
							notvar[0]=tempce->var[1];
							notvar[1]=tempce->var[2];
							notvar[2]='\0';
						}
						else
						{
							notvar[0]='~';
							notvar[1]=tempce->var[0];
							notvar[2]=tempce->var[1];
						}
						ch1=ch->next;
				  		while(ch1!=NULL)
						{
							//printf("\n checking in %s-------------",ch1->ptrc->str);
							struct CE_node *tempce1=ch1->ptrc->ce;
				   			while(tempce1!=NULL)
								{
									if(strcmp(notvar,tempce1->var)==0)
										{
											f++;
								/**********???????Already in child list ***********/
											int found=0;
											struct child_queue_node *ps=chhead;
											while(ps!=NULL)
											{
												if(ps->ptrc->val==ch1->ptrc->val)  {found=1;break;}
												ps=ps->next;
											}
								/**********???????Already in child list ***********/
											if(!found)
											{
												newch=new_child_queue_node;
					    						newch->ptrc=ch1->ptrc;
												newch->next=NULL;
												chlist->next=newch;
												chlist=chlist->next;
												//printf("\n inconsis found  %s    and    %s    in     %s     and     %s\n",notvar,tempce1->var,ch->ptrc->str,ch1->ptrc->str);
											}
											break;
										}
									tempce1=tempce1->next;
								}
							if(f) 		break;
							ch1=ch1->next;
						}
						tempce=tempce->next;
					}
				/******************************sibling inconsistency***********************/

					/*if(e)//OR entailment conflict node creation
					{
						//printf("\nConflict node OR E created");
						struct conflict *new=new_conflict;
						new->conflicting_pnode=t;
						new->conflicting_cnode=ch;
						new->con_flag=3;
						new->next_conflict=NULL;
						if (conhead==NULL)
							conhead=conptr=new;
						else
						{
							conptr->next_conflict=new;
							conptr=conptr->next_conflict;
						}
					}*/
					if(c)//HC conflict node creation
					{
						//printf("\nConflict node HC created");
						struct conflict *new=new_conflict;
						new->conflicting_pnode=t;
						new->conflicting_cnode=ch;
						new->con_flag=1;
						new->el_no=-1;
						new->next_conflict=NULL;
						if (conhead==NULL)
							conhead=conptr=new;
						else
						{
							conptr->next_conflict=new;
							conptr=conptr->next_conflict;
						}
					}

					if(f)//SC conflict node creation
					{
						//printf("\nConflict node SC created");
						struct conflict *new=new_conflict;
						new->conflicting_pnode=t;
						new->conflicting_cnode=chhead;
						new->con_flag=2;
						new->el_no=-1;
						new->next_conflict=NULL;
						if (conhead==NULL)
							conhead=conptr=new;
						else
						{
							conptr->next_conflict=new;
							conptr=conptr->next_conflict;
						}
					}

					ch=ch->next;
				}
			t=t->next;
		}
		p=p->next_actor;
	}
	//printf("\nConflict checking --------------END--------------------\n\n");
 	return conhead;
}
