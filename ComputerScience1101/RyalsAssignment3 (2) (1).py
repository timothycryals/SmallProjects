#Name: Chase Ryals
#File: Assignment 3 Turtle in a Box
#Date: September 27, 2015
#Purpose: Write a game where the user tries to get a turtle in a square   

import turtle
import random

s=0 #S is the variable containing the score
cont='y'
while cont=='y':
#This section draws the first box
    turtle.showturtle()
    turtle.penup()
    x = random.randint(-200, 200)
    y = random.randint(-200, 200)
    turtle.setx(x)
    turtle.sety(y)
    turtle.pendown()

    turtle.forward(200)
    turtle.left(90)
    turtle.forward(200)
    turtle.left(90)
    turtle.forward(200)
    turtle.left(90)
    turtle.forward(200)
    turtle.penup
    x_lowerright =(x+200)
    y_lowerright = y
    x_upperright =(x+200)
    y_upperright =(y+200)
    x_upperleft = x
    y_upperleft = (y+200)

    #This section draws the second box

    aturtle=turtle.Turtle()
    aturtle.showturtle()
    aturtle.penup()
    aturtle.goto(x, y)

    aturtle.left(90)
    aturtle.forward(50)
    aturtle.right(90)
    aturtle.forward(50)
    aturtle.pencolor("red")
    aturtle.pendown()

    aturtle.forward(100)
    aturtle.left(90)
    aturtle.forward(100)
    aturtle.left(90)
    aturtle.forward(100)
    aturtle.left(90)
    aturtle.forward(100)
    aturtle.penup()

    x2=x+50
    y2=y+50
    x2_lowerright=(x2+100)
    y2_lowerright=y2
    x2_upperright=(x2+100)
    y2_upperright=(y2+100)
    x2_upperleft=x2
    y2_upperleft=(y2+100)

#This section starts the input given by the user
    userTurtle = turtle.Turtle()
    userTurtle.showturtle()
    userTurtle.penup()
    xcor = turtle.numinput("Player Input","Please enter the x-coordinate")
    ycor = turtle.numinput("Player Input","Please enter the y-coordinate")
    userTurtle.goto(xcor, ycor)
    
    if x<xcor<x_lowerright:
        if y<ycor<y_upperright:
    ##        turtle.write("You're in!")
            if x2<=xcor<=x2_lowerright:
                if y2<=ycor<=y_upperright:
                    s=s+2 #Adds 2 points to the score
                    turtle.write("You're in! Score: %s" % s)
                else:
                    s=s+1 #Adds 1 point to the score
                    turtle.write("Almost there! Score: %s" % s)
            else:
                s = s+1 #Adds 1 point to the score
                turtle.write("Almost there! Score: %s" % s)
        else:
            turtle.write("We missed you! Score: %s" % s)
    else:
        turtle.write("We missed you! Score: %s" % s)
    cont=turtle.textinput("Next Round","Continue? (y/n)")
    aturtle.reset()#Erases the inner box
    turtle.reset() #Erases the outer box
    userTurtle.reset() #Erases the user's turtle
    
turtle.write("GAME OVER! Your score is %s" % s)



                
                
