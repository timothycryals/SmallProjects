#Name: Chase Ryals
#File: Lab 14
#Date: September 23, 2015
#Description: Practice with if, elif, else, and while statements

print("Enter '0' to move to next part") #Starts part 1
num = int(input("Please enter an integer: "))
if num > 0:
    print("The absolute value of ", num, "is ", num)
elif num < 0:
    absvalue = num * (-1) #Absolute value of negative integer
    print("The absolute value of ", num, "is ", absvalue)
while num<0 or num>0: #Starts part 2
    num = int(input("Please enter an integer: "))
    if num > 0:
        print("The absolute value of ", num, "is ", num)
    elif num < 0:
        absvalue = num * (-1)
        print("The absolute value of ", num, "is ", absvalue)

print()
print("Enter '0' to move to next part") #Starts part 3
num2 = int(input("Please enter an integer: "))
if num2>20:
    print(num2, " is greater than 20")
elif 10<num2<20:
    print(num2, " is in between 10 and 20")
elif num2<10:
    print(num2, " is less than 10")
while num2<0 or num2>0: #Starts part 4
    num2 = int(input("Please enter an integer: "))
    if num2>20:
        print(num2, " is greater than 20")
    elif 10<num2<20:
        print(num2, " is in between 10 and 20")
    elif num2<10:
        print(num2, " is less than 10")

print()
print("Enter '0' to quit") #Starts part 5
num3 = int(input("Please enter an integer: "))
if num3 % 2 == 0: #If there is no remainder, then the number is even
    print(num3, " is an even number")
elif num3 % 2 != 0: #If there is a remainder, the number is odd
    print(num, " is an odd number")
while num3<0 or num3>0: #Starts part 6
    num3 = int(input("Please enter an integer: "))
    if num3 % 2 == 0:
        print(num3, " is an even number")
    elif num3 % 2 != 0:
        print(num, " is an odd number")
print()
print("Goodbye")
           
