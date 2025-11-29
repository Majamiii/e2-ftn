using LinearAlgebra, Plots;
t = 0:0.1:6;

y1 = abs.(sin.(pi/3 * t));

p = 1/6 * t;

y = min.(y1, p);

scatter(t, y1, markershape=:o, markerstrokecolor=:green, color=:yellow, label="y1");
plot!(t, y, xlabel="t", lw = 2, ylabel="|sin|", color=:cyan, label=:"y")