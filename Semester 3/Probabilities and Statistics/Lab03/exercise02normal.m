p = input('p = ');

for n = 1 : 5 : 100
    v = 0 : n;

    mu = n * p;
    sigma = sqrt(n * p * (1 - p));

    plot(v, binopdf(v, n, p), 'r-', v, normcdf(v, mu, sigma), 'b-');
    
    pause(1);
end
