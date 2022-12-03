x = [7 7 4 5 9 9 4 12 8 1 8 7 3 13 2 1 17 7 12 5 6 2 1 13 14 10 2 4 9 11 3 5 12 6 10 7];

dataLength = length(x);
fprintf("The length of the data: %d\n", dataLength);

oneMinusAlpha = input ('1-alpha = ');
while (oneMinusAlpha >= 1 || oneMinusAlpha <= 0)
    oneMinusAlpha = input('1-alpha in (0,1) = ');
end

sigma = 5;
xMean = mean(x);

u1 = xMean - sigma/sqrt(dataLength) * norminv(1 - oneMinusAlpha/2);
u2 = xMean - sigma/sqrt(dataLength) * norminv(oneMinusAlpha/2);

fprintf("a) The confidence interval for the mean(where sigma is %d) is (%.2f, %.2f).\n", sigma, u1, u2);

u1 = xMean - std(x) / sqrt(dataLength) * tinv(1 - alpha/2, dataLength-1);
u2 = xMean - std(x) / sqrt(dataLength) * tinv(alpha/2, dataLength-1);

fprintf("b) The confidence interval for the mean(where sigma is not known) is (%.2f, %.2f).\n", u1, u2);

o1 = (dataLength-1) * std(x) * std(x) / chi2inv(1 - oneMinusAlpha/2, dataLength-1);
o2 = (dataLength-1) * std(x) * std(x) / chi2inv(oneMinusAlpha/2, dataLength-1);
fprintf('c) The confidence intervals for the variance is (%.2f, %.2f).\n', o1, o2);

s1 = sqrt(o1);
s2 = sqrt(o2);
fprintf('   The confidence intervals for the standard deviation is (%.2f, %.2f).\n', s1, s2);

