#include <stdio.h>
#include <string.h>
#include <io.h>
#include <stdlib.h>
#include "structure.h"

int remove_ce(struct actor_node *head, struct tree_node *root)
{
//  printf("\n\n Start: Remove CE---------------");
  struct actor_node *actor_list=head;
  while(actor_list!=NULL)
       {
        struct actor_node *p3;		
		p3=actor_list;             
		struct tree_node *temp=p3->next;
        if(p3->next->val==root->val)
        {	
	    	while(p3->next!=NULL)	
		     {      
		      p3->next->ce=NULL;
			  p3->next=p3->next->next;
			 }
			 actor_list->next=temp;
			 break;
	    }
        else		  
			actor_list=actor_list->next_actor;	
	   }
// printf("\n\n End: Remove CE---------------");
return 0;
} 
