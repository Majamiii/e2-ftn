using ControlSystems

g1 = tf([1.0], [1.0, 3.4])
g2 = tf([2.0, 1.1], [1,2,2])
g3 = tf([1], [1,2,0])
g4 = tf([1], [1, 1.5])
g5 = tf([7.], [1])
g6 = tf([2.2],[1])

g12f = feedback(g1*g2, 1)
g34 = g3 * g4
g34f = feedback(g34,1)
h1 = feedback(g12f, 1/g4 * g34f * g5)
W11 = minreal(h1)
W12 = minreal(series(h1, g5 * g34f))

######################### W2x

W22 = minreal(feedback(g34f, 1/g4 * g12f * g5))
W21 = minreal(series(W22, g12f))

W = [W11 W12
     W21 W22]

function u1(t)
    tp = rem.(t, 40)
    return 5 .* ((tp .> 10) .& (tp .< 40)) 
end

function u2!(t)
    tp = rem.(t, 40)
    return 1/4 .* tp .* (tp .< 20) .+ (-1/4 .* tp .+ 10) .* ((tp .>= 20) .& (tp .< 40))
end
t = 0:0.01:10
U = [u1(t)' u2!(t)']
Y = U' .* W

y1, ~, ~ = lsim(W11, (u1(t))', t)
y2, ~, ~ = lsim(W12, (u2!(t))', t)
y3, ~, ~ = lsim(W21, (u2!(t))', t)
y4, ~, ~ = lsim(W22, (u1(t))', t)



plot(t, [y1'])
plot!(t, [y2'])
plot!(t, [y3'])
plot!(t, [y4'])