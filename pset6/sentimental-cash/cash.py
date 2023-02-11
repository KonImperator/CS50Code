from cs50 import get_float
# Importing get_float function to avoid writing error catching code

change = get_float("The change is: ") * 100
# Gettin change and 100x-ing since math is dumb

# Looping in case I get unwanted input
while change < 0:
    change = get_float("The change is: ") * 100

# Initializing coin counter
coinCounter = 0

# Loop until change == 0 whereas coins grow with each iteration
while change > 0:
    # Quarters
    while change >= 25:
        change = change - 25
        coinCounter += 1
    # Dimes
    while change >= 10:
        change = change - 10
        coinCounter += 1
    # Nickels
    while change >= 5:
        change = change - 5
        coinCounter += 1
    # Pennies
    while change > 0:
        change = change - 1
        coinCounter += 1

print(coinCounter)
