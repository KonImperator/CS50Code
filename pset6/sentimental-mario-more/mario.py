def get_height():
    while True:
        try:
            height = int(input("Height: "))
            if height > 0 and height < 9:
                break
        except ValueError:
            print("This is not an integer!")

    return height


height = get_height()

for i in range(height):
    print(" " * (height - i - 1) + "#" * (i + 1) + " " * 2 + "#" * (i + 1))