# Name:     Timothy Ryals
# Program:  GeneticAlgorithm.py
# Date:     April 30, 2018

import random
import math


numGenerations = 50
numChromosomes = 60

population = []
fitnessValues = []

generationNum = 0

decodeValue = 6 / 255
    
currentXValue = 0
currentYValue = 0
currentGeneration = 0
maxPeakResult = 0


#Create a random initial population
for i in range(0, numChromosomes):
    temp = ''
    for k in range(0,16):
        rand = random.randint(0,1)
        temp += str(rand)
    population.append(temp)


#Print the header for the table
print("\n\t\tx\t\t|\t\ty\t\t|\t\tf(x,y)\n" +
      "--------------------------------------------------------------------------------------------------")


#Creates a set number of generations derived from the initial population and calculates the max and average fitness for each generation
ind = 0
while ind < numGenerations:
    totalChromosomes = 0
    tempPop = []
    fitnessValues = []
    maxFitnessValue = 0
    maxX = 0
    maxY = 0
    workingPop = population.copy()
    temp = ""

    #Calcualate the fitness for every chromosome in the current generation
    for chromosome in population:
        binX = ""
        binY = ""
        #Split each chromosome into an x half and a y half
        for a in range(0, 8):
            binX += chromosome[a]
            binY += chromosome[a + 8]

        decX = 0
        decY = 0
        x = 0
        y = 0

        #Convert each half of the chromosome from a binary bitstring to base 10
        index = 7
        for g in range(0, 8):
            decX += (int(binX[index]) * (2 ** g))
            decY += (int(binY[index]) * (2 ** g))
            index -= 1
        
        #Calculate the decoded values of x and y to be used in the fitness function
        x = (decX * decodeValue) - 3
        y = (decY * decodeValue) - 3

        #Calculates the fitness of the current chromosome using the decoded values of x and y
        peak = (((1 - x)**2) * math.exp((-x**2) - ((y + 1)**2))) - ((x - (x**3) - (y**3)) * math.exp((-x**2) - (y**2)))

        #Add the fitness value to the fitnessValue list
        fitnessValues.append(peak)

        #If the current chromosome has a higher fitness value than the current max value, replace the max value with this chromosome's fitness value
        if peak > maxPeakResult:
            maxPeakResult = peak
            currentXValue = x
            currentYValue = y
            currentGeneration = generationNum
        
        #If the chromosome has a higher fitness value than the current max value for the current generation, replace the generation's max value with this
        #chromosome's fitness value
        if peak > maxFitnessValue:
            maxFitnessValue = peak
            maxX = x
            maxY = y

    #Calculates the average of all fitness values for the current generation
    generationAvg = 0.00
    for element in fitnessValues:
        generationAvg += element
    generationAvg /= numChromosomes

    #Print the max fitness value and the average fitness value for the curernt generation
    print(str(maxX) + "\t\t| " + str(maxY) + "\t\t| " + str(maxFitnessValue) + 
            "\t\t\tGeneration " + str(generationNum + 1) + " average: " + str(generationAvg))


    #Take the two most fit chromosomes in this generation to perform crossover on them
    mostFit = ""
    mostFitValue = None
    secondFit = ""
    secondFitValue = None

    mostFitValue = max(fitnessValues)
    mostFit = population[fitnessValues.index(mostFitValue)]
    workingPop.pop(fitnessValues.index(mostFitValue))
    fitnessValues.pop(fitnessValues.index(mostFitValue))

    secondFitValue = max(fitnessValues)
    secondFit = population[fitnessValues.index(secondFitValue)]

    crossoverChance = random.randint(1, 10)
    if crossoverChance < 8:
        crossoverPoint = random.randint(1, 14)
        tempString1 = ""
        tempString2 = ""
        for first in range(0, crossoverPoint):
            tempString1 += mostFit[first]
            tempString2 += secondFit[first]
        for second in range(crossoverPoint, 16):
            tempString1 += secondFit[second]
            tempString2 += mostFit[second]
        #Add the two new chromosomes to the new population
        tempPop.append(tempString1)
        tempPop.append(tempString2)
    else:
        #If they do not crossover, they will be cloned into the next generation
        tempPop.append(mostFit)
        tempPop.append(secondFit)

    workingPop = []

    #Perform crossover on the rest of the population until the next generation is full
    while len(tempPop) < len(population):
        parent1 = population[random.randint(0, numChromosomes - 1)]
        parent2 = population[random.randint(0, numChromosomes - 1)]
        if population.index(parent1) == population.index(parent2):
            while population.index(parent1) == population.index(parent2):
                parent1 = population[random.randint(0, numChromosomes - 1)]
                parent2 = population[random.randint(0, numChromosomes - 1)]
        else:
            crossoverChance = random.randint(1, 10)
            if crossoverChance < 8:
                crossoverPoint = random.randint(1, 14)
                tempString1 = ""
                tempString2 = ""
                for first in range(0, crossoverPoint):
                    tempString1 += parent1[first]
                    tempString2 += parent2[first]
                for second in range(crossoverPoint, 16):
                    tempString1 += parent2[second]
                    tempString2 += parent1[second]
                tempPop.append(tempString1)
                tempPop.append(tempString2)
            else:
                tempPop.append(parent1)
                tempPop.append(parent2)
    
    #In case there is an overflow of chromosomes in the next population, remove random values until the next population is the correct size
    if len(tempPop) > numChromosomes:
        ran = random.randint(0, len(tempPop) - 1)
        tempPop.pop(ran)
                
    
    #Perform mutation on all chromosomes in the new generation
    for num in range(0, numChromosomes):
        mutationChance = random.randint(1, 1000) #0.001 probability of mutation
        if mutationChance == 50:
            tempString = ""
            mutateIndex = random.randint(0, 15)
            for bit in tempPop[num]:
                #Swap bits with their opposite value if they are at the index specified
                if bit.index == mutateIndex:
                    if bit == "0":
                        tempString += "1"
                    else:
                        tempString += "0"
                else:
                    tempString += bit
            #Remove and replace the chromosome with the new mutated chromosome
            tempPop.remove(tempPop[num])
            tempPop.append(tempString)
        else:
            #If the selected chromosome does not mutate, continue with the loop
            continue

    #print("\n---------------------------------------------------------------------------------------------------------------")
    population = []
    population = tempPop.copy()
    generationNum += 1
    ind += 1

#Print the overall most fit value
print("\n\nThe pair (" + str(currentXValue) + ", " + str(currentYValue) + ") in generation " + str(currentGeneration + 1) + " gives the maximum value of " + str(maxPeakResult))