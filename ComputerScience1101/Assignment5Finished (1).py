#Davion Clark
#Tyvon Cruz
#Timothy Rylas

def MoreMales():
    file1=open("WorldCensusAges0-14.csv")
    file2=open("WorldCensusAges15-64.csv")
    file3=open("WorldCensusAges64+.csv")
    c=0
    d=0
    e=0
    for line in file1:
        fields=line.split(",")
        line2=file2.readline()
        fields2=line2.split(",")
        line3=file3.readline()
        fields3=line3.split(",")
        fields[1]=int(fields[1])
        fields[2]=int(fields[2])
        fields2[1]=int(fields2[1])
        fields2[2]=int(fields2[2])
        fields3[1]=int(fields3[1])
        fields3[2]=int(fields3[2])
        ratio1=fields[1] / fields[2]
        ratio2=fields2[1] / fields2[2]
        ratio3=fields3[1] / fields3[2]
        if ratio1>1:
            c+=1
        if ratio2>1:
            d+=1
        if ratio3>1:
            e+=1
    print("Ages 0-14: ",c, "countries have more males than females")
    print("Ages 15-64: ",d, "countries have more males than females")
    print("Ages 64+: ",e, "countries have more males than females")
    print()
    file1.close()
    file2.close()
    file3.close()

def male_to_female():
    file1=open("WorldCensusAges0-14.csv")
    file2=open("WorldCensusAges15-64.csv")
    file3=open("WorldCensusAges64+.csv")
    a=0
    b=20
    print("Country".ljust(25), "Males".ljust(10), "Females".ljust(10))
    for line in file1:
        fields=line.split(",")
        fields[1]=int(fields[1])
        fields[2]=int(fields[2])
        line2=file2.readline()
        fields2=line2.split(",")
        fields2[1]=int(fields2[1])
        fields2[2]=int(fields2[2])
        line3=file3.readline()
        fields3=line3.split(",")
        fields3[1]=int(fields3[1])
        fields3[2]=int(fields3[2])
        fields[1] = fields[1]+fields2[1]+fields3[1]
        fields[2] = fields[2]+fields2[2]+fields3[2]
        ratio=fields[1] / fields[2]
        ratio=round(ratio, 2)
        fields[1]=str(fields[1])
        fields[2]=str(fields[2])
        ratio=str(ratio)
        if a!=b:
            print(fields[0].ljust(25), fields[1].ljust(10), fields[2].ljust(10), "Male to Female Ratio:", ratio)
            a+=1
            continue
        if a==b:
            print()
            userInput=input("Would you like to continue? (y/n): ")
            print('\n')
            if userInput=='y':
                print()
                b+=20
                continue
            else:
                break
    print()
    file1.close()
    file2.close()
    file3.close()

def children_to_adults():
    file1=open("WorldCensusAges0-14.csv")
    file2=open("WorldCensusAges15-64.csv")
    a=0
    b=20
    print("Country".ljust(25), "Children".ljust(10), "Adults".ljust(10))
    for line in file1:
        fields=line.split(",")
        fields[1]=int(fields[1])
        fields[2]=int(fields[2])
        line2=file2.readline()
        fields2=line2.split(",")
        fields2[1]=int(fields2[1])
        fields2[2]=int(fields2[2])
        children=fields[1] + fields[2]
        adults=fields2[1] + fields2[2]
        ratio=children / adults
        ratio=round(ratio, 2)
        fields[1]=children
        fields[2]=adults
        fields[1]=str(fields[1])
        fields[2]=str(fields[2])
        ratio=str(ratio)
        if a!=b:
            print(fields[0].ljust(25), fields[1].ljust(10), fields[2].ljust(10), "Children to Adult Ratio:", ratio)
            a+=1
            continue
        if a==b:
            print()
            userInput=input("Would you like to continue? (y/n): ")
            print('\n')
            if userInput=='y':
                print()
                b+=20
                continue
            else:
                break
    print() 
    file1.close()
    file2.close()

def global_population():
    file1=open("WorldCensusAges0-14.csv")
    file2=open("WorldCensusAges15-64.csv")
    file3=open("WorldCensusAges64+.csv")
    print(" ".ljust(28),"Global".ljust(28), "Children".ljust(28), "Adults".ljust(28), "Seniors".ljust(28))
    children = []
    adults = []
    seniors = []
    children_m = []
    children_f = []
    adults_m = []
    adults_f = []
    seniors_m = []
    seniors_f = []
    for line in file1:
        group1 = line.split(",")
        group1[1] = int(group1[1])
        group1[2] = int(group1[2])
        children.append(group1[1] + group1[2])
        children_m.append(group1[1])
        children_f.append(group1[2])                      
    for line in file2:
        group2 = line.split(",")
        group2[1] = int(group2[1])
        group2[2] = int(group2[2])
        adults.append(group2[1] + group2[2])
        adults_m.append(group2[1])
        adults_f.append(group2[2])
    for line in file3:
        group3 = line.split(",")
        group3[1] = int(group3[1])
        group3[2] = int(group3[2])
        seniors.append(group3[1] + group3[2])
        seniors_m.append(group3[1])
        seniors_f.append(group3[2])
    a = 0
    b = 20
    sum_of_children = sum(children)
    sum_of_adults = sum(adults)
    sum_of_seniors = sum(seniors)
    sum_of_children_m = sum(children_m)
    sum_of_children_f = sum(children_f)
    sum_of_adults_m = sum(adults_m)
    sum_of_adults_f = sum(adults_f)
    sum_of_seniors_m = sum(seniors_m)
    sum_of_seniors_f = sum(seniors_f)
    total_m = sum_of_children_m + sum_of_adults_m + sum_of_seniors_m
    total_f = sum_of_children_f + sum_of_adults_f + sum_of_seniors_f
    total = sum_of_children + sum_of_adults + sum_of_seniors
    print('Total Population %22d %28.0f %28.0f %27.0f' % (total,sum_of_children,sum_of_adults,sum_of_seniors))
    print('Males:Females %25d:%d %16d:%d %19d:%d %16d:%d' %(total_m,total_f,sum_of_children_m,sum_of_children_f,sum_of_adults_m,sum_of_adults_f,sum_of_seniors_m,sum_of_seniors_f))
    print('\n')
    file1.close()
    file2.close()
    file3.close()

def letter_display():
    file1=open("WorldCensusAges0-14.csv")
    file2=open("WorldCensusAges15-64.csv")
    file3=open("WorldCensusAges64+.csv")
    country = []
    population = []
    children = []
    adults = []
    seniors = []
    findValue = str(input("Enter a letter to find countries that start with that letter: "))
    for line in file1:
        group1 = line.split(",")
        group1[1] = int(group1[1])
        group1[2] = int(group1[2])
        if line[0] == findValue.upper():
            country.append(group1[0].strip())
        children.append(group1[1] + group1[2])
        
    for line in file2:
        group2 = line.split(",")
        group2[1] = int(group2[1])
        group2[2] = int(group2[2])
        adults.append(group2[1] + group2[2])
    for line in file3:
        group3 = line.split(",")
        group3[1] = int(group3[1])
        group3[2] = int(group3[2])
        seniors.append(group3[1] + group3[2])
    a = 0
    b = 20
    userinput = 'none'
    print("Country".ljust(28), "Population".ljust(28))
    while userinput != 'n':
        all_ages = [x + y + z for x,y,z in zip(children,adults,seniors)]
        for x,y in zip(country[a:b],all_ages):
                print(x.ljust(28),'%10.0f' %y)
        userinput = input("Do you want to continue? (y/n): ")
        print('\n')
        a += 20
        b += 20 
    file1.close()
    file2.close()
    file3.close()

def mtf_all_ages():
    file1=open("WorldCensusAges0-14.csv")
    file2=open("WorldCensusAges15-64.csv")
    file3=open("WorldCensusAges64+.csv")
    print("Country".ljust(28), "Children".ljust(28), "Adults".ljust(28), "Seniors".ljust(28))
    country = []
    children = []
    adults = []
    seniors = []
    for line in file1:
        group1 = line.split(",")
        children.append(group1[1].strip() + ":" + group1[2].strip())
        country.append(group1[0].strip()) 
    for line in file2:
        group2 = line.split(",")
        adults.append(group2[1].strip() + ":" + group2[2].strip())
    
    for line in file3:
        group3 = line.split(",")
        seniors.append(group3[1].strip() + ":" + group3[2].strip())
    a = 0
    b = 20
    userinput = 'none'
    while userinput != 'n':
        for w,x,y,z in zip(country[a:b],children[a:b],adults[a:b],seniors[a:b]):
            print(w.ljust(28),x.ljust(28),y.ljust(28),z.ljust(28))
        userinput = input("Do you want to continue? (y/n): ")
        print('\n')
        a += 20
        b += 20 
    file1.close()
    file2.close()
    file3.close()

def CountriesTotal():
    file1=open("WorldCensusAges0-14.csv")
    file2=open("WorldCensusAges15-64.csv")
    file3=open("WorldCensusAges64+.csv")
    print("Country".ljust(28),"Children".ljust(26), "Adults".center(8), "Seniors".center(41))
    country = []
    children_m = []
    children_f = []
    adults_m = []
    adults_f = []
    seniors_m = []
    seniors_f = []
    children = []
    adults = []
    seniors = []
    for line in file1:
        group1 = line.split(",")
        group1[1] = int(group1[1])
        group1[2] = int(group1[2])
        country.append(group1[0].strip())
        children.append(group1[1] + group1[2])
    for line in file2:
        group2 = line.split(",")
        group2[1] = int(group2[1])
        group2[2] = int(group2[2])
        adults.append(group2[1] + group2[2])

    for line in file3:
        group3 = line.split(",")
        group3[1] = int(group3[1])
        group3[2] = int(group3[2])
        seniors.append(group3[1] + group3[2])

    a = 0
    b = 20
    userinput = 'none'
    while userinput != 'n':
        for w,x,y,z in zip(country[a:b],children[a:b],adults[a:b],seniors[a:b]):
            print (w.ljust(28),str(x).ljust(27),str(y).ljust(24),z)
        userinput = input("Do you want to continue? (y/n): ")
        print('\n')
        a += 20
        b += 20 
    file1.close()
    file2.close()
    file3.close()

def children_to_seniors():
    file1=open("WorldCensusAges0-14.csv")
    file2=open("WorldCensusAges64+.csv")
    a=0
    b=20
    print("Country".ljust(25), "Children".ljust(10), "Seniors".ljust(10))
    for line in file1:
        fields=line.split(",")
        fields[1]=int(fields[1])
        fields[2]=int(fields[2])
        line2=file2.readline()
        fields2=line2.split(",")
        fields2[1]=int(fields2[1])
        fields2[2]=int(fields2[2])
        children=fields[1] + fields[2]
        seniors=fields2[1] + fields2[2]
        ratio=children / seniors
        ratio=round(ratio, 2)
        fields[1]=children
        fields[2]=seniors
        fields[1]=str(fields[1])
        fields[2]=str(fields[2])
        ratio=str(ratio)
        if a!=b:
            print(fields[0].ljust(25), fields[1].ljust(10), fields[2].ljust(10), "Children to Senior Ratio:", ratio)
            a+=1
            continue
        if a==b:
            print()
            userInput=input("Would you like to continue? (y/n): ")
            print('\n')
            if userInput=='y':
                print()
                b+=20
                continue
            else:
                break
    print() 
    file1.close()
    file2.close()

def adults_to_seniors():
    file1=open("WorldCensusAges15-64.csv")
    file2=open("WorldCensusAges64+.csv")
    a=0
    b=20
    print("Country".ljust(25), "Adults".ljust(10), "Seniors".ljust(10))
    for line in file1:
        fields=line.split(",")
        fields[1]=int(fields[1])
        fields[2]=int(fields[2])
        line2=file2.readline()
        fields2=line2.split(",")
        fields2[1]=int(fields2[1])
        fields2[2]=int(fields2[2])
        adults=fields[1] + fields[2]
        seniors=fields2[1] + fields2[2]
        ratio=adults / seniors
        ratio=round(ratio, 2)
        fields[1]=adults
        fields[2]=seniors
        fields[1]=str(fields[1])
        fields[2]=str(fields[2])
        ratio=str(ratio)
        if a!=b:
            print(fields[0].ljust(25), fields[1].ljust(10), fields[2].ljust(10), "Adult to Senior Ratio:", ratio)
            a+=1
            continue
        if a==b:
            print()
            userInput=input("Would you like to continue? (y/n): ")
            print('\n')
            if userInput=='y':
                print()
                b+=20
                continue
            else:
                break
    print() 
    file1.close()
    file2.close()

def main():
    cont='cont'
    while cont!='Q':
        print("A-Total population of each age group")
        print("B-Number of countries with more males than females in each age group")
        print("C-Population of countries starting with a certain letter")
        print("D-Total male to female population per country")
        print("E-Children to adult Population")
        print("F-Adult to senior population")
        print("G-Global population statistics")
        print("H-Children to senior popultaion")
        print("I-Male to female populations for each age group")
        list_choice=input("Please select from A-I or enter Q to quit: ")
        print()
        cont=list_choice
        if list_choice=="A" or list_choice=='a':
            CountriesTotal()
        if list_choice=='B' or list_choice=='b':
            MoreMales()
        if list_choice=='C' or list_choice=='c':
            letter_display()
        if list_choice=='D' or list_choice=='d':
            male_to_female()
        if list_choice=='E' or list_choice=='e':
            children_to_adults()
        if list_choice=='F' or list_choice=='f':
            adults_to_seniors()
        if list_choice=='G' or list_choice=='g':
            global_population()
        if list_choice=='H' or list_choice=='h':
            children_to_seniors()
        if list_choice=='I' or list_choice=='i':
            mtf_all_ages()
        if list_choice == 'q' or list_choice == 'Q':
            break
main()

        
    

