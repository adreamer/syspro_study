import sys

def sum():
    total = 0
    while True:
        x = (yield total)
        total += x

co = sum()
print("Sum: ", next(co))
while True:
    print("num? ", end="")
    num = int(sys.stdin.readline())
    print("\nSum: ", co.send(num))
