using LinearAlgebra, Plots;

t = 0:0.04:6;

y1 = abs.(sin.(pi/3 * t));

period = rem.(t, 3);
p = 1/3 * period;
y = min.(y1, p);

scatter!(t, y1, markershape=:o, markerstrokecolor=:green, color=:yellow, label = "ys")
plot!(t, y, lw=2, xlabel="t", ylabel="|sin|", color=:blue, label = "y", xticks=0:1:6)