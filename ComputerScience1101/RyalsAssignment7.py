#Name: Chase Ryals
#File: Assignment 7 - Turtle the Robot
#Date: December 7, 2015
#Description: Write a program to have turtle follow commands from a text file.

import random
import turtle

moves = open("moves.txt")
turtle.penup()

alph = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
nums = '0123456789'
commands = []
for line in moves:
    for c in line:
        if c not in alph:     #If a character is not a letter or
            if c not in nums: #number, it is removed
                line = line.replace(c," ")
    commands = line.split() #Splits items in line at each space
    if 'goto' in commands:
        turtle.pendown()
        a = int(commands[1]) #moves turtle to a point while drawing
        b = int(commands[2])
        turtle.goto(a,b)
        turtle.penup()
    if 'color' in commands:
        turtle.color(random.random(), random.random(), random.random()) #Applies a random color to turtle
    if 'jumpto' in commands:                                            #for each instance of 'color'
        a = int(commands[1]) #Moves to a point without drawing
        b = int(commands[2])
        turtle.goto(a,b)

moves.close()
