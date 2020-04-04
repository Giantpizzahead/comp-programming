'''
USACO 2018 December Contest (Bronze)
Problem 1: Mixing Milk
By Giantpizzahead

Practicing for the current USACO contest. Here we go! :)
'''


def main():
    # Input parsing
    file_in = open("mixmilk.in", mode='r')
    input = file_in.readlines()
    file_in.close()
    b1_cap, b1_amount = map(int, input[0].split())
    b2_cap, b2_amount = map(int, input[1].split())
    b3_cap, b3_amount = map(int, input[2].split())
    # Problem solving
    # I know this is hardcoding ok but it's sooo easy
    # I don't want to waste time making this neat so yeah
    pours = 0
    while pours < 100:
        pours += 1
        if pours % 3 == 1:
            space_left = b2_cap - b2_amount
            amount_to_pour = b1_amount
            if amount_to_pour > space_left:
                amount_to_pour = b2_cap - b2_amount
            b1_amount -= amount_to_pour
            b2_amount += amount_to_pour
        elif pours % 3 == 2:
            space_left = b3_cap - b3_amount
            amount_to_pour = b2_amount
            if amount_to_pour > space_left:
                amount_to_pour = b3_cap - b3_amount
            b2_amount -= amount_to_pour
            b3_amount += amount_to_pour
        else:
            space_left = b1_cap - b1_amount
            amount_to_pour = b3_amount
            if amount_to_pour > space_left:
                amount_to_pour = b1_cap - b1_amount
            b3_amount -= amount_to_pour
            b1_amount += amount_to_pour
    file_out = open("mixmilk.out", mode='w')
    file_out.write(str(b1_amount) + "\n" +
                   str(b2_amount) + "\n" +
                   str(b3_amount))
    file_out.close()


if __name__ == "__main__":
    main()
