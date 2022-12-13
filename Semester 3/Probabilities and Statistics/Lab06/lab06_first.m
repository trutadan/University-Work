clear

alpha = input('significance level alpha = ');
while (alpha >= 1 || alpha <= 0)
    alpha = input('significance level alpha(between 0 and 1) = ');
end

x = [7, 7, 4, 5, 9, 9, 4, 12, 8, 1, 8, 7, 3, 13, 2, 1, 17, 7, 12, 5, 6, 2, 1, 13, 14, 10, 2, 4, 9, 11, 3, 5, 12, 6, 10, 7];
n = length(x);

fprintf('a. Assuming that past experience indicates that σ = 5, at the 5 percent significance level, \n');
fprintf('does the data suggest that the standard is met? What about at 1 percent?\n\n');
% a)
% The null hypothesis H0: mu = 9;
% The alternative hypothesis H1: mu < 9 => left-tailed test for mu.

sigma = 5;

% m0 = theta0
m0 = input('test value m0 = '); 
% m0 in this case will be 9

% -1 is for left-tailed, 0 for two-tailed (default), 1 for right-tailed
[H, P, CI, zval] = ztest(x, m0, sigma, alpha, -1);

fprintf('\nH = %d\n', H);

% result of the test:
% h = 0, if H0 is NOT rejected,
% h = 1, if H0 is rejected
if H == 1 
    fprintf('The null hypothesis is rejected!\n');
else
    fprintf('The null hypothesis is not rejected!\n');
end

z2 = norminv(alpha);
% rejection region for left-tailed test
RR = [-inf, z2];

fprintf('\nThe confidence interval for mu is (%.2f, %.2f).\n', CI);
fprintf('The rejection region is (%.2f, %.2f).\n', RR);
fprintf('The value of the test statistic z is %.2f.\n', zval);
fprintf('The P-value of the test is %.2f.\n\n', P);

fprintf('b. Without the assumption on σ, does the data suggest that, on average, \n');
fprintf('the number of files stored exceeds 5.5? (same significance level)\n\n');
% b)
% The null hypothesis H0: mu = 5.5;
% The alternative hypothesis H1: mu > 5.5 => right-tailed test for mu.

fprintf('Right-tailed test for the mean(sigma unknown): \n')

m0b = input('\ntest value m0 = ');
% m0 is in this case 5.5.
[H, P, CI, stats] = ttest(x, m0b, alpha, 1);

fprintf('\nH is %d\n', H);

% quantile for right-tailed test
t1 = tinv(1 - alpha, n - 1);

% rejection region for right-tailed test
RR = [t1, Inf]; 

if H==1
    fprintf('The null hypothesis is rejected! (the average exceeds 5.5)\n\n');
else
    fprintf('The null hypothesis is not rejected! (the average does not exceed 5.5)\n\n');
end    

fprintf('The confidence interval for mu is (%.2f,%.2f).\n', CI);
fprintf('The rejection region is (%.2f,%.2f).\n', RR);
fprintf('The value of the test statistic t is %.2f.\n', stats.tstat);
fprintf('The P-value of the test is %.2f.\n\n', P);

