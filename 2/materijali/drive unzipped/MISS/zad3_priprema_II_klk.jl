using ControlSystems, LinearAlgebra, Plots

function prenos_U1()
    g12 = g1 * g2
    g34 = g3 * g4

    Gfb = feedback(1, -g12 * g34)

    return minreal(Gfb * g1), minreal(Gfb * -g12 * g4), minreal(Gfb * (-g12 * g34))
end

function prenos_U2()
    g12 = g1 * g2
    g34 = g3 * g4

    Gfb = feedback(1, -g12 * g34)

    return minreal(Gfb * g34 * g1), minreal(Gfb * g4), minreal(Gfb * (-g34))
end

g1 = tf([1,-1.0], [1, 0, 1])
g2 = tf([1], [1, 2.0])
g3 = tf([1.0], [1, 0])
g4 = tf([1, 0, 3], [1, 0, 4.0, 0])

W11, W21, W31 = prenos_U1();
W12, W22, W32 = prenos_U2();

W = minreal([W11 W12
            W21 W22
            W31 W32])

t = 0:0.001:30

Ulaz1 = cos.(2 .* t)
Ulaz2 = 4 .* exp.(-2 .* t) .+ 1

y11, ~, ~ = lsim(W11, Ulaz1', t)
y21, ~, ~ = lsim(W21, Ulaz1', t)
y31, ~, ~ = lsim(W31, Ulaz1', t)
y12, ~, ~ = lsim(W12, Ulaz2', t)
y22, ~, ~ = lsim(W22, Ulaz2', t)
y32, ~, ~ = lsim(W32, Ulaz2', t)

y1 = y11 .+ y12
y2 = y21 .+ y22
y3 = y31 .+ y32

plot(t, [y1', y2', y3', Ulaz1, Ulaz2], label=["y1(t)" "y2(t)" "y3(t)" "u1(t)" "u2(t)"], xlabel="t", lw=2)