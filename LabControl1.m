%Práctica 1 Laboratorio de Control 

syms t s;

w=0:0.01:20;

r1=1;
r2=1;
c1=1;
c2=1;
kp= 10;


Ent = 1/s;
G = kp * ((1) / (((r1*c1*r2*c2)*s.^2)+((r1*c1+r2*c2+r2*c1)*s)+(1)));
Planta = (kp*G)/(1+(kp*G));
Salida = Planta * Ent;

f1 = ilaplace(Planta, s, t);
v1 = subs(f1, t, w);



hold on
plot(w,v1)
hold off
title('Funcion Tanques Sin Controlador')
grid on 

