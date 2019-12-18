#Author: Chase Ryals
#File Name: ChaseRyalsLab7
#Date: September 2, 2015
#Description: Calculating the are of a house and its rooms.

W=int(input("W: "))
X=int(input("X: "))
Y=int(input("Y: "))
Z=int(input("Z: "))


print("The area of the house: ", (W+X)*(Y+Z*0.75), "sq ft")
print("Total area of carpet needed:", (W*Z*0.5)+(X*Y), "sq ft")
