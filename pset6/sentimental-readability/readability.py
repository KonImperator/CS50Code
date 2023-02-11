# Importing regex
import re
# Asking for input
text = input("Your text here: ")
# Counting sentences, words and letters
sentenceCount = len(re.findall(r'[A-Z][A-Za-z|\s|,|:|"|\'|\-|;]+[?|.|!]', text))
wordCount = len(re.findall(r'[\w-]+\'?([\w]+)?', text))
letterCount = len(re.findall(r'[A-Za-z]', text))
# Finding value of L and S
L = (letterCount / wordCount) * 100
S = (sentenceCount / wordCount) * 100
# Calculating grade via given formula
result = round((0.0588 * L) - (0.296 * S) - 15.8)
# Printing respective grades
if result >= 16:
    print("Grade 16+")
elif result < 1:
    print("Before Grade 1")
else:
    print(f"Grade {result}")