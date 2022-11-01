n = input('n = ');
p = input('p = ');

v = 0 : n;

poissonValue = v;
poissonRateParameter = n * p;

plot(v, binopdf(v, n, p), 'r-', v, poisspdf(poissonValue, poissonRateParameter), 'b-');