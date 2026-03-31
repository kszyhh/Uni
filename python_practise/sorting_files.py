import pathlib


def cleaning(path: str) -> None:
    """
        Sorts files in the given directory into subfolders based on their extensions.
    """
    p = pathlib.Path(path).resolve()

    if not p.exists():
        print(f"Error: The path '{path}' does not exist.")
        return

    if not p.is_dir():
        print(f"Error: '{path}' is a file, not a directory.")
        return

    for item in p.iterdir():

        if item.is_dir() or not item.suffix:
            continue
        try:
            no_dot = item.suffix.removeprefix('.')
            new_dir = p / f"{no_dot}"
            new_dir.mkdir(exist_ok=True)
            new_location = new_dir / item.name
            item.rename(new_location)
            print(f"Moved {item.name} to {new_location}")
        except PermissionError:
            print(
                f"kipped: {item.name} (File is currently in use or access denied)")
        except Exception as e:
            print(f"Unexpected error moving {item.name}: {e}")


if __name__ == "__main__":
    path = input("Determine the path to sort your files: ")
    cleaning(path)
