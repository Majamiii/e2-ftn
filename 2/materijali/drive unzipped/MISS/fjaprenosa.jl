using ControlSystems, Plots
function sistem()
G1 = tf(10, [1, 10])
G2 = tf([5, 2], [1, 2, 1, 0])
G3 = tf(5)
G4 = tf([1, 0.1], [1, 0.05])
# W11 -> U1, Y
G34 = minreal(series(G3, G4))
G234 = minreal(feedback(G2, G34))
W11 = minreal(parallel(-G1, G234))
# W12 -> U2, Y
G24 = minreal(series(-G2, G4))
W12 = minreal(feedback(G24, -G3))
return W11, W12
end
t = 0:0.01:5
u = sin.(t)
u2 = cos.(t)
W11, W12 = sistem()
y1, ~, ~ = lsim(W11, u', t)
y2, ~, ~ = lsim(W12, u2', t)
y = y1 .+ y2
plot(t, [y', u, u2], label=["y(t)" "u1(t)" "u2(t)"], xlabel="t", lw=2)