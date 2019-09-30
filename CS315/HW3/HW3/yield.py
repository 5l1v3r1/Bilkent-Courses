def asd(n):
    for i in xrange(0, n):
        for j in xrange(i + 1, n):
            yield (i, j)

for i in asd(4):
    print i

