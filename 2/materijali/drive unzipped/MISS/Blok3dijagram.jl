using ControlSystems, DifferentialEquations, LinearAlgebra, Plots


function gornja_grana!(dx, x, t, p)
    r = signal.(t);
    e = r - 0.5 * x[1]
    q = x[3] * x[3]


    dx[1] = x[2]
    dx[2] = q - x[1] - 4 * x[1] * x[2] ^ 2
    dx[3] = 4 * r - 2 * x[1] - x[3]

end

function signal(t)
    tp = rem.(t, 2);
    return 2.5 .* tp .* (tp .<= 1)
end

t = (0.0,10.0);

x0 = [-1 1 0];
p = 0
problem = ODEProblem(gornja_grana!, x0, t, p)

sol = solve(problem)
y = [x[1] for x in sol.u]
y1 = [x[2] for x in sol.u]
plot(sol.t, y)