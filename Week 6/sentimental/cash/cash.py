def main():

    while True:
        try:
            change = round(float(input("Change: ")), 2)
            if (change > 0):
                break
        except ValueError:
            pass

    quarter = change // 0.25
    change = round(change - quarter * 0.25, 2)

    dime = change // 0.10
    change = round(change - dime * 0.10, 2)

    nickel = change // 0.05
    change = round(change - nickel * 0.05, 2)

    penny = change // 0.01
    change = round(change - penny * 0.01, 2)

    print(int(quarter + dime + nickel + penny))


if __name__ == "__main__":
    main()
