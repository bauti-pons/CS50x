import re
import sys


def main():

    number = input("Number: ")
    matches = re.search(r"^\d{13,16}$", number)
    if not matches:
        sys.exit("INVALID")

    count = 0
    length = len(number)
    if len(number) % 2 == 0:
        for i in range(0, length, 2):
            n = int(number[i]) * 2
            if n > 9:
                n = str(n)
                n1 = int(n[0])
                n2 = int(n[1])
                count += n1 + n2
            else:
                count += n
        for i in range(1, length, 2):
            count += int(number[i])
    else:
        for i in range(1, length, 2):
            n = int(number[i]) * 2
            if n > 9:
                n = str(n)
                n1 = int(n[0])
                n2 = int(n[1])
                count += n1 + n2
            else:
                count += n
        for i in range(0, length, 2):
            count += int(number[i])

    if count % 10 != 0:
        sys.exit("INVALID")

    if number[0] == "4" and length in [13, 16]:
        sys.exit("VISA")
    elif number[:2] in ["34", "37"] and length == 15:
        sys.exit("AMEX")
    elif number[:2] in ["51", "52", "53", "54", "55"] and length == 16:
        sys.exit("MASTERCARD")
    else:
        sys.exit("INVALID")


if __name__ == "__main__":
    main()
