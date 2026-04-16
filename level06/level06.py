import sys


assert len(sys.argv) == 2
login = sys.argv[1]
assert len(login) >= 6
serial = (ord(login[3]) ^ 4919) + 6221293
for c in map(ord, login):
    serial += (serial ^ c) % 1337
print(serial)
