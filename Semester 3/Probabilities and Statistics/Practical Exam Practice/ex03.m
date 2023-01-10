% Nickel powders are used in coatings used to shield electronic equipment.
% A random sample is selected and the sizes of nickel particles in each
% coating are recorded (they are assumed to be approximately normally
% distributed):
% 3.26, 1.89, 2.42, 2.03, 3.07, 2.95, 1.39, 3.06, 2.46, 3.35, 1.56, 1.79,
% 3.82, 2.42, 2.96
x = [3.26, 1.89, 2.42, 2.03, 3.07, 2.95, 1.39, 3.06, 2.46, 3.35, 1.56, 1.79, 3.82, 2.42, 2.96];
n = length(x);

% a. Find a 95% confidence interval for the average size of nickel particles.
confidence_interval_value = input('confidence interval value = ');
while (confidence_interval_value >= 1 || confidence_interval_value <= 0)
    confidence_interval_value = input('confidence interval value (between 0 and 1) = ');
end

alpha = 1 - confidence_interval_value;

t = tinv(1 - alpha/2, n - 1);

m = mean(x); 
s = std(x);

left_limit = m - s/sqrt(n)*t;
right_limit = m + s/sqrt(n)*t;

confidence_interval = [left_limit, right_limit];

fprintf("Confidence interval for the average size: (%4.4f, %4.4f)\n\n", left_limit, right_limit);

% b. At the 1% significance level, on average, do these nickel particles
% seem to be smaller than 3?
fprintf('b.\n');

alpha = input('significance level alpha = ');
while (alpha >= 1 || alpha <= 0)
    alpha = input('significance level alpha(between 0 and 1) = ');
end

miu0 = 3;
% H0: miu0 = 3
% H1: miu0 < 3
% => left-tailed test
tail = -1;

% stats.tstat = value of the test statistic
[h, p, ci, stats] = ttest(x, miu0, alpha, tail);
if h == 0
    fprintf('The null hypothesis is not rejected; the nickel particles seem to be equal to 3!\n');
else
    fprintf('The null hypothesis is rejected; the nickel particles seem to be smaller than 3!\n');
end

% quantile 
degree_of_freedom = length(x) - 1;
q = tinv(1 - alpha, degree_of_freedom);

rejection_region = [-inf, q];

fprintf('The rejection region of the test: (%4.4f, %4.4f)\n', rejection_region);

fprintf('The confidence interval for miu0: (%4.4f, %4.4f)\n', ci);
fprintf('The value of the test statistic: %4.4f\n', stats.tstat);
fprintf('The P-value of the test: %4.4f\n\n', p);