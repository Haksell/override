printf_output = "756e505234376848|45414a3561733951|377a7143574e6758|354a35686e475873|48336750664b394d"
flag = ""

for block in printf_output.split("|"):
    # input is in little endian
    for i in reversed(range(8)):
        flag += chr(int(block[2 * i : 2 * i + 2], 16))

print(flag)
