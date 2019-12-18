#Name: Chase Ryals
#File: Independent Programming 1
#Date: September 25, 2015
#Description: Calcualate the fees for the total amount of bags a person has.

cont = 'yes' #Variable saves yes so the program will run at least once

while cont == 'yes':
    name = input("What is your name?  ")
    bags = int(input("How many bags do you have?  "))
    if bags<1: #Fees for 0 bags
        print("There are no fees.")
    elif bags == 1: #Fees for 1 bag
        print("The fee is $25")
    elif bags == 2: #fees for 2 bags
        print("The fee is $35")
    elif bags > 2: #Fees for more than 2 bags
        fee =(bags - 2) *50 + 60
        print("The fee is $", fee)
    print()
    print("Bon Voyage ", name)
    print()
    cont = input("Would you like to continue? (yes/no)   ") #Asks the user to say 'yes' or 'no to run the program again
    cont = cont.lower() #Changes the input to lower case if it isn't already

print()

print("Thank you for using the Baggage Fee Calculator")

    
    
