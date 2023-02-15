#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This program will read the first 3 lines of input 
   and prints a static 2D maze*/

#define TRUE 1
#define FALSE 0

typedef struct mazeStruct
{
 char** arr;  
 int xsize, ysize;
 int xstart, ystart;
 int xend, yend;
} maze;

void initMaze(maze* m1)
{
	 m1->arr = (char**)malloc((m1->xsize+2) * sizeof(char*));
  	for(int i = 0; i < m1->xsize+2; i++)
  	{
  		m1->arr[i] = (char*)malloc((m1->ysize+2) * sizeof(char));
  	}	
}


struct node{ 
    int xpos;
    int ypos; 
    struct node* next; 
};

//
//  init: initilize stack to null
//
void init(struct node** head)
{
    head = NULL;
}


//
//  push: given an instance of a stack and a character: this function will push
//  the given coordinate onto the top of the stack. If debugMode is == 1 
//	then the function will print out debugging information when called.
//
void push(int datax, int datay, struct node** head, int debug){
    struct node* temp = (struct node*)malloc(sizeof(struct node));   
    
    temp -> xpos = datax; 
    temp -> ypos = datay;
    
    temp -> next = *head;
    
    (*head) = temp;
    
    if(debug == TRUE)
    {
    	printf("(%d,%d) pushed into the stack.\n", datax, datay);
    }
}


//
//  returns 1 if the stack is empty, otherwise returns 0
//
int isEmpty(struct node* head)
{
    return head == NULL ? 1 : 0;
}


//
//  top: given an instance of a stack: this function will return the
//  coordinate found at the top of the stack.
//
void top(struct node* head, int* first, int* second){

    struct node* cur = head;
    
    if(cur != NULL)
    {    	
    	//printf("(%d, %d)", cur->xpos, cur->ypos);
    	*first = cur->xpos;
    	*second = cur->ypos;
    }
    else
    {
    	//printf("Stack is empty.\n");    	
	}
}


//
//  pop: given an instance of a stack: this function will pop(remove) the top
//  coordinate of the stack. If debugMode is == 1 then the function will print out
//  debugging information when called.
//
void pop(struct node** head, int debug){
    if(*head != NULL)
    {
    	struct node* temp = *head;
    	*head = (*head) -> next;
    	
    	if(debug == TRUE)
		{
			printf("(%d,%d) popped off the stack.\n", temp->xpos, temp->ypos);
		}
		
    	free(temp);
	}
}

//
//  reset: given a stack: this function will free all memory in use and reset
//  the stack to its initial values;
//
//
void reset(struct node** head)
{
    while(*head != NULL){        
        struct node* tempPtr = *head;
        *head = (*head) -> next;
        free(tempPtr);
    }    
}

void freeMaze(maze* m1)
{
	for (int i = 0; i < m1->xsize+2; ++i)
    {        
        free(m1->arr[i]);
    }
	free(m1->arr);
}



//
//	algorithm to solve the maze and output any relevent information
//
//
void solver(maze* m1, int debug)
{
	int coins = 0;
	struct node* stack = NULL;
	init(&stack);	
	
	push(m1->xstart, m1->ystart, &stack, debug);	
	 
	m1->arr[m1->xstart][m1->ystart] = 'V';
	
	
	int first = 0, second = 0;
	top(stack, &first, &second);
	
	while( isEmpty(stack) != 1 && m1->arr[first][second] != 'e')
	{		
		if(first == m1->xend && second == m1->yend)
		{		
			break;
		}
		
		if( m1->arr[first+1][second] == '.' || m1->arr[first+1][second] == 'C' || m1->arr[first+1][second] == 'e')
		{
			push(first+1, second, &stack, debug);
			if(m1->arr[first+1][second] == 'C')
			{
				coins++;
			}			
			m1->arr[first+1][second] = 'V';
			
		}
		else if(m1->arr[first][second+1] == '.' || m1->arr[first][second+1] == 'C' || m1->arr[first][second+1] == 'e')
		{
			push(first, second+1, &stack, debug);
			if(m1->arr[first][second+1] == 'C')
			{
				coins++;
			}		
			m1->arr[first][second+1] = 'V';
		}
		else if(m1->arr[first-1][second] == '.' || m1->arr[first-1][second] == 'C' || m1->arr[first-1][second] == 'e')
		{
			push(first-1, second, &stack, debug);
			if(m1->arr[first-1][second] == 'C')
			{
				coins++;
			}
			m1->arr[first-1][second] = 'V';
		}
		else if(m1->arr[first][second-1] == '.' || m1->arr[first][second-1] == 'C' || m1->arr[first][second-1] == 'e')
		{
			push(first, second-1, &stack, debug);
			if(m1->arr[first][second-1] == 'C')
			{
				coins++;
			}				
			m1->arr[first][second-1] = 'V';
		}
		else
		{
			pop(&stack, debug);			
		}
		
		
		top(stack, &first, &second);		
	}
	
	if(isEmpty(stack) == 1)
	{
		printf("This maze has no solution.\n");
	}
	else
	{
		printf("\n");
		printf("The maze has a solution.\n");
		printf("The amount of coins collected: %d\n", coins);
		printf("The path from start to end: \n");
		
		struct node* stackR = NULL;
		init(&stackR);
		
		while (isEmpty(stack) != 1)
		{
			int one = 0, two = 0;
			top(stack, &one, &two);		
			push(one, two, &stackR, 0);
			pop(&stack, 0);			
		}		
		while(isEmpty(stackR)!= 1)
		{
			int one = 0, two = 0;
			top(stackR, &one, &two);
			printf("(%d,%d) ", one, two);
			push(one, two, &stack, 0);
			pop(&stackR, 0);
		}
		
		printf("\n");
		while (isEmpty(stack) != 1)
		{
			int one = 0, two = 0;
			top(stack, &one, &two);					
			pop(&stack, debug);			
		}		
		
		reset(&stackR);
	}
	reset(&stack);
	
}

int main (int argc, char **argv)
{
  maze m1;

  int xpos, ypos;
  int i,j;

  FILE *src;

  /* verify the proper number of command line arguments were given */
  if(argc < 1 || argc > 4) {
     printf("Usage: %s <input file name>\n", argv[0]);
     exit(-1);
  }
   
   
   char flag[] = "-d";

   int debugMode = FALSE;

   for (int i = 0; i < argc; i++)
   {
       if (strcmp(flag, argv[i]) == 0) //  check for the -d flag from the command line
       {
           debugMode = TRUE;
           //printf ("Debugging Information \n");
       }
   } 
   
  /* Try to open the input file. */
  if ( ( src = fopen( argv[1], "r" )) == NULL )
  {
    printf ( "Can't open input file: %s", argv[1] );
    exit(-1);
  }

   int count = 0;
  /* read in the size, starting and ending positions in the maze */
  int checker = fscanf (src, "%d %d", &m1.xsize, &m1.ysize);  
  if (checker == 2)
  {
  	count ++;
  }
  
  checker = fscanf (src, "%d %d", &m1.xstart, &m1.ystart);
  if(checker == 2)
  {
  	count++;
  }
  
  checker = fscanf (src, "%d %d", &m1.xend, &m1.yend);
  if(checker == 2)
  {
  	count++;
  }
  
  
  /* print them out to verify the input */
  
  if ( count != 3 ) // check if values were never set
  {
  	printf("Invalid data file.\n");
  	return 0;
  }
  
  
  if (m1.xsize <= 0 || m1.ysize <= 0) // check if invalid maze size
  {
  	printf("Maze sizes must be greater than 0\n");
  	return 0;
  }
  else
  {
  	printf ("size: %d, %d\n", m1.xsize, m1.ysize);
  }
  
  
  if ( ((m1.xstart <= 0 || m1.ystart <= 0) || (m1.xend <= 0 || m1.yend <= 0)) )
  			// check if start/end pos is outside maze range
  {
  	printf("Start/End position outside of maze range.\n");
  	return 0;
  }
  else
  {
  	printf ("start: %d, %d\n", m1.xstart, m1.ystart);
  	
  }
  
  
  if ( ((m1.xstart > m1.xsize) || (m1.ystart > m1.ysize) || (m1.xend > m1.xsize) || (m1.yend > m1.ysize)) )
  {
  	printf("Start/End position outside of maze range.\n");
  	return 0;
  }
  else
  {
  	printf ("end: %d, %d\n", m1.xend, m1.yend);
  }
  
  
  
  
  
    
  
  initMaze(&m1); 
 
	
  /* initialize the maze to empty */
  for (i = 0; i < m1.xsize+2; i++)
     for (j = 0; j < m1.ysize+2; j++)
       m1.arr[i][j] = '.';

  /* mark the borders of the maze with *'s */
  for (i=0; i < m1.xsize+2; i++)
    {
     m1.arr[i][0] = '*';
     m1.arr[i][m1.ysize+1] = '*';
    }
  for (i=0; i < m1.ysize+2; i++)
    {
     m1.arr[0][i] = '*';
     m1.arr[m1.xsize+1][i] = '*';
    }

  /* mark the starting and ending positions in the maze */
  m1.arr[m1.xstart][m1.ystart] = 's';
  m1.arr[m1.xend][m1.yend] = 'e';
		  
  /*This code will only read the first three lines */
  /*Complete this code by reading the rest of the input
    and placing blocked and coin positions. */
  /* Blocked positions are marked with 'b' in the input file
     They should be marked by * in the maze */     
     
     /*Coin positions are marked by 'c' in the input file
    They should be marked by C in the maze*/
     
  int first;
  int second;
  char type;  
     
  while ( fscanf(src, "%d %d %c", &first, &second, &type) != EOF)
  {
  	if (type != 'c' && type != 'b') // check for invalid type
  	{
  		printf("Invalid type: type is not recognized.\n");
  		//return 0;
  	}
  	else if ( (first > m1.xsize || second > m1.ysize) || (first < 0 || second < 0) ) // check if values are outside maze range
  	{
  		printf("Invalid coordinates: outside of maze range.\n");
  		//return 0;
  	}
  	else if ( (first == m1.xstart && second == m1.ystart) || (first == m1.xend && second == m1.yend) ) // check if attempting to block start or end
  	{
  		printf("Invalid coordinates: attempting to block start/end position.\n");
  		//return 0;
  	}
  
  	else if ( type == 'c' )
  	{
  		m1.arr[first][second] = 'C';
  	}
  	else if ( type == 'b' )
  	{
  		m1.arr[first][second] = '*';
  	}
  } 

  /*Close the file*/
   fclose(src);

  /* print out the initial maze */
  for (i = 0; i < m1.xsize+2; i++)
    {
     for (j = 0; j < m1.ysize+2; j++)
       printf ("%c", m1.arr[i][j]);
     printf("\n");
    }
	
	
	solver(&m1, debugMode);
	
	freeMaze(&m1);
}
