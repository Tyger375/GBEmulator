import sys

def read_file(filename: str) -> bytes:
    with open(filename, "rb") as f:
        return f.read()

if __name__ == "__main__":
    data1 = read_file(sys.argv[1])
    data2 = read_file(sys.argv[2])

    for i, (x, y) in enumerate(zip(data1, data2)):
        if x != y:
            print(f"DIFF at {hex(i)}: {x} {y}")