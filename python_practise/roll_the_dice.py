import random


def roll(sides: int = 6) -> tuple[int, int]:

    """
    Function simulates roll of dice.

    Args:
    Function takes one argument of int type. The argument stand for number of dice sides. Defaultly 6.

    Returns:
    The functions returns tuple of 2 ints which stands for the result of the roll.  
    """

    x = random.randint(1, sides)
    y = random.randint(1, sides)
    return x, y


def main() -> None:

    """ Main function of the program """

    while True:
        user_input = input(">Roll the dice? y/n: ").strip().lower()

        if user_input in ['y', 'yes', 'ye']:
            side1, side2 = roll()
            print(f"({side1},{side2})")

        elif user_input in ['no', 'n']:
            print("No problem.Thanks for playing.")
            break

        else:
            print("Incorrect answer")


# dunder variable __name__
if __name__ == '__main__':
    main()
