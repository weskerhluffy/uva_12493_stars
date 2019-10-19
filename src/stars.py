from array import array
from math import exp, log, ceil


class QuadraticSieve():

	def __init__(self, max_numero):
		self.max_numero = max_numero
		self.primos = array('I')

	def _inicializa_criba():
		# XXX: https://stackoverflow.com/questions/521674/initializing-a-list-to-a-known-number-of-elements-in-python
		bandera_primos = array('B', (1,) * (self.max_numero + 1))
		for i in range(2, self.max_numero + 1):
			if bandera_primos[i]:
				self.primos.append(i)
			
			for primo in self.primos:
				compuesto = primo * i
				if compuesto > self.max_numero:
					break
				bandera_primos[compuesto] = 0
				if not (i % primo):
					break
				
	def _simbolo_legendre(self, a, p):
		s = (a ** ((p - 1) >> 1)) % p
		return s
	
	def _encuentra_base_de_factores(self, n, b):
		rc = array("I")
		for p in self.primos:
			if p > b:
				break
			if self._simbolo_legendre(n, p) == 1:
				rc.append(p)
		return rc
	
	def _calcula_limite_b_suave(self, n):
		b = ceil(exp(((log(n) * log(log(n))) / 2) / 2))
		return int(b)
	
	# XXX: https://rosettacode.org/wiki/Tonelli-Shanks_algorithm#Python
	def _calcula_z_shanks_tonelli(self, p):
		for z in range(2, p):
			if p - 1 == self._simbolo_legendre(z, p):
				break
		return z

	def _calcula_conguencia_residuo_cuadratico(self, n, p, M):
		p_menos_1 = p - 1
		S = 0
		while not (p_menos_1 & 1):
			p_menos_1 >>= 1
			S += 1
		Z = self._calcula_z_shanks_tonelli(p)
		Q = p_menos_1
		c = (Z ** Q) % p
		R = (n ** ((Q + 1) >> 1)) % p
		t = (n ** Q) % p
		M = S
		while (t % p) != 1:
			i = 0
			for i in range(1, M):
				if ((t ** (i << 1)) % p) == 1:
					break
			b = (c ** (1 << (M - i - 1))) % p
			R = R * b
			t = t * (b ** 2)
			c = b ** 2
			M = i
		return R, p - R
