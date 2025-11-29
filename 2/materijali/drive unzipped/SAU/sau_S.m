clf;
W = zpk([1,2],[-1,-2,-3],1);
 sys = W;
 t = 0:0.01:10;
 u = zeros (length(t) ,1)
 x0 = [0 0 0];
 lsim(sys, u, t, x0);
