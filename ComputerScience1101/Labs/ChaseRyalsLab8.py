#Author: Chase Ryals
#File Name: Lab 8
#Date: September 4, 2015
#Description: Outputting a mixed fraction from an improper fraction

numerator=int(input("Numerator: "))
denominator=int(input("Denominator: "))

mix_frac1 = int(numerator // denominator)
mix_frac2 = int(numerator % denominator)

print(numerator, '/', denominator, "is equal to ", mix_frac1, mix_frac2, '/', denominator)

