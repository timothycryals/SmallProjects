#Name: Chase Ryals
#File: Lab 12
#Date: September 18, 2015
#Description: Averaging grades and assigning letters to the average.
print("Welcome to My Auto Grader")
print()
print("*Grade values should be between 0 and 100*")
grade1 = int(input("Please enter a grade for Assignment 1: "))
grade2 = int(input("Please enter a grade for Assignment 2: "))
grade3 = int(input("Please enter a grade for Assignment 3: "))
grade4 = int(input("Please enter a grade for Assignment 4: "))
grade5 = int(input("Please enter a grade for Assignment 5: "))
print()
num_avg = float((grade1 + grade2 + grade3 + grade4 + grade5) / 5) #Average of the 5 inputs
print("The numeric average is: ", num_avg)

if 90<=num_avg<=100:
    print("The letter grade is an A")
else:
    if 80<=num_avg<=89:
        print("The letter value is a B")
    else:
        if 70<=num_avg<=79:
            print("The letter value is a C")
        else:
            if 60<=num_avg<=69:
                print("The letter value is a D")
            else:
                print("The letter value is an F")
    
