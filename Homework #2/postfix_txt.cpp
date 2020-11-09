//***********************************************************
// Author: D.S. Malik
//
// Program: Postfix Calculator  
// This program evaluates postfix expressions.
//***********************************************************
  
#include <iostream>  
#include <iomanip>
#include <fstream>
#include "mystack.h"
 
 /*in the main alogrithm, the pseudocode is:
 Read the first character
 while not the input data
 {
	a. initialize the stack
	b. process the expression
	c. output result
	d. get the next expression
 }
 */
using namespace std; 
//the function evaluateExpression evaluates each postfix expression.
//each expression ends with =.  
void evaluateExpression(ifstream& inpF, ofstream& outF, 
                        stackType<double>& stack,
                        char& ch, bool& isExpOk);
void evaluateOpr(ofstream& out, stackType<double>& stack,
                 char& ch, bool& isExpOk);
void discardExp(ifstream& in, ofstream& out, char& ch);
void printResult(ofstream& outF, stackType<double>& stack,
                 bool isExpOk);


int main()
{
    bool expressionOk;
    char ch;
    stackType<double> stack(100);
    ifstream infile; //stream class to read from files
    ofstream outfile; //stream class to write on files
 /*
PREFIX QUESTION #2

bool isOperand (char c)
double evaluatePrefix (string exprsn)

*/
    infile.open("RpnData.txt");

    if (!infile)
    {
        cout << "Cannot open the input file. "
             << "Program terminates!" << endl;
        return 1;
    }
     
    outfile.open("RpnOutput.txt");

    outfile << fixed << showpoint;
    outfile << setprecision(2); 

    infile >> ch;
    while (infile)
    {
        stack.initializeStack();
        expressionOk = true;
        outfile << ch;

        evaluateExpression(infile, outfile, stack, ch, 
                           expressionOk);
		//process each expression
		//= marks the end of an expression
        printResult(outfile, stack, expressionOk);
        infile >> ch; //begin processing the next expression
    } //end while 

    infile.close();
    outfile.close();

    return 0;

} //end main

//function has five parameters, one to access the outfile
//one to access the stack
// one to passa character of the expression
//one to indicate whether there is an error in the expression
void evaluateExpression(ifstream& inpF, ofstream& outF, stackType<double>& stack,char& ch, bool& isExpOk)
{
    double num;

    while (ch != '=')
    {
        switch (ch)
        {
        case '#': 
            inpF >> num;
            outF << num << " ";
            if (!stack.isFullStack())
                stack.push(num);
            else
            {
                cout << "Stack overflow. "
                     << "Program terminates!" << endl;
                exit(0);  //terminate the program
            }

            break;
        default: 
            evaluateOpr(outF, stack, ch, isExpOk);
        }//end switch

        if (isExpOk) //if no error
        {
            inpF >> ch;
            outF << ch;

            if (ch != '#')
                outF << " ";
        }
        else
            discardExp(inpF, outF, ch);
    } //end while (!= '=')
} //end evaluateExpression


void evaluateOpr(ofstream& out, stackType<double>& stack,
              char& ch, bool& isExpOk)
//evaluateOpr evaluates an expression if possible.
//two operands are needed to evaluated an operation, and operands are saved in the stack
//the stack must contain at least two numbers. If less than two then there will be an error

{
    double op1, op2;

    if (stack.isEmptyStack())
    {
        out << " (Not enough operands)";
        isExpOk = false;
    }
    else
    {
        op2 = stack.top();
        stack.pop();

        if (stack.isEmptyStack())
        {
            out << " (Not enough operands)";
            isExpOk = false;
        }
        else
        {
            op1 = stack.top();
            stack.pop();
			//if operation is legao, perform the operation
			//and push the result onto stack

            switch (ch)
            {
            case '+': 
                stack.push(op1 + op2);
				//perform the operation and
				//push the result onto stack
                break;
            case '-': 
					//same as last note
                stack.push(op1 - op2);
                break;
            case '*': 
					//same as last note
                stack.push(op1 * op2);
                break;
            case '/': 
					//if (op2 ! 0), perform the operation and
					//push the result onto stack
                if (op2 != 0)
                    stack.push(op1 / op2);
					//otherwirse, report the error
					//set expressionOk to false
                else
                {
                    out << " (Division by 0)";
                    isExpOk = false;
                }
                break;
            default:  
                out << " (Illegal operator)";
                isExpOk = false;
            }//end switch
        } //end else
    } //end else
} //end evaluateOpr

//whenever there is an error in the expression, it reads and writes
//the input data only until the input is '=', the end of the expression
void discardExp(ifstream& in, ofstream& out, char& ch)
{
    while (ch != '=')
    {
        in.get(ch);
        out << ch;
    }
} //end discardExp

/*if this function has no errors, then printResult prints the result,
otherwise, it outputs the right message, the result of the expression is in the stack
the output is sent to a file
therefore, the function must have an access to the stack and output file.
if stack only has one element, the the expression is error free and the top element
of the stack is printed. If either the stack is empty or it has more than one element,
then there is an error in the postfix expression. 
This code delivers the appropriate error message.
*/
void printResult(ofstream& outF, stackType<double>& stack,
                 bool isExpOk)
{
    double result;

    if (isExpOk) //if no error, print the result
    {
        if (!stack.isEmptyStack())
        {
            result = stack.top();
            stack.pop();

            if (stack.isEmptyStack())
                outF << result << endl;
            else
                outF << " (Error: Too many operands)" << endl;
        } //end if
        else
            outF << " (Error in the expression)" << endl;
    }
    else
        outF << " (Error in the expression)" << endl;

    outF << "_________________________________" 
         << endl << endl;
} //end printResult
