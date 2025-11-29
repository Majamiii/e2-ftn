using Plots;

t = 0:0.1:4;
tp = rem.(t, 2);
y = 5 * tp .* (tp .< 0.5) + (-5 * tp .+ 10) .* ((tp .>= 1) .& (tp .<= 2));
plot(t, y, title="Periodicni signal 1")
xlabel!("t")
ylabel!("y")


t = 0:0.1:10;
tp = rem.(t, 2);
period1 = 5 * tp .* (tp .<= 1) + (-5 * tp .+ 10) .* ((tp .> 1) .& (tp .<= 2));


plot(t, period1, title="Periodicni signal 1:", label="Graf1", lw=1.2, xlabel="Vreme", ylabel="Cena", xticks=0:0.5:10);



t_sin = 0:0.01:6;
ys = abs.(sin.(pi/3 * t));
y = min.(ys, 0.75);

scatter(t, ys, markershape=:cross, markerstrokecolor=:green, color=:blue)
plot!(t, y, lw=2, xlabel="t", ylabel="|sin(t_sin)|", color=:red)