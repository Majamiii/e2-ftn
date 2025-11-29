using Plots, DifferentialEquations, LinearAlgebra

#=function signal_f(t)
    t = (0:0.01:20)
    fja = sin.(pi./4 .* t)
    y = min.(fja, 0.5)
    y = max.(y, 0)
    #=f1 = fja .* ((tp .>= 0) .& (tp .< (2/3))) .+ 
          0.5 .* ((tp .>= 2/3) .& (tp .<= (10/3))) .+
          fja .* ((tp .> 10/3) .& (tp .< 4)) .+
          0 .* ((tp .>= 4) .& (tp .<= 8) ) 
    =#
    return f1;
end
=#

function sistem!(dx, x, p, t)
    m1, m2, c, k1, k2, R = p
    f = sin.(pi./4 .* t)
    f = min.(f, 0.5)
    f = max.(f, 0)
    dx[1] = x[2];
    dx[2] = (1 / m1) * (-k2 * (x[3] + x[1]) + f);
    dx[3] = x[4];
    dx[4] = (2 / (m2 * R * R)) * (-c * x[4] 
    * R * R - k1 * x[3] - k2 * R * (x[3] * R + x[1])) 
    return f,t;
end 


#f = signal_f(t);
t = (0.0, 20.0)
p = (10.0, 5.0, 10.0, 10.0, 15.0, 1)
x0 = [0, 0, 0, 0]

prob = ODEProblem(sistem!, x0, t, p)
sol = solve(prob)
ug_pom = [x[3] for x in sol.u]
ug_brz = [x[4] for x in sol.u]
alpha = diff(ug_brz) ./ diff(sol.t)
d_alpha = diff(alpha) ./ diff(sol.t[1:end-1])

m2_poz = [x[1] for x in sol.u]
m2_brz = [x[2] for x in sol.u]

plot(sol.t, [ug_pom, ug_brz,#= alpha, d_alpha,=# m2_brz, m2_poz], 
lw=2, label=["ug_pom" "ug_brz" #= "ug_ubrz" "prom_ubrz" =# "m2_v" "m2_x2"])
plot!(sol.t[1:end-1],alpha, label="ug_ubrz", linestyle=:dash )


vrsta1 = A[1, :]

kolona_end = A[:, end]

nep_vrste = A[1:2:end, :]

pozitivni = A[A .>= 0]
s = sum(pozitivni)
avg= s ./ (size(pozitivni))

el_opseg=A[(A .> -5) .& (A.<5)]
el_opseg = zeros(size(A))
el_opseg[odabrani_opseg]

suma_svake_kolone=sum(A, dims=1)
max_kol=maximum(suma_svake_kolone)
vrste = findall(suma_svake_kolone .== max_kol)