pkg load symbolic
pkg load control
pkg load signal

syms s t

G = 2/(s+2);
u_t = 2 * sin(4 * t + 2)
u_s = ilaplace(sym()
