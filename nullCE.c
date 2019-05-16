#include <stdio.h>
#include <string.h>
#include <io.h>
#include <stdlib.h>
#include "structure.h"

void null_CE(struct actor_node *head)
{
  
  struct actor_node *actor_list=head;
  while(actor_list!=NULL)
       {
			struct tree_node *tree=actor_list->next;
			while(tree!=NULL)
			{
				tree->ce=NULL;
				tree=tree->next;
			}	
  			actor_list=actor_list->next_actor;      
	   }
} 
