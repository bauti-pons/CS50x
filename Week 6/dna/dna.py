import csv
import sys


def main():
    # Check for command-line usage
    if len(sys.argv) < 3:
        sys.exit("Too few command-line arguments")
    elif len(sys.argv) > 3:
        sys.exit("Too many command-line arguments")
    else:
        if sys.argv[1][-4:] != ".csv":
            sys.exit("Not a CSV file")

    # Read database file into a variable
    try:
        # Get file headers into a list
        with open(sys.argv[1]) as file:
            reader = csv.DictReader(file)

        # Get file rows (dicts) into a list
        rows = []
        with open(sys.argv[1]) as file:
            reader = csv.DictReader(file)
            for row in reader:
                rows.append(row)

    except FileNotFoundError:
        sys.exit("File does not exist")

    # Read DNA sequence file into a variable
    try:
        with open(sys.argv[2]) as file:
            sequence = file.read()

    except FileNotFoundError:
        sys.exit("File does not exist")

    # Find longest match of each STR in DNA sequence
    matches = {}
    for i in range(1, len(reader.fieldnames), 1):
        length = longest_match(sequence, reader.fieldnames[i])
        matches[reader.fieldnames[i]] = str(length)

    # Check database for matching profiles
    for row in rows:
        count = 0
        for i in range(1, len(reader.fieldnames), 1):
            if row[reader.fieldnames[i]] == matches[reader.fieldnames[i]]:
                count += 1
        if count == len(reader.fieldnames) - 1:
            sys.exit(row["name"])
    else:
        sys.exit("No match")


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
