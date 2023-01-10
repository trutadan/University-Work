% It is thought that the gas mileage obtained by a particular model of
% automobile will be hiher if unleaded premium gasoline is used in the
% vehicle rather than regular unleaded gasolne. To gather evidence in this
% matter, 10 cars are randomly selected from the assembly line and tested
% using a specified brand of premium gasoline; 10 others are randomly
% selected and tested using the brand's regular gasoline. Tests are
% conducted under identical controlled conditions and gas mileages for both
% types of gas are assumed independent and (approximately) normally
% distributed. These data result: 
%   Premium            Regular
% 22.4  21.7    !    17.7  14.8 
% 24.5  23.4    !    19.6  19.6 
% 21.6  23.3    !    12.1  14.8 
% 22.4  21.6    !    15.4  12.6 
% 24.8  20.0    !    14.0  12.2 
x1 = [22.4 21.7 24.5 23.4 21.6 23.3 22.4 21.6 24.8 20.0];
x2 = [17.7 14.8 19.6 19.6 12.1 14.8 15.4 12.6 14.0 12.2];

% a. At the 5% significance level, is there evidence that the variances of
% the two populations are equal?
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

% b. Based on the result in part a., at the same significance level, does
% gas mileage seem to be higher, on average, when premium gasoline is used?
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