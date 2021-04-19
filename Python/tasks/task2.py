mod = int(input())
step = int(input())
start = int(input())
end = int(input()) + 1
if(start > end):
    step = step * -1
    end = end - 2
for i in range(start, end, step):
    if(i % mod == 0): continue
    print(str(i), end = ' ')
