def main():
    x = Var("x")
    y = Var("y")
    z = Var("z")
    e = 3 + (x + 2 * y) * z

    print evaluate(x, x=3)
    print evaluate(e, **{"x": 3, "y": 4, "z": 2})
    print evaluate(e, x=3, y=-1, z=4)
    print

    expr = x + y * 3 - 8 / 2 * 3 - 10
    expr2 = x * 6 / 2 - 1
    print evaluate(expr, x=2, y=5)
    print evaluate(expr2, x=2)

    print e.string()
    print e.desc()
    print

    print x.string()
    print x.desc()
    print

    print (x + 3).string()
    print (x + 3).desc()
    print

    print (3 + x).string()
    print (3 + x).desc()
    print

    print (y * (x + 1)).string()
    print (y * (x + 1)).desc()
    print

    print ((x + 1) * y).string()
    print ((x + 1) * y).desc()
    print

    print (x * y + 3).string()
    print (x * y + 3).desc()
    print

    print (x + y + 3).string()
    print (x + y + 3).desc()
    print

    print ((x + y) + 3).string()
    print ((x + y) + 3).desc()
    print

    print (x + (y + 3)).string()
    print (x + (y + 3)).desc()
    print

    print ((x + y) * (3 + x)).string()
    print ((x + y) * (3 + x)).desc()
    print

    print ((4 + 3 * x) * 3 + 5).string()
    print ((4 + 3 * x) * 3 + 5).desc()
    print

    print derivative(2*x*x+3*x+5, x).string()
    # 2*x*1+(2*1+0*x)*x+(3*1+0*x)+0

import operator

def evaluate(expr, **namedValues):
    return expr.eval(namedValues)

def derivative(expr, variable):
    return Derivative(expr, variable)

class Derivative:
    def __init__(self, expr, variable):
        self.expr = expr
        self.variable = variable

    def string(self):
        return self.expr.derivative()

class Expr:
    def eval(self, values):
        raise NotImplementedError()

    def desc(self):
        raise NotImplementedError()

    def string(self):
        raise NotImplementedError()


class VarExpr(Expr):
    def __init__(self, var):
        self.var = var

    def eval(self, values):
        return values[self.var.getName()]

    def derivative(self):
        return "0"

    def eval(self, values):
        return values[self.var.getName()]

    def desc(self):
        return "VarExpr(" + self.var.desc() + ")"

    def string(self):
        return self.var.getName()


class LiteralExpr(Expr):
    def __init__(self, val):
        self.val = val

    def eval(self, values):
        return self.val

    def desc(self):
        return "LiteralExpr(" + str(self.val) + ")"

    def string(self):
        return str(self.val)

    def derivative(self):
        return "0"


def opToSign(op): #extended this part to consider addition and division operations
    if op == operator.__add__:
        return "+"
    if op == operator.__sub__:
        return "-"
    if op == operator.__mul__:
        return "*"
    if op == operator.__div__:
        return "/"
    raise NotImplementedError()


def opToPrecedence(op): #extended this part to consider addition and division operations
    if op == operator.__add__ or op == operator.__sub__:
        return 0
    if op == operator.__mul__ or op == operator.__div__:
        return 1
    raise NotImplementedError()

class BinaryExpr(Expr):
    def __init__(self, op, lhs, rhs):
        self.op = op
        self.lhs = lhs
        self.rhs = rhs

    def __add__(self, val):
        if isinstance(val, int):
            return BinaryExpr(operator.__add__, self, LiteralExpr(val))
        elif isinstance(val, Var):
            return BinaryExpr(operator.__add__, self, VarExpr(val))
        else:
            return BinaryExpr(operator.__add__, self, val)

    def __radd__(self, val):
        if isinstance(val, int):
            return BinaryExpr(operator.__add__, LiteralExpr(val), self)
        elif isinstance(val, Var):
            return BinaryExpr(operator.__add__, VarExpr(val), self)
        else:
            return BinaryExpr(operator.__add__, val, self)

    #this part was added to support subtraction
    def __sub__(self, val):
        if isinstance(val, int):
            return BinaryExpr(operator.__sub__, self, LiteralExpr(val))
        elif isinstance(val, Var):
            return BinaryExpr(operator.__sub__, self, VarExpr(val))
        else:
            return BinaryExpr(operator.__sub__, self, val)

    def __rsub__(self, val):
        if isinstance(val, int):
            return BinaryExpr(operator.__sub__, VarExpr(val), self)
        elif isinstance(val, Var):
            return BinaryExpr(operator.__sub__, VarExpr(val), self)
        else:
            return BinaryExpr(operator.__sub__, val, self)
    #end of subtraction

    def __mul__(self, val):
        if isinstance(val, int):
            return BinaryExpr(operator.__mul__, self, LiteralExpr(val))
        elif isinstance(val, Var):
            return BinaryExpr(operator.__mul__, self, VarExpr(val))
        else:
            return BinaryExpr(operator.__mul__, self, val)

    def __rmul__(self, val):
        if isinstance(val, int):
            return BinaryExpr(operator.__mul__, LiteralExpr(val), self)
        elif isinstance(val, Var):
            return BinaryExpr(operator.__mul__, VarExpr(val), self)
        else:
            return BinaryExpr(operator.__mul__, val, self)

    #this part was added to support division
    def __div__(self, val):
        if isinstance(val, int):
            return BinaryExpr(operator.__div__, self, LiteralExpr(val))
        elif isinstance(val, Var):
            return BinaryExpr(operator.__div__, self, VarExpr(val))
        else:
            return BinaryExpr(operator.__div__, self, val)

    def __rdiv__(self, val):
        if isinstance(val, int):
            return BinaryExpr(operator.__div__, LiteralExpr(val), self)
        elif isinstance(val, Var):
            return BinaryExpr(operator.__div__, VarExpr(val), self)
        else:
            return BinaryExpr(operator.__div__, val, self)
    #end of division

    def eval(self, values):
        return self.op(self.lhs.eval(values), self.rhs.eval(values))

    def derivative(self, result = ""):
        if isinstance(self.lhs, BinaryExpr):
            result += "(" + self.lhs.derivative(result) + ")"
            self.lhs = result.__str__
        if isinstance(self.rhs, BinaryExpr):
            result += "(" + self.rhs.derivative(result) + ")"

        if (isinstance(self.lhs, VarExpr)) and isinstance(self.rhs, LiteralExpr) and self.op == operator.__mul__:
            result += "1" + "*" + self.rhs.string() + "+" + "0" + "*" + self.lhs.string()

        elif(isinstance(self.lhs, LiteralExpr) and isinstance(self.rhs, VarExpr)) and self.op == operator.__mul__:
            result += "0" + "*" + self.rhs.string() + "+" + self.lhs.string() + "*" + "1"

        elif(isinstance(self.rhs, VarExpr)) and isinstance(self.lhs, VarExpr) and self.op == operator.__mul__:
            result += self.lhs.string() + "+" + self.rhs.string()

        elif(isinstance(self.rhs, LiteralExpr)) and isinstance(self.lhs, LiteralExpr) and self.op == operator.__mul__:
            result += "0" + "+" + "0"

        elif(isinstance(self.rhs, BinaryExpr)) and isinstance(self.lhs, LiteralExpr) and self.op == operator.__mul__:
            result += self.rhs.string() + "*" + self.lhs.string() + "+" + "1"

        elif(isinstance(self.rhs, BinaryExpr)) and isinstance(self.lhs, VarExpr) and self.op == operator.__mul__:
            result += self.rhs.string() + "*" + self.lhs.string()

        elif(isinstance(self.lhs, BinaryExpr)) and isinstance(self.rhs, LiteralExpr) and self.op == operator.__mul__:
            result += self.lhs.string() + "*" + self.rhs.string() + "+" + "1"

        elif(isinstance(self.lhs, BinaryExpr)) and isinstance(self.rhs, VarExpr) and self.op == operator.__mul__:
            result += self.lhs.string() + "*" + self.rhs.string()

        elif(isinstance(self.rhs, VarExpr)) and isinstance(self.lhs, VarExpr) and self.op == operator.__add__:
            result += "1" + "+" + "1"

        elif(isinstance(self.rhs, LiteralExpr)) and isinstance(self.lhs, LiteralExpr) and self.op == operator.__add__:
            result += "0" + "+" + "0"

        elif(isinstance(self.rhs, VarExpr)) and isinstance(self.lhs, LiteralExpr) and self.op == operator.__add__:
            result += "1" + "+" + "0"

        elif(isinstance(self.rhs, LiteralExpr)) and isinstance(self.lhs, VarExpr) and self.op == operator.__add__:
            result += "0" + "+" + "1"

        elif(isinstance(self.rhs, BinaryExpr)) and isinstance(self.lhs, LiteralExpr) and self.op == operator.__add__:
            result += self.rhs.string() + "+" + "0"

        elif(isinstance(self.rhs, BinaryExpr)) and isinstance(self.lhs, VarExpr) and self.op == operator.__add__:
            result += self.rhs.string() + "+" + "1"

        elif(isinstance(self.lhs, BinaryExpr)) and isinstance(self.rhs, LiteralExpr) and self.op == operator.__add__:
            result += "0" + "+" + self.rhs.string()

        elif(isinstance(self.lhs, BinaryExpr)) and isinstance(self.rhs, VarExpr) and self.op == operator.__add__:
            result += "1" + "+" + self.rhs.string()

        return result

    def desc(self):
        return "BinaryExpr(" + self.op.__name__ + "," + self.lhs.desc() + "," + self.rhs.desc() + ")"

    def string(self):
        res = ""
        if (isinstance(self.lhs, BinaryExpr) and
                (opToPrecedence(self.lhs.op) < opToPrecedence(self.op))):
            res += "(" + self.lhs.string() + ")"
        else:
            res += self.lhs.string()
        res += opToSign(self.op)
        if (isinstance(self.rhs, BinaryExpr) and
                (opToPrecedence(self.rhs.op) <= opToPrecedence(self.op))):
            res += "(" + self.rhs.string() + ")"
        else:
            res += self.rhs.string()
        return res


class Var:
    def __init__(self, name):
        self.name = name

    def getName(self):
        return self.name

    def __add__(self, val):
        if isinstance(val, int):
            return BinaryExpr(operator.__add__, VarExpr(self), LiteralExpr(val))
        elif isinstance(val, Var):
            return BinaryExpr(operator.__add__, VarExpr(self), VarExpr(val))
        else:
            return BinaryExpr(operator.__add__, VarExpr(self), val)

    def __radd__(self, val):
        if isinstance(val, int):
            return BinaryExpr(operator.__add__, LiteralExpr(val), VarExpr(self))
        elif isinstance(val, Var):
            return BinaryExpr(operator.__add__, VarExpr(val), VarExpr(self))
        else:
            return BinaryExpr(operator.__add__, val, VarExpr(self))

    #this part was added to support subtraction
    def __sub__(self, val):
        if isinstance(val, int):
            return BinaryExpr(operator.__sub__, VarExpr(self), LiteralExpr(val))
        elif isinstance(val, Var):
            return BinaryExpr(operator.__sub__, VarExpr(self), VarExpr(val))
        else:
            return BinaryExpr(operator.__sub__, VarExpr(self), val)

    def __rsub__(self, val):
        if isinstance(val, int):
            return BinaryExpr(operator.__sub__, LiteralExpr(val), VarExpr(self))
        elif isinstance(val, Var):
            return BinaryExpr(operator.__sub__, VarExpr(val), VarExpr(self))
        else:
            return BinaryExpr(operator.__sub__, val, VarExpr(self))
    #end of subtraction

    def __mul__(self, val):
        if isinstance(val, int):
            return BinaryExpr(operator.__mul__, VarExpr(self), LiteralExpr(val))
        elif isinstance(val, Var):
            return BinaryExpr(operator.__mul__, VarExpr(self), VarExpr(val))
        else:
            return BinaryExpr(operator.__mul__, VarExpr(self), val)

    def __rmul__(self, val):
        if isinstance(val, int):
            return BinaryExpr(operator.__mul__, LiteralExpr(val), VarExpr(self))
        elif isinstance(val, Var):
            return BinaryExpr(operator.__mul__, VarExpr(val), VarExpr(self))
        else:
            return BinaryExpr(operator.__mul__, val, VarExpr(self))

    #this part was added to support division
    def __div__(self, val):
        if isinstance(val, int):
            return BinaryExpr(operator.__div__, VarExpr(self), LiteralExpr(val))
        elif isinstance(val, Var):
            return BinaryExpr(operator.__div__, VarExpr(self), VarExpr(val))
        else:
            return BinaryExpr(operator.__div__, VarExpr(self), val)

    def __rdiv__(self, val):
        if isinstance(val, int):
            return BinaryExpr(operator.__div__, LiteralExpr(val), VarExpr(self))
        elif isinstance(val, Var):
            return BinaryExpr(operator.__div__, VarExpr(val), VarExpr(self))
        else:
            return BinaryExpr(operator.__div__, val, VarExpr(self))
    #end of division

    def eval(self, values):
        return values[self.name]

    def desc(self):
        return "Var(" + self.name + ")"

    def string(self):
        return self.name

if __name__ == '__main__':
    main()