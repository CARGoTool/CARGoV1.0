#include <stdio.h>
#include <string.h>
#include <io.h>
#include <stdlib.h>
#include "structure.h"

#define new_tree_node (struct tree_node*)malloc(sizeof(struct tree_node))
#define new_IE_node (struct IE_node*)malloc(sizeof(struct IE_node))
#define new_child_queue_node (struct child_queue_node*)malloc(sizeof(struct child_queue_node))
#define new_CE_node (struct CE_node*)malloc(sizeof(struct CE_node))
#define new_parent_queue_node (struct parent_queue_node*)malloc(sizeof(struct parent_queue_node))


int e_resolution(struct conflict* cf,struct actor_node *hd)
{   
	printf("\nEntailment start");
	extern int track;
	int num=track;

	extern int i;
	int id=i;
	
	char count1,count2='0';
	count1=num+48;

	struct tree_node *tmp=NULL;
    struct conflict *cf1=cf;
    while(cf!=NULL)
	{		
		int deficiency_check=0;
		if((cf->con_flag==3 || cf->con_flag==4) && cf->conflicting_cnode!=NULL)/*OR Entailment conflict*/
		{         
          struct tree_node *t=cf->conflicting_pnode;
		  struct child_queue_node *ch=cf->conflicting_cnode;

		  struct IE_node *ie=t->ie;		  
		  struct IE_node *deficiency=NULL;	  
		  int found=0;
          
		  /*implement the deficiency list for ie*/
		  while(ie!=NULL)
				{			  
				  struct CE_node *tempce=ch->ptrc->ce;
				  int flag=0;
                  while(tempce!=NULL)
                  {
					if(strcmp(ie->var,tempce->var)==0)
					   {
                         flag=1;
						 break;
					   }
					tempce=tempce->next;
				  }	
				  if(flag==0)
				  {					
                    struct IE_node *tempie=new_IE_node;
					strcpy(tempie->var,ie->var);
					tempie->next=NULL;

					if(deficiency==NULL)
						deficiency=tempie;
					else
					    {
							struct IE_node *ptr=deficiency;
							while(ptr->next!=NULL)
							  	ptr=ptr->next;
							ptr->next=tempie;
						}
				  }
				ie=ie->next;
				}
			  
			 struct tree_node *tnew=NULL;	
             struct tree_node *z=NULL;
          //---------------check if there exists any node with the deficient CE element in its IE-----------------

             struct tree_node *t1=t->children->ptrc;			
			 while(t1!=NULL) 
			  {
				if(t1->val!=ch->ptrc->val)
				{
                struct IE_node *ix=t1->ie;
				struct IE_node *iex=deficiency;
				if(iex==NULL)
				{
					printf("\nNo deficiency");
					deficiency_check=1;
					break;
			    }
                int search=0;
				while(iex!=NULL)
				{
					search=0;
					struct IE_node *ix1=ix;
					while(ix1!=NULL)
					{
						if(strcmp(iex->var,ix1->var)==0)
						{
						   search=1;
                           break;
						}
						if(search==1)
                          break;
                        else
                          ix1=ix1->next;
					}
					if(search==0)
						break;
					else
					    iex=iex->next;
				}
                if(search==1)				
                  break;					
				else				
                   t1=t1->next;								                 
			  }
				else
					t1=t1->next;
		}
			     if(deficiency_check==1)
                     {
				       cf=cf->next_conflict;
				       continue;
			         }


          //------------------------------------------------------------------------------------------------------------------

                if(t1==NULL)
                {
		   /*-----------check the temporary node list------------*/
			     if(tmp!=NULL)
				 {				  
				  z=tmp;
				  while(z!=NULL)
				  {
					struct IE_node *cx=z->ie;
					struct IE_node *cy=deficiency;
					int same=1;
					while(cx!=NULL && cy!=NULL)
					{
						if(strcmp(cx->var,cy->var)!=0)
						{
							same=0;
							break;
						}
						cx=cx->next;
						cy=cy->next;
					}
					if(same==1 && cx==NULL && cy==NULL)
					{
                        /*check if they belongs to same parent conflicting case*/
                        if(z->parent->ptrp->parent->ptrp->val==ch->ptrc->parent->ptrp->val)			
                        {			
						  found=1;						 
						  break;
					    }
					}
                    z=z->next;
				  }		 
			     }
               
			    if(found==1)
				{
				 struct actor_node *a=hd;
				 while(a!=NULL)
                 {				  
                   struct actor_node *p3;		
	               p3=a;             
		           struct tree_node *temp=p3->next;	
                   while(p3->next!=NULL)	
		           {      
		            if(p3->next->val==z->val)			                 
		              tnew=p3->next;              				   
			        p3->next=p3->next->next;
			       }		           
			       a->next=temp;
			       a=a->next_actor;	
		         }
				
			    }
			    
                if(tmp==NULL || found==0)
			     {			
                  /*implement a new temporary leaf node containing the required ce and ie values*/
         
                   /*set name of the new node*/
				   char name[10]="temp";
				   name[4]=count1;
				   if(num>9)
					 name[5]=count2;
				   strcat(name,"\0");
                   num++;
				   if (num<10)
	                   count1=num+48;
	               else
	               {
		            count1=(num/10)+48;
                    count2=num-10+48;
	               }
                 
				   /*new tree_node creation*/
                   tnew=new_tree_node;	                
				//   tnew->val=(int)-((count-1) -48);
				   tnew->val=--id;
				   tnew->type=2;
				   tnew->children=NULL;		
                   tnew->parent=NULL;/*will be updated later*/	
				   tnew->depends_on=NULL;
				   tnew->ie=deficiency;
				   tnew->ce=NULL;
				   tnew->gtr=213;
			       tnew->next=NULL;
                   strcpy(tnew->str,name);	
                  
		           /*append new leaf node in the temporary leaf node list*/
				   if(tmp==NULL)
				   {					
				   tmp=new_tree_node;
				   strcpy(tmp->str,tnew->str);
				   tmp->val=tnew->val;
				   tmp->children=tnew->children;
				   tmp->parent=tnew->parent;/*will be updated later*/            
				   tmp->depends_on=tnew->depends_on;
				   tmp->ie=tnew->ie;
				   tmp->ce=tnew->ce;
				   tmp->gtr=213;
				   tmp->next=NULL;
				   }
				   else
				   {
					//printf("\ncreate new leaf node");
					struct tree_node *tw=tmp;
					while(tw->next!=NULL)
						 tw=tw->next;
					tw->next=new_tree_node;
				   strcpy(tw->next->str,tnew->str);
				   tw->next->val=tnew->val;
				   tw->next->children=tnew->children;
				   tw->next->parent=tnew->parent;/*will be updated later*/ 
				   tw->next->depends_on=tnew->depends_on;
				   tw->next->ie=tnew->ie;
				   tw->next->ce=tnew->ce;
				   tw->next->gtr=213;
				   tw->next->next=NULL;
				   }
			     }
                 }
/*----------------implement another temporary node which will be placed in place of conflicting child node------------------*/

               /*set name of the new node*/
				char name1[10]="temp";
				name1[4]=count1;
			    if(num>9)
					 name1[5]=count2;
				strcat(name1,"\0");
                num++;
			    if (num<10)
	             count1=num+48;
                else
	             {
		          count1=(num/10)+48;
                  count2=num-10+48;
	             }

			    /*new tree_node creation*/
				struct tree_node *tnew1=new_tree_node;
				//tnew1->val=(int)-((count-1) -48);
			    tnew1->val=--id;
				tnew1->type=1;
			    
				struct child_queue_node *cn=new_child_queue_node;/*will be updated later*/
                cn->ptrc=ch->ptrc;	
			    cn->next=NULL;
                tnew1->children=cn;
                tnew1->parent=NULL;	/*will be updated later*/	
				tnew1->depends_on=NULL;
				tnew1->ie=ch->ptrc->ie;
				tnew1->ce=NULL;/*will be updated later*/
			    tnew1->gtr=213;
                strcpy(tnew1->str,name1);   
              
			    /*Parent queue updation of the intermediate temporary node*/
			    struct parent_queue_node *pp=new_parent_queue_node;
			    pp->ptrp=t;
			    pp->pnext=NULL;
			    tnew1->parent=pp;
                
			      /*Parent queue updation of the leaf temporary node*/
			      if(found==0 && t1==NULL)
				  {
			      pp=new_parent_queue_node;
			      pp->ptrp=tnew1;
			      pp->pnext=NULL;
			      tnew->parent=pp; 

                  struct tree_node *m=tmp;
                  while(m->next!=NULL)
                       m=m->next;
				  
                  m->parent=pp;				  
                  }
			      else if (t1==NULL && found==1)
				  {
				   pp=tnew->parent;
				   while(pp->pnext!=NULL)
					 pp=pp->pnext;
				   pp->pnext=new_parent_queue_node;
				   pp->pnext->ptrp=tnew1;
				   pp->pnext->pnext=NULL;
			      }
                  
                  /*parent queue updation of child conflicting node*/
			      struct parent_queue_node *pn=ch->ptrc->parent;
			      struct parent_queue_node *prv=pn;
			      if(pn->ptrp->val==t->val)
				     ch->ptrc->parent=pn->pnext;
			      else
				  {				   
				   pn=pn->pnext;
				   while(pn!=NULL)
					   {
					     if(pn->ptrp->val==t->val)
						 {
						   prv->pnext=pn->pnext;
						   free(pn);
						   break;
					     }
					     prv=prv->pnext;
				       }
			      }
                  
			       struct parent_queue_node *pn1=ch->ptrc->parent;
			       if(pn1==NULL)
				     {
				       //printf("\nPARENT IS NULL");
				       pn1=new_parent_queue_node;
				       pn1->ptrp=tnew1;
				       pn1->pnext=NULL;
				       ch->ptrc->parent=pn1;
			         }
				   else
				     {
				      while(pn1->pnext!=NULL)
					       pn1=pn1->pnext;
				       pn1->pnext=new_parent_queue_node;
				       pn1->pnext->ptrp=tnew1;
				       pn1->pnext->pnext=NULL;
				       ch->ptrc->parent=pn1->pnext;
			         }

                  /*child queue updation*/ 
                 struct child_queue_node *cc=new_child_queue_node;
			     if(t1==NULL)//if there is no existing node with deficient CE
			        cc->ptrc=tnew;
			     else				   
				    cc->ptrc=t1;				    			        
				   
			     cc->next=NULL;
                 
			     struct child_queue_node *x=tnew1->children;			    
			     while(x->next!=NULL)
				      x=x->next;
			     x->next=cc;
                
			     //parent queue updation if a node with deficient CE already exist
			     if(t1!=NULL)
				 {
				   struct parent_queue_node *px=t1->parent;
				   struct parent_queue_node *pn=new_parent_queue_node;
				   pn->ptrp=tnew1;
				   pn->pnext=NULL;

				   while(px->pnext!=NULL)
					   px=px->pnext;
				   px->pnext=pn;	
                   fprintf(flog,"\n%s becomes parent of %s\n",pn->ptrp->str,t1->str);			   
			     }
			   
                  
			      /*insert these new temporary nodes into main data structure*/			     
			        tnew1->next=t->next;
			        t->next=tnew1;
			       
			        if(t1== NULL && found==0)
				    {
                      struct tree_node *tt=t;
			          while(tt->next!=NULL)
				         tt=tt->next;
			          tt->next=tnew; 		          
                    }
                     fprintf(flog,"\n%s is added to the data structure",tnew1->str);
			         fprintf(flog,"\nParent: %s",tnew1->parent->ptrp->str);
			         if(tnew1->children==NULL)
                          fprintf(flog,"\nChildren: NULL \n");
			         else
				         {
				            fprintf(flog,"\nChildren: ");
				            struct child_queue_node *c=tnew1->children;
				            while(c!=NULL)
					         {
					           fprintf(flog,"%s ",c->ptrc->str);
					           c=c->next;
				             }
				             fprintf(flog,"\n\n");
			             }

               /*update the child queue node of the conflicting parent's queue*/
                struct child_queue_node *pr=t->children;
			    struct child_queue_node *prev=new_child_queue_node;
			    prev->next=pr;
			    int first=0;
			    while(pr!=NULL)
			    {
				  if(pr->ptrc->val==ch->ptrc->val)
				  {
				   
                   if(pr==t->children)/*The first node in the parent queue list*/	
                      {
						first=1;
						t->children=pr->next;
					  }				     
				   else
					{
                      prev->next=pr->next;
					  
					  if(prev->next!=NULL)
					     pr=prev->next;
					  else
							pr=NULL;
					}
				  }
				 if(pr!=NULL)
				  {
                     pr=pr->next;
				     prev=prev->next;
				  } 
			    }
			   
			    if(first==0)
			    {
			     prev->next=new_child_queue_node;
			     prev->next->ptrc=tnew1;
			     prev->next->next=NULL;	
                }
			    
			    else if(first==1)
			    {
				  struct child_queue_node *yq=new_child_queue_node;
				  yq->ptrc=tnew1;
				  if(t->children!=NULL)
					 {
					   struct child_queue_node *w=t->children;
					   t->children=yq;
					   yq->next=w;
				     }
				 else
				    {
					 t->children=yq;
					 yq->next=NULL;
				    }
			    }
                     
			        t=cf->conflicting_pnode;
			        while(t->parent!=NULL)
				         t=t->parent->ptrp;
                   
			        int remove_ce(struct actor_node *, struct tree_node *);
                    remove_ce(hd, t);			    
			        int sem_rec(struct actor_node *);
			        sem_rec(hd);
		}
		
/*------------------------------------------------------------------------------------------------------------------------------------*/
	    else if(cf->con_flag==3 && cf->conflicting_cnode==NULL)//AND Full Entailment conflict
	    {
		  //printf("\nParent=%s",cf->conflicting_pnode->str);
          //printf("\nel_num=%d",cf->el_no);		  
		  int single_ce=1, ce_element_count=1,countx=1, partial=0;
          struct tree_node *t=cf->conflicting_pnode;	
          
		  /*check if the parent has single set of CE or multiple set of CE*/
          struct CE_node *cep=t->ce;
		  while(cep!=NULL)
			{
              if(strcmp(cep->var,",")==0)
				{
					single_ce=0;
					ce_element_count++;
					break;
				}
				cep=cep->next;
			}
		  /*if the parent has multiple set of CE*/
          if(single_ce==0)
		  {
			struct conflict* cfx=cf->next_conflict;          		
			while(cfx!=NULL)/*check if all the set of CE has full entailment conflict*/
				{
                  if(cfx->conflicting_pnode->val==cf->conflicting_pnode->val && cfx->con_flag==3)
						countx++;		
				  cfx=cfx->next_conflict;
				}	
                struct conflict *cp=cf1;
                while(cp!=NULL)
				{
					 if(cp->con_flag==4 && cp->conflicting_pnode->val==cf->conflicting_pnode->val)
                     partial=1;
					 cp=cp->next_conflict;
				}
                    		    	
		  }
          if(partial==1)
			{
				cf=cf->next_conflict;
				continue;
			}
				
		  
              
		  /*partial entailments are solved before full entailment, in case of mixed entailement condition in multiple CE set*/
		  
          /*if parent has single set of CE or parent has multiple SET of CE and all of them have full entailment conflict*/
 	      if(single_ce==1 || ce_element_count==countx|| partial==0)
		  {
		  struct IE_node *ie=t->ie;		  
		  struct IE_node *deficiency=NULL;	  
          
		  //implement the deficiency list for ie
		  while(ie!=NULL)
				{			  
				  struct CE_node *tempce=t->ce;
				  if(single_ce==0)
					{
					  int x=1;
					  if(x!=cf->el_no)
					  {
                      struct CE_node *t2=t->ce;
					  while(t2!=NULL)
						{
							if(strcmp(t2->var,",")==0)
                               x++;
							t2=t2->next;
							if(x==cf->el_no)
							{
								tempce=t2;
								break;
							}
						}
					  }
					}
				  int flag=0;
                  while(tempce!=NULL && strcmp(tempce->var, ",")!=0) 
                  {
					if(strcmp(ie->var,tempce->var)==0)
					   {
						 printf("\nsame=%s",ie->var);
                         flag=1;
						 break;
					   }
					tempce=tempce->next;
				  }	
				  if(flag==0)
				  {					
                    struct IE_node *tempie=new_IE_node;
					strcpy(tempie->var,ie->var);
					tempie->next=NULL;

					if(deficiency==NULL)
						deficiency=tempie;
					else
					    {
							struct IE_node *ptr=deficiency;
							while(ptr->next!=NULL)
							  	ptr=ptr->next;
							ptr->next=tempie;
						}
				  }
				ie=ie->next;
				}              
			     
				if(deficiency==NULL)
					{
					 printf("\nNo deficiency");
					 cf=cf->next_conflict;
					 continue;
				    }
                //implement a new temporary leaf node containing the required ce and ie values
         
                   //set name of the new node
				   char name[6]="temp";
				   name[4]=count1;
			       if(num>9)
					 name[5]=count2;
				   strcat(name,"\0");
                   num++;
			        if (num<10)
	                  count1=num+48;
					else
	    			{
		   			count1=(num/10)+48;
            		count2=num-10+48;
	    			}
      
				   //new tree_node creation
                   struct tree_node *tnew=new_tree_node;	                
				   //tnew->val=(int)-((count-1) -48);
			       tnew->val=--id;
				   tnew->type=2;
				   tnew->children=NULL;		
                   tnew->parent=NULL;//will be updated later
				   tnew->depends_on=NULL;
				   tnew->ie=deficiency;
				   tnew->ce=NULL;
			       tnew->gtr=213;
			       tnew->next=NULL;
                   strcpy(tnew->str,name);

			       //update parent queue of the leaf node
			       struct parent_queue_node *pp=new_parent_queue_node;
			       pp->ptrp=t;
			       pp->pnext=NULL;
			       tnew->parent=pp; 
			   
			       //update child queue of the conflicting parent node
			       struct child_queue_node *cc=new_child_queue_node;
			       cc->ptrc=tnew;
			       cc->next=NULL;
			       struct child_queue_node *x=t->children;			    
			       while(x->next!=NULL)
				      x=x->next;
			       x->next=cc;
			       x->next->next=NULL;

			         t=cf->conflicting_pnode;
			        while(t->parent!=NULL)
				         t=t->parent->ptrp;
                    
			        int remove_ce(struct actor_node *, struct tree_node *);
                    remove_ce(hd, t);
			        int sem_rec(struct actor_node *);
			        sem_rec(hd);
	            
				    //insert these new temporary node into main data structure			     
			        tnew->next=t->next;
			        t->next=tnew;	  
                   fprintf(flog,"\n%s is added to the data structure",tnew->str);
			       fprintf(flog,"\nParent: %s \n",tnew->parent->ptrp->str);
				  
                   if(tnew->children==NULL)
                          fprintf(flog,"\nChildren: NULL \n");
			         else
				         {
				            fprintf(flog,"\nChildren: ");
				            struct child_queue_node *c=tnew->children;
				            while(c!=NULL)
					         {
					           fprintf(flog,"%s ",c->ptrc->str);
					           c=c->next;
				             }
				             fprintf(flog,"\n\n");
			             }
		    }
			
	    }		
	    cf=cf->next_conflict;                     	    
    }

	while(cf1!=NULL)
	{	  
	  printf("\nPARTIAL AND CONFLICT:      Parent: %s",cf1->conflicting_pnode->str);      
      if(cf1->con_flag==4 && cf1->conflicting_cnode==NULL)
	    {		  
          int el_num=cf1->el_no, numx=1, single_ch=0;
		  if(cf1->conflicting_pnode->children->next==NULL)
				single_ch=1;
		  struct CE_node *common=NULL, *deficiency=NULL;
		  struct CE_node *cex=cf1->conflicting_pnode->ce;
          
		  printf("\nel_num=%d\n",el_num);

		  while(numx!=el_num)
			{
				printf("%s",cex->var);
				if(strcmp(cex->var,",")==0)
					numx++;
				if(numx!=el_num)
				   cex=cex->next;				
			}
			//printf("%s",cex->var);
				
			struct CE_node *cex1=cex;
			while(cex1!=NULL)
			{
			  printf("\n**** %s",cex1->var);//the ce element in which conflict occurs
              cex1=cex1->next;
			}

		  struct IE_node *iex=cf1->conflicting_pnode->ie;
          struct CE_node *cx=cex;
		  int cmn=0;

		  //find out the common and deficieny parts of CE
		  while(iex!=NULL)
               {
				 struct CE_node *c=new_CE_node;
				 strcpy(c->var,iex->var);
				 c->next=NULL;
                 cx=cex;
				 cmn=0;
                 printf("\n IE=%s",iex->var);
				 while( cx!=NULL && strcmp(cx->var,",")!=0 )
				 {
				  printf("\n CE=%s",cx->var);
				  if(strcmp(cx->var,iex->var)==0)
				     {
					  if(common==NULL)
						common=c;
					  else
					    {
						  struct CE_node *x=common;
						  while(x->next!=NULL)
							x=x->next;
						  x->next=c;
					    }
					  cmn=1;
					  break;
				     }
                  else
					 cx=cx->next;					
				 }
				
                  if(cmn==0)
                  {
                    if(deficiency==NULL)
						deficiency=c;
					  else
					    {
						  struct CE_node *x=deficiency;
						  while(x->next!=NULL)
							x=x->next;
						  x->next=c;
					    }
				  }   
				iex=iex->next;
			   }
			   printf("\nNode=%s element num: %d",cf1->conflicting_pnode->str,cf1->el_no);
               printf("\n\nThe common part:");
			   struct CE_node *c1=common;
			   while(c1!=NULL)
				     {
				     printf("%s",c1->var);
			         c1=c1->next;
			         }
			   printf("\n\nThe deficiency part:");
			   c1=deficiency;
			   while(c1!=NULL)
				     {
				     printf("%s",c1->var);
			         c1=c1->next;
			         }
			   //find out which child node contains the maximum common part
			   int max1=0,max2=0;
			   
			   if(deficiency==NULL)
			   {
				cf1=cf1->next_conflict;
				continue;
			   }

			   if(deficiency!=NULL)
			   {
				 struct child_queue_node *ch=cf1->conflicting_pnode->children;
				 struct tree_node *max_node=NULL;
				 while(ch!=NULL)
				 {
					max2=0;
                    struct CE_node *c1=ch->ptrc->ce;
					struct CE_node *c2=common;

					while(c2!=NULL)
					{
						struct CE_node *c3=c1;
						while(c3!=NULL)
						{
							if(strcmp(c2->var,c3->var)==0)
							{
								max2++;
								break;
							}
							c3=c3->next;
						}
						c2=c2->next;
					}
                    if(max2>max1)
					{
						max1=max2;
						max_node=ch->ptrc;
					}
					ch=ch->next;	
				 }
				 printf("\nThe node having maximum common ce: %s",max_node->str);
				 
                 if(max_node->type==1 || max_node->type==2)
				 {					
				   /*set name of the new node*/
				   char name[10]="temp";
				   name[4]=count1;				   
				   if(num>9)
					 name[5]=count2;
				   strcat(name,"\0");
                   num++;
				   if (num<10)
	                   count1=num+48;
	               else
	               {
		            count1=(num/10)+48;
                    count2=num-10+48;
	               }
                   

					//create the ie list
					struct IE_node *ie_hd=NULL;
					cex=deficiency;
					while(cex!=NULL)
					{
                       struct IE_node *in=new_IE_node;
					   strcpy(in->var,cex->var);
					   in->next=NULL;

					   if(ie_hd==NULL)
							ie_hd=in;
					    else
						{
							struct IE_node *i=ie_hd;
							while(i->next!=NULL)
								i=i->next;
							i->next=in;
						}
						cex=cex->next;
					}

				   //create the new node
				   struct tree_node *tnew2=new_tree_node;
				   tnew2->val=--id;
				   tnew2->type=2;
				   tnew2->children=NULL;		
                   tnew2->parent=NULL;/*will be updated later*/	
				   tnew2->depends_on=NULL;
				   tnew2->ie=ie_hd;
				   tnew2->ce=NULL;
				   tnew2->gtr=213;
			       tnew2->next=NULL;
                   strcpy(tnew2->str,name);	
                   //printf("\nThe new node: %s",tnew2->str);

                   //update child list of conflicting node
					struct child_queue_node *cq=NULL;
					 cq=max_node->children;
                  
                    
					struct child_queue_node *cq1=new_child_queue_node;
					cq1->ptrc=tnew2;
					cq1->next=NULL;

                    if(cq!=NULL)
                    {                
					while(cq->next!=NULL)
						cq=cq->next;
					cq->next=cq1;
				    }
                    else
						max_node->children=cq1;

                    
					 //update parent list of new node
                     struct parent_queue_node *p=new_parent_queue_node;					 
                     p->ptrp=max_node;					 
                     p->pnext=NULL;                                 
            		 tnew2->parent=p;            	
                        
                     /*insert these new temporary node into main data structure*/	
					 struct tree_node *hold=NULL;
                     if(max_node->next!=NULL)		     
			             hold=max_node->next;
					 max_node->next=tnew2;
		             if(max_node->next!=NULL)
					     tnew2->next=hold;

					 if(max_node->type==2)
						max_node->type=1;
                     fprintf(flog,"\n%s is added to the data structure",tnew2->str);
			               fprintf(flog,"\nParent: %s \n",tnew2->parent->ptrp->str);
					 if(tnew2->children==NULL)
                          fprintf(flog,"\nChildren: NULL \n");
			         else
				         {
				            fprintf(flog,"\nChildren: ");
				            struct child_queue_node *c=tnew2->children;
				            while(c!=NULL)
					         {
					           fprintf(flog,"%s ",c->ptrc->str);
					           c=c->next;
				             }
				             fprintf(flog,"\n\n");
			             }

				 }
                 
				 if(max_node->type==0)
				 {
                 //find out from which node the common ce part comes
					
					struct child_queue_node *cq=max_node->children;
					while(cq!=NULL)
					{ 
                      int countx=0;    
                      int flag=0;               
					  struct CE_node *ce2=common;
					  while(ce2!=NULL)
						{
							flag=0;
							struct CE_node *ce1=cq->ptrc->ce;							
							while(ce1!=NULL && strcmp(ce1->var,",")!=0)
							{
							   if(strcmp(ce1->var,ce2->var)==0)
								{
									flag=1;
                                    countx++;
									break;
								}
								ce1=ce1->next;
							}
							if(flag==0)							
                              break;							
							else							
                               ce2=ce2->next;							
						}
					
							
						if(flag==0)
							cq=cq->next;
						else
							{
							 printf("\nThe common part comes from node %s",cq->ptrc->str);
							 break;
						    }
					}
					
					printf("\n\nThe having max number of common CE is: %s",cq->ptrc->str);
						    
				
					
          //search if there exists the deficient CE in other children of conflicting parent

					struct child_queue_node *cq2=cf1->conflicting_pnode->children;
					struct child_queue_node *hold=NULL;
					while(cq2!=NULL)
					{
						if(cq2->ptrc->val!=cf1->conflicting_cnode->ptrc->val)//-----------------THIS IF STATEMENT IS ADDED LATER
					    {
						int flag=0;
						struct CE_node *ce1=deficiency;
						struct IE_node *ce2=cq2->ptrc->ie;
						while(ce1!=NULL)
						{
						   flag=0;
                           while(ce2!=NULL && strcmp(ce2->var,",")!=0)
							{
								if(strcmp(ce1->var,ce2->var)==0)
								{
									flag=1;
									break;
								}
								ce2=ce2->next;
							}
							if(flag==0)
							  break;
							else
							  ce1=ce1->next;
						}
						if(flag==0)
							cq2=cq2->next;
						else
						   {
							if(cq2->ptrc->type==0 || cq2->ptrc->type==1 )
							{
                                hold=cq2;
								cq2=cq2->ptrc->children;
						    }
							else
                                break;
						   }						   
					}
					else
						cq2=cq2->next;
					}
					if(cq2==NULL && hold!=NULL)
						cq2=hold;
                    //if(cq2!=NULL)					
					    //printf("\nThe deficient CE is found at node %s",cq2->ptrc->str);
				 
//-------------------------------------------------------------------------------------------------------------------------------------
                   //construct a new intermediate node

				  //set name of the new node
				   char name[10]="temp";				 
				   name[4]=count1;
				   if(num>9)
					 name[5]=count2;
				   strcat(name,"\0");
                   num++;
				   if (num<10)
	                   count1=num+48;
	               else
	               {
		            count1=(num/10)+48;
                    count2=num-10+48;
	               }
                   printf("\nTHE NAME: %s",name);
				   
                    //create the ie list
					struct IE_node *ie_hd=NULL;
					cex=cq->ptrc->ce;
					while(cex!=NULL)
					{
                       struct IE_node *in=new_IE_node;
					   strcpy(in->var,cex->var);
					   in->next=NULL;

					   if(ie_hd==NULL)
							ie_hd=in;
					    else
						{
							struct IE_node *i=ie_hd;
							while(i->next!=NULL)
								i=i->next;
							i->next=in;
						}
						cex=cex->next;
					}

             
                   //create the new node
				   struct tree_node *tnew3=new_tree_node;
				   tnew3->val=--id;
				   tnew3->type=1;
				   tnew3->children=NULL;//will be updated later		
                   tnew3->parent=NULL;//will be updated later
				   tnew3->depends_on=NULL;
				   tnew3->ie=ie_hd;
				   tnew3->ce=NULL;
				   tnew3->gtr=213;
			       tnew3->next=NULL;
                   strcpy(tnew3->str,name);	

               

				    //update child list of conflicting node
					struct child_queue_node *cw=max_node->children;					
					while(cw->next!=NULL)
						cw=cw->next;
					struct child_queue_node *cw1=new_child_queue_node;
					cw1->ptrc=tnew3;
					cw1->next=NULL;
					cw->next=cw1;
                    
					 //update parent list of new node
                     struct parent_queue_node *p=new_parent_queue_node;
                     p->ptrp=max_node;
                     p->pnext=NULL;                     
            		 tnew3->parent=p;	
 
                     //update child list of the new node
					 struct child_queue_node *chd=new_child_queue_node;
					 chd->ptrc=cq->ptrc;
					 chd->next=NULL;
					 tnew3->children=chd;


					 struct tree_node *tnew4=NULL;
                     struct child_queue_node *chd1=NULL;
					 if(cq2!=NULL)
					 {					   
                       chd1=new_child_queue_node;
					   chd1->ptrc=cq2->ptrc;
					   chd1->next=NULL;
						 
					   struct child_queue_node *x=tnew3->children;
					   while(x->next!=NULL)
							x=x->next;
					   x->next=chd1;

					   //only for error checking------
					   x=tnew3->children;
					   printf("\n\nChildren of %s",tnew3->str);
                       while(x!=NULL)
						{
							printf("  %s",x->ptrc->str);
							x=x->next;
						}
					  //----------------------------------*/
					 }
					 else
					{
						
					//create new leaf node

                    //set name of the new node
				   char name[10]="temp";				 
				   name[4]=count1;
				   if(num>9)
					 name[5]=count2;
				   strcat(name,"\0");
                   num++;
				   if (num<10)
	                   count1=num+48;
	               else
	               {
		            count1=(num/10)+48;
                    count2=num-10+48;
	               }
                    printf("\nTHE NAME: %s",name);
					

                    //create the ie list
					struct IE_node *ie_hd=NULL;
					cex=deficiency;
					while(cex!=NULL)
					{
                       struct IE_node *in=new_IE_node;
					   strcpy(in->var,cex->var);
					   in->next=NULL;

					   if(ie_hd==NULL)
							ie_hd=in;
					    else
						{
							struct IE_node *i=ie_hd;
							while(i->next!=NULL)
								i=i->next;
							i->next=in;
						}
						cex=cex->next;
					}
					
                    
                   //create the new node
				   tnew4=new_tree_node;
				   tnew4->val=--id;
				   tnew4->type=2;
				   tnew4->children=NULL;//will be updated later		
                   tnew4->parent=NULL;//will be updated later
				   tnew4->depends_on=NULL;
				   tnew4->ie=ie_hd;
				   tnew4->ce=NULL;
				   tnew4->gtr=213;
			       tnew4->next=NULL;
                   strcpy(tnew4->str,name);	

				   struct child_queue_node *chd1=new_child_queue_node;
				   chd1->ptrc=tnew4;
				   chd1->next=NULL;
                   tnew3->children->next=chd1;	

				   struct parent_queue_node *p=new_parent_queue_node;
				   p->ptrp=tnew3;
				   p->pnext=NULL;

                   tnew4->parent=p;                   			  
				 }                       

                     /*insert these new temporary node into main data structure*/	
					 struct tree_node *hold1=NULL;
                     if(max_node->next!=NULL)
                         {		     
			              hold1=max_node->next;
					      max_node->next=tnew3;
						  tnew3->next=hold1;
					     }
                     else
                         max_node->next=tnew3;		             
                     
                     fprintf(flog,"\n !!! %s is added to the data structure",tnew3->str);
			         fprintf(flog,"\nParent: %s \n",tnew3->parent->ptrp->str);
					 if(tnew3->children==NULL)
                          fprintf(flog,"\nChildren: NULL \n");
			         else
				         {
				            fprintf(flog,"\nChildren: ");
				            struct child_queue_node *c=tnew3->children;
						    
				            while(c!=NULL)
					         {
					           fprintf(flog,"%s ",c->ptrc->str);
							   printf("\n-----%s ",c->ptrc->str);
					           c=c->next;
				             }		                        		     
				             fprintf(flog,"\n\n");
			             }
					 
                    if(cq2==NULL)
					{
					struct tree_node *ty=tnew3;
					while(ty->next!=NULL)
						ty=ty->next;
					ty->next=tnew4;
                    fprintf(flog,"\n%s ** is added to the data structure",tnew4->str);
			        fprintf(flog,"\nParent: %s \n",tnew4->parent->ptrp->str);                  
                    fprintf(flog,"\nChildren: NULL \n");
			        }
                    
				     //update the child queue node of new node
					 struct child_queue_node *chx=new_child_queue_node;
					 chx->ptrc=cq->ptrc;
					 chx->next=NULL;
                      	

                   //eliminate the old parent 
				  // printf("\n%s is no more parent of %s",max_node->str,cq->ptrc->str);			     
				   struct parent_queue_node *px=cq->ptrc->parent;
				   struct parent_queue_node *prev=px;
					
				   if(px->ptrp->val==max_node->val)
					 {	                        				    			    
						cq->ptrc->parent=cq->ptrc->parent->pnext;
					   // free(px);
				     }					  
				   else
				    {
					 px=px->pnext;
					 while(px!=NULL)
					  {
                        if(px->ptrp->val==max_node->val)
						{
                          prev->pnext=px->pnext;
						  free(px);
						  break;
						}
						px=px->pnext;
						prev=prev->pnext;
					  }
				    }
                     
                   //eliminate the that child also
                   struct child_queue_node *cx=max_node->children;
				   struct child_queue_node *prev1=cx;
				   if(cx->ptrc->val==cq->ptrc->val)
					 {                                     				    			    
						max_node->children=max_node->children->next;
					   // free(cx);
				     }					  
				   else
				    {					    
					 cx=cx->next;
					 while(cx!=NULL)
					  {
                        if(cx->ptrc->val==cq->ptrc->val)
						{
                          prev1->next=cx->next;						 
						  //free(cx);						  
						  break;
						}						
						cx=cx->next;
						prev1=prev1->next;
					  }					
				    }	
			   		   
                  
			       //update child list of max_node					
                   struct child_queue_node *px1=max_node->children;
				   struct child_queue_node  *prv1=px1;
				   if(px1->ptrc->val==cq->ptrc->val)
					 {                                                                				    			    
						max_node->children=max_node->children->next;
					    //free(px1);
				     }					  
				   else
				    {                     				 
					 px1=px1->next;                    
					 while(px1!=NULL)
					  {						
                        if(px1->ptrc->val==cq->ptrc->val)
						{                          						  
                          prv1->next=px1->next;
						  free(px1);
						  break;
						}
						px1=px1->next;
						prv1=prv1->next;
					  }						
				    }
                     
					/*---------------for checking only------------*/


                     /*printf("\n NODE=%s",max_node->str);
					 struct child_queue_node *w=max_node->children;
					 printf("\n CHILDREN:");
					 while(w!=NULL)
						{
                          printf("%s  ",w->ptrc->str);
						  w=w->next;
					    }
                     printf("\n NODE=%s",cq->ptrc->str);
					 struct parent_queue_node *z=cq->ptrc->parent;
					 printf("\n PARENT:");
					 if(z==NULL)
						printf(" NULL");
					 while(z!=NULL)
						{
                          printf("%s  ",z->ptrp->str);
						  z=z->pnext;
					    }*/


					/*---------------------------------------------*/
                     
                       
				       //parent list update					  
					   struct parent_queue_node *pp=cq->ptrc->parent;				      
					   struct parent_queue_node *pp2=new_parent_queue_node;
					   pp2->ptrp=tnew3;
					   pp2->pnext=NULL;
                      
                       if(pp!=NULL)		
                          {                         
                         // printf("\npp=%s",pp->ptrp->str); 
					      while(pp->pnext!=NULL)
							pp=pp->pnext;
					      pp->pnext=pp2;
					      }
					    else
						  cq->ptrc->parent=pp2;
				         
				 if(cq2==NULL)
				 {
					//set name of the new node
				   char name[10]="temp";
				   name[4]=count1;
				   if(num>9)
					 name[5]=count2;
				   strcat(name,"\0");
                   num++;
				   if (num<10)
	                   count1=num+48;
	               else
	               {
		            count1=(num/10)+48;
                    count2=num-10+48;
	               }

                    //create the ie list
					struct IE_node *ie_hd=NULL;
					cex=deficiency;
					while(cex!=NULL)
					{
                       struct IE_node *in=new_IE_node;
					   strcpy(in->var,cex->var);
					   in->next=NULL;

					   if(ie_hd==NULL)
							ie_hd=in;
					    else
						{
							struct IE_node *i=ie_hd;
							while(i->next!=NULL)
								i=i->next;
							i->next=in;
						}
						cex=cex->next;
					}


                   //create the new node
				   struct tree_node *tnew4=new_tree_node;
				   tnew4->val=--id;
				   tnew4->type=2;
				   tnew4->children=NULL;	
                   tnew4->parent=NULL;//will be updated later
				   tnew4->depends_on=NULL;
				   tnew4->ie=ie_hd;
				   tnew4->ce=NULL;
				   tnew4->gtr=213;
			       tnew4->next=NULL;
                   strcpy(tnew4->str,name);	

                       //parent list update					   
						struct parent_queue_node *pp2=new_parent_queue_node;
						pp2->ptrp=tnew3;
						pp2->pnext=NULL;
						tnew4->parent=pp2;
				}
				else
					{
						struct parent_queue_node *q1=cq2->ptrc->parent;
						struct parent_queue_node *qhd=NULL;
						while(q1!=NULL)	
                            {
                              struct parent_queue_node *q=new_parent_queue_node;
                              q->ptrp=q1->ptrp;
                              q->pnext=NULL;
					          
							  if(qhd==NULL)
								qhd=q;
							  else
							   {
								struct parent_queue_node *q3=qhd;
								while(q3->pnext!=NULL)
                                     q3=q3->pnext;
								q3->pnext=q;
							   }
							  q1=q1->pnext;
						    } 
                            
                        cq2->ptrc->parent=qhd;
						struct parent_queue_node *q2=new_parent_queue_node;
						q2->ptrp=tnew3;
						q2->pnext=NULL;
						
                        while(qhd->pnext!=NULL)
                        	qhd=qhd->pnext;	                        				
						qhd->pnext=q2;						
					}
                     if(tnew3->children==NULL)					
					     tnew3->children=chx;					 
				   }
                    
                    struct tree_node *t=cf1->conflicting_pnode;
                    struct tree_node *t1=t;

				   printf("\n\n******************THE TREE**************************\n\n");
				    while(t1!=NULL)
				    {
					  printf("\nNode= %s",t1->str);
					  struct parent_queue_node *p=t1->parent;
					  struct child_queue_node *c=t1->children;
					  printf("\nParent:  ");
					  if(p==NULL)
						printf("NULL");
					  while(p!=NULL)
					     {
						 printf("%s  ",p->ptrp->str);
					     p=p->pnext;
					     }
					   printf("\nChildren:  ");
					   if(c==NULL)
						 printf("NULL");
					   while(c!=NULL)
					     {
						 printf("%s  ",c->ptrc->str);
					     c=c->next;
					     }
					  t1=t1->next;
				    }  
                   
                    int remove_ce(struct actor_node *, struct tree_node *);		           
                    remove_ce(hd, t);		             
			        int sem_rec(struct actor_node *);
			        sem_rec(hd);                                                      
			   }	
		}		     
        cf1=cf1->next_conflict;	
		
		//printf("\nTrack=%d\n\n",num);	    
	}
	 

 /*--------------------------------------------------------------------------------------------------------------------------*/

printf("\nEnd: Entailment resolution\n\n");
extern int track;
track=num;
return id;
}
