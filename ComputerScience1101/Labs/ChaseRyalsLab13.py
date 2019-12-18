#Name: Chase Ryals
#File: Lab 13
#Date: September 21, 2015
#Description: Averaging grades and assigning letters to the average. Usin while loops to bring users back to a certain line.
print("Welcome to My Auto Grader")
print()
print("*Grade values should be between 0 and 100*")
grade1 = int(input("Please enter a grade for Assignment 1: "))
while grade1>100:
    grade1 = int(input("Grade not valid. Please enter a grade between 0 and 100: "))
grade2 = int(input("Please enter a grade for Assignment 2: "))
while grade2>100:
    grade2 = int(input("Grade not valid. Please enter a grade between 0 and 100: "))
grade3 = int(input("Please enter a grade for Assignment 3: "))
while grade3>100:
    grade3 = int(input("Grade not valid. Please enter a grade between 0 and 100: "))
grade4 = int(input("Please enter a grade for Assignment 4: "))
while grade4>100:
    grade4 = int(input("Grade not valid. Please enter a grade between 0 and 100: "))
grade5 = int(input("Please enter a grade for Assignment 5: "))
while grade5>100:
    grade5 = int(input("Grade not valid. Please enter a grade between 0 and 100: "))
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
    
print()

print("Would you like to run the program again?")#Program asks if the user wants to run it again.
runagain = int(input("Enter 1 to continue or 0 to quit: "))#Variable to run the program again
while runagain == 1:
    grade1 = int(input("Please enter a grade for Assignment 1: "))
    while grade1>100:
        grade1 = int(input("Grade not valid. Please enter a grade between 0 and 100: "))
    grade2 = int(input("Please enter a grade for Assignment 2: "))
    while grade2>100:
        grade2 = int(input("Grade not valid. Please enter a grade between 0 and 100: "))
    grade3 = int(input("Please enter a grade for Assignment 3: "))
    while grade3>100:
        grade3 = int(input("Grade not valid. Please enter a grade between 0 and 100: "))
    grade4 = int(input("Please enter a grade for Assignment 4: "))
    while grade4>100:
        grade4 = int(input("Grade not valid. Please enter a grade between 0 and 100: "))
    grade5 = int(input("Please enter a grade for Assignment 5: "))
    while grade5>100:
        grade5 = int(input("Grade not valid. Please enter a grade between 0 and 100: "))
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
    print()
    print("Would you like to run the program again?")
    runagain = int(input("Enter 1 to continue or 0 to quit: "))
    
    
print("Goodbye")
