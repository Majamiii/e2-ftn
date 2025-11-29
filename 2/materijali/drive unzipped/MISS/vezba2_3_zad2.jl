t = 0:0.01:(2*pi);

tp = rem.(t, pi/3);

p = sin.(t);

signal1 = p;
signal2 = 0;

y = signal1 .* (tp .<= pi/6) + signal2 .* ((tp .> pi/6) .& (tp .<= pi/3));

plot(t, p, color=:green, ls=:dash, xlabel="t", ylabel="sin(t) sa prekidima:", xticks = 0:pi:2*pi, yticks = -1:0.5:1)
plot!(t, y, color=:magenta, lw = 1.99)