#Name: Chase Ryals
#File: Assignment 6 - Ciphers
#Date: November 23, 2015
#Description: Encrypting and Decrypting files

alphabet="abcdefghijklmnopqrstuvwxyz"


def encryptMessage():
    file=open("message.txt")
    file2=open("cipher.txt", "w")
    shift=int(input("Enter the key number (1-26): "))
    while 1>shift or shift>26:
        shift=int(input("Invalid. Choose from 1-26: "))
    message=file.readline()
    file.close()
    a=0
    encryption="" #New string that hold the encrypted message
    for i in message:
        if i in alphabet:
            encryption += alphabet[(alphabet.index(i)+shift)%(len(alphabet))] #Takes the index i minus the shift amount
        else:                                                                 #and finds the remainder of the sum and 26
            encryption += i #If i is not a letter, it will be copied to the encrypted message

        a+=1
    file2.write(encryption)
    file2.close()
    return encryption




    
def decryptMessage():
    file2=open("cipher.txt")
    file3=open("plain.txt", "w")
    shift=int(input("Enter the key number (1-26): "))
    while 1>shift or shift>26:
        shift=int(input("Invalid. Choose from 1-26: "))
    a=0
    message=file2.readline()
    file2.close()
    decryption='' #Starts a new string to hold the decrypted message
    for i in message:
        if i in alphabet:
            letter = (ord(i)-shift) % 122 #Finds the ASCII code of the letter and subtracts shift
            if letter < 97:               #and finds the remainder of the sum and 122 (the end of lowercase letter codes)
                letter+=26                        
            decryption += chr(letter) #Converts the ASCII code to letter and adds it to the decrypted message
        else:
            decryption += i #If i is not a letter, it is copied to the decrypted message

        a+=1
    file3.write(decryption)
    file3.close()
    return decryption

def bruteForce():
    file2=open("cipher.txt")
    file4=open("possibilities.txt", "w")
    numbers=[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25]
    message=file2.readline()
    file2.close()
    a=0 #Initializes a, the index of each item in message
    decryption=''
    for field in numbers: #Goes through list of numbers; field is the shift amount
        for i in message:
            if i in alphabet:
                letter = (ord(i)-field) % 122
                if letter < 97:
                    letter+=26                       
                decryption += chr(letter)
            else:
                decryption += i
            a+=1
        print("%d. %5s" % (field,decryption)) #Prints the shift amount and decryption, with spacing
        file4.write("%d. %5s\n" % (field,decryption)) #Copies to 'possibilities.txt' starts a new line with each iteration of the loop
        a=0 #Resets a for every new shift amount
        decryption='' #Resets decryption message for every new shiift amount
    file4.close()


def printMenu():
    userInput='y'
    while userInput!='n':
        print("Welcome to Caesar Cipher")
        print()
        print("1. Encrypt message.txt")
        print("2. Decrypt cipher.txt")
        print("3. Break the cipher")
        print("4. Quit")
        print()
        userInput=int(input("Enter your choice: "))
        while 1>userInput or userInput>4: #Input validation for choice options
            userInput=int(input("Wrong input. Please enter again: "))
        if userInput==1:
            print("Your encrypted message is:",encryptMessage())
            print()
            print("Also see the file cipher.txt")
            print()
        if userInput==2:
            print("Your decrypted message is:",decryptMessage())
            print()
            print("Also see the file plain.txt")
            print()
        if userInput==3:
            bruteForce()
            print()
        if userInput==4:
            print("Goodbye")
            break

printMenu()



        
