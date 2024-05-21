def main():
    text = input("Text: ").strip()  # Prompt the user for some text
    letters = count_letters(text)  # Count the number of letters in the text
    words = count_words(text)  # Count the number of words in the text
    sentcs = count_sentcs(text)  # Count the number of sentences in the text
    index = get_Coleman_Liau_index(letters, words, sentcs)  # Compute the Coleman-Liau index
    print_grade_level(index)  # Print the grade level


def count_letters(t):
    count = 0
    for c in t:
        if c.isalpha() == True:
            count += 1
    return count


def count_words(t):
    count = 1
    for c in t:
        if c.isspace() == True:
            count += 1
    return count


def count_sentcs(t):
    count = 0
    for c in t:
        if (c == "." or c == "!" or c == "?"):
            count += 1
    return count


def get_Coleman_Liau_index(l, w, s):
    L = l / w * 100
    S = s / w * 100
    ind = round(0.0588 * L - 0.296 * S - 15.8)
    return ind


def print_grade_level(ind):
    if (ind < 1):
        print("Before Grade 1")
    elif (ind >= 16):
        print("Grade 16+")
    else:
        print("Grade", ind)


if __name__ == "__main__":
    main()
