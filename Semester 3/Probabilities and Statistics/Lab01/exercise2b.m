x=0:0.1:3;
subplot(3, 1, 1);
plot(x, x.*sin(x), 'r--');
subplot(3, 1, 2);
plot(x, x.^5/100), 'g->';
subplot(3, 1, 3);
plot(x, cos(x), 'b.');