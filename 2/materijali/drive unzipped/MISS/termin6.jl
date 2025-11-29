using Plots;


function heaviside(t)
    return 1 * (t.>0)
    
end

function ramp(t)
    return t .* heaviside(t);
end

A = 3
T = 1

t = -0.5:0.01:4*T

u = A/T * ramp(t) - A/T * ramp(t .- T) - A * heaviside(t .- 2*T)

plot(t,u, lw=2)