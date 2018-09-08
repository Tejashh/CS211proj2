//
//  main.c
//  Tejash Contractor
//
//  Created by Tejash Contractor on 9/18/16.
//  Copyright © 2016 Tejash Contractor. All rights reserved.
//

//Include the libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// defination of TRUE and FALSE
#define FALSE 0
#define TRUE 1

//
//struct for the stact which include the pointer to the dynamic array, also the size of the dynamic array
//and the variable which are on the top of the stack
//
typedef struct stack
{
    char *stackPointer;
    int sizeStack;
    int topStack;
}S;

typedef S * StackPointer;

void debug();
int debugMode = FALSE;
void Push_Element_On_Stack (StackPointer stack, char Par);
S *Create_Stack (int n);
int Empty (S * st);
char Popping (S * st);
int Checking_Balance (char *ent_characters, int *Error);

//start the main function
int main (int argc, char *argv[])
{
    debugMode = FALSE;
    char charArray[301];    //characters array that stores the user input
    int  err;           //intializing of error
    int  ReturnVal;     //intializing of ReturnVal
    int i;
    int linesize = sizeof(charArray) / sizeof(charArray[0]);
    debug( *argv[i]);
    
    while( !(FALSE) )    // start of the while loop
    {
        printf("Enter the Expression (q to quit)\n ");
        
        //fgets function to get standard input
        fgets(charArray,linesize,stdin);
        
        //exiting the function if user inputs q
        if(charArray[0]=='q')
        {
            exit(0);
        }
        
        //check if balance
        ReturnVal = Checking_Balance(charArray, &err);
        if(ReturnVal == FALSE)
        {
            printf ("Balanced!!!!\n");
        }
        else
        {
            char* pointer = charArray;      //pointer to the array
            printf ("Not Balanced!!!!\n%s", charArray);
            int index;
            for(index=0; index<(err-1); index++)
            {
                printf(" ");
            }
            printf("^Expecting %c\n",pointer[err-1]);
        }
    }
    return 0;
} //end of main


void debug(char *argv[])
{
    int i;              //initialzing i
    
    //if i is grater then value of 2
    if( i > 2 )
    {
        printf("Use this: %s[-d]\n", argv[0]);
        exit(0);
    }
    
    
    if( i == 2 && argv[1][1] == 'd' && argv[1][0] == '-')
    {
        printf("\nPrinting the debugging information\n");
        debugMode = TRUE;
    }
}

//make the stack which will be empty to use again.
void Delete(S *st)
{
    if (st != NULL)
    {
        if (st->stackPointer)
        {
            free(st->stackPointer);
        }
        free(st);
    }
} // end of delete function.

//Push_Element_On_Stack
void Push_Element_On_Stack(StackPointer stack, char Par)
{
    if(stack->topStack >= 301)
    {
        printf ("\nFULL Stack is creating whole new stack");
        
        //only Two elements
        char *T = (char *)malloc( sizeof(char) * (stack->sizeStack + 2) );
        //Freeing the previous stack
        free(stack->stackPointer);
        
        
        stack->stackPointer = T;
        stack->stackPointer += 2;
        
    }
    else
    {
        stack->stackPointer[++(stack->topStack)] = Par;
    }
    
} //end of Push function


//Create_Stack method
S *Create_Stack(int num)
{
    //temp pointer variable
    S *T = malloc(sizeof (S)+2);
    if(T == NULL)
    {
        exit(1);
    }
    T->stackPointer = malloc(sizeof(char)*(num+2));
    if(T->stackPointer == NULL)
    {
        exit(1);
    }
    T->topStack = -1;
    return T;
}//end of the create function

//Empty function
int Empty(S * st)
{
    if(st->topStack <= -1)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}//end of the Empty function

//Popping function
char Popping(S *st)
{
    if(st->topStack <= -1)
    {
        return '\0';
    }
    else
    {
        return st->stackPointer[(st->topStack)--];
    }
}//end of the Popping function

//Checking_Balance function
int Checking_Balance(char *ent_characters, int *Error){
    char par = '\0';
    char T;
    int error = FALSE;
    int i;
    
    S *st = Create_Stack (301);
    i = 0;
    //start of the while function
    while(ent_characters[i] != '\0')
    {
        par = ent_characters[i];
        if(par == '<' || par == '{' )
        {
            Push_Element_On_Stack(st,par);
        }
        if(par == '[' || par == '(')
        {
            Push_Element_On_Stack(st,par);
        }
        else if(par == ')' || par == '}' || par == ']'||  par == '>')
        {
            if(Empty(st))
            {
                error = TRUE;
                break;
            }
            //Use of the Popping method
            T = Popping(st);
            
            //checking the expressions
            if(!(T == ')' && par == '('))
            {
                error = TRUE;
                break;
            }
            else if(T == '}' && par == '{')
            {
                error = TRUE;
                break;
            }
            else if(T == ']' && par == '[')
            {
                error = TRUE;
                break;
            }
            else if(T == '<' && par == '>')
            {
                error = TRUE;
                break;
            }
        }
        i++;    //incrementing
    }
    
    //If not Empty
    if(!Empty(st))
    {
        error = TRUE;
    }
    //if Error is not NULL
    if(Error != NULL)
    {
        *Error = i + 1;
    }
    //if error is TRUE
    if(error == TRUE)
    {
        *Error = i + 1;
    }
    
    //Delete the stack
    Delete(st);
    
    //return error
    return error;
    
} // end of Checking_Balance function


