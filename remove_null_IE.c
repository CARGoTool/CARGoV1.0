#include <stdio.h>
#include <string.h>
#include <io.h>
#include <stdlib.h>
#include "structure.h"


int Rem_Node_Having_Null_IE(struct actor_node *head)
{
  //fprintf(flog,"\nTHE nodes having null IE set is being deleted.....\n");
 // printf("\n------------------------------------------------------------------\n\n\n");
 
  struct actor_node *actor_list=head;
  while(actor_list!=NULL)
       {
        struct tree_node *tree=actor_list->next,*prev_tree=NULL;
		while(tree!=NULL)
		{
			if(tree->ie==NULL)//Tree_node that has NULL IE set
			{
					
					fprintf(flog,"\nThe tree node %s is deleted as it's IE set became NULL\n",tree->str);
	//--------------------------------------------  Parent setup   --------------------------------------------------------------

					struct parent_queue_node *parent_list=tree->parent;
				    while(parent_list!=NULL)
					{
					    //DELETING OWN LINK FROM PARENT'S CHILD_LIST
						struct child_queue_node *sibling_list = parent_list->ptrp->children,*prev_sibling=NULL;
					    if(sibling_list->next==NULL) //Single child, making parent a leaf node//new change
						  {
							parent_list->ptrp->children=NULL;
						    parent_list->ptrp->type=2;
						  }
					    else//new change
						  {
							while(sibling_list!=NULL)//traversing sibling_list
							{
								if(sibling_list->ptrc->val==tree->val)
								{		
									 if(prev_sibling==NULL)
										parent_list->ptrp->children=sibling_list->next;
								     else
									 	prev_sibling->next=sibling_list->next;
									break;	//REMOVED OWN LINK
								}
								prev_sibling=sibling_list;
								sibling_list=sibling_list->next;
							}
					      }
					   	if(tree->children!=NULL)//new change
						{	
						   //ADDING OWN CLILD_LIST WITH THE PARENT'S CHILD_LIST
							sibling_list = parent_list->ptrp->children;
							while(sibling_list->next!=NULL)//traversing sibling_list
								sibling_list=sibling_list->next;
							sibling_list->next=tree->children; //ADDED CHILD_LIST
						}	
						parent_list=parent_list->pnext;
					}					
//-----------------------------------------------------  Parent setup  ----------------------------------------------------------

					printf("***parent setup done****");	
//-----------------------------------------------------  Child setup   ----------------------------------------------------------

					struct child_queue_node *child_list=tree->children;
				   // printf("\nNODE TO BE DELETED: %s", tree->str);
					while(child_list!=NULL)
					{	                         
					    int flag=0;
					    //DELETING OWN LINK FROM CHILD'S PARENT_LIST
						struct parent_queue_node *p_list = child_list->ptrc->parent,*prev_p=NULL;
						while(p_list!=NULL)//traversing p_list
						{			    
							if(p_list->ptrp->val==tree->val)
							{		
							     flag=1;
                                // printf("\nCHILD: %s",child_list->ptrc->str); 
							     //printf("  PARENT: %s",p_list->ptrp->str);
								 if(prev_p==NULL)
								    {
								      //printf("  ONE");
                                      child_list->ptrc->parent=p_list->pnext;
								      //printf("  DONE");
							        }
									
							     else
								     {
								        //printf("  TWO");
                                       	prev_p->pnext=p_list->pnext;								 
							         }	                                					   
								break;	//REMOVED OWN LINK
							}
							prev_p=p_list;
							p_list=p_list->pnext;
						}
					 		 
					   	//ADDING OWN PARENT_LIST WITH THE CHILD'S PARENT_LIST
					    if(child_list->ptrc->parent!=NULL && flag==1)
                            {
						        struct parent_queue_node *pq=NULL;	
                                struct parent_queue_node *hd=new_parent_queue_node;	
					        
						        p_list = tree->parent;
						        hd->ptrp=p_list->ptrp;
							    hd->pnext=NULL;

                                while(p_list->pnext!=NULL)//traversing p_list	
                                      {
							            pq=new_parent_queue_node;
							            pq->ptrp=p_list->pnext->ptrp;
							            pq->pnext=NULL;
                                        
                                        if(hd->pnext==NULL)
								            hd->pnext=pq;
							            else
								            {
								             struct parent_queue_node *x=hd;
								             while(x->pnext!=NULL)
									            x=x->pnext;
								             x->pnext=pq;
							                }
							            p_list=p_list->pnext;	
						              }			
                               pq=child_list->ptrc->parent;
						       struct parent_queue_node *xx=new_parent_queue_node;
						       xx->ptrp=pq->ptrp;
						       xx->pnext=NULL; 

						       while(pq->pnext!=NULL)
							        {
							          struct parent_queue_node *y=new_parent_queue_node;
							          y->ptrp=pq->pnext->ptrp;
							          y->pnext=NULL;

							          if(xx->pnext==NULL)
								         xx->pnext=y;
							          else
								          {
								            struct parent_queue_node *z=xx;
								            while(z->pnext!=NULL)
									           z=z->pnext;
								            z->pnext=y;
							              }
							          pq=pq->pnext;
						            }							        
						       xx->pnext=hd;
                               child_list->ptrc->parent=xx;			       
					        }						   
			             else if(flag==1)
						    child_list->ptrc->parent=tree->parent;  
                        
                        //printf("\n NEXT: %s",child_list->next->ptrc->str);
						child_list=child_list->next;
					}					
//------------------------------------------------------  Child setup   -----------------------------------------------------------



//----------------------------------------------------- dependency setup  ----------------------------------------------------------
						struct actor_node *actor_list_dep=head;
  						while(actor_list_dep!=NULL)
       					{
							if(actor_list->val==actor_list_dep->val)
								{	actor_list_dep=actor_list_dep->next_actor;	 continue;	}

							struct tree_node *tree_dep=actor_list_dep->next;
							while(tree_dep!=NULL)
							{
								struct dependency_queue_node *depqn=tree_dep->depends_on,*prev_depqn=NULL;
								while(depqn!=NULL)
								{
									//printf(" \n\n%s dependsOn %s->%s\n\n",tree_dep->str,depqn->depen_actor->str,depqn->depen_node->str);
									//printf("%d---%d",depqn->depen_node->val,tree->val);
									if(depqn->depen_node->val==tree->val)
									{
										if(prev_depqn==NULL)
											tree_dep->depends_on=depqn->depen_next;
										else
											prev_depqn->depen_next=depqn->depen_next;
										//printf("\nDeleting depen node %s from %s\n",tree->str,tree_dep->str);
										break;
									}
									prev_depqn=depqn;
									depqn=depqn->depen_next;
								}

								tree_dep=tree_dep->next;
							}


							actor_list_dep=actor_list_dep->next_actor;
						}
//--------------------------------------------------  dependency setup  -------------------------------------------------------------
						
//--------------------------------------------------  next setup  ---------------------------------------------------------------------
						if(prev_tree==NULL)
						{
							actor_list->next=tree->next;
							tree=tree->next;
						}
						else
						{
							prev_tree->next=tree->next;
							tree=prev_tree->next;				
						}
//----------------------------------------------------  next setup  ----------------------------------------------------------------


			}
			else  //Node having non null IE
			{
				prev_tree=tree;
				tree=tree->next;
		    }
		}	  
		actor_list=actor_list->next_actor;	//NEXT ACTOR NODE    	
	   }

	return 0;

}
