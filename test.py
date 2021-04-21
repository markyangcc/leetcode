a = 'My Name is Python'

print(a[len(a)-1])

for i in range(0, len(a)):
    if(i <= len(a)-1-i):
        print(a[i], end='')
        print(a[len(a)-1-i], end='')
