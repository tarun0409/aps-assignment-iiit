import random

# n = number of integers you want to generate, x ** y denotes x^y
n = 10 ** 5

# minimum and maximum possible value of random number generated
minn = 1
maxx = 10 ** 9

# first line containing the value of n
print(n)

# generating and printing n newline separated random integers
for i in range(n) :
	print(random.randint(minn, maxx))
