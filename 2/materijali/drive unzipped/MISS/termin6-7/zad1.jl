using ControlSystems, Plots

G = tf([1], [1,1])

y, t, x = step(G, 10)

plot(t, y')