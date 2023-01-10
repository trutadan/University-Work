% A food store owner receives 1-liter water bottles from two suppliers.
% After some complaints from customers, he wants to check the accuracy of
% the weights of 1-liter water bottles. He finds the following weights (the
% two populations are approximately normally distributed):
% Supplier A
% 1021 980 1017 988 1005 998 1014 985 995 1004 1030 1015 995 1023
% ------------------------------------------------------------------------
% Supplier B
% 1070 970 993 1013 1006 1002 1014 997 1002 1010 975
x1 = [1021 980 1017 988 1005 998 1014 985 995 1004 1030 1015 995 1023];
x2 = [1070 970 993 1013 1006 1002 1014 997 1002 1010 975];

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

fprintf('The confidence interval: (%4.4f, %4.4f)', ci);
fprintf('The value of the test statistic: %4.4f\n', stats.fstat);
fprintf('The P-value of the test: %4.4f\n\n', p);

% b. At the same significance level, on average, does Supplier A seem to be
% more reliable?
fprintf('b.\n');

% H0: miu1 = miu2
% H1: miu1 > miu2
% => right-tailed test
tail = 1;

% equal variances
if h == 0
    % stats.tstat = value of test statistic
    [h, p, ci, stats] = ttest2(x1, x2, alpha, tail, 'equal');

    if h == 0
        fprintf('The null hypothesis is not rejected; Supplier A does not seem to be more reliable!\n');
    else
        fprintf('The null hypothesis is rejected; Supplier A seem to be more reliable!\n');
    end

    degree_of_freedom = length(x1) + length(x2) - 2;
    % quantile
    q = tinv(1 - alpha, degree_of_freedom);
    
    rejection_region = [q, inf];
    
    fprintf('The rejection region of the test: (%4.4f, %4.4f)\n', rejection_region);
    
    fprintf('The confidence interval: (%4.4f, %4.4f)\n', ci);
    fprintf('The value of the test statistic: %4.4f\n', stats.tstat);
    fprintf('The P-value of the test: %e\n\n', p);

% not equal variance
else 
    % stats.tstat = value of test statistic
    [h, p, ci, stats] = ttest2(x1, x2, alpha, tail, 'unequal');

    if h == 0
        fprintf('The null hypothesis is not rejected; gas mileage is not higher with premium gasoline!\n');
    else
        fprintf('The null hypothesis is rejected; gas mileage is not higher with premium gasoline!\n');
    end
    
    degree_of_freedom = length(x1) + length(x2) - 2;
    % quantile
    q = tinv(1 - alpha, degree_of_freedom);
    
    rejection_region = [q, inf];
    
    fprintf('The rejection region of the test: (%4.4f, %4.4f)\n', rejection_region);
    
    fprintf('The confidence interval: (%4.4f, %4.4f)\n', ci);
    fprintf('The value of the test statistic: %4.4f\n', stats.tstat);
    fprintf('The P-value of the test: %e \n\n', p);
end