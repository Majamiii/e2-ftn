using Plots
t = (0:0.01:20)
fja = sin.(pi./4 .* t)
y = min.(fja, 0.5)
y = max.(y, 0)
#=f1 = fja .* ((tp .>= 0) .& (tp .< (2/3))) .+ 
      0.5 .* ((tp .>= 2/3) .& (tp .<= (10/3))) .+
      fja .* ((tp .> 10/3) .& (tp .< 4)) .+
      0 .* ((tp .>= 4) .& (tp .<= 8) ) 
=#
plot(t, y)