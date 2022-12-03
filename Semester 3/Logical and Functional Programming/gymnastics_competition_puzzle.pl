% https://www.brainzilla.com/logic/zebra/gymnastics-competition/

% Gymnastics Competition Puzzle
% Five gymnasts are side by side at a gymnastics competition. 
% Each one is wearing an uniform, represents a country and got a score. 
% Follow the clues to figure out how each gymnast performed at this competition.

:- use_rendering(table, [header(gymnast('Uniform', 'Country', 'Score', 'Height', 'Weight', 'Age'))]).

% 4, 16 -> left
% 8, 13, 20 -> right = left reversed
somewhereToLeft(A, B, Ls):-
    append(_, [A, B|_], Ls).
somewhereToLeft(A, B, Ls):-
    append(_, [A, _, B|_], Ls).
somewhereToLeft(A, B, Ls):-
    append(_, [A, _, _, B|_], Ls).
somewhereToLeft(A, B, Ls):-
    append(_, [A, _, _, _, B|_], Ls).

% 12 -> right = left reversed
exactlyToTheLeft(A, B, Ls):-
    append(_, [A, B|_], Ls).

% 7
atOneOfTheEnds(A, Ls):-
    Ls = [A|_].
atOneOfTheEnds(A, Ls):-
    Ls = [_, _, _, _, A].

% 2, 11, 17
somewhereBetween(A, B, C, Ls):-
    somewhereToLeft(A, B, Ls),
    somewhereToLeft(B, C, Ls).

% description about positions
% 1, 6, 10, 14, 18, 21

% other characteristics
% 3, 5, 9, 15, 19, 22

generateGymnasticsCompetitors(Gymnasts):-
    length(Gymnasts, 5),
    
    % 1. At the third position is the 120 lbs gymnast.
    % 18. In the middle is the 25-year-old gymnast.
    Gymnasts = [_, _, gymnast(_, _, _, _, 120, 25), _, _],
    
    % 3. The 5'5" gymnast got the lowest score.
    LowestScore = gymnast(_, _, 88, 5.5, _, _),
    member(LowestScore, Gymnasts),
    
    % 5. The tallest gymnast weighs 125 lbs.
    Tallest = gymnast(_, _, _, 5.6, 125, _),
    member(Tallest, Gymnasts),
    
    % 6. At the second position is the smallest athlete.
    Smallest = gymnast(_, _, _, 5.2, _, _),
    Gymnasts = [_, Smallest, _, _, _],
    
    % 9. The youngest athlete is 5'4" tall.
    Youngest = gymnast(_, _, _, 5.4, _, 21),
    member(Youngest, Gymnasts),
    
    % 10. At the fourth position is the 21-year-old gymnast.
    % 21. At the fourth position is the gymnast that weighs 115 lbs.
    Gymnasts = [_, _, _, gymnast(_, _, _, _, 115, 21), _],
    
    % 14. At the fifth position is the lightest athlete.
    Lightest = gymnast(_, _, _, _, 110, _),
    Gymnasts = [_, _, _, _, Lightest],
    
    % 15. The oldest gymnast is wearing the White uniform.
    Oldest = gymnast('White', _, _, _, _, 29),
    member(Oldest, Gymnasts),
    
    % 19. The 5'6" gymnast got 90 points.
    member(gymnast(_, _, 90, 5.6, _, _), Gymnasts),
    
    % 22. The gymnast from China got 88 points.
    member(gymnast(_, 'China', 88, _, _, _), Gymnasts),
    
    % 2. The Japanese is somewhere between the Russian and the gymnast wearing the Black uniform, in that order.
	  somewhereBetween(gymnast(_, 'Russia', _, _, _, _), gymnast(_, 'Japan', _, _, _, _), gymnast('Black', _, _, _, _, _), Gymnasts),
    
    % 4. The athlete wearing the Blue uniform is somewhere to the left of the 115 lbs athlete.
  	somewhereToLeft(gymnast('Blue', _, _, _, _, _), gymnast(_, _, _, _, 115, _), Gymnasts),
    
    % 7. At one of the ends is the 27-year-old gymnast.
	  atOneOfTheEnds(gymnast(_, _, _, _, _, 27), Gymnasts),
    
    % 8. The gymnast wearing the Black uniform is somewhere to the right of the gymnast wearing the Green uniform.
    somewhereToLeft(gymnast('Green', _, _, _, _, _), gymnast('Black', _, _, _, _, _), Gymnasts),
    
    % 11. The gymnast wearing the Blue uniform is somewhere between the Russian and the gymnast wearing the Green uniform, in that order.
    somewhereBetween(gymnast(_, 'Russia', _, _, _, _), gymnast('Blue', _, _, _, _, _), gymnast('Green', _, _, _, _, _), Gymnasts),
    
    % 12. The American is exactly to the right of the 120 lbs athlete.
    exactlyToTheLeft(gymnast(_, _, _, _, 120, _), gymnast(_, 'United States', _, _, _, _), Gymnasts),
    
    % 13. The gymnast that got 92 points is somewhere to the right of the gymnast wearing the Blue uniform.
    somewhereToLeft(gymnast('Blue', _, _, _, _, _), gymnast(_, _, 92, _, _, _), Gymnasts),
    
    % 16. The gymnast wearing the Black uniform is somewhere to the left of the gymnast who got 91 points.
    somewhereToLeft(gymnast('Black', _, _, _, _, _), gymnast(_, _, 91, _, _, _), Gymnasts),
    
    % 17. The athlete wearing the Blue uniform is somewhere between the 125 lbs athlete and the 110 lbs athlete, in that order.
    somewhereBetween(gymnast(_, _, _, _, 125, _), gymnast('Blue', _, _, _, _, _), gymnast(_, _, _, _, 110, _), Gymnasts),
    
    % 20. The athlete wearing the White uniform is somewhere to the right of the athlete wearing the Red uniform.
	somewhereToLeft(gymnast('Red', _, _, _, _, _), gymnast('White', _, _, _, _, _), Gymnasts),
    
    % Additional information about competitors in order to complete all the table's sections.
    member(gymnast(_, 'Germany', _, _, _, _), Gymnasts),
    member(gymnast(_, _, 89, _, _, _), Gymnasts),
    member(gymnast(_, _, _, 5.3, _, _), Gymnasts),
    member(gymnast(_, _, _, _, 130, _), Gymnasts),
    member(gymnast(_, _, _, _, _, 23), Gymnasts), !.

% Results:
% generateGymnasticsCompetitors(R).
% R = [gymnast('Red', 'Russia', 90, 5.6, 125, 27), 
% gymnast('Blue', 'Japan', 89, 5.2, 130, 23), 
% gymnast('Green', 'China', 88, 5.5, 120, 25), 
% gymnast('Black', 'United States', 92, 5.4, 115, 21), 
% gymnast('White', 'Germany', 91, 5.3, 110, 29)]
