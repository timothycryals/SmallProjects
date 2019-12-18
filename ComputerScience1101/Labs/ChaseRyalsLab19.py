#Name: Chase Ryals
#File: Lab 18
#Date: October 5, 2015
#Description: Break and continue practice

#Step 1
x=1
while x<=10:
    print(x)
    x+=1
    if x == 4:
        print(x) #Prints 4
        break #Ends loop so it does not pass 4

print()

#Step 2
for x in range(1,10):
    if x == 5: #If x equals 5, it will not print,  but it will continue the loop
        continue
    else:
        print(x) #print numbers other than 5

print()

#Step 3
def valid_number(a):
    if 1<=a and a<=120:
        return True
    else:
        return False

#Step 4
while True:
    a=int(input("Age: "))
    a1=valid_number(a) #a1 is the variable holding the function from step 3
    if a1 is False:
        print("Invalid age. Please enter another.")
        continue #Repeats the loop
    print("Thank you!")
    break
