% To reach the maximum efficiency in performing an assembling operation in
% a mnufacturing plant, new employees are required to take a 1-month
% training course. A new method was suggested, and the manager wants to
% compare the new method with the standard one, by looking at the lengths
% of time required for employees to assemble a certain device. They are
% given below (and assumed approximately normally distributed):
% Standard:
% 46 37 39 48 47 44 35 31 44 37
% -----------------------------
% New:
% 35 33 31 35 34 30 27 32 31 31
x1 = [46 37 39 48 47 44 35 31 44 37];
x2 = [35 33 31 35 34 30 27 32 31 31];

% a. At the 5% significance level, do the population variances seem to
% differ?
fprintf('\na.\n');

alpha = input('significance level alpha = ');
while (alpha >= 1 || alpha <= 0)
    alpha = input('significance level alpha(between 0 and 1) = ');
end

% H0: sigma1^2  = sigma2^2
% H1: sigma1^2 != sigma2^2
% => two-tailed test

% tail values: -1 -> left tailed 
%               0 -> default, two-tailed
%               1 -> right tailed
tail = 0;

% h = hypothesis test result
% p = P-value
% ci = confidence interval
% stats.fstat = value of test statistic
[h, p, ci, stats] = vartest2(x1, x2, alpha, tail);

if h == 0
    fprintf('The null hypothesis is not rejected; the variances are equal!\n');
else
    fprintf('The null hypothesis is rejected; the variances are not equal!\n');
end

degree_of_freedom1 = length(x1) - 1;
degree_of_freedom2 = length(x2) - 1;
% quantiles
q1 = finv(alpha/2, degree_of_freedom1, degree_of_freedom2);
q2 = finv(1 - alpha/2, degree_of_freedom1, degree_of_freedom2);

left_rejection_region = [-inf, q1];
right_rejection_region = [q2, inf];

fprintf('The rejection region of the test: (%4.4f, %4.4f) U (%4.4f, %4.4f)\n', left_rejection_region, right_rejection_region);

fprintf('The confidence interval: (%4.4f, %4.4f)\n', ci);
fprintf('The value of the test statistic: %4.4f\n', stats.fstat);
fprintf('The P-value of the test: %4.4f\n\n', p);

% b. Find a 95% confidence interval for the difference of the average
% assembling times.
fprintf('b.\n');

n1 = length(x1);
n2 = length(x2);

m1 = mean(x1);
m2 = mean(x2);

v1 = var(x1);
v2 = var(x2);

if  h == 0
    n = n1 + n2 - 2;

    t = inv(1 - alpha/2, n);

    rad = sqrt(1/n1 + 1/n2);
    sp = sqrt(((n1 - 1) * v1 + (n2 - 1) * v2)/n);

    li = m1 - m2 - t * sp * rad;
    ri = m1 - m2 + t * sp * rad;
else 
    c = (v1/n1) / (v1/n1 + v2/n2);
    n = 1/(c^2/(n1 - 1) + (1 - c)^2/(n2 - 1));

    t = tinv(1 - alpha/2, n);
    rad = sqrt(v1/n1 + v2/n2);

    li = m1 - m2 - t * rad;
    ri = m1 - m2 + t * rad;
end

fprintf('Confidence interval for the difference of the means: (%4.4f, %4.4f)\n\n', li, ri);