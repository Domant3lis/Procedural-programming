// Domantas Keturakis © 2021 · Homework 1
#include "stdio.h"
#include "limits.h"
#include "ctype.h"
#include "stdbool.h"

// the task is to get input consisting of whole numbers. The input is registered while the number entered is not bigger than the previous. After finishing the sequence the count and the aveagre of input must be displayed.

int main()
{

   printf("This program lets input a sequence of whole numbers while they're not getting any biger\n"
      "After the sequence has been finished, the program will calculate the average and the count of all the number entered\n"
      "Please enter the first number(s) seperated by spaces or in each line seperatly: ");

   long input0 = LONG_MAX, input1; // for storing and comparing user input
   long sum = 0; // keeps sums of all entered numbers
   int count = 0; // keeps count of all numbers entered by the user
   int args_in_line_count = 0; // counts how many arguments in one line there are

   // This loop accepts user input and keeps count of the numbers entered
   do
   {
      bool clean_up = false;
      char c; // used to check for incorrect input

      // gets input from the user
      input1 = input0;
      int input_check = scanf("%18ld%c", &input0, &c);

      ++args_in_line_count;

      /// checks for bad input
      // checks if the number is decimal
      if (('.' == c) || (',' == c))
      {
         printf("Argument no. %2i is not a whole number! It will be discarded.\n", args_in_line_count);
         clean_up = true;
      }
      // checks if the number is too big to store and process
      else if (('0' <= c) && ('9' >= c))
      {
         printf("Argument no. %2i is too long to compute! It will be discarded. \n", args_in_line_count);
         clean_up = true;
      }
      // checks if number has any other characters beside it
      else if (!isspace(c))
      {
         printf("Argument no. %2i is not a number! It will be discarded. \n", args_in_line_count);
         clean_up = true;
      }
      // checks for other cases of bad input
      else if (input_check < 2)
      {
         printf("Argument no. %2i is incorrect! It will be discarded.\n", args_in_line_count);
         clean_up = true;
      }

      // clears incorrect input
      if (clean_up)
      {
         scanf("%*[^ \n\t]%c", &c);
         // printf("CLENUP_CHAR: '%c'", c);

         // if the the input is incorrect this ensures that the loop continues on
         input0 = input1;
      }
      // if the input is good it will be used to do calculations
      else if (input0 <= input1)
      {
         printf("Argument no. %2i is correct and will be counted\n", args_in_line_count);
         sum += input0;
         ++count;
      }

      // asks for input if it is a new line and not the last number in the sequence
      if(('\n' == c) && input0 <= input1)
      {
         args_in_line_count = 0;
         printf("\nPlease, enter a whole number: ");
      }

   }
   while (input0 <= input1);

   // prints the answer
   printf("\nThe sequence ended with %ld as the last number, because it was bigger than the previous number\n"
      "You've entered %i numbers and their average is %.2lf\n", input0, count, ((double) sum / count));

   return 0;
}
