clear

alpha = input ('significance level alpha = ');
while (alpha >= 1 || alpha <= 0)
    alpha = input('significance level alpha in (0,1) = ');
end

x1 = [22.4 21.7 24.5 23.4 21.6 23.3 22.4 21.6 24.8 20.0];
x2 = [17.7 14.8 19.6 19.6 12.1 14.8 15.4 12.6 14.0 12.2];

n1 = length(x1);
n2 = length(x2);

fprintf('a. At the 5 percent significance level, ');
fprintf('\nis there evidence that the variances of the two populations are equal?\n\n');

m1 = mean(x1); 
m2 = mean(x2);

v1 = var(x1); 
v2 = var(x2);

% quantiles for two-tailed test (for rejection region)
f1 = finv(alpha/2, n1 - 1, n2 - 1);
f2 = finv(1 - alpha/2, n1 - 1, n2 - 1); 

% The null hypothesis H0: sigma1**2 = sigma2**2
% The alternative hypothesis H1: sigma1**2 ~= sigma2**2
% Two-tailed for comparing the variances.
[H, P, CI, stats] = vartest2(x1, x2, alpha);

fprintf('Comparing variances by using two-tailed test:\n');

if H == 0
    fprintf('H = %d\n', H);
    fprintf('The null hypothesis is not rejected! (the variances are equal)\n\n');
    fprintf('The rejection region for F is (%.2f, %.2f) U (%.2f, %.2f).\n', -inf, f1, f2, inf);
    fprintf('The value of the test statistic F is %.2f.\n', stats.fstat);
    fprintf('The P-value for the variances test is %.2f.\n\n', P);
else
    fprintf('H = %d\n', H);
    fprintf('The null hypothesis is rejected! (the variances are different)\n');
    fprintf('The rejection region for F is (%.2f, %.2f)U(%.2f, %.2f).\n', -inf, f1, f2, inf);
    fprintf('The value of the test statistic F is %.2f.\n', stats.fstat);
    fprintf('The P-value for the variances test is %.2f.\n\n', P);
end
% For this example, the answer is to NOT reject H0 => the population variances are equal.
   

fprintf('b. Based on the result in part a., at the same significance level, ');
fprintf('\ndoes gas mileage seem to be higher, on average, when premium gasoline is used?\n\n');
% The null hypothesis H0: mu1 = mu2
% The alternative hypothesis H1: mu1 > mu2
% Right-tailed for the difference of means.

n = n1 - 1 + n2 - 1;
% quantile for right-tailed test (for rejection region)
t2 = tinv(1 - alpha, n); 

[h2, p2, ci2, stats2] = ttest2(x1, x2, alpha, 1);

fprintf('\nRight-tailed test for the difference of means.\n')
fprintf('h2 = %d\n', h2)

if h2 == 1
    fprintf('The null hypothesis is rejected! (gas mileage is higher with premium gasoline)\n');
else
    fprintf('The null hypothesis is not rejected! (gas mileage is not higher with premium gasoline)\n');
end

fprintf('The rejection region for T is (%.2f, %.2f).\n', t2, inf);
fprintf('The value of the test statistic T is %.2f.\n', stats2.tstat);
fprintf('The P-value of the test for diff. of means is %e.\n', p2);
