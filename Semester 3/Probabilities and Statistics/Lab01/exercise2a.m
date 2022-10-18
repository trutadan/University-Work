x=0:0.1:3
plot(x, x.*sin(x), 'r--', x, x.^5/100, 'g->', x, cos(x), 'b.');
title("Functions");
legend("x*sin(x)", "x^5/10", "cos(x)");

