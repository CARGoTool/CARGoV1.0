#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "structure.h"
int count=1,track=1,i;

int main_count(void)
	 {		
		return count++;
	 }

extern char* filename(char[],int);
extern int IsSame(int);
int main(int argc,char *argv[])
{
	
	 system("del *.opm");

     flog=fopen("AFSRlogs.opm","a");/*Change ----  File is empty. flog is declared in structure.h*/
	 printf("Main --------------------\n");
	
	 extern int filtoken_func(int,char**);
	 filtoken_func(argc,argv);
    
     extern int recognize_func();
	 i=recognize_func();  /*CHANGE*/  
     printf("\nInitial id=%d",i);


     extern int modlroot(); 
	 modlroot();

	 extern struct actor_node *my_datastructure();
	 struct actor_node *head_actor=my_datastructure(); 	

	 extern struct conflict* sem_rec(struct actor_node *);
	 struct conflict* conflict_list=sem_rec(head_actor);	
    // printf("Conflict check--");

	 int c=1;
	 extern void conflict_display(struct conflict* ,char*);
    // printf("Conflict display--%d ",c);
	 conflict_display(conflict_list,filename("Conflict_V",c));

	 extern int display(struct actor_node *,char*);//change---- extra argument added
	 display(head_actor,filename("datastructure_V",c));
     
	 extern int e_resolution(struct conflict* ,struct actor_node *);
     extern int Rem_Node_Having_Null_IE(struct actor_node *head);
	 extern void hc_resolution(struct conflict*);
	 extern void sc_resolution(struct conflict*);
	 extern void null_CE(struct actor_node *);
     static int it;
     //int loop=0;
     while(conflict_list!=NULL)
	 {
		++it; //iteration count
	    // printf("\n\n",it);
         fprintf(flog,"\n----------Conflict Resolution : ITERATION %d:---------",it);
		 
		 fprintf(flog,"\n\t**********************************************");
		 fprintf(flog,"\n\t**********************************************");

		 hc_resolution(conflict_list);
		 printf("\n\nHC     end  ");
		 Rem_Node_Having_Null_IE(head_actor);
		 null_CE(head_actor);
		 conflict_list=sem_rec(head_actor);	
  		 c++;
		 display(head_actor,filename("datastructure_V",c));
		 //conflict_list=conflict_check(head_actor);
		 conflict_display(conflict_list,filename("Conflict_V",c)); 
		 
         
         fprintf(flog,"\n------ End of Hierarchical Consistency Conflict Resolution ------\n");  

         i=e_resolution(conflict_list, head_actor);
		 printf("\n\nid value=%d  ",i); 
	     Rem_Node_Having_Null_IE(head_actor);
		 null_CE(head_actor);
		 conflict_list=sem_rec(head_actor);	
		 c++;
		 display(head_actor,filename("datastructure_V",c));
		 //conflict_list=conflict_check(head_actor);
		 conflict_display(conflict_list,filename("Conflict_V",c)); 
	  
	     fprintf(flog,"\n------ End of Entailment Conflict Resolution ------\n");


		 sc_resolution(conflict_list);
		 printf("\n\nSC     end  ");
		 Rem_Node_Having_Null_IE(head_actor);//new change
		 null_CE(head_actor);
		 conflict_list=sem_rec(head_actor);	
  		 c++;
		 display(head_actor,filename("datastructure_V",c));
		 conflict_display(conflict_list,filename("Conflict_V",c));

         fprintf(flog,"\n------ End of Sibling Consistency Conflict Resolution ------\n\n\n"); 
  
	     if(IsSame(c)) break;//if two conflict files from last 2 iterations are same, then break		
	 }
	 extern int create_output_text(struct actor_node *);
	 create_output_text(head_actor);
     fprintf(flog,"\nOutput text is generated and strored in output_goal.xgrl\n");
	 fprintf(flog,"\nIteration required= %d\n",it);
     fclose(flog);
	 exit(0);
	 return 0;

}

