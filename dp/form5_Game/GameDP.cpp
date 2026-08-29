/*
dp(config) = W / L
whoever comes to that pos, his fate is pre defined, calculate the predefine w/l
now check who is coming to that pos

// for most cases they follow a pattern, u can print all of them
// directly print if (this) or that then what happens directly without using dp all together


(state) w-> A(move) -> L(opp lose)
        w-> B(move) -> L(opp lose)
        l-> C(move) -> W(opp win)


(state) l-> A(move) -> W(opp win)
        l-> B(move) -> W(opp win)
        l-> C(move) -> W(opp win)

*/

