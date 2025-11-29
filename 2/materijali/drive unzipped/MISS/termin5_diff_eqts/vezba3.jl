using Plots, DifferentialEquations;

function jna!(dx, x, p, t)
    
    f = sin(t);
    m, c1, c2, k1, _, g = p

    dx[1] = x[2];
    dx[2] = (1 / m) * (m * g - c1 * x[2] - k1 * (2*x[1] - x[3]));
    dx[3] = (1 / ( 9 * c2)) * (-3 * f + k1 * (x[1]-x[3]));

end




t = (0.00, 100.00)
x0 = [-1, 0, 0]
p = (10.0, 10.0, 10.0, 15.0, 10.0, 9.81)

probl = ODEProblem(jna!, x0, t, p)
sol = solve(probl)

theta = [x[1] for x in sol.u]
omega = [x[3] for x in sol.u] 
v = [x[2] for x in sol.u]
ubrzanje = diff(omega) ./ diff(sol.t)

plot(sol.t, [theta, omega],lw=[1.5,1.99], label=["x1(t)" "x2(t)"])
#plot!(sol.t[1:end-1], ubrzanje, ls=:dash, label = "ubrzanje")
plot!(sol.t[sol.t .<= 20], v[sol.t .<= 20], lw = 2, ls=:dash, label="v(t)", yticks=-1:1:6 )