% A study is conducted to compare heat loss in glass pipes, versus steel
% pipes of the same size. Various liquids at identical starting
% temperatures are run through segments of each type and the heat loss (in
% celsius) is measured. These data result (normality of the two populations 
% is assumed):
% Steel:
% 4.6 0.7 4.2 1.9 4.8 6.1 4.7 5.5 5.4
% ----------
% Glass:
% 2.5 1.3 2.0 1.8 2.7 3.2 3.0 3.5 3.4
x1 = [4.6 0.7 4.2 1.9 4.8 6.1 4.7 5.5 5.4];
x2 = [2.5 1.3 2.0 1.8 2.7 3.2 3.0 3.5 3.4];

% a. At the 5% significance level, do the population variances seem to differ?
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

% b. At the significance level, does it seem that on average, steel pipes
% lose more heat than glass pipes?
fprintf('b.\n');

% H0: miu1 = miu2
% H1: miu1 > miu2
% => right-tailed test
tail = 1;

% variances unknown but equal
if h == 0
    % stats.tstat = value of the test statistic
    [h, p, ci, stats] = ttest2(x1, x2, alpha, tail, 'equal');

    if h == 0
        fprintf('The null hypothesis is not rejected; steel pipes do not lose more heat than glass pipes!\n');
    else
        fprintf('The null hypothesis is rejected; steel pipes lose more heat than glass pipes!\n');
    end

    degree_of_freedom = length(x1) + length(x2) - 2;
    % quantile
    q = tinv(1 - alpha, degree_of_freedom);
    
    rejection_region = [q, inf];

% variances unknown but unequal
else
    [h, p, ci, stats] = ttest2(x1, x2, alpha, tail, 'unequal');

    if h == 0
        fprintf('The null hypothesis is not rejected; steel pipes do not lose more heat than glass pipes!\n');
    else
        fprintf('The null hypothesis is rejected; steel pipes lose more heat than glass pipes!\n');
    end
    
    degree_of_freedom = length(x1) + length(x2) - 2;
    % quantile
    q = tinv(1 - alpha, degree_of_freedom);
    
    rejection_region = [q, inf];
end

fprintf('The rejection region of the test: (%4.4f, %4.4f)\n', rejection_region);

fprintf('The confidence interval: (%4.4f, %4.4f)\n', ci);
fprintf('The value of the test statistic: %4.4f\n', stats.tstat);
fprintf('The P-value of the test: %4.4f\n\n', p);