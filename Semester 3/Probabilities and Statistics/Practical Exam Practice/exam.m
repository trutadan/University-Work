x = [1001.7 975.0 978.3 988.3 978.7 988.9 1000.3 979.2 968.9 983.5 999.2 985.6];
n = length(x);

% a.
fprintf('\na.\n');

confidence_interval_value = input('confidence interval value = ');
while (confidence_interval_value >= 1 || confidence_interval_value <= 0)
    confidence_interval_value = input('confidence interval value (between 0 and 1) = ');
end

% as we know, CI = mean(x) +/- t * (s / square(n))

% we find the mean of the sample
m = mean(x); 

% we find the standard deviation of the sample
s = std(x);

% for our example, for a 95% confidence interval, the alpha should be 0.05
alpha = 1 - confidence_interval_value;

% find the upper and lower confidence bounds for the 95% confidence interval
pLo = alpha/2;
pUp = 1 - alpha/2;

% compute the critical values for the confidence bounds
t = tinv([pLo pUp], n - 1);

% we apply the formula for finding the confidence interval
% determine the confidence interval for the population mean
confidence_interval = m + s/sqrt(n)*t;

fprintf("Confidence interval for the average size: (%4.4f, %4.4f)\n\n", confidence_interval);

% b.
fprintf('b.\n');

alpha = input('significance level alpha = ');
while (alpha >= 1 || alpha <= 0)
    alpha = input('significance level alpha(between 0 and 1) = ');
end

miu0 = 995;
% H0: miu0 = 995
% H1: miu0 > 995
% => right tailed test
tail = 1;

fprintf('It is a right-tailed test.\n');

% h = hypothesis test result
% p = P-value
% ci = confidence interval
% stats.tstat = value of the test statistic
[h, p, ci, stats] = ttest(x, miu0, alpha, tail);

fprintf('The hypothesis test result: %d\n', h);

if h == 0
    fprintf('The null hypothesis is not rejected; on average, the muzzles are not faster than 995 m/s!\n');
else
    fprintf('The null hypothesis is rejected; on average, the muzzles seem to be faster than 995 m/s!\n');
end

degree_of_freedom = length(x) - 1;

% quantile 
q = tinv(1 - alpha, degree_of_freedom);

rejection_region = [q, inf];

fprintf('The rejection region of the test: (%4.4f, %4.4f)\n', rejection_region);

fprintf('The confidence interval for miu0: (%4.4f, %4.4f)\n', ci);
fprintf('The value of the test statistic: %4.4f\n', stats.tstat);
fprintf('The P-value of the test: %4.4f\n\n', p);