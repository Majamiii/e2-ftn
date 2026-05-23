function dxdt = sistem(t, x, w, m, g, kt, c2, D, c)
  dxdt = zeros(2, 1);
  dxdt(1) = x(2);
  dxdt(2) = kt*c2*D^4/(2*pi*m)*w*sqrt((w/(2*pi))^2 + 0.001) - c/m*x(2) - g;
end

