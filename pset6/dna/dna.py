import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py CSVFILE TXTFILE")

    # TODO: Read database file into a variable

    # Initializing a list to hold the STR names (0 index is 'name') and a dict to appoint them with values
    STRlist = []
    STRdict = {}
    people = []
    
    # Reading CSV file and filling STRlist with the field headers
    # Adding strands to STRlist
    # Adding individuals to the people list
    with open(sys.argv[1], "r") as file:
        CSVfile = csv.DictReader(file)

        for element in CSVfile.fieldnames:
            STRlist.append(element)

        for row in CSVfile:
            people.append(row)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as file2:
        text = file2.read()

    # TODO: Find longest match of each STR in DNA sequence
    # Filling STRdict with all the STRs and the newly found longest matches
    for index in range(1, len(STRlist)):
        subsequence = STRlist[index]
        STRdict[subsequence] = longest_match(text, subsequence)

    # TODO: Check database for matching profiles
    # Initializing bool as false and matchName to be able to use it within the next loop
    # Breaking out of loop if all STRs match (matching person is found)
    # Resetting value to true if they didn't match in the previous iteration below
    # Using index to match the STR's name from the list and compare below
    isFound = False
    matchName = ""
    for keys in people:
        if isFound:
            break
        isFound = True
    # Assigning current person's name in case they are a match
    # Comparing STR count from the CSV file with the dict from the text file
        for index in range(1, len(keys)):
            dna = STRlist[index]
            matchName = keys["name"]
            if int(keys[dna]) != STRdict[dna]:
                isFound = False
                break
    if isFound:
        print(matchName)
    else:
        print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
