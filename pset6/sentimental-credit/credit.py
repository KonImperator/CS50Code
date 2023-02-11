from cs50 import get_int

num = get_int("Card Number: ")
num = str(num)

cardLength = len(num)

if cardLength < 13 or cardLength > 16:
    print("INVALID")
    exit()

type = ""

# Chechking starting digits and length for AMEX
if num[0] == "3" and (num[1] == "4" or num[1] == "7"):
    if cardLength == 15:
        type = "AMEX\n"
# Chechking starting digits and length for VISA
elif num[0] == "4":
    if cardLength == 13 or cardLength == 16:
        type = "VISA\n"
# Chechking starting digits and length for MASTERCARD
elif num[0] == "5" and int(num[1]) in range(1, 6):
    if cardLength == 16:
        type = "MASTERCARD\n"
# Otherwise setting type to be INVALID
else:
    type = "INVALID\n"

# Continuing if card is of valid type, otherwise printing INVALID and ending program
if not type == "INVALID\n":
    # Initializing needed variables
    addition = 0
    multiplication = 0
    counter = 0
    product = []
    sumProduct = 0
    # number1Range and number2Range are added due different outcome for odd end even numbers in the loops
    number1Range = 0
    if (cardLength % 2) != 0:
        number1Range = 1

    # Using reverse range to start from the back and iterate over the numbers
    for i in reversed(range(number1Range, cardLength, 2)):
        multiplication = int(num[i]) * 2
        # Adding numbers to list in order to add the products together
        product.append(multiplication)
        # Using counter for indexing
        counter += 1

    for j in range(len(product)):
        # If it's a 2 digit number split it and add both sides together
        if (len(str(product[j])) > 1):
            sumProduct += int(str(product[j])[0]) + int(str(product[j])[1])
        else:
            # Otherwise just add the number
            sumProduct += product[j]

        number1Range = 1

    if (cardLength % 2) != 0:
        number1Range = 0

    for k in reversed(range(number1Range, cardLength + number1Range, 2)):
        addition += int(num[k])
    final = addition + sumProduct
    final = str(final)

    # Checking if final result's last digit is equal to 0 and printing the card type if yes, other wise printing INVALID
    if final[len(final) - 1] == "0":
        print(type)
    else:
        print("INVALID\n")
else:
    print(type)
