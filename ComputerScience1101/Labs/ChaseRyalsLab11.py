#Name: Chase Ryals
#File: Lab 11
#Date: September 16, 2015
#Description: Calculate the cost per unit of three boxes of cereal and determine which is a better deal.

#Welcome message
print("Welcome to the product chooser!")

print()
print()

#First product
name1 = input("Please enter the name of the first product: ")
price1 = float(input("Please enter the price of the first product: "))
size1 = int(input("Please enter the size of the first product: "))

print()
print()

#Second product
name2 = input("Please enter the name of the second product: ")
price2 = float(input("Please enter the price of the second product: "))
size2 = int(input("Please enter the size of the second product: "))

print()
print()

#Third product
name3 = input("Please enter the name of the third product: ")
price3 = float(input("Please enter the price of the third product: "))
size3 = int(input("Please enter the size of the third product: "))

print()
print()

#Cost per ounce
unit_cost1 = (price1 / size1)
unit_cost2 = (price2 / size2)
unit_cost3 = (price3 / size3)

if unit_cost2>unit_cost1<unit_cost3:
    print("The best deal is ", name1, "! Enjoy your breakfast!!!")
else:
    if unit_cost1>unit_cost2<unit_cost3:
        print("The best deal is ", name2, "! Enjoy your breakfast!!!")
    else:
        print("The best deal is ", name3, "! Enjoy your breakfast!!!")
