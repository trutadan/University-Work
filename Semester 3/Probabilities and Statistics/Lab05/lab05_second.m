premiumGasoline = [22.4 21.7 24.5 23.4 21.6 23.3 22.4 21.6 24.8 20.0];
regularGasoline = [17.7 14.8 19.6 19.6 12.1 14.8 15.4 12.6 14.0 12.2];

premiumGasolineLength = length(premiumGasoline);
regularGasolineLength = length(regularGasoline);

fprintf("premium gasoline length: %d.\n", premiumGasolineLength);
fprintf("regular gasoline length: %d.\n", regularGasolineLength);

oneMinusAlpha = input ('1-alpha = ');
while (oneMinusAlpha >= 1 || oneMinusAlpha <= 0)
    oneMinusAlpha = input('1-alpha in (0,1) = ');
end

premiumGasolineMean = mean(premiumGasoline);
regularGasolineMean = mean(regularGasoline);

premiumGasolineStandard = std(premiumGasoline);
regularGasolineStandard = std(regularGasoline);

u1 = premiumGasolineMean - regularGasolineMean - tinv(1 - oneMinusAlpha/2, premiumGasolineLength - 1 + regularGasolineLength - 1) * sqrt(premiumGasolineStandard * premiumGasolineStandard/premiumGasolineLength + regularGasolineStandard * regularGasolineStandard/regularGasolineLength);
u2 = premiumGasolineMean - regularGasolineMean + tinv(1 - oneMinusAlpha/2, premiumGasolineLength - 1 + regularGasolineLength - 1) * sqrt(premiumGasolineStandard * premiumGasolineStandard/premiumGasolineLength + regularGasolineStandard * regularGasolineStandard/regularGasolineLength);

fprintf("The confidence interval is (%.2f, %.2f).\n", u1, u2);

c = (premiumGasolineStandard * premiumGasolineStandard / premiumGasolineLength) / (premiumGasolineStandard * premiumGasolineStandard / premiumGasolineLength + regularGasolineStandard * regularGasolineStandard / regularGasolineLength);
n = 1 / (c*c/(premiumGasolineLength - 1) + (1 - c)*(1 - c)/(regularGasolineLength - 1));

u1 = premiumGasolineMean - regularGasolineMean - tinv(1 - oneMinusAlpha/2, n) * sqrt(premiumGasolineStandard/premiumGasolineLength + regularGasolineStandard/regularGasolineLength);
u2 = premiumGasolineMean - regularGasolineMean + tinv(1 - oneMinusAlpha/2, n) * sqrt(premiumGasolineStandard/premiumGasolineLength + regularGasolineStandard/regularGasolineLength);

fprintf("The confidence interval is (%.2f, %.2f).\n", u1, u2);
