#!/Library/Frameworks/Python.framework/Versions/3.7/bin/python3
from eulerlib import Divisors
from functools import reduce
import sys

d=Divisors(1E5)

for line in sys.stdin:
	if line:
		n=int(line)
		phi=int(d.phi(n))
#		print("n {} phi {}".format(n,phi))
		print(phi>>1)
