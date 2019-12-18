#Chase Ryals
#File: Lab 18
#Date: October 2, 2015
#Description: Counting with loops

for i in range(1, 101):
    if i%3==0: #Only if i%3==0
        print("Fizz")
        if i%5==0: #If i%5 and i%3==0
            print("FizzBuzz")
    if i%5==0: #Only if i%5==0
        print("Buzz")
    print(i)
    
