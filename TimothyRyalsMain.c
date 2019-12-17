//Timothy Ryals
//August 30, 2017
//Project 1 - Amortization Schedule

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main ( int argc, char *argv[]){

    float initialAmount = strtof(argv[1], '\0');
    float intRate = strtof(argv[2], '\0');          //The command-line arguments are stored and converted
    int numYears = atoi(argv[3]);                   //to number values from strings

    printf("Amortization Schedule\n");

    printf("\n\nInitial Balance: $%.2f", initialAmount); //Prints the initial balance to two decimal places
    printf("\nAPR: %.3f", intRate); //Prints the APR to three decimal places
    printf("\nYears: %d\n", numYears); //Prints the number of years

    int bal = (int) initialAmount * 100; //Converts the balance from float to integer

    int N = 12; //N is the number of compounding periods in a year
    double J = intRate / N; //J is the monthly interest rate
    int numPayments = N * numYears;
    double A = J + 1; //A is a placeholder variable
    double exp = (double) pow(A, numPayments); //exp is the result of A raised to the
    exp = exp - 1;                             //power of the amount of payments
    exp = J / exp;
    exp = J + exp;
    double M = (double) (bal * exp) / 100; //Multiplies the balance by exp and converts it to a double

    printf("\n\nMonthly Payment: $%.2f\n", M); //Prints the monthly payment to two decimal places

    printf("\n\nMonth\tInt.\tPrinc.\tBalance"); //Column headers

    double newBal = (double) bal / 100; //Copy of the initial balance, but converted to double
    double monthlyInterest; //Holds the total interest for the month

    int i = 0;
    for(i = 0; i < numPayments; i++){
                                        //Monthly interest is calculated by multiplying the most recent
        monthlyInterest = newBal * J;   //balance and multiplying it by the monthly interest rate

        double princ = M - monthlyInterest; //Principal is calculated by subtracting the
                                            //monthly interest from the monthly payment

        newBal = newBal - princ; //The balance is updated as the principal for the month is subtracted
                                 //from the last month's balance

        if(i == 6){         //If i is equal to 6 (7th month) three dots will be placed
            printf("\n...");
        }
        if(i < 6){                  //Any i value will be displayed
            printf("\n%d\t", i+1);//if it is less than 6
            printf("$%.2f\t", monthlyInterest);
            printf("$%.2f\t", princ);
            printf("$%.2f\t", newBal);
        }
        if(i > (numPayments - 7)){    //If i is greater than the number of payments minus 7 (last 6 months),
            printf("\n%d\t", i+1);  //then the remaining values for i will be displayed
            printf("$%.2f\t", monthlyInterest);
            printf("$%.2f\t", princ);
            printf("$%.2f\t", newBal);
        }
    }

    return 0;
}
