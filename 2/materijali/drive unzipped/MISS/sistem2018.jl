using ControlSystems, InverseLaplace, LinearAlgebra

G = tf([2], [1, 2])

u_t = 2 * sin(4 * t + 2)