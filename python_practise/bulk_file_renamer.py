import pathlib


def bulk_file_renamer(path: str, prefix: str):
    '''
     Renames all files in a directory to a standard sequence - prefix_number chronogically. 
    '''

    p = pathlib.Path(path).resolve()

    if not p.exists():
        print(f"Error: The path '{path}' does not exist.")
        return

    if not p.is_dir():
        print(f"Error: '{path}' is a file, not a directory.")
        return

    files = [f for f in p.iterdir() if f.is_file()]  # chronogical order

    files.sort(key=lambda f: f.stat().st_mtime)

    for index, file in enumerate(files, start=1):
        try:
            new_name = f"{prefix}_{index:03d}{file.suffix}"
            file.rename(p / new_name)
        except PermissionError:
            print(f"Skipped {file.name}: Permission denied.")
        except Exception as e:
            print(f"Failed to rename {file.name}: {e}")


if __name__ == "__main__":
    user_path = input("Enter the folder path: ").strip()
    user_prefix = input("Enter the new prefix (e.g., 'Vacation'): ")
    bulk_file_renamer(user_path, user_prefix)
