#Name: Chase Ryals
#File: Lab 16
#Date: September 28, 2015
#Description: Display numbers within a range using for loops

print("Numbers from 1 to 100")
print()
for i in range(1, 101): #Prints numbers from 1 to 100
    print(i, end= " ")
print()
print()
print("Numbers from 100 to 1")
print()
for i in range(100, 0, -1): #Prints numbers from 100 to 1
    print(i, end= " ")
print()
print()
print("Even numbers from 1 to 100")
print()
for i in range(2, 101, 2):#Prints even numbers from 1 to 100
    print(i, end= " ")
print()
print()
print("Odd numbers from 1 to 100")
print()
for i in range(1, 101, 2): #Prints odd numbers between 1 and 100
    print(i, end= " ")
print()
print()
userInput=int(input("Please enter an integer: ")) #User will input an integer
print("Numbers from 1 to ", userInput)
print()
for i in range(1, userInput+1): #Numbers from 1 to user's integer
    print(i, end= " ")
print()
print()
print("Numbers from ", userInput, "to 1") 
print()
for i in range(userInput, 0, -1): #numbers from user's integer to 1
    print(i, end= " ")
print()
print()
print("Even numbers from 1 to ", userInput) #Even numbers from 1 to user's integer
print()
for i in range(2, userInput, 2):
    print(i, end= " ")
print()
print()
print("Odd numbers from 1 to ", userInput)
print()
for i in range(1, userInput+1, 2):#Odd numbers from 1 to user's integer
    print(i, end= " ")
    


