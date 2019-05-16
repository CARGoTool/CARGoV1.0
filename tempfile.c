if(t->type)//AND DECOMPOSITION
			{
				e=c=0;
				struct IE_node *tempie=t->ie;
				while(tempie!=NULL) 
				{
					char notvar[3];
					//notvar contains ~IE
					if(tempie->var[0]=='~')
					{
						notvar[0]=tempie->var[1];
						notvar[1]=tempie->var[2];
						notvar[2]='\0';
					}
					else
					{
						notvar[0]='~';
						notvar[1]=tempie->var[0];
						notvar[2]=tempie->var[1];
					}
					printf("\n%s---inside tempie---%s",tempie->var,notvar);
					int flag=0;
					int flag1=0;
					//AND ENTAILMENT
					struct CE_node *tempce=t->ce;
					while(tempce!=NULL)
					{
						printf("**%s",tempce->var);
						if(strcmp(tempie->var,tempce->var)==0)
						{
							flag=1;
						    break;
						}
						tempce=tempce->next;
					}
					//AND CONSISTENCY
					struct child_queue_node *ch=t->children;
					while(ch!=NULL)
					{
						tempce=ch->ptrc->ce;
						while(tempce!=NULL)
						{
							if(strcmp(notvar,tempce->var)==0)
							{
								flag1=1;
								break;
							}
							tempce=tempce->next;
						}
						if(flag1) break;
						ch=ch->next;
					}
					if(flag==0)
					{
						printf("\n%s has entailment conflict with %s ",t->str,tempie->var);
						e=1; 
						
					}
					if(flag1==1)
					{
						printf("\n%s has consistency conflict with %s ",t->str,tempie->var); 
						c=1;
					}
					//if(flag1 && !flag) break;
					tempie=tempie->next;
				}
				if(e||c)//conflict node creation
				{
					struct conflict *new=new_conflict;
					new->conflicting_pnode=t;
					new->conflicting_cnode=NULL;
					new->consis=c;
					new->entail=e;
					new->next_conflict=NULL;
					if (conhead==NULL)
						conhead=conptr=new;
					else
					{
						conptr->next_conflict=new;
						conptr=conptr->next_conflict;
					}
				}
			}
			else //OR DECOMPOSITION
			{
				int flag,flag1;
				struct child_queue_node *ch=t->children;
				while(ch!=NULL)
				{
					e=c=0;
					printf("\n %s",ch->ptrc->str);
					struct IE_node *tempie=t->ie;
					while(tempie!=NULL) 
					{
						//printf("\n%s----inside tempie---",tempie->var);
						char notvar[3];//notvar contains ~IE
						if(tempie->var[0]=='~')
						{
							notvar[0]=tempie->var[1];
							notvar[1]=tempie->var[2];
							notvar[2]='\0';
						}
						else
						{
							notvar[0]='~';
							notvar[1]=tempie->var[0];
							notvar[2]=tempie->var[1];
						}
						printf("\n%s---inside tempie---%s\n",tempie->var,notvar);
						flag=0;
						flag1=0;
						//OR ENTAILMENT AND CONSISTENCY
						struct CE_node *tempce=ch->ptrc->ce;
						while(tempce!=NULL)
						{
							printf("**%s\t",tempce->var);
							if(strcmp(tempie->var,tempce->var)==0)
								{ flag=1;}
							if(strcmp(notvar,tempce->var)==0)
								{ flag1=1;}
							//if(flag1 && !flag) break;
							tempce=tempce->next;
						}
						if(flag==0)
						{
							printf("\n%s --------- %s has entailment conflict with %s ",t->str,ch->ptrc->str,tempie->var); 
							e=1;
						}
						if(flag1==1)
						{
							printf("\n%s --------- %s has consistency conflict with %s ",t->str,ch->ptrc->str,tempie->var); 
							c=1;
						}				

						//if(flag1 && !flag) break;
						tempie=tempie->next;
					}
					if(e||c)//conflict node creation
					{
						struct conflict *new=new_conflict;
						new->conflicting_pnode=t;
						new->conflicting_cnode=ch->ptrc;
						new->consis=c;
						new->entail=e;
						new->next_conflict=NULL;
						if (conhead==NULL)
							conhead=conptr=new;
						else
						{
							conptr->next_conflict=new;
							conptr=conptr->next_conflict;
						}
					}
					ch=ch->next;
				}
