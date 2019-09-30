import itertools


def perms(vals, r):
    return itertools.permutations(vals, r)

for i in xrange(1, 5):
    vals = range(0, i)
    print "Permutations of ", vals, " are:"

    for subset in perms(vals, i):
        print "\t", subset
    print ""
