% In a study of the size of various computer systems, the random variable
% X, the number of files stored (in hundreds of thousands), is considered.
% If a computer system cannot store at least 9, on average, it does not
% meet the efficiency standard and has to be replaced. These data are
% obtained:
% 7 7 4 5 9 9
% 4 12 8 1 8 7
% 3 13 2 1 17 7
% 12 5 6 2 1 13
% 14 10 2 4 9 11
% 3 5 12 6 10 7
x = [7 7 4 5 9 9 4 12 8 1 8 7 3 13 2 1 17 7 12 5 6 2 1 13 14 10 2 4 9 11 3 5 12 6 10 7];

% a. Assuming that past experience indicates that sigma = 5, at the 5%
% significance level, does the data suggest that the standard is met? What
% about at 1%?
fprintf('\na.\n');

sigma = 5;

alpha = input('significance level alpha = ');
while (alpha >= 1 || alpha <= 0)
    alpha = input('significance level alpha(between 0 and 1) = ');
end

miu0 = 9;
% H0: miu0 = 9
% H1: miu0 < 9
% => left-tailed test

% tail values: -1 -> left tailed 
%               0 -> default, two-tailed
%               1 -> right tailed
tail = -1;

% h = hypothesis test result
% p = P-value
% ci = confidence interval
% zstat = value of test statistic
[h, p, ci, zstat] = ztest(x, miu0, sigma, alpha, tail);

if h == 0
    fprintf('The null hypothesis is not rejected; the standard is met!\n');
else
    fprintf('The null hypothesis is rejected; the standard is not met!\n');
end

% quantile
q = norminv(alpha);

rejection_region = [-inf, q];

fprintf('The rejection region of the test: (%4.4f, %4.4f)\n', rejection_region);

fprintf('The confidence interval for miu0: (%4.4f, %4.4f)', ci);
fprintf('The value of the test statistic: %4.4f\n', zstat);
fprintf('The P-value of the test: %4.4f\n\n', p);

% b. Without the assumption on sigma, does the data suggest that, on average,
% the number of files stored exceeds 5.5? (same significance level)
fprintf('b.\n');

miu0 = 5.5;
% H0: miu0 = 5.5
% H1: miu0 > 5.5
% => right-tailed test
tail = 1;

% stats.tstat = value of the test statistic
[h, p, ci, stats] = ttest(x, miu0, alpha, tail);
if h == 0
    fprintf('The null hypothesis is not rejected; the number of files stored do not exceed 5.5!\n');
else
    fprintf('The null hypothesis is rejected; the number of files stored exceeds 5.5!\n');
end

% quantile 
degree_of_freedom = length(x) - 1;
q = tinv(1 - alpha, degree_of_freedom);

rejection_region = [q, inf];

fprintf('The rejection region of the test: (%4.4f, %4.4f)\n', rejection_region);

fprintf('The confidence interval for miu0: (%4.4f, %4.4f)', ci);
fprintf('The value of the test statistic: %4.4f\n', stats.tstat);
fprintf('The P-value of the test: %4.4f\n\n', p);
