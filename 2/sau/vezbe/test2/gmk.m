clc
clear
close all

pkg load control

%% zad 1

s = tf('s');

W = 1/(s*(s+2)*(s+3));

% rltool(W);
rlocus(W);
controlSystemDesigner("rlocus",W);

%%

s = tf('s');

W = (s+2)/((s+1)*(s^2+6*s+10));

rlocus(W);
rltool(W);

%%

s = tf('s');

W = 1/(s*(s^2+4*s+8));

rlocus(W);
rltool(W)

%%

s = tf('s');

W = (s+3)/((s-1)^2*(s+1)^2);

rlocus(W);
rltool(W);

%%
s = tf('s');


W = (s-1)^2/((s+1)^2*(s+3));

rlocus(W);
rltool(W);

