import random


def input_to_int(s: str) -> int:
    """
        Function maps input() to integer and protects it against wrong signs and negative numebers.

        Args: 
            The function works exactly the same as the "input()" function.

        Returns:
            The same value user inserts but mapped to integer and secured from incorrect signs and negative values. 

    """

    while True:
        try:
            user_input = int(input(s))
            if user_input < 0:
                print("Only positive values! Please try again.")
                continue
            else:
                break

        except ValueError:
            print("ValueError! Wrong sign. Please try again.")
    return user_input


def play_game() -> None:
    """ Main function of the program."""

    print(">Welcome to 'Guess-random-number' game!")
    threshold = input(
        ">Please insert an upper threshold of number range: ")

    random_number = random.randint(0, threshold)

    while True:
        input_number = input_to_int(f">Now guess the number between 0 and {threshold} (range boundaries included): ")

        if input_number == random_number:
            print("Congratulation, you guessed the right number!")
            break

        elif input_number > random_number:
            print("Too high!")

        else:
            print("Too low!")


# dunder variable __name__
if __name__ == '__main__':
    play_game()
