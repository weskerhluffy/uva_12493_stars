from math import log, exp, sqrt

def L(N):
	return exp((log(N)*log(log(N)))/2)

N=87463
print(sqrt(L(N)))
