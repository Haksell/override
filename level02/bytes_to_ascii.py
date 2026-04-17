import sys

assert len(sys.argv) == 2
printf_output = sys.argv[1]
flag = ""

for block in printf_output.split("|"):
    # input is in little endian
    for i in reversed(range(8)):
        flag += chr(int(block[2 * i : 2 * i + 2], 16))

print(flag)
