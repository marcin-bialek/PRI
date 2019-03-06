import subprocess 

for i in range(0, 1000):
    out = subprocess.check_output(["./bin/BinToDec", str(i)]).decode()[:-1]

    if out == bin(i)[2:]:
        print(i, ":", out)
    else:
        print("Error for i = ", i)
        quit()

print("Ok")