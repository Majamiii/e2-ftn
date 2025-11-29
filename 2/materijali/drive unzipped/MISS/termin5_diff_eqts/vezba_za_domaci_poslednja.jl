using DifferentialEquations, Plots, LinearAlgebra;

function signal(t)
    tp = rem.(t, 2);
    f1 = sqrt.(1 .- (tp .- 1) .^ 2);
    f2 = (2 .* tp) .* ((tp .<= 1) .& (tp .>= 0)) .+ (-2 * tp .+ 4) .* ((tp .> 1) .& (tp .< 2)); 
    f3 = min.(f1, f2)

    return f3;
end


function sistem!(dx, x, p, t)
    
    f = signal(t);

    m, c1, c2, k1, k2, R, L1, L2 = p


    dx[1] = x[2];
    dx[2] = (2 / (m * R * R)) * 
    (-c1 * x[2] * R * R - k1 * x[1] - k2 * R * (x[1] * R + x[3] * L1));
    dx[3] = (1 / (L2*L2*c2)) * (L1 * f - L1 * k2 * (x[1] * R + x[3] * L1));


end;

#telo

t = (0.00, 100.00);
p = (10.0, 10.0, 8.0, 10.0, 15.0, 1.0, 1.0, 2.0);
x0 = [0.0, 0.0, 0.0, 0.0];

prob = ODEProblem(sistem!, x0, t, p);
sol = solve(prob);

theta1 = [x[1] for x in sol.u];
omega1 = [x[3] for x in sol.u]
plot(sol.t, [theta1, (omega1)])
alpha1 = diff(omega1) ./ diff(sol.t)
_, i = findmax(abs.(alpha1))
plot!(sol.t[1:end-1], alpha1, lw=2)
plot!([sol.t[i]], [sol.u[i]], markershape=:o)


###    jna kruznice sqrt(1-(x-1)^2)