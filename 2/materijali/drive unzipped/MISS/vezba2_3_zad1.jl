t = 0:0.1:10;
tp = rem.(t,5);

sekcija1 = 2 * tp;
sekcija2 = 2;
sekcija3 = -2 * tp .+ 10;

y = sekcija1 .* (tp .<= 2) + sekcija2 .* ((tp .> 2) .& (tp .<= 4)) + sekcija3 .* ((tp .> 4) .& (tp .<= 5));

plot(t, y, lw=1.3, xlabel="Vreme", ylabel="vredost f-je", xticks=0:1:10)