#Name: Chase Ryals
#File: Lab 17
#Date: September 30, 2015
#Description: Counting wih loops

print("Step 1") #Step 1
i=20
while i>0:
    print(i)
    i-=2 #i decreases by 2 each time the loop runs

print()

print("Step 2") #Step 2
for a in range(0, 101, 10):
    print(a, end=" ")

print()
print()

print("Step 3") #Step 3
print("The answer to number 3 is no.")

print()
print()

print("Step 4") #Step 4
for i in range(1, 4):
    if i==1:
        for j in range(1, i*11): #Creates a line with 10 asterisks
            print("*", end= " ")
        print()
    if i==2:
        for j in range(2, i+5): #Creates a line with 5 asterisks
            print("*", end= " ")
        print()
    if i==3:
        for j in range(3, i+20): #Creates a line with 20 asterisks
            print("*", end=" ")
        print()

print()
print()

print("Step 5") #Step 5
for c in range(10):
    for d in range(10): #Adds 9 asterisks to each line
        print("*", end=" ")
    print()

print()
print()

print("Step 6") #Step 6
for e in range(0, 10):
    for g in range(0, e+1): #adds a new number each line
        print(g, end=" ")
    print()
    
    
