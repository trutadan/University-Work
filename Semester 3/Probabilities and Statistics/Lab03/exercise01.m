distribution = input('normal/student/chi2/fischer\n', 's');

switch distribution
    case 'normal'
        muNormal = input('Enter mu variable: ');
        sigmaNormal = input('Enter sigma variable: ');
        
        % a)
        aNormalProb1 = normcdf(0, muNormal, sigmaNormal);
        aNormalProb2 = 1 - aNormalProb1;

        % b)
        bNormalProb1 = normcdf(1, muNormal, sigmaNormal) - normcdf(-1, muNormal, sigmaNormal);
        bNormalProb2 = 1 - bNormalProb1;

        % c)
        alphaNormal = input('Enter an alpha value between 0 and 1: ');
        if (alphaNormal >= 1 || alphaNormal <= 0)
            fprintf("Not a number between 0 and 1!\n");
            exit;
        end
        cNormalProb = norminv(alphaNormal, muNormal, sigmaNormal);

        % d)
        betaNormal = input('Enter a beta value between 0 and 1: ');
        if (betaNormal >= 1 || betaNormal <= 0)
            fprintf("Not a number between 0 and 1!\n");
            exit;
        end
        dNormalProb = norminv(1 - betaNormal, muNormal, sigmaNormal);

        % output
        fprintf("a) %f; %f \nb) %f; %f \nc) %f \nd) %f\n", aNormalProb1, aNormalProb2, bNormalProb1, bNormalProb2, cNormalProb, dNormalProb);

    case 'student'
        nStudent = input('Enter the n variable: ');

        % a)
        aStudentProb1 = tcdf(0, nStudent); 
        aStudentProb2 = 1 - aStudentProb1;

        % b)
        bStudentProb1 = normcdf(1, nStudent) - normcdf(-1, nStudent);
        bStudentProb2 = 1 - bStudentProb1;

        % c)
        alphaStudent = input('Enter an alpha value between 0 and 1: ');
        if (alphaStudent >= 1 || alphaStudent <= 0)
            fprintf("Not a number between 0 and 1!\n");
            exit;
        end
        cStudentProb = tinv(alphaStudent, nStudent);
        
        % d)
        betaStudent = input('Enter a beta value between 0 and 1: ');
        if (betaStudent >= 1 || betaStudent <= 0)
            fprintf("Not a number between 0 and 1!\n");
            exit;
        end
        dStudentProb = tinv(1 - betaStudent, nStudent);

        % output
        fprintf("a) %f; %f \nb) %f; %f \nc) %f \nd) %f\n", aStudentProb1, aStudentProb2, bStudentProb1, bStudentProb2, cStudentProb, dStudentProb);

    case 'chi2'
        nChi2 = input('Enter the n variable: ');

        % a)
        aChi2Prob1 = chi2cdf(0, nChi2);
        aChi2Prob2 = 1 - aChi2Prob1;

        % b)
        bChi2Prob1 = normcdf(1, nChi2) - normcdf(-1, nChi2);
        bChi2Prob2 = 1 - bChi2Prob1;

        % c)
        alphaChi2 = input('Enter an alpha value between 0 and 1: ');
        if (alphaChi2 >= 1 || alphaChi2 <= 0)
            fprintf("Not a number between 0 and 1!\n");
            exit;
        end
        cChi2Prob = cho2inv(alphaChi2, nChi2);

        % d)
        betaChi2 = input('Enter a beta value between 0 and 1: ');
        if (betaChi2 >= 1 || betaChi2 <= 0)
            fprintf("Not a number between 0 and 1!\n");
            exit;
        end
        dChi2Prob = chi2inv(1 - betaChi2, nChi2);

        % output
        fprintf("a) %f; %f \nb) %f; %f \nc) %f \nd) %f\n", aChi2Prob1, aChi2Prob2, bChi2Prob1, bChi2Prob2, cChi2Prob, dChi2Prob);

    case 'fischer'
        mFischer = input('Enter the m variable: ');
        nFischer = input('Enter the n variable: ');

        % a)
        aFischerProb1 = fcdf(0, m, n);
        aFischerProb2 = 1 - aFischerProb1;

        % b)
        bFischerProb1 = normcdf(1, mFischer, nFischer) - normcdf(-1, mFischer, nFischer);
        bFischerProb2 = 1 - bFischerProb1;

        % c)
        alphaFischer = input('Enter an alpha value between 0 and 1: ');
        if (alphaFischer >= 1 || alphaFischer <= 0)
            fprintf("Not a number between 0 and 1!\n");
            exit;
        end
        cFischerProb = finv(alphaFischer, mFischer, nFischer);

        % d)
        betaFischer = input('Enter a beta value between 0 and 1: ');
        if (betaFischer >= 1 || betaFischer <= 0)
            fprintf("Not a number between 0 and 1!\n");
            exit;
        end
        dFischerProb = finv(1 - betaFischer, mFischer, nFischer);

        % output
        fprintf("a) %f; %f \nb) %f; %f \nc) %f \nd) %f\n", aFischerProb1, aFischerProb2, bFischerProb1, bFischerProb2, cFischerProb, dFischerProb);

    otherwise
        fprintf("Not a valid input!\n");
end
