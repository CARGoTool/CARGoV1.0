
#include <stdio.h>
#include <string.h>
#include <io.h>
#include <stdlib.h>
#include "structure.h"


void conflict_display(struct conflict *conhead,char *fname)
{
	//printf("\n Start: Display---------------");
	FILE *fpo=fopen(fname,"w");
 	fprintf(flog,"\n\nTHE CONFLICTS ARE SHOWN IN THE FILE %s",fname);
  	printf("\n------------------------------------------------------------------------------------\n\n\n");
	struct conflict *conptr=conhead;
	if(conptr!=NULL)
		fprintf(fpo,"\n-------------------Conflicts---------------------\n");
	else
		fprintf(fpo,"\n-------------------No Conflicts---------------------\n");
	while(conptr!=NULL)
	{
		fprintf(fpo,"\n\n%s ------ [ ",conptr->conflicting_pnode->str);
		struct child_queue_node *chi=conptr->conflicting_cnode; 
		while(chi!=NULL)
		{
			fprintf(fpo,"%s  ",chi->ptrc->str);
			if(conptr->con_flag!=2) break;
			chi=chi->next;
		}
		fprintf(fpo," ]");
		if(conptr->con_flag==3)	fprintf(fpo,"\nFull Entailment Conflict");
		else if(conptr->con_flag==1) fprintf(fpo,"\nHierarchical Consistency Conflict");
		else if(conptr->con_flag==2) fprintf(fpo,"\nSibling Consistency Conflict");
		else if(conptr->con_flag==4)	fprintf(fpo,"\nPartial Entailment Conflict");
		if(conptr->el_no>=0)	fprintf(fpo,"\nElement No: %d",conptr->el_no);
		conptr=conptr->next_conflict;
	}
	  //printf("\n\n End: Display---------------");
	fclose(fpo);
}
