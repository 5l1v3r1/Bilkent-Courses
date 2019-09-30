def perms(values, r):

    val_tupples = tuple(values)
    len_tupp = len(val_tupples)

    indices = range(len_tupp)
    cycles = range(len_tupp, len_tupp - r, -1)

    yield tuple(val_tupples[i] for i in indices[:r])

    while len_tupp:
        for i in reversed(range(r)):
            cycles[i] -= 1

            if cycles[i] != 0:
                cyc_i = cycles[i]
                swp_tmp = indices[i]
                indices[i] = indices[-cyc_i]
                indices[-cyc_i] = swp_tmp
                yield tuple(val_tupples[i] for i in indices[:r])
                break
            else:
                indices[i:] = indices[i+1:] + indices[i:i+1]
                cycles[i] = len_tupp - i
        else:
            return


for i in xrange(1, 5):
    vals = range(0, i)
    print "Permutations of ", vals, " are:"

    for perm in perms(vals, i):
        print "\t", perm
    print ""