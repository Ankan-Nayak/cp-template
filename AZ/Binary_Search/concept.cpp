/*
* Q -> i (1 + 2 + 3...m) <= workerTimes[i]

* workerTimes[i] <= mid / (m * (m + 1) / 2) 
* we use Binary serach for m, might overflow
* workerTimes[i] <= (2 * mid) / (m * (m + 1)
* workerTimes[i] <= (2 * mid) / m / (m + 1)

cnt = (2 * mid) / workerTimes[i]
(m * (m + 1) <= cnt
m^2 + m − cnt = 0
m = -b +- root(b^2 - 4ac) / 2a = (-1 + root(1 + 4cnt)) 2;
ll temp = (ll)((sqrtl(cnt * 4 + 1) - 1) / 2);

*/
