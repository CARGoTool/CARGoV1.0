struct actor_node    /*INFORMATION OF EACH ACTOR*/
{
      int val;            /*CODE-NUMBER OF THE ACTOR*/
      char str[100];       /*NAME OF THE ACTOR*/
      struct tree_node *next;   /*POINTS THE LIST OF NODES UNDER THE ACTOR*/
	  struct actor_node *next_actor;  /*POINTS NEXT ACTOR*/
};

struct tree_node            /*INFORMATION OF EACH NODE(GOAL/TASK/RESOURCE) OF THE LIST UNDER AN ACTOR*/
{
	int val;      /* CODE-NUMBER OF THE GOAL/TASK/RESOURCE */
	char str[100];     /* NAME OF THE GOAL/TASK/RESOURCE */	
	int type;         //DECOMPOSITION TYPE 
	int gtr;
	struct IE_node *ie;     //IE LIST
	struct CE_node *ce;
	struct parent_queue_node *parent;	// POINTS THE PARENT QUEUE   
	struct child_queue_node *children;	// POINTS THE CHILD QUEUE 
	struct dependency_queue_node *depends_on;     //POINTS DEPENDENCY QUEUE
    struct tree_node *next;		// POINTS NEXT NODE
};

struct child_queue_node       /*INFORMATION OF EACH CHILD NODE*/
{
   struct tree_node *ptrc;     /*POINTER TO THE CHILD */
   struct child_queue_node *next;    /* POINTS NEXT NODE STORING POINTER TO ITS SIBLING */
};

struct parent_queue_node 	/*INFORMATION OF EACH PARENT NODE*/
{
   struct tree_node *ptrp; 			/*POINTER TO THE PARENT*/
   struct parent_queue_node *pnext;		/* POINTS NEXT NODE STORING POINTER TO NEXT PARENT */
};

struct dependency_queue_node	/*INFORMATION OF EACH DEPENDEE*/
{
	struct actor_node *depen_actor;		/*DEPENDEE ACTOR */
	struct tree_node *depen_node;		/*DEPENDEE NODE*/
	struct dependency_queue_node *depen_next;	/*NEXT DEPENDEE*/
};

struct dependsOn    //TEMPORARILY STORING DEPENDER AND DEPENDEE'S TOKEN ID
{
	int a_depender,t_depender,a_dependee,t_dependee;
	struct dependsOn *dnext;  //NEXT NODE 
};
struct IE_node	//IE LIST
{
 char var[3];   
 struct IE_node *next;
};
struct CE_node	//CE LIST
{
 char var[3];   
 struct CE_node *next;
};
struct conflict
{
	struct tree_node *conflicting_pnode;
	struct child_queue_node	*conflicting_cnode;
	int con_flag;
	int el_no;
	struct conflict *next_conflict;
};

struct CE_p
{
  struct CE_node *c;
  struct CE_p *next;
};

#define new_actor_node (struct actor_node*)malloc(sizeof(struct actor_node))
#define new_tree_node (struct tree_node*)malloc(sizeof(struct tree_node))
#define new_child_queue_node (struct child_queue_node*)malloc(sizeof(struct child_queue_node))
#define new_parent_queue_node (struct parent_queue_node*)malloc(sizeof(struct parent_queue_node))
#define new_dependency_queue_node (struct dependency_queue_node*)malloc(sizeof(struct dependency_queue_node))
#define new_IE_node (struct IE_node*)malloc(sizeof(struct IE_node))
#define new_dependsOn (struct dependsOn*)malloc(sizeof(struct dependsOn))
#define new_CE_p (struct CE_p*)malloc(sizeof(struct CE_p))
FILE *flog;
