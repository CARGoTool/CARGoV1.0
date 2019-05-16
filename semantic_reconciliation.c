#include <stdio.h>
#include <string.h>
#include <io.h>
#include <stdlib.h>
#include "structure.h"

#define new_CE_node (struct CE_node*)malloc(sizeof(struct CE_node))

struct CE_node * rec(struct tree_node *Ai, struct tree_node *Aj)
{
	struct CE_node *cn=Aj->ce;
	struct CE_node *chead=NULL, *cc=chead;
    char temp_ie[3], temp_ce[30];
    while(cn!=NULL)
	{
		int flag=0;
		strcpy(temp_ce,cn->var);
		struct IE_node *in=Ai->ie;
		while(in!=NULL)
		{
          strcpy(temp_ie,in->var);
          if (temp_ie[0]=='~' && temp_ce[0]!='~')
			{
              if(temp_ie[1]==temp_ce[0])
				{
					flag=1;
				}
			}
			else if(temp_ie[0]!='~' && temp_ce[0]=='~')
			{
				if(temp_ie[0]==temp_ce[1])
				{
                    flag=1;
				}
			}			
            in=in->next;
		}
            if(flag==0)
			{
                    struct CE_node *ct=new_CE_node;
					strcpy(ct->var,temp_ce);
					ct->next=NULL;

				   if(chead==NULL)
						chead=ct;
				   else 
						{
						 cc=chead;
						 while(cc->next!=NULL)               
						    cc=cc->next;
						 cc->next=ct;							
						}
			}
		flag=0;
		cn=cn->next;
	}
	return chead;    
}

int sem_rec(struct actor_node *head)
{
  printf("\n\n\n Start: Semantic Reconciliation---------------");
  struct actor_node *p=head;  
  while(p!=NULL)
  {
	struct tree_node *t=p->next;	
	while(t->ce==NULL)
	{	     
		struct child_queue_node *ch=t->children;
		if(ch!=NULL)
	    {
        while(ch->ptrc->ce!=NULL && ch->next!=NULL)
        {		
		  ch=ch->next;
		  if(ch->ptrc->ce==NULL)
		      t=ch->ptrc;
		}		
		
		while(ch->ptrc->ce==NULL && ch->ptrc->children!=NULL)
		{   			
			t=ch->ptrc;
			ch=t->children;			
		}
	        
		    while(ch->ptrc->ce!=NULL && ch->next!=NULL)
	        {			  
			  ch=ch->next;
		      if(ch->ptrc->ce==NULL)
				 break;			
		    }  
	     }
   
		 if(ch==NULL)
			{
				ch=new_child_queue_node;
				ch->ptrc=t;
				ch->next=NULL;
             }
		 if(ch->ptrc->ce==NULL)
		 {		
			struct CE_node *ce_head=NULL;
			
			while(ch!=NULL)
		    {
            if(ch->ptrc->ce==NULL)			
			   t=ch->ptrc;		   
            if(t->type==2 && t->depends_on==NULL && t->ce==NULL )/*independent leaf node*/
			  { 	                            
                struct IE_node *i2=t->ie;	
				struct CE_node *c=NULL, *c1=NULL;
				ce_head=NULL;
				//if(i2==NULL)
					//printf("\n NO IE");
				while(i2!=NULL)
				{                    	
					c=new_CE_node;					
					strcpy(c->var,i2->var);					
					c->next=NULL;	
 				   
					if(ce_head==NULL)
						ce_head=c;
					else
                        {
						  c1=ce_head;
						  while(c1->next!=NULL)               
							   c1=c1->next;
						  c1->next=c;	
                          c->next=NULL;						
						}					
					i2=i2->next;                    					
				}                      	 
			    t->ce=ce_head; 
				//if(t->ce!=NULL)
                   //printf("\n%s get ce",t->str);   
			  }					
            else if(t->type==2 && t->depends_on!=NULL)/*dependent leaf node*/
                    {
						struct CE_node *r=rec(t,t->depends_on->depen_node);
						t->ce=r;
						
					}                      
			if(t->type==2 && t->parent!=NULL)
                  {
                    t=t->parent->ptrp;
					//printf("\nt=%s",t->str);
					ch=ch->next;
					while(ch!=NULL && ch->ptrc->ce!=NULL )
						 {
						//	printf("\nch=%s",ch->ptrc->str);
							ch=ch->next;
						 }
                        /* if(ch!=NULL)
                            printf("\nch=%s",ch->ptrc->str);
					if(ch!=NULL)
					   printf("\n NEXT=  %s",ch->ptrc->str);
					if(ch!=NULL && ch->ptrc->ce!=NULL)
							printf(" has CE\n"); */
				  }		
             else
                  {
						ch=t->children;
                        while(ch!=NULL && ch->ptrc->ce!=NULL)
							ch=ch->next;
				  }                               
            }
          //   printf("\nOut of loop");			 
		 }
		  //printf("\nt=%s",t->str);
          //if(t->ce!=NULL)
				//printf("\n Has CE");
			//else
				//printf("\n Has no CE");  
		 if(t->type==0 && t->ce==NULL)/*OR reconciliation*/
		 {           		  
		   struct CE_node *hd=NULL, *r=NULL, *pt, *pp;
           ch=t->children;
		   int null=0;
		   while(ch!=NULL)
		   {
			 if(ch->ptrc->ce==NULL)
			 {
				t=ch->ptrc;
				null=1;
				//printf("\nThe child %s has no CE\n",ch->ptrc->str);
				break;
			 }
			 else
			 {
			 r=rec(t,ch->ptrc);
			
			 if(hd==NULL)
				  hd=r;				
			 else
			    {
				  pp=new_CE_node;
				  strcpy(pp->var,",");
				  pp->next=NULL;

                  pt=hd;
				  while(pt->next!=NULL)
					  pt=pt->next;
				  pt->next=pp;
				  pp->next=r;     
				}
			 ch=ch->next;
			 }
		   }
			
		   if(null==0)
				{
				//printf("\n%s get ce\n",t->str);
		        t->ce=hd;
				
		    if(t->ce!=NULL)
				{
                 //printf("\n %s has CE  ",t->str);	        
				}						
                 struct CE_node *c=t->ce;
				 while(c!=NULL)
						{
							//printf("%s",c->var);
							c=c->next;
						}				      	
                  while(t->parent!=NULL)		
                  {
				   if(t->parent->ptrp->ce==NULL)
				     {
							t=t->parent->ptrp;
							break;
				     }
                    t->parent=t->parent->pnext;
				  }		
				}				
		 }          
        
     if(t->type==1 && t->ce==NULL)/*AND reconciliation*/
	  {	
         //printf("\nT=%s",t->str);	   
		 int null=0;
		 ch=t->children;
		 while(ch!=NULL)
		    {
				if(ch->ptrc->ce==NULL)
				  {
				    null=1;
				    break;
				  }
				ch=ch->next;
			}
			if(null==0)
			  {
                struct CE_p *start=NULL, *hdd=NULL;
				ch=t->children;
				while(ch!=NULL)
				     {
                       if(  (ch->ptrc->type==0 || ch->ptrc->type==1)   && hdd==NULL)
						{							
							struct CE_node *c1=ch->ptrc->ce;
							while(c1!=NULL)
							{								
								if(strcmp(c1->var, ",")==0)
								{
									struct CE_p *s2=new_CE_p;
                                    s2->c=NULL;							
									s2->next=NULL;

									start->next=s2;
									start=start->next;									
									c1=c1->next;
								}
                                //printf("\n--------------------------------%s",c1->var);

								struct CE_node *n=new_CE_node;
								strcpy(n->var,c1->var);
								n->next=NULL;                                
                              
                                if(start==NULL)
									{
									  start=new_CE_p;
									  start->c=n;
									  start->next=NULL;
									  hdd=start;									  
 								    }
								else
								   {						
									struct CE_node *n1=start->c;
									if(n1==NULL)
										start->c=n;
									else
								    {
									while(n1->next!=NULL)
										n1=n1->next;
									n1->next=n;
								    }
								   }			
                                   c1=c1->next;									   
							}
                            //printf("\nOut of loop");							
						}

						else if((ch->ptrc->type==0 || ch->ptrc->type==1) )
					    {
                            //printf("\nchild %s",ch->ptrc->str);
							int num=1;
							struct CE_node *c1=ch->ptrc->ce;
							while(c1!=NULL)
							{
								if(strcmp(c1->var, ",")==0)
									num++;
								c1=c1->next;
							}							
                                  int i1,i2=0,row=1;
							      struct CE_p *h2=hdd;
							     
							      while(h2->next!=NULL)
								         {
								          row++;								         						          
								          h2=h2->next;                                          							          
							             }
									     //printf("\nRow=%d",row);

							      for(i1=1;i1<num;i1++)
								  {
								    struct CE_p *z=hdd;
								    i2=0;
								    while(i2<row)
								    {
									//printf("\nRow%d:  ",i2);
								    struct CE_p *y=hdd;
								    while(y->next!=NULL)
									     y=y->next;
									
								    y->next=new_CE_p;
								    y->next->c=NULL;
								    y->next->next=NULL;                               

								    struct CE_node *c2=z->c;
									
								    while(c2!=NULL)
									   {
										// printf("%s",c2->var);

									     struct CE_node *c3=new_CE_node;
									     strcpy(c3->var,c2->var);
									     c3->next=NULL;
                                         
                                         if(y->next->c==NULL)
										    y->next->c=c3;
									     else
										   {
										    struct CE_node *ctmp=y->next->c;
										    while(ctmp->next!=NULL)											
											      ctmp=ctmp->next;
										    ctmp->next=c3;
									       }
									   c2=c2->next;
								       }
									   //printf("\nOut of inner loop");
									   z=z->next;
									   i2++;
								    }
								    //printf("\nOut of outer loop");
								  }	
							      int xx=1,flag=0;
                                  struct CE_p *hh=hdd;
                                  struct CE_p *hh1=hh->next;
							      while(hh1!=NULL)
								  {
								    flag=0;
								    struct CE_node *c=hh1->c;
								    struct CE_node *ck=hh->c;
								    while(c!=NULL)
									 {
									   if(strcmp(c->var,ck->var)!=0)
										 {
										  xx++;
										  flag=1;
										  break;
									     }
									   c=c->next;
									   ck=ck->next;
								     }
								     if(flag==0)
									   break;
								     else
									   hh1=hh1->next;								     
							      }
							      //printf("\nxx=%d",xx);
                                  

                                  c1=ch->ptrc->ce;							      
							      struct CE_p *h=hdd;
                                  
							      /*-------------only for error checking---------------*/
							       //printf("\n");
							       while(h!=NULL)
								   {
                                      struct CE_node *c=h->c;
								      while(c!=NULL)
									  {
                                         //printf("%s",c->var);
									     c=c->next;
   								      }
								      //printf("\n");
								      h=h->next;
  							       }
							      /*---------------------------------------------*/
                                    //printf("\nNUM=%d",num);
                                    struct CE_node *c2=ch->ptrc->ce;
                                    h=hdd;
							           int num2=1;
							        while(h!=NULL)
								    {								   
								    while(c2!=NULL)
								    {									 
								     struct CE_node *c3=h->c;
								     if(c3!=NULL)
								        while(c3->next!=NULL)
									       c3=c3->next;

								     if(strcmp(c2->var,",")!=0)
									 {
								       struct CE_node *x1=new_CE_node;
								       strcpy(x1->var,c2->var);
								       x1->next=NULL;									 
									   c3->next=x1;
                                     }
                                     c2=c2->next;
                                     
								     if(c2!=NULL && strcmp(c2->var, ",")==0 )
									   {
                                        //printf("\nNUM=%d NUM2=%d",num,num2);										
										if(num2<xx) 
										{
											c2=c1;
                                            num2++;
										}	
                                        else
                                            {		
                                            num2--;								   
                                            c2=c2->next;
											c1=c2;
                                            }                                           								   
										break;
									   }							    							   
									}
									h=h->next;
								    if(h!=NULL && c2==NULL)
									   {
                                         c2=c1;
									     num2=1;
								       }
									   
								    }
                                   // printf("\nOut of loop");	

                                   /*-------------only for error checking---------------*/
							       h=hdd;
							       //printf("\n");
							       while(h!=NULL)
								   {
                                      struct CE_node *c=h->c;
								      while(c!=NULL)
									  {
                                         //printf("%s",c->var);
									     c=c->next;
   								      }
								      //printf("\n");
								      h=h->next;
  							       }
							      /*---------------------------------------------*/
					      
						}

						else if(ch->ptrc->type==2)
						{
							//printf("\nchild %s",ch->ptrc->str);
							if(hdd==NULL)
						    {
                               struct CE_node *c1=ch->ptrc->ce;	
							   while(c1!=NULL)
								{
									struct CE_node *ce=new_CE_node;
									strcpy(ce->var,c1->var);
									ce->next=NULL;

									if(hdd==NULL)
									{
										hdd=new_CE_p;
										hdd->c=ce;
										hdd->next=NULL;
									}
									else if(hdd->c==NULL)
                                       hdd->c=ce;
                                    else
                                        {
										  struct CE_node *hc=hdd->c;
										  while(hc->next!=NULL)
											hc=hc->next;
										  hc->next=ce;
									    }	
									c1=c1->next;
								}
							//	printf("\n Outof loop");
							}
							else
							{
                                struct CE_node *c1=ch->ptrc->ce;
                                struct CE_p *xh=hdd;
                                while(xh!=NULL)
                                {	
							  	  while(c1!=NULL)
								   {
									   struct CE_node *ce=new_CE_node;
									   strcpy(ce->var,c1->var);
									   ce->next=NULL;

                                       struct CE_node *ck=xh->c;
									   while(ck->next!=NULL)
                                              ck=ck->next;
										ck->next=ce;
									    c1=c1->next;
								   }
									xh=xh->next;
									c1=ch->ptrc->ce;
							    }
							}
						}		
						ch=ch->next;
					 }
                  
			  struct CE_p *h1=hdd;
			  struct CE_node *hd=NULL;
              

              while(h1!=NULL)
				{
				   struct CE_node *cp=h1->c;
				   struct CE_node *prev=cp;

				   while(cp!=NULL)
					{
							struct CE_node *cp2=cp->next;
							prev=cp;
							while(cp2!=NULL)
							{
								
                                if(strcmp(cp->var,cp2->var)==0)
                                {
                                    //printf("\ncp=%s  cp2=%s  prev=%s",cp->var, cp2->var, prev->var);	
									if(cp2->next!=NULL)
									{
										prev->next=cp2->next;
										free(cp2);
										cp2=prev->next;
									}	
									else
									{
										prev->next=NULL;
										cp2=NULL;
									    free(cp2);
								    }
								}	
								else
								{
                                cp2=cp2->next;
                                prev=prev->next;
                                }						
							}
							
							cp=cp->next;
					}
					h1=h1->next;
				}
			 
	         h1=hdd;
			  while(h1!=NULL)
				{
                  struct CE_node *cc=h1->c;
				  while(cc!=NULL)
                      {
							struct CE_node *cc1=new_CE_node;
							strcpy(cc1->var,cc->var);
							cc1->next=NULL;

							if(hd==NULL)
								hd=cc1;
							else
							{
								struct CE_node *ct=hd;
								while(ct->next!=NULL)
									ct=ct->next;								
								ct->next=cc1;
							}						
						    	cc=cc->next;
					  }
					  if(cc==NULL)
						{
						  h1=h1->next;
						  if(h1!=NULL)
						  {
						  struct CE_node *z=new_CE_node;
                          strcpy(z->var,",");
						  z->next=NULL;
						  struct CE_node *ct=hd;
								while(ct->next!=NULL)
									ct=ct->next;
						  ct->next=z;
                          }
						}
							
				}
			  t->ce=hd;
              t->ce=rec(t,t);
             // printf("\n\n%s has CE\n",t->str);
			  if(t->parent!=NULL)		
                  t=t->parent->ptrp;
			  }
	  } 
      
	}		
	p=p->next_actor;               
  }

  printf("\n End: Semantic Reconciliation---------------");
  return 0;
}

