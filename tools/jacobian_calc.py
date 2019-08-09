from sympy import sin, cos, Matrix
from sympy.abc import theta, X, Y, v, a, t

# Shamrock motion model
f = Matrix([X + v*cos(theta)*t, Y + v*sin(theta)*t, v + a*t, a, theta])
x = Matrix([X, Y, v, a, theta])

# Shamrock Fk matrix
print(f.jacobian(x))

