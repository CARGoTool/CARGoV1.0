#include <stdio.h>
#include <string.h>
#include <io.h>
#include <stdlib.h>
#include "structure.h"
/*
#define new_actor_node (struct actor_node*)malloc(sizeof(struct actor_node))
#define new_tree_node (struct tree_node*)malloc(sizeof(struct tree_node))
#define new_child_queue_node (struct child_queue_node*)malloc(sizeof(struct child_queue_node))
#define new_parent_queue_node (struct parent_queue_node*)malloc(sizeof(struct parent_queue_node))
#define new_dependency_queue_node (struct dependency_queue_node*)malloc(sizeof(struct dependency_queue_node))
#define new_IE_node (struct IE_node*)malloc(sizeof(struct IE_node))
#define new_dependsOn (struct dependsOn*)malloc(sizeof(struct dependsOn))  */


struct actor_node * my_datastructure(void)
	{
		  int size,i,k1=0,k2=0,k=0,x=0,t=0,count=0;
		  char c1,c2,c3;
		  char extr[2],temp[2],actor_code[4],actor_name[30],treenode_code[4],treenode_name[30],chktype1[5],chktype2[5],p_temp[4],check[3],child[3],IE[4];
		   
		  struct tree_node *p1, *track=new_tree_node,*tn=NULL;
		  struct actor_node *p,*trk=new_actor_node, *actor_list=NULL,*head_actor=NULL,*an=NULL; //ACTOR_LIST POINTS LAST ACTOR ADDED, HEAD_ACTOR POINTS FIRST ACTOR ADDED
		  struct child_queue_node *q, *rear=new_child_queue_node;
		  struct parent_queue_node *prnt, *prear=new_parent_queue_node;  
		  struct IE_node *ip,*h=NULL, *pi=NULL;
		  struct dependsOn *hd=NULL,*ld=NULL;

		  FILE *fp;
		  fp=fopen("codtoken.opm","r");  /* this file contains code-number of each token*/		  
		  size = _filelength(_fileno(fp)); /*length of input file*/

		  temp[0]='\0';      /* temporarily holds code-number of any token*/
		  actor_code[0]='\0';/* temporarily holds code-number of actor */
		  actor_name[0]='\0';/* temporarily holds name of actor*/
		  treenode_code[0]='\0';/* temporarily holds code-number of a goal/task/resource */
		  treenode_name[0]='\0';/* temporarily holds name of a goal/task/resource */
		  chktype1[0]='\0';
		  chktype2[0]='\0';
		  p_temp[0]='\0';  /* temporarily holds a string which may or may not be the code-number of a parent*/
		  check[0]='\0';   /* hold a string which may or may not be the code-number of the keyword 'decomposedBy' */
		  child[0]='\0'; 
		  IE[0]='\0';  

		while(size>0)
		 {
		  fread(extr, 1, 1, fp);/* read one character and store it in extr */
		  size--;  
		  c1=extr[0];
		  
		/*------------------------------------------FOR VARIABLES(NEGATIVE TOKEN ID)----------------------------------------------------*/ 
					
		 if(c1=='-' && count>0 ) 
		 {   
		   /* READ CHARACTERS UP TO TAB AND MAKE A STRING */
		   while(extr[0]!='\t')
			{
				fread(extr, 1, 1, fp);
			    size--;
				strcat(p_temp,extr);
			}	

			/*CONVERTING TOKEN_ID INTO INTEGER AND NEGATING*/
		    k1=(int)p_temp[2]-48+ (int)(p_temp[1]-48)*10+(int)(p_temp[0]-48)*100;
			k1=-k1; /* numeric value of code-number of parent */
		 	 /*---------------------------------parent node pointer-------------------------------*/
						 
								an=actor_list;
								tn=an->next;
								while(tn!=NULL)
								{
									if(tn->val==k1)
										break;
									tn=tn->next;
								}

						/*----------------------------------parent node pointer---------------*/
			/* CREATING PARENT NODE WITH VALUE K1 */
		    prnt=new_parent_queue_node;
		    prnt->ptrp=tn;
		    prnt->pnext=NULL;
				
		    while(extr[0]!='\n')/* SKIPPING LINE */
			{
				fread(extr, 1, 1, fp);
			    size--;
			}	

			while(extr[0]!='\t')/* UPTO TAB CHAR */
			{
			   fread(extr, 1, 1, fp);
			   size--;
			   if(extr[0]!='\t')
		          strcat(check,extr); /* this string contains next token */
			}
			/*CONVERTING NEXT TOKEN_ID INTO INTEGER*/
			int ch=(int)check[2]-48+ (int)(check[1]-48)*10+(int)(check[0]-48)*100;

			if(ch==292)/* IF PARENT NAME FOLLOWED BY KEYWORD "decomposedBy" */
		    {
			   while(extr[0]!='\n')/* SKIPPING LINE */
			   {
			     fread(extr, 1, 1, fp);
			     size--;
			   }	   
			   while(extr[0]!=';')/* UNTIL keyword ';' IS FOUND */
				{
		            fread(extr, 1, 1, fp);
			        size--;
					if(extr[0]=='-')/* VARIABLE FOUND */
					 {
		                while(extr[0]!='\t')/* UNTIL TAB */
			              {
			                fread(extr, 1, 1, fp);
			                size--;
			                if(extr[0]!='\t')
		                    strcat(child,extr);/* STORING CHILD TOKEN_ID */					
			              }

						  /*CONVERTING TOKEN_ID INTO INTEGER AND NEGATING*/
						  k2=(int)child[2]-48+ (int)(child[1]-48)*10+(int)(child[0]-48)*100;
			              k2=-k2;	
						  //printf("\nK2=%d",k2);
					  	 /*---------------------------------child node pointer-------------------------------*/
						 
								an=actor_list;
								tn=an->next;
								while(tn!=NULL)
								{
									if(tn->val==k2)
										break;
									tn=tn->next;
								}
		                        
						/*----------------------------------child node pointer------------------------------*/
					     /* CREATING CHILD NODE WITH VALUE K2 */
					     q=new_child_queue_node;
		                 q->ptrc=tn;
					     q->next=NULL;				 

					    /* HEAD OF THE TREE OF CURRENT ACTOR IS PT */
		                struct tree_node *pt=actor_list->next;
					    while(pt!=NULL)//LIST OF TREE NODES TRAVERSAL & PARENT CHILD RELATION UPDATION
							{
								if(k2==pt->val)//IF CHILD FOUND, SETTING PARENT QUEUE
									{ 
										if(pt->parent==NULL)//PARENT QUEUE NULL
		                            	 {
										 	pt->parent=prnt; 
										 	prear=prnt;
									 	 }	
		                             else//NOT NULL
										{
											 prear->pnext=prnt;
											 prear=prear->pnext;
			                                 prear->pnext=NULL;                   
			                            }          
									}
								else if(k1==pt->val)//IF PARENT FOUND, SETTING CHILD QUEUE
		                           {
									 if(pt->children==NULL)//CHILD QUEUE NULL
		                            	 {
										 	pt->children=q; 
										 	rear=q;
									 	 }	
		                             else//NOT NULL
										{
											 rear->next=q;
											 rear=rear->next;
			                                 rear->next=NULL;                   
			                            }                                                                                 						 
								   }
								pt=pt->next;
							}
		             }
                    
                      //printf("\%c",extr[0]);
		              for(i=0;i<4;i++)
		    		     child[i]='\0';//FLUSHING CHILD TOKEN ID ARRAY
				}               
			}
		   	//------------------------------------DEPENDS ON---------------------------------------------------------
			if(ch==333)//k1 followed by dependsOn 
			{
						//DEPENDS_ON NODE CREATION
						struct dependsOn *new=new_dependsOn;
						new->dnext=NULL;
						new->a_depender=actor_list->val;
						new->t_depender=k1;
					
						while(extr[0]!='\n')	/* SKIPPING LINE */
						   {
						     fread(extr, 1, 1, fp);
						     size--;
						   }	//dependsOn word

						for(i=0;i<4;i++)
						   child[i]='\0';	//	FLUSHING CHILD ARRAY

						fread(extr, 1, 1, fp);	//NEXT CHARACTER IN CODTOKEN
						size--;
						if(extr[0]=='-')	/* VARIABLE FOUND */
						{
					        while(extr[0]!='\t')	/* UNTIL TAB */
					             {
					                fread(extr, 1, 1, fp);
					                size--;
					                if(extr[0]!='\t')
					                strcat(child,extr);		/* STORING ACTOR TOKEN_ID */					
					             }
					  		/*CONVERTING TOKEN_ID INTO INTEGER AND NEGATING*/
						    int d=(int)child[2]-48+ (int)(child[1]-48)*10+(int)(child[0]-48)*100;
					        d=-d;	//DEPENDEE	ACTOR
							new->a_dependee=d;

							for(i=0;i<2;i++)//SKIPPING THIS LINE AND COMMA LINE
						  	 {
								fread(extr, 1, 1, fp);
					            size--;
								while(extr[0]!='\n')/* SKIPPING LINE */
								   {
								     fread(extr, 1, 1, fp);
								     size--;
								   }
							 }


						  	for(i=0;i<4;i++)	//FLUSHING CHILD ARRAY
							  child[i]='\0';
						 	fread(extr, 1, 1, fp);
						 	size--;
						    if(extr[0]=='-')	/* VARIABLE FOUND */
							   {
						           while(extr[0]!='\t')		/* UNTIL TAB */
						             {
						                fread(extr, 1, 1, fp);
						                size--;
						                if(extr[0]!='\t')
						                strcat(child,extr);		/* STORING TOKEN_ID OF TREE NODE*/					
						              }
							        /*CONVERTING TOKEN_ID INTO INTEGER AND NEGATING*/
								    d=(int)child[2]-48+ (int)(child[1]-48)*10+(int)(child[0]-48)*100;
							        d=-d;	//DEPENDEE TREE NODE		
								    new->t_dependee=d;
									for(i=0;i<4;i++)
										child[i]='\0';
							   }

			            }
							if(hd==NULL)//first dependsOn node
							{
								ld=hd=new;
							}
							else    //intermediate dependsOn node
							{
					            ld->dnext=new;
								ld=ld->dnext;
							}

						   for(i=0;i<2;i++)//SKIPPING THIS LINE AND SEMICOLON LINE
						  	 {
								fread(extr, 1, 1, fp);
							    size--;
								while(extr[0]!='\n')/* SKIPPING LINE */
								   {
								     fread(extr, 1, 1, fp);
								     size--;
								   }
		   					 }
			}
			//------------------------------------DEPENDS ON---------------------------------------------------------

			//FLUSHING p_temp & check
			for(i=0;i<4;i++)
			{
		      p_temp[i]='\0';
			  check[i]='\0';
			}		
		 }

		/*------------------TEMP LOADING WITH ACTOR/GOAL/TASK/RESOURCE TOKEN IDS----------------------*/
		else if(c1=='2')
		  {
				fread(extr, 1, 1, fp);
				size--;
				c2=extr[0];
				fread(extr, 1, 1, fp);
				size--;
				c3=extr[0];
				temp[0]=c1;
				temp[1]=c2;
				temp[2]=c3;
		  }

		/*-----------------------------------------------------IF ACTOR IS FOUND---------------------------------------------------*/

		      if(strcmp(temp,"208")==0)	/* 208 is the code-number of keyword 'actor'*/
				{
					while(extr[0]!='\n')//SKIPPING LINE 
					{
						fread(extr, 1, 1, fp);
			            size--;
					}			
		            while(extr[0]!='\t')//UNTIL TAB CHAR
					{
						fread(extr, 1, 1, fp);
						size--;
					    strcat(actor_code,extr); /* STORING ACTOR'S TOKEN ID */     
					}   

					//CONVERTING ACTOR'S TOKEN_ID TO INTEGER AND NEGATING
					k=(int)actor_code[3]-48+ (int)(actor_code[2]-48)*10+(int)(actor_code[1]-48)*100;//converting to integer
					k=-k; 
					
					//TOKEN ID OF ACTOR'S NAME			
				    while(extr[0]!='\n')//UNTIL NEXT LINE
					{
						fread(extr, 1, 1, fp);
						size--;
						if(extr[0]!='\n')
					       strcat(actor_name,extr);	 //STORING ACTOR NAME           
					}       

					//CREATING ACTOR NODE    
		            p=new_actor_node;
					p->val=k;
					strcpy(p->str, actor_name);
					p->next=NULL;

					/*----------------------ACTOR_LIST---------------------*/
					p->next_actor=NULL;
					if(head_actor==NULL)
					{
						actor_list=head_actor=p;
					}
					else
					{
			            actor_list->next_actor=p;
						actor_list=actor_list->next_actor;
					}
					count++;
				   /*----------------------ACTOR_LIST----------------------*/


					//FLUSHING ACTOR_CODE & ACTOR_NAME & TEMP VARIABLES
					for(i=0;i<5;i++)
				        actor_code[i]='\0'; 
					for(i=0;i<50;i++)
				        actor_name[i]='\0';  
		            for(i=0;i<5;i++)
				        temp[i]='\0';            
		             trk=p;//TRK POINTS CURRENT ACTOR NODE p 
				}	   
		        
		/*-------------------------------------------------IF GOAL/TASK/RESOURCE----------------------------------------------------------*/
				
				else if(strcmp(temp,"213")==0 || strcmp(temp,"218")==0 || strcmp(temp,"237")==0 )
				{
			        int gtr;
                    if(strcmp(temp,"213")==0)
				        gtr=213;
			         else if(strcmp(temp,"218")==0)
				        gtr=218;
			         else if(strcmp(temp,"237")==0)
				        gtr=237;
			         else 
				        gtr=0;

				    while(extr[0]!='\n')//SKIPPING LINE
					{
						fread(extr, 1, 1, fp);
			            size--;
					}			
				  while(extr[0]!='\t')//UNTIL TAB
					{
						fread(extr, 1, 1, fp);
						size--;
					    strcat(treenode_code,extr);	//STORING TOKEN ID OF G/T/R(TREENODE_CODE)            
					}
					x=k;
					//CONVERTING G/T/R'S TOKEN_ID TO INTEGER AND NEGATING	
					k=(int)treenode_code[3]-48+ (int)(treenode_code[2]-48)*10+(int)(treenode_code[1]-48)*100;
					k=-k; //ID OF TREENODE			
					int ccnt=0;
					while(extr[0]!='\n')//NAME OF TREENODE STORING
					{
						fread(extr, 1, 1, fp);
						size--;
						if(extr[0]!='\n')
					       strcat(treenode_name,extr);
						ccnt++;	            
					}	
					treenode_name[ccnt]='\0';		
			        //printf("----%s-------\n",treenode_name);
					
					fread(extr,1,1,fp);
						size--;
					while(extr[0]!='\n')//SKIPPING '{'
					  {
						fread(extr,1,1,fp);
						size--;
					  }
					while(extr[0]!='\t')//NEXT TOKEN OF '{' IN CHKTYPE1
					  {
						fread(extr,1,1,fp);
						size--;
						strcat(chktype1,extr);
					  }

		            while(!(chktype1[0]=='1' && chktype1[1]=='0')) //UNTIL '}' FOUND
					{		
		  /*------------------------------------DECOMPOSITION TYPE----------------------------------- */ 
				
						if(chktype1[0]=='3' && chktype1[1]=='0' && chktype1[2]=='0') //IF DECOMPOSITIONTYPE FOUND
						{
								int w;
								for(w=0;w<2;w++)//SKIPPING THE KEYWORDS 'decompositionType' and '='
								{
									fread(extr, 1, 1, fp);
						     		size--;
									while(extr[0]!='\n')//SKIPPING LINE 
										{
										   fread(extr, 1, 1, fp);
						     		       size--;
										}
								}						
		                       for(i=0;i<5;i++)
							      chktype1[i]='\0';
								while(extr[0]!='\t')//CHKTYPE1 STORING OR/AND TOKEN ID
								  {
									fread(extr,1,1,fp);
									size--;
									strcat(chktype1,extr);
								  }
								 	    	
								if(chktype1[0]=='3' && chktype1[1]=='0')// IF OR / AND
		 							{
										if(chktype1[2]=='7') //OR
											t=0;
										else if(chktype1[2]=='4')  //AND
											t=1;	
									}	
		                       
							   for(i=0;i<5;i++)
							      chktype1[i]='\0';
							   for(i=0;i<2;i++)
							    {
		                          fread(extr,1,1,fp);
									size--;
								  while(extr[0]!='\n')
								  {
									fread(extr,1,1,fp);
									size--;
								  }
						     	}
							
		                        while(extr[0]!='\t')
								{
									fread(extr,1,1,fp);
									size--;
									if(extr[0]!='\t')
									   strcat(chktype1,extr);
								}
							   // printf("\n**%s**",chktype1);							   
						}
		 /* ---------------------------------------IDENTIFY THE IE OF EACH NODE---------------------------------------------------- */	
						
					 if(chktype1[0]=='3' && chktype1[1]=='1' && chktype1[2]=='1')
					    {
						  h=NULL;
						  for(i=0;i<20;i++)
		                      IE[i]='\0';
						  while(extr[0]!='<')
						    {
		                     fread(extr,1,1,fp);
						     size--;
						    }				  
						  while(extr[0]!='>')
							{
							   fread(extr,1,1,fp);
						       size--;
							   while(extr[0]!=',')
							   {
		                           fread(extr,1,1,fp);
						           size--;
								   if(extr[0]=='\t')
								   {
		                              fread(extr,1,1,fp);
						              size--;
									  if(extr[0]=='>')
										 break;							 
									  if(extr[0]!=',')
										strcat(IE,extr);							  
								   }
							   }                             

							   ip=new_IE_node;
							   strcpy(ip->var,IE);
							   ip->next=NULL;			
								 
							   if(h==NULL)
								  h=ip;
								
								else 
								{
									pi=h;
									while(pi->next!=NULL)               
									   pi=pi->next;
									pi->next=ip;							
								}
								
							   for(i=0;i<4;i++)
								   IE[i]='\0';
							}
						}
		/*-------------------------------------------IE IS IDENTIFIED------------------------------------------------*/			

			
						while(extr[0]!=';')//SKIPPING ALL UNTIL ';' FOUND
						{
							fread(extr, 1, 1, fp);
				            size--;
						}	
						fread(extr, 1, 1, fp);//SKIPPING '\n'
				            size--;
						for(i=0;i<5;i++)
							 chktype1[i]='\0';//FLUSHING
						while(extr[0]!='\t') //TAKING NEXT TOKENID OF ;
						  {
							fread(extr,1,1,fp);
							size--;
							strcat(chktype1,extr);
						  }				
					}
							
					

					//CREATING TREENODE
		             p1=new_tree_node;
					 p1->val=k;
					 strcpy(p1->str, treenode_name);
					 p1->parent=NULL;
					 p1->type=t;
					 p1->ie=h;
			         p1->ce=NULL;
					 p1->next=NULL;
					 p1->children=NULL;
					 p1->depends_on=NULL;
			         p1->gtr=gtr;
		 			 t=2;
		             if(trk->next==NULL)//TRK -> CURRENT ACTOR'S HEAD 
						{ 
						trk->next=p1;//IF HEAD IS NULL, THEN FIRST TREE NODE
						track=p1;
					    }           
		                else //TRACK CONTAINS LAST TREE NODE
					    {
							track->next=p1;
						    track=track->next;
						    track->next=NULL;
					    }	  
		            for(i=0;i<5;i++)//FLUSHING
					{
						 treenode_code[i]='\0'; 
						 temp[i]='\0'; 
						 chktype1[i]='\0';
						 chktype2[i]='\0';
					}		       
					for(i=0;i<50;i++)
				        treenode_name[i]='\0';           
				}		
		} 
			/*------------------------------------------------SETTING UP DEPENDENCY QUEUE-----------------------------------------------------------------------*/
			if(hd!=NULL)	//HEAD OF TEMP DEPENDS_ON LIST
			{
				ld=hd;		//LD POINTS A DEPENDS_ON NODE
				while(ld!=NULL)
				{
					actor_list=head_actor;
					while(actor_list!=NULL)
					{
						if(actor_list->val==ld->a_depender)
							break;
						actor_list=actor_list->next_actor;
					}
					//-------------------------ACTOR_LIST POINTS TO DEPENDER ACTOR NODE----------------------------------------
					
					tn=actor_list->next;
					while(tn!=NULL)
					{
						if(tn->val==ld->t_depender)
							break;
						tn=tn->next;
					}
					struct tree_node *tn1=tn;
					//printf("%s (%s)----->",actor_list->str,tn1->str);
					//-------------------------TN1 POINTS TO DEPENDER TREE NODE-------------------------------------
					
					struct dependency_queue_node *dqn1=new_dependency_queue_node,*dqn2;  //DQN1 POINTS TO DEPENDENCY_QUEUE_NODE
					dqn1->depen_next=NULL;

					actor_list=head_actor;
					while(actor_list!=NULL)
					{
						if(actor_list->val==ld->a_dependee)
							break;
						actor_list=actor_list->next_actor;
					}
					dqn1->depen_actor=actor_list;
					//-------------------------ACTOR_LIST POINTS TO DEPENDEE ACTOR NODE----------------------------------------

					
					tn=actor_list->next;
					while(tn!=NULL)
					{
						if(tn->val==ld->t_dependee)
							break;
						tn=tn->next;
					}
					dqn1->depen_node=tn;
					//-------------------------TN POINTS TO DEPENDEE TREE NODE-------------------------------------

					if(tn1->depends_on==NULL)		//DEPENDENCY QUEUE NULL
		                  	tn1->depends_on=dqn1; 
		            else		//NOT NULL
					{
							dqn2=tn1->depends_on;		//DQN2 POINTS LAST DEPENDENCY NODE
							while(dqn2->depen_next!=NULL)
									dqn2=dqn2->depen_next;
							dqn2->depen_next=dqn1;		//DQN1 ADDED TO THE DEPENDENCY QUEUE									 
		            }          
					
			
					
					//printf("%s (%s)\n",actor_list->str,tn->str);
					ld=ld->dnext;
				}  
			}
		  /*------------------------------------------------SETTING UP DEPENDENCY QUEUE-----------------------------------------------------------------------*/

		fclose(fp);    
	printf("\nDATA STRUCTURE HAS BEEN CREATED");	
	return head_actor;          
	        
    }
