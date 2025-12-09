using Plots;
using DifferentialEquations;

function sistem(dx,x,p,t)
    m1,m2,c,k1,k2,k3,g = p;

    dx[1] = x[2]
    dx[2] = k2 * x[3]/m1 - (k1 + k2) * x[1]/m1 + g
    dx[3] = x[4]
    dx[4] = k2 * x[1]/m2 - c * x[4]/m2 - (k2 + k3) * x[3]/m2 - g
end

# obicne zagrade su za immutable vrednosti

t=(0.0, 20.0)
p = (5.0,8.0,10.0,20.0,20.0,20.0,9.81)
x0 = [2.0,0.0,0.0,0.0]

prob = ODEProblem(sistem,x0,t,p)
sol = solve(prob)

plot(sol)
savefig("sistem_1.png")