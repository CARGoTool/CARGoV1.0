#include <stdio.h>
#include <string.h>
#include <io.h>
#include <stdlib.h>
#include "structure.h"

int display(struct actor_node *head,char *fname) //change---- extra argument added
{
  FILE *fpo=fopen(fname,"w");
	//if(fpo==NULL) exit(0);
  fprintf(flog,"\n\nTHE DATA STRUCTURE IS SHOWN IN THE FILE %s",fname);
  //printf("\n------------------------------------------------------------------------------------\n\n\n");
 
  struct actor_node *actor_list=head;
  while(actor_list!=NULL)
       {
		//printf("%s*************\n",actor_list->str);
        struct actor_node *p3;		
		p3=actor_list;               
		fprintf(fpo,"[%d",p3->val);
		fprintf(fpo,"|%s]\n\n\t",p3->str);
		struct tree_node *temp=p3->next;		
		while(p3->next!=NULL)	
		     {      
		     fprintf(fpo,"----->[%d|%s|type=%d]", p3->next->val,p3->next->str,p3->next->type);
			//----------------------PARENT QUEUE----------------------------
		     struct parent_queue_node *prpq;
		     prpq=p3->next->parent;
		     if(prpq!=NULL)	
				{
				 fprintf(fpo,"\n\t parent queue: |");
				 while(prpq!=NULL)
					{
						fprintf(fpo,"%d|",prpq->ptrp->val);
						prpq=prpq->pnext;
					}				    
				}
			//--------------------------CHILD QUEUE--------------------------------
					struct child_queue_node *pq;
		            pq=p3->next->children;
		            if(pq!=NULL)	
					{
						fprintf(fpo,"\n\t child queue: |");
						while(pq!=NULL)
							{
								fprintf(fpo,"%d|",pq->ptrc->val);
								pq=pq->next;
							}				    
					}
						//-----------------------DEPENDENCY QUEUE---------------------------------
					struct dependency_queue_node *depq;
		            depq=p3->next->depends_on;
		            if(depq!=NULL)	
					{
						fprintf(fpo,"\n\t dependency: |");
						while(depq!=NULL)
						{
								//if(depq->depen_actor!=NULL)
										fprintf(fpo,"%d (%d)|",depq->depen_actor->val,depq->depen_node->val);
										depq=depq->depen_next;
						}				    
					 }
			
                 
					//------------------------IE LIST--------------------------
					struct IE_node *ip2;
		            ip2=p3->next->ie;
                    if(ip2!=NULL)
                    {		           
					fprintf(fpo,"\n\t IE list  : |");
			       
					while(ip2!=NULL)
						{   				                 
						    	fprintf(fpo,"%s|",ip2->var);
							    ip2=ip2->next;
					     }   
					}   
                       // ------------------------CE LIST--------------------------
					struct CE_node *cp=NULL;
		            cp=p3->next->ce;		           
					fprintf(fpo,"\n\t CE list  : |");
			       
					while(cp!=NULL)
						{				            
							fprintf(fpo,"%s|",cp->var);
							cp=cp->next;                                                               		           
						}           

                     // ------------------------ELEMENT COUNT OF CE--------------------------
			        //fprintf(fpo,"\n\t CE ELEMENTS COUNT: %d\n\n",p3->next->CE_count);
           
					p3->next=p3->next->next;		//NEXT TREE NODE	
			        fprintf(fpo,"\n\t");	
			       
			}
			  actor_list->next=temp;
			  actor_list=actor_list->next_actor;	//NEXT ACTOR NODE    	
              fprintf(fpo,"\n");
		}


//-------------------------------------------------------------------------------------------------------------------------------

/*while(actor_list!=NULL)
       {
        struct actor_node *p3;		
		p3=actor_list;               
		printf("[%d",p3->val);
		printf("|%s]\n\n\t",p3->str);
		struct tree_node *temp=p3->next;		
		while(p3->next!=NULL)	
		     {      
		     printf("----->[%d|%s|type=%d]", p3->next->val,p3->next->str,p3->next->type);
			//----------------------PARENT QUEUE----------------------------
		     struct parent_queue_node *prpq;
		     prpq=p3->next->parent;
		     if(prpq!=NULL)	
				{
				 printf("\n\t parent queue: |");
				 while(prpq!=NULL)
					{
						printf("%d|",prpq->ptrp->val);
						prpq=prpq->pnext;
					}				    
				}
			//--------------------------CHILD QUEUE--------------------------------
					struct child_queue_node *pq;
		            pq=p3->next->children;
		            if(pq!=NULL)	
					{
						printf("\n\t child queue: |");
						while(pq!=NULL)
							{
								printf("%d|",pq->ptrc->val);
								pq=pq->next;
							}				    
					}					
			
                 
					//------------------------IE LIST--------------------------
					struct IE_node *ip2;
		            ip2=p3->next->ie;
                    if(ip2!=NULL)
                    {		           
					printf("\n\t IE list  : |");
			       
					while(ip2!=NULL)
						{   				                 
						    	printf("%s|",ip2->var);
							    ip2=ip2->next;
					     }   
					}   
                       // ------------------------CE LIST--------------------------
					struct CE_node *cp=NULL;
		            cp=p3->next->ce;		           
					printf("\n\t CE list  : |");
			       
					while(cp!=NULL)
						{				            
							printf("%s|",cp->var);
							cp=cp->next;                                                               		           
						}           

                     // ------------------------ELEMENT COUNT OF CE--------------------------
			        //fprintf(fpo,"\n\t CE ELEMENTS COUNT: %d\n\n",p3->next->CE_count);
           
					p3->next=p3->next->next;		//NEXT TREE NODE	
			        printf("\n\t");	
			       
			}
			  actor_list->next=temp;
			  actor_list=actor_list->next_actor;	//NEXT ACTOR NODE    	
              printf("\n");
		}
  fclose(fpo);  
*/
return 0;
} 

