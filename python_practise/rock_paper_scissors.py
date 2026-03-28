import random

BEATS = {
    'p': 'r',
    's': 'p',
    'r': 's'
}

OPTIONS = tuple(BEATS.keys())

print('>Welcome to the Rock, Paper and Scissors game!\n')


def main() -> None:

    while True:

        user_choice = input('>What do you choose? r/p/s ?\n>Press q to quit ').strip().lower()

        if user_choice == 'q':
            print(">Thank you for playing!")
            break

        opponent_choice = random.choice(OPTIONS)

        if user_choice not in OPTIONS:
            print('>Wrong sign! Try again.')
            continue

        if user_choice == opponent_choice:
            print(">Draw!")

        elif BEATS[user_choice] == opponent_choice:
            print(f">{opponent_choice}, wygrałeś!")

        else:
            print(f">{opponent_choice}, przegrałeś!")


if __name__ == '__main__':
    main()
