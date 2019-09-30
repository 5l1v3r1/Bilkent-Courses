import numpy

def graphReader(filename):
    with open(filename, 'r') as f:
        content = f.readlines()  # content[1] contains the num nodes. content[4] and beyond contains vertices
        num_nodes = int(content[1])
        matrix = numpy.zeros(shape=(num_nodes, num_nodes))  # create empty numpy matrix

        for z in range(4, len(content)):  # fill the matrix
            matrixX = int(content[z][0])
            matrixY = int(content[z][5])
            matrix[matrixX][matrixY] = 1
            matrix[matrixY][matrixX] = 1

        for z in range(0, len(matrix)):
            print matrix[z]

        return numpy.matrix(matrix)

def pathFinder(matrix, m):
    power_matrix = matrix ** m
    for x in range(0, len(matrix)):
        for y in range(0, x + 1):  #go through the diagonal not to count edges twice
            if matrix[x,y] == 1:
                print "From " + str(x) + " to " + str(y) + ": " + str(power_matrix[x,y])


pathFinder(graphReader("input.txt"), 4)

#source for how to find number of paths http://math.stackexchange.com/questions/602207/finding-number-of-paths-between-vertices-in-a-graph