using Plots, DifferentialEquations;

function sistem!(dx, x, p, t)
    m1, m2, c, k1, k2, R, g = p
J = 1 / 2 * m1 * R *R
f = signal(t)   
dx[1] = x[2]
dx[2] = (-1 / J) * (k2 * (x[3] + R * x[1]) * R + c * R*R * x[2])
dx[3] = x[4]
dx[4] = (1 / m2) * (m2 * g - f - k1 * x[3] - k2 * (x[3] + R * x[1]))
end

#=function signal(t)
    tp = rem.(t,3);
    
    f1 = 5.00 .* ((tp .> 0) .& (tp .<= 2)) .+ 0 .* ((tp .> 2) .& (tp <= 3));
    
    f2 = max.(f1, 5/15.0 .* t .+ 5.0);

end
=#

function signal(t)
    tp = rem.(t, 3)
    y = (-1 / 3 * t .+ 5) .* (tp .< 2)
end



t = (0.00, 15.0);
p = (10.0, 5.0, 10.00, 15.0, 10.00, 1.0, 9.81);
x0 = [0.0, 0.0, 0.0, 0.0];

problem = ODEProblem(sistem!, x0, t, p);
sol = solve(problem);

x = [x[3] for x in sol.u]
d = sum(abs.(diff(x)))
println(d)
theta = [x[1] for x in sol.u]
omega = [x[2] for x in sol.u]
alpha  = diff(omega) ./ diff(sol.t)
a = findmax(sol.u)

plot(sol.t, [theta, omega], lw=[1.5, 1.99], label=["theta(t)" "omega(t)"])
#plot!(sol.t[1:end-1], alpha, lw=2, label="alpha(t)")