using Plots, LinearAlgebra
using DifferentialEquations

function sistem!(dx, x, p, t)
    m1, m2, c1, c2, c3, k1, k2 = p
    f = signal(t)
    dx[1] = x[2]
    dx[2] = 1 / m1 * (f + c1 * (x[4] - x[2]) - k1 * x[1])
    dx[3] = x[4]
    dx[4] = - 1 / m2 * (c1 * (x[4] - x[2]) + (c2 + c3) * x[4] + k2 * x[3])
end

function signal(t) 
    tp = rem.(t, 5);
    return (4 * tp) .* (tp .< 1) + 4 .* ((tp .>= 1) .& (tp .< 2)) +
    (-2 * tp .+ 8) .* ((tp .>= 2) .& (tp .< 3)) + 2 .* ((tp .>= 3) .& (tp .< 4)) +
    (-2 * tp .+ 10) .* (tp .>= 4)
end

t = (0.0,10.0)
p = (10.0, 15.0, 20.0, 20.0, 20.0, 40.0, 40.0)
x0 = [0.0, 0.0, 0.0, 0.0]
prob = ODEProblem(sistem!, x0, t, p)
sol = solve(prob)
x1 = [el[1] for el in sol.u]
x2 = [el[2] for el in sol.u]
~, i = findmax(abs.(x1));
plot(sol.t, x1, label="brz1")
plot!(sol.t, x2, label="ubrz1")
scatter!([sol.t[i]], [x1[i]], )
a = diff(x2) ./ diff(sol.t);
plot!(sol.t[2:end], a)
pp = sum(abs.(diff(x1)))

x1[sol.t .< 5];
plot!(sol.t[sol.t .< 5], x1[sol.t .< 5])

pp = sum(abs.(diff(x1[sol.t .< 5])))
