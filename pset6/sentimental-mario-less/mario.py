# Initializing get_height function
def get_height():
    # Starting an infinte loop that is manually broken
    while True:
        # Testing for errors
        try:
            height = int(input("Height: "))
            # If check passes, no error occurred, break loop
            if height > 0 and height < 9:
                break
            # Else if error occurs, print this
        except ValueError:
            print("That's not an integer!")
    # Returning value
    return height

# assuming an input of 4 for testing
height = get_height()

    # i = 0/1/2/3
for i in range(0, height):
    # emptySpace = 3/2/1/0
    emptySpace = height - 1 - i
    # hashtags = 1/2/3/4
    hashtags = i + 1
    print(" " * emptySpace + "#" * hashtags)

# Or

for i in range(height):
    # First loop to make up the rows of the pyramid
    for j in range(height - i - 1):
        # Second loop to make up the number of empty spaces
        print(" ", end="")
    # Printing empty space to allign the pyramid to the right
    for k in range(i + 1):
        # Third loop to make up the number of hashes/"#"
        print("#", end="")
    print()
    # Adding new line
