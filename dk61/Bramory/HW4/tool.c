//  tool.c
//  dz3
//
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "tool.h"

#define DK_PRINT_COMMA_TO_FILE(f) DK_PRINT_SYM_TO_FILE(f, ',')

float Square (Circle *aCircle)
{
	return 3.14159*aCircle->radius * aCircle->radius;
}

FigureList *createFigureList ( int aSize)
{
	FigureList *theList = (FigureList *)malloc (sizeof(FigureList));
	if (theList != NULL)
	{
		theList -> circles = (Circle *) malloc(aSize * sizeof(Circle));
		memset(theList -> circles, 0, aSize * sizeof(Circle) );	
			
		theList -> size = aSize;
		theList -> current_size = 0;
	printf("The FigureList has sucsessfully created!\n");
	}
return theList;
}

void destroyFigureList(FigureList *aList)
{
	if (NULL != aList)
	{
		if(NULL != aList -> circles)
		{		
			free(aList->circles);
		}
	free(aList);
	}
}

//	interface
int addCircle (FigureList *aList, int x, int y, int radius)
{
	if (NULL != aList && 0 <= radius )
	{
		if ( aList->current_size < aList -> size )
		{
			Circle *theCircle = &(aList -> circles [aList -> current_size] );
				if (NULL != theCircle)
			{
				theCircle -> x = x;
				theCircle -> y = y;
				theCircle -> radius = radius;		
				
				aList -> current_size ++;
			}
		}
		else
		{
			printf("\tError! FigureList is already full.\n");
			sad();
			return -2;
		}
	}
	else 
	{
		return -1;
	}
	printf("The circle has sucsessfully created!\n");
	return 0; 
}

//	Put structure FigureList in the *.JSON
int fileWrite(FILE *aFile, FigureList *aList)
{
	if (NULL != aFile)	//	File exist, go on
	{
		fprintf(aFile, "{\n");
		
		fprintf(aFile, "\t\"size\": %d,\n", aList->size); 
		
		fprintf(aFile, "\t\"current_size\": %d,\n", aList->current_size);		
			
		fprintf(aFile, "\t\"circles\": ");
	
		if (NULL == aList->circles)	//	objects == NULL
		{
			fprintf(aFile, "\tnull");
		}
		else						// objects exists
		{
			fprintf(aFile, "\n\t[\n");
			
			int i;
			for (i = 0; i < aList->current_size; i++)
			{
				Circle *theCircle = &(aList->circles[i]);	
				writeCircle(aFile, theCircle);
				if (i < (aList->current_size - 1))
				{
					fprintf(aFile, ",\n");
				}
			}
			fprintf(aFile, "\n\t");
			fprintf(aFile, "]");
			fprintf(aFile, "\n");
		}
		fprintf (aFile, "}");	
	} 
	else 
	{
		return -1; //	File == NULL
	}
return 0;	
}

int writeCircle( FILE *aFile, Circle *aCircle)
{
	if (NULL != aFile)	//	File exist, go on
	{
		if (NULL == aCircle)	//objects == NULL
			fprintf(aFile, "null");
		else					// objects exists
		{
			fprintf (aFile, "\t\t{");
			
			fprintf (aFile, "\n\t\t\"center x\": %d", aCircle->x);
			
			fprintf (aFile, ",\n\t\t\"center y\": %d", aCircle->y);
			
			fprintf (aFile, ",\n\t\t\"radius\": %d", aCircle->radius);
			
			fprintf (aFile, "\n\t\t}");
		}
	}
	else
	{
		return -1;	//	File not found
	}
	return 0;	
}	


//on the screen
int printFigureList(FigureList *aList)
{
	int i;
	printf("{");
	printf("\n");
	printf("[");
	for(i = 0; i < aList->current_size; i++)
	{
		Circle *theCircle = &(aList->circles[i]);
		printCircle(theCircle);
		if (i < aList -> current_size - 1) 
		printf(",\n");
	}
	printf("\n]");
	printf("\n");
	printf("}");
	
}

int printCircle(Circle *aCircle)
{
	if (NULL == aCircle)	//objects == NULL
		printf("null");
		else					// objects exists
		{
			printf ("\t\t{");
			printf ("\n\t\t\"center x\": %d", aCircle->x);
			printf (",\n\t\t\"center y\": %d", aCircle->y);
			printf (",\n\t\t\"radius\": %d", aCircle->radius);
			printf ("\n\t\t}");
		}
return 0;	
}
	

void swap (Circle *var1, Circle *var2)
{
	Circle temp = *var1;
	*var1 = *var2;
    *var2 = temp;
}


//notifications
	void sad (void)
{
	system("color 1F"); // Change color
	printf("\a");		// Beep
}
