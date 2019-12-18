#Name: Chase Ryals
#File Name: Lab 9 Exercise 2 Part C
#Date: September 9, 2015
#Description: This program accepts the weight in pounds, height in inches, and name of the user.
#It will convert these measurements to metric and display the Body Mass Index.

name=input("Please enter your name: ")
weight_lbs=float(input("Please enter your weight in pounds: "))
height_inches=float(input("Please enter your height in inches: "))

weight_kg = float(weight_lbs * 0.45359237) #Converting from pounds to kilograms
height_meters = float(height_inches * 0.0254) #Converting from inches to meters
bmi = float(weight_kg / height_meters ** 2)

print("Your BMI is: ", bmi)
