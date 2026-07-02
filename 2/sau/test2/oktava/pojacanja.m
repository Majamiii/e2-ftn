pkg load control;

w =1000

argjw = atand(w/40) - 90 - 2*atand(w/10) - atand(w/80)


a = 20*log10(0.5) - 20*log10(w) - 40*log10(w/10) + 20*log10(w/40) - 20*log10(w/80)

s = tf('s');
Wp = (s+3)/s/(s+1)/(s+1);
[pojacanje, faza, wpi, wpf] = margin(Wp);
margin(Wp);grid on;
pojacanje
faza
wpi
wpf
