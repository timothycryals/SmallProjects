#Name: Chase Ryals
#File: Assignment 4
#Date: October 14, 2015
#Description:

import turtle
import random

#This function receives input for the amount of circles that will be drawn
def main():
    global amount #'amount' will store the number of circles
    amount=int(input("How many circles would you like to draw? "))
    while amount<=0:
        amount=int(input("Invalid input. The amount must be an integer greater than 0: "))
    return amount

#This function receives input for the radius of a circle
def circle_radius():
    global userradius #'userradius' will store the radius of the largest circle
    userradius=int(input("Please enter the radius of the largest circle (50-300): "))
    while userradius<50 or userradius>300:
        if userradius<50:
            userradius=int(input("Too small. Enter an integer between 50 and 300: "))
        if userradius>300:
            userradius=int(input("Too large. Enter an integer between 50 and 300: "))
    return userradius


print("This program draws circles with decreasing radius sizes.")
print()

main()
print()
circle_radius()
radius=userradius
turtle.title("CPSC1301 Assignment 4 T.Ryals")
for x in range(amount, 0, -1):
    turtle.penup()
    turtle.goto(0, radius*(-1))
    turtle.showturtle()
    turtle.begin_fill()
    turtle.color(random.random(), random.random(), random.random())
    turtle.pendown()
    turtle.speed(9)
    turtle.circle(radius)
    turtle.penup()
    turtle.end_fill()
    turtle.hideturtle()
    radius = radius - 20

#This section creates the caption for the drawing
turtle.goto(0 , userradius+50)
turtle.write("Thank you for using the program.", align='center')
