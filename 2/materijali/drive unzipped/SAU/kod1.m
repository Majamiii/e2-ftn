pkg load symbolic;

syms s t;

sistem = 0.1/(s*s + 0.05*s + 0.1);
u_t = heaviside(t);
u_s = laplace(u_t);
y_t = ilaplace(u_s * sistem);
y_t = simplify(simplify(y_t))

assume t clear;
t = 0:0.01:70;










