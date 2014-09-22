Stochastic simulation for Counter-Strike: Global Offensife matches
===============
Using this program, you can simulate an outcome of matches in the long run given several starting variables.
[You can download exe file from releases](https://github.com/jonnyrobbie/csgo_stochastic/releases) or you can compile the source on your own.

When you run the program:

**Enter the number of games to simulate (1..2147483647), 0 to quit:** I recommend somewhere around 1000000 tries, but it depends on the speed of your computer.

**Enter the probability of Team A winning rounds with their skill (0..1):** You probably want to start with equally strong teams, so 0.5 should be good. Be careful that this is the probability of team winning a single round, so if you have anything other than 0.5, the resulting probability of winning an entire match is much more pronnounced.

**Enter the probability of team winning rounds on the side Team A started given the map imbalance (0..1):** Some maps in CS are not balanced. For example if you want to simulate a game on a de_nuke, you might want to enter something close to 0.7 (or 0.3 - depending on which side you want your team to start).

**Enter the probability of Team A winning pistol rounds (0..1):** The same as pevious, but only applies to pistol rounds. A map can be more balanced in pistol rounds than in other rounds.

**Enter the probability of a team winning the next round given they won the previous round (momentum) (0..1):** This simulates momentum. If a team is in a momentum it is likely to win the next round if they won the previous round. I may be simmilar to autocorrelation. Setting it to 0.5 is like there is no momentum in the game, setting it to closer 1 is like a positive autocorrelation (a team is more likely to win ne next round if they won the previous one) and setting it to number closer to 0 means the opposite.