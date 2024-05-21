def main():

    while True:
        try:
            height = int(input("Height: "))
            if (0 < height < 9):
                break
        except ValueError:
            pass

    for i in range(height):
        print(" " * (height - i - 1), end="")
        print("#" * (i + 1))


if __name__ == "__main__":
    main()
