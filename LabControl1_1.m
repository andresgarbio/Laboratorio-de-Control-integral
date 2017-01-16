%Práctica 1 Laboratorio de Control 

%num y den vectores con los coeficientes del numeradory denominador de la planta
num = [1];
den = [1 3 1];
rlocus(num,den)
v= [-6 0 -6 6];
axis(v); axis('square')
grid;
title('Lugar de las Raíces del sistema de tanques')


