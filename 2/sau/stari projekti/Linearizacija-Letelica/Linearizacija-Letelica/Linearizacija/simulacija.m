clear all
clear sqrt
clc
pkg load control

% Parametri modela
m = 1.8;
g = 3.71;
c = 1.8;
D = 1.2;
c2 = 0.02;
kt = 0.05;

% M.R.T.
x10 = 5;
x20 = 0;

a = (g*m/(kt*c2*D^4))^2;

delta = (-1e-3 + sqrt(1e-6 + 4*a)) / 2;


w0 = 2*pi*sqrt(delta);

w = w0+1; % malo se pomerimo iz radne tačke
x0 = [x10; x20];
tspan = [0 50];

% Nelinearni sistem
f = @(t,x) sistem(t,x,w,m,g,kt,c2,D,c);
[t, x] = ode45(f, tspan, x0);

% Linearizovani model
A = [0 1; 0 -c/m];

freq = (w0/(2*pi))^2 + 0.001;
sqrt_freq = sqrt(freq);

B = [0;
     kt*c2*D^4 / (2*pi*m) * (sqrt_freq + w0^2 / (4*pi^2*sqrt_freq))];

C = [1 0;0  1];
D_lin = 0;

sys = ss(A, B, C, D_lin);

dw = w - w0;
t_lin = 0:0.001:50;
w_lin = dw * ones(size(t_lin));

[y_lin, t_out, x_lin] = lsim(sys, w_lin, t_lin, [0; 0]);

% Poređenje brzina
x2_nelin = x(:,2);
x2_lin = x_lin(:,2) + x20;

figure;
plot(t, x2_nelin, 'r', 'LineWidth', 1);
hold on
plot(t_out, x2_lin, 'b--', 'LineWidth', 1);
xlabel('vreme (s)');
ylabel('brzina x_2');
title('Poređenje brzine nelinearnog i linearizovanog modela');
legend('Nelinearni model', 'Linearizovani model');
grid on;

