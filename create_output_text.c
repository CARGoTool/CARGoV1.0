#include <stdio.h>
#include <string.h>
#include <io.h>
#include <stdlib.h>
#include "structure.h"

int create_output_text(struct actor_node *head)
{

  FILE *fpo=fpo=fopen("output_goalTDA.xgrl","w");
  fprintf(fpo,"grl test model\n{");
 
  struct actor_node *actor_list=head;
  while(actor_list!=NULL)
     {
        printf("\nACTOR=%s",actor_list->str);         
		fprintf(fpo,"\n\tactor %s{\n\t\t",actor_list->str);
	    struct tree_node *t;

 /*------------------------------------------------DECOMPOSITION TYPE & IE--------------------------------------------------*/
               
        int x;
		for (x=0;x<2;x++)
		{
			t=actor_list->next;
			while(t!=NULL)
			{
				if((x==0 && t->type==2)||(x==1 && t->type!=2))  goto nxt;
				if (x==1)  fprintf(fpo,"\t");
				if(t->gtr==213)
					fprintf(fpo, "goal ");
				 else if(t->gtr==218)
	                fprintf(fpo, "task ");
	             else if(t->gtr==237)
	                fprintf(fpo, "resource ");
				fprintf(fpo,"%s{",t->str);
				if(t->type==0)
					fprintf(fpo,"decompositionType=or;IE=<");
				else if(t->type==1)
					fprintf(fpo,"decompositionType=and;IE=<");
				else
					fprintf(fpo,"IE=<");
				fprintf(fpo,"%s",t->ie->var);
				struct IE_node *tie=t->ie->next;
				while(tie!=NULL)
				{
					fprintf(fpo,",%s",tie->var);
					tie=tie->next;
				}
				fprintf(fpo,">;}\n\t\t");
				nxt:
				 t=t->next;
			}
        }

		
 /*------------------------------------------------DEPENDS ON--------------------------------------------------*/
               
		t=actor_list->next;
		while(t!=NULL)
		{
	         struct dependency_queue_node *d=t->depends_on;
	         while(d!=NULL)
		        {
		          fprintf(fpo,"%s dependsOn %s.%s;\n\t\t",t->str,d->depen_actor->str,d->depen_node->str);
		          d=d->depen_next;
	            }
	          t=t->next;
	    }

 /*------------------------------------------------DECOMPOSED BY--------------------------------------------------*/
               
		t=actor_list->next;
		while(t!=NULL)
		{
			if(t->type!=2)
			 {
				fprintf(fpo,"%s decomposedBy %s",t->str,t->children->ptrc->str);
				struct child_queue_node *cq=t->children->next;
				while(cq!=NULL)
				 {
					fprintf(fpo,",%s",cq->ptrc->str);
					cq=cq->next;
				 }
				fprintf(fpo,";\n\t\t");
			 }
			t=t->next;
		}
	    actor_list=actor_list->next_actor;	//NEXT ACTOR NODE    	
        fprintf(fpo,"}\n\n");
     }
  fprintf(fpo,"\n}");
  fclose(fpo);  

  return 0;
} 
