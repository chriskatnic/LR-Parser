/*
 /	Wyatt Dorn
 /	Christopher Katnic
 /	Assignment 8.2
 /	CPSC 323 - 13214
 /	Instructor: Ray Ahmadnia
 */

#include <stack>
#include <iostream>

//table of values to read from, numbers correspond to elements of "words"
// 5# = s#
// 0# = r#
// 00 = blank
// 99 = accept

int table[16][11] = {
    //		  i   +   -   *   /   (   )   $   E   T   F
    /*00*/	{55, 00, 00, 00, 00, 54, 00, 00, 01, 02, 03},
    /*01*/	{00, 56, 57, 00, 00, 00, 00, 99, 00, 00, 00},
    /*02*/	{00, 03, 03, 58, 59, 00, 03, 03, 00, 00, 00},
    /*03*/	{00, 06, 06, 06, 06, 00, 06, 06, 00, 00, 00},
    /*04*/	{55, 00, 00, 00, 00, 54, 00, 00, 10, 02, 03},
    /*05*/	{00,  8,  8,  8,  8, 00,  8,  8, 00, 00, 00},
    /*06*/	{55, 00, 00, 00, 00, 54, 00, 00, 00, 11, 03},
    /*07*/	{55, 00, 00, 00, 00, 54, 00, 00, 00, 12, 03},
    /*08*/	{55, 00, 00, 00, 00, 54, 00, 00, 00, 00, 13},
    /*09*/	{55, 00, 00, 00, 00, 54, 00, 00, 00, 00, 14},
    /*10*/	{00, 56, 57, 00, 00, 00, 65, 00, 00, 00, 00},
    /*11*/	{00, 01, 01, 58, 59, 00, 01, 01, 00, 00, 00},
    /*12*/	{00, 02, 02, 58, 59, 00, 02, 02, 00, 00, 00},
    /*13*/	{00, 04, 04, 04, 04, 00, 04, 04, 00, 00, 00},
    /*14*/	{00, 05, 05, 05, 05, 00, 05, 05, 00, 00, 00},
    /*15*/	{00, 07, 07, 07, 07, 00, 07, 07, 00, 00, 00}};


std::stack<int> myStack;
std::stack<char> myInput;
void printstack(std::stack<int>);

int myRules[8] =	{6, 6, 2, 6, 6, 2, 6, 2};	//2 * the length of each rule

char rules[8][2] = {
    /*r1*/	{'3', 'E'}, //element 0 of each row is the length of the rule
    /*r2*/	{'3', 'E'}, //element 1 of each row is the result which needs to be pushed
    /*r3*/	{'1', 'E'},
    /*r4*/	{'3', 'T'},
    /*r5*/	{'3', 'T'},
    /*r6*/	{'1', 'T'},
    /*r7*/	{'3', 'F'},
    /*r8*/	{'1', 'F'}};

char inputs[3][8] = {
    {'(', 'i', '+', 'i', ')', '*', 'i', '$'},
    {'i', '*', '(', 'i', '-', 'i', ')', '$'},
    {'i', '(', 'i', '+', 'i', ')', '$', ' '}};


int main()
{
    int choose;
BEGIN:
    
    std::cout	<<"Which input would you like to test?"<<std::endl
				<<"1. (i+i)*i$"<<std::endl
				<<"2. i*(i-i)$"<<std::endl
				<<"3. i(i+i)$"<<std::endl;
    std::cin>>choose;
    
    if(choose != 1 && choose !=2 && choose != 3)
    {
        std::cout<<"\nERROR: Invalid selection, try again.\n"<<std::endl;
        goto BEGIN;
    }
    
    choose--;
    
    /////////////////////////////
    //push the input in reverse order
    //and push '0' onto the stack
    /////////////////////////////
    for(int x = 7; x >= 0; x--)
    {
        if(inputs[choose][x]!=' ')
        {
            myInput.push(inputs[choose][x]);
        }
    }
    myStack.push(0);
    
    
    /////////////////////////////
    //begin parsing
    /////////////////////////////
    std::cout << "\nNext on Stack: " << myStack.top();
    std::cout << "\nNext Input: " << myInput.top() << "\n----------------------------";
while(1)
{
    
    /////////////////////////////
    //Get row and column values
    /////////////////////////////
    int row = (int)myStack.top();
    int column;
    
    switch (myInput.top())
    {
        case 'i':
            column =  0;
            break;
        case '+':
            column =  1;
            break;
        case '-':
            column =  2;
            break;
        case '*':
            column =  3;
            break;
        case '/':
            column =  4;
            break;
        case '(':
            column =  5;
            break;
        case ')':
            column =  6;
            break;
        case '$':
            column =  7;
        default:
            break;
    }
    
    /////////////////////////////
    //get value from table, print
    /////////////////////////////
    
    //reached an empty space
    if (table[row][column] == 0)
    {
        //formatting
        std::cout << "\n[ " << myStack.top() << " , " << myInput.top() << " ] = NULL"
                  << "\n----------------------------"
                  << "\nEmpty position! Word not accepted\n\n";
        return 0;
    }
    
    //word accepted
    else if (table[row][column] == 99)
    {
        std::cout << "\n[ 1 , $ ] = accept"
                << "\n----------------------------"
                << "\nWord accepted! Congratulations\n\n";
        return 0;
    }
    
    //shift
    else if (table[row][column] - 50 > 0)
    {
        //formatting
        std::cout << "\n[ " << myStack.top() << " , " << myInput.top() << " ] = shift( " << table[row][column] - 50 << " )\n----------------------------";
        
        
        //shift; pop top value from the input, push on to stack, push number on stack
        char temp = myInput.top();
        myInput.pop();
        myStack.push(temp);
        myStack.push(table[row][column] - 50);
    }
    
    //rule
    else
    {
        //formatting
        std::cout << "\n[ " << myStack.top() << " , " << myInput.top() << " ] = rule( " << table[row][column] << " )\n----------------------------";
        
        //rule; first thing is to pop off appropriate number of items from stack
        int lcount = myRules[table[row][column] - 1];
        for (int i = 0; i < lcount; i++)
        {
            myStack.pop();
        }
        
        //then, save the top two items from the stack to get the newest member of the stack
        int row2 = myStack.top();
        char test = rules[table[row][column] - 1][1];
        myStack.push(rules[table[row][column]][1]);
        
        //push value onto stack
        switch(test)
        {
            case 'F': myStack.push(table[row2][10]); break;
            case 'T': myStack.push(table[row2][9]); break;
            case 'E': myStack.push(table[row2][8]); break;
            default: break;
        }
        
    }
    
    printstack(myStack);
    std::cout << "\nNext on Stack: " << myStack.top();
    std::cout << "\nNext Input: " << myInput.top() << "\n----------------------------";
}
    
    
    return 0;
}


void printstack(std::stack<int> myStack)
{
    std::stack<int> tempstack = myStack;
    std::cout << "\nStack: ";
    for(int i = 0; i < tempstack.size(); i++)
    {
            if (tempstack.top() < 15)
                std::cout << tempstack.top();
            else
                std::cout << (char)tempstack.top();
        tempstack.pop();
    }
    
}