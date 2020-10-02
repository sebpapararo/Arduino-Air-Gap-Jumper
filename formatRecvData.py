import re

inFile = r"C:\\Users\\sebpa\\Documents\\University Work\\Year 4 - MSc\\Dissertation\\serialLog"
with open(inFile) as f:
    f = f.read().replace('\n', '')

tempList = re.split("<|>", f)
# Remove empty elements from the list
eachAttempt = list(filter(None, tempList))

outFile = open("C:\\Users\\sebpa\\Documents\\University Work\\Year 4 - MSc\\Dissertation\\formattedData.txt", "w")

for counter, attempt in enumerate(eachAttempt):
    outFile.write("#### Attempt " + str(counter + 1) + " ####\n")

    # Split each attempt into its files and contents
    splitString = ["C:" + fPath for fPath in attempt.split("C:") if fPath]
    splitString = [fContents.split("~") for fContents in splitString]

    for combo in splitString:
        outFile.write("File: " + combo[0] + "\n")
        outFile.write("Contents: " + combo[1] + "\n\n")

    outFile.write("\n")

print("Finished formatting!")