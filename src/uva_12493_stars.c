/*
 ============================================================================
 Name        : uva_12493_stars.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

// XXX: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3937
#if 1
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <stddef.h>
#ifndef ONLINE_JUDGE
#include <unistd.h>
#include <sys/time.h>
#endif
#include <math.h>
#include <stdint.h>
#include <ctype.h>

#ifdef COMUN_LOG
#include <execinfo.h>
#endif

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#else
#include <time.h>
#include <stdarg.h>
#endif

#if 1
#ifndef LONG_LONG_MAX
#define LONG_LONG_MAX LONG_MAX
#endif

#ifndef ULONG_LONG_MAX
#define ULONG_LONG_MAX ULONG_MAX
#endif

#define COMUN_TAM_MAX_LINEA (16*200000)
#define HEAG_LOG_MAX_TAM_CADENA 2000

#define COMUN_BUF_STATICO_TAM 1000
#define COMUN_BUF_STATICO (char[COMUN_BUF_STATICO_TAM] ) { '\0' }

#define BITCH_VECTOR_NUM_BITS (sizeof(bitch_vector) * 8)

#define COMUN_ASSERT_DUROTE 0
#define COMUN_ASSERT_SUAVECITO 1
#define COMUN_ASSERT_NIMADRES 2

#define COMUN_VALOR_INVALIDO ((tipo_dato)UINT_MAX)
#define COMUN_IDX_INVALIDO ((natural)COMUN_VALOR_INVALIDO)
#define COMUN_FUNC_STATICA static

typedef char byteme;
typedef unsigned int natural;
typedef natural tipo_dato;
typedef long long entero_largo;
typedef unsigned long long entero_largo_sin_signo;
typedef long long bitch_vector;

typedef enum BOOLEANOS {
	falso = 0, verdadero
} bool;

#define COMUN_TIPO_ASSERT COMUN_ASSERT_SUAVECITO
/*
 #define COMUN_TIPO_ASSERT COMUN_ASSERT_DUROTE
 #define COMUN_TIPO_ASSERT COMUN_ASSERT_NIMADRES
 */

#define assert_timeout_dummy(condition) 0;

#if COMUN_TIPO_ASSERT == COMUN_ASSERT_DUROTE
#define assert_timeout(condition) assert(condition);
#endif
#if COMUN_TIPO_ASSERT == COMUN_ASSERT_SUAVECITO
#define assert_timeout(condition) if(!(condition)){while(1){printf("");};abort();}
#endif
#if COMUN_TIPO_ASSERT == COMUN_ASSERT_NIMADRES
#define assert_timeout(condition) 0
#endif

#ifdef COMUN_LOG
#define comun_log_debug(formato, args...) \
			do \
			{ \
				size_t profundidad = 0; \
				void *array[HEAG_LOG_MAX_TAM_CADENA]; \
				profundidad = backtrace(array, HEAG_LOG_MAX_TAM_CADENA); \
				comun_log_debug_func(formato,__FILE__, __func__, __LINE__,profundidad,##args); \
			} \
			while(0);
#else
#define comun_log_debug(formato, args...) 0
#endif

#define comun_max(x,y) ((x) < (y) ? (y) : (x))
#define comun_min(x,y) ((x) < (y) ? (x) : (y))

#define comun_calloc_local(tipo) (&(tipo){0})

void comun_log_debug_func(const char *format, ...);

#ifndef ONLINE_JUDGE
COMUN_FUNC_STATICA void comun_current_utc_time(struct timespec *ts) {

#ifdef __MACH__
	clock_serv_t cclock;
	mach_timespec_t mts;
	host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
	clock_get_time(cclock, &mts);
	mach_port_deallocate(mach_task_self(), cclock);
	ts->tv_sec = mts.tv_sec;
	ts->tv_nsec = mts.tv_nsec;
#else
#ifdef COMUN_LOG
	clock_gettime(CLOCK_REALTIME, ts);
#endif
#endif

}

COMUN_FUNC_STATICA void comun_timestamp(char *stime) {
	time_t ltime;
	long ms;
#ifndef ONLINE_JUDGE
	struct tm result;
	struct timespec spec;
#endif
	char parte_milisecundos[50];

	ltime = time(NULL);

#ifndef ONLINE_JUDGE
	localtime_r(&ltime, &result);
	asctime_r(&result, stime);
#endif

	*(stime + strlen(stime) - 1) = ' ';

#ifndef ONLINE_JUDGE
	comun_current_utc_time(&spec);
	ms = round(spec.tv_nsec / 1.0e3);
#endif
	sprintf(parte_milisecundos, "%ld", ms);
	strcat(stime, parte_milisecundos);
}

#endif
#ifdef COMUN_LOG
void comun_log_debug_func(const char *format, ...) {

	va_list arg;
	va_list arg2;
	const char *PEDAZO_TIMESTAMP_HEADER = "tiempo: %s; ";
	const char *HEADER =
	"archivo: %s; funcion: %s; linea %d; nivel: %zd 8====D ";
	char formato[HEAG_LOG_MAX_TAM_CADENA + sizeof(HEADER)
	+ sizeof(PEDAZO_TIMESTAMP_HEADER)] = {'\0'};
	char pedazo_timestamp[sizeof(PEDAZO_TIMESTAMP_HEADER) + 100] = {'\0'};
	char cadena_timestamp[100] = {'\0'};

	comun_timestamp(cadena_timestamp);
	sprintf(pedazo_timestamp, PEDAZO_TIMESTAMP_HEADER, cadena_timestamp);

	strcpy(formato, pedazo_timestamp);
	strcat(formato, HEADER);
	strcat(formato, format);
	strcat(formato, "\n");

	va_start(arg, format);
	va_copy(arg2, arg);
	vprintf(formato, arg2);
	va_end(arg2);
	va_end(arg);
	setbuf(stdout, NULL);
}
#endif

#ifdef COMUN_LOG
COMUN_FUNC_STATICA char *comun_arreglo_a_cadena(tipo_dato *arreglo, natural tam_arreglo,
		char *buffer) {
	int i;
	char *ap_buffer = NULL;
	int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
	return NULL;
#endif

	memset(buffer, 0, 100);
	ap_buffer = buffer;

	for (i = 0; i < tam_arreglo; i++) {
		characteres_escritos += sprintf(ap_buffer + characteres_escritos,
				"%1d", *(arreglo + i));
		if (i < tam_arreglo - 1) {
			*(ap_buffer + characteres_escritos++) = ',';
		}
	}
	*(ap_buffer + characteres_escritos) = '\0';
	return ap_buffer;
}

COMUN_FUNC_STATICA char *comun_arreglo_a_cadena_natural(natural *arreglo,
		natural tam_arreglo, char *buffer) {
	int i;
	char *ap_buffer = NULL;
	int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
	return NULL;
#endif

	memset(buffer, 0, 100);
	ap_buffer = buffer;

	for (i = 0; i < tam_arreglo; i++) {
		characteres_escritos += sprintf(ap_buffer + characteres_escritos, "%2u",
				*(arreglo + i));
		if (i < tam_arreglo - 1) {
			*(ap_buffer + characteres_escritos++) = ',';
		}
	}
	*(ap_buffer + characteres_escritos) = '\0';
	return ap_buffer;
}
char *comun_matrix_a_cadena(tipo_dato *matrix, natural filas_tam,
		natural columas_tam, char *buffer) {
	int i, j;
	natural inicio_buffer_act = 0;
	for (i = 0; i < filas_tam; i++) {
		comun_arreglo_a_cadena(matrix + i * columas_tam, columas_tam,
				buffer + inicio_buffer_act);
		inicio_buffer_act += strlen(buffer + inicio_buffer_act);
		buffer[inicio_buffer_act++] = '\n';
		/*		comun_log_debug("pero q mierda inicio buffer act %u %s",inicio_buffer_act,buffer);*/
	}
	return buffer;
}

COMUN_FUNC_STATICA char *comun_arreglo_a_cadena_entero_largo_sin_signo(
		entero_largo_sin_signo *arreglo, entero_largo_sin_signo tam_arreglo,
		char *buffer) {
	int i;
	char *ap_buffer = NULL;
	int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
	return NULL;
#endif

	memset(buffer, 0, 100);
	ap_buffer = buffer;

	for (i = 0; i < tam_arreglo; i++) {
		characteres_escritos += sprintf(ap_buffer + characteres_escritos,
				"%llu", *(arreglo + i));
		if (i < tam_arreglo - 1) {
			*(ap_buffer + characteres_escritos++) = ',';
		}
	}
	*(ap_buffer + characteres_escritos) = '\0';
	return ap_buffer;
}
#else
COMUN_FUNC_STATICA char *comun_arreglo_a_cadena(tipo_dato *arreglo,
		natural tam_arreglo, char *buffer) {
	return NULL;
}
COMUN_FUNC_STATICA char *comun_arreglo_a_cadena_natural(natural *arreglo,
		natural tam_arreglo, char *buffer) {
	return NULL;
}
char *comun_matrix_a_cadena(tipo_dato *matrix, natural filas_tam,
		natural columas_tam, char *buffer) {
	return NULL;
}

COMUN_FUNC_STATICA char *comun_arreglo_a_cadena_entero_largo_sin_signo(
		entero_largo_sin_signo *arreglo, entero_largo_sin_signo tam_arreglo,
		char *buffer) {
	return NULL;
}
#endif

#define comun_arreglo_a_cadena_entero_largo_sin_signo_buf_local(a,a_tam) comun_arreglo_a_cadena_entero_largo_sin_signo(a,a_tam,COMUN_BUF_STATICO)
#define comun_arreglo_a_cadena_buf_local(a,a_tam) comun_arreglo_a_cadena(a,a_tam,COMUN_BUF_STATICO)
#define comun_arreglo_a_cadena_natural_buf_local(a,a_tam) comun_arreglo_a_cadena_natural(a,a_tam,COMUN_BUF_STATICO)

COMUN_FUNC_STATICA void comun_strreplace(char s[], char chr, char repl_chr) {
	int i = 0;
	while (s[i] != '\0') {
		if (s[i] == chr) {
			s[i] = repl_chr;
		}
		i++;
	}
}

COMUN_FUNC_STATICA int comun_lee_matrix_long_stdin(tipo_dato *matrix,
		int *num_filas, int *num_columnas, int num_max_filas,
		int num_max_columnas) {
	int indice_filas = 0;
	int indice_columnas = 0;
	tipo_dato numero = 0;
	char *siguiente_cadena_numero = NULL;
	char *cadena_numero_actual = NULL;
	char *linea = NULL;

	linea = calloc(COMUN_TAM_MAX_LINEA, sizeof(char));

	while (indice_filas < num_max_filas
			&& fgets(linea, COMUN_TAM_MAX_LINEA, stdin)) {
		indice_columnas = 0;
		cadena_numero_actual = linea;
		comun_strreplace(linea, '\n', '\0');
		if (!strlen(linea)) {
			comun_log_debug("weird, linea vacia");
			continue;
		}
		for (siguiente_cadena_numero = linea;; siguiente_cadena_numero =
				cadena_numero_actual) {
			numero = strtol(siguiente_cadena_numero, &cadena_numero_actual, 10);
			if (cadena_numero_actual == siguiente_cadena_numero) {
				break;
			}
			*(matrix + indice_filas * num_max_columnas + indice_columnas) =
					numero;
			indice_columnas++;
		}
		if (num_columnas) {
			num_columnas[indice_filas] = indice_columnas;
		}
		indice_filas++;
		comun_log_debug("las filas son %d, con clos %d", indice_filas,
				indice_columnas);
	}

	*num_filas = indice_filas;
	free(linea);
	return 0;
}

COMUN_FUNC_STATICA natural comun_cuenta_bitchs(tipo_dato num) {
	natural bitch_cnt = 0;
	tipo_dato num_mod = 0;
	num_mod = num;
	while (num_mod) {
		num_mod &= ~(num_mod & (-num_mod));
		bitch_cnt++;
	}
	return bitch_cnt;
}

COMUN_FUNC_STATICA char comun_letra_a_valor_minuscula(char letra) {
	return letra - 'a';
}

COMUN_FUNC_STATICA natural comun_max_natural(natural *nums, natural nums_tam) {
	natural max = 0;
	int i = 0;

	for (i = 0; i < nums_tam; i++) {
		natural num_act = nums[i];
		if (num_act > max) {
			max = num_act;
		}
	}

	return max;
}

COMUN_FUNC_STATICA char *comun_trimea(char *cad, natural cad_tam) {
	char c = cad[0];
	char tmp = '\0';
	natural i = 0;
	natural j = 0;

	comun_log_debug("entrada %s cad_tam %u", cad, cad_tam);
	while (j < cad_tam && cad[j] != '\0') {
		comun_log_debug("en j %u car %c", j, cad[j]);
		while (j < cad_tam && !isalpha(cad[j])) {
			comun_log_debug("brincando j %u car %c", j, cad[j]);
			j++;
		}
		comun_log_debug("aora j %u car %c", j, cad[j]);
		if (j == cad_tam) {
			comun_log_debug("q ped");
			break;
		}
		tmp = cad[i];
		cad[i] = cad[j];
		cad[j] = tmp;
		i++;
		j++;
	}
	comun_log_debug("mierda '%c'", cad[j]);

	i = 0;
	while (isalpha(cad[i++]))
		;
	comun_log_debug("salida %s", cad);
	cad[i - 1] = '\0';

	return cad;
}

#endif

#define COMUN_LIMPIA_MEM(m,s) (memset(m,0,s))
#define COMUN_LIMPIA_MEM_STATICA(m) (memset(m,0,sizeof(*(m))))

COMUN_FUNC_STATICA bool comun_es_digito(char c) {
	return c >= '0' && c <= '9';
}

COMUN_FUNC_STATICA byteme comun_caracter_a_num(char c) {
	return c - '0';
}

COMUN_FUNC_STATICA void comun_invierte_arreglo_byteme(byteme *a, natural a_tam) {
	natural i = 0;
	natural j = a_tam - 1;
	while (i < j) {
		byteme t = a[i];
		a[i] = a[j];
		a[j] = t;
		i++;
		j--;
	}
}

COMUN_FUNC_STATICA void comun_invierte_arreglo_natural(natural *a,
		natural a_tam) {
	natural i = 0;
	natural j = a_tam - 1;
	while (i < j) {
		natural t = a[i];
		a[i] = a[j];
		a[j] = t;
		i++;
		j--;
	}
}

COMUN_FUNC_STATICA natural comun_encuentra_minimo_natural(natural *a,
		natural a_tam) {
	natural min = COMUN_VALOR_INVALIDO;
	natural i;
	for (i = 0; i < a_tam; i++) {
		if (min > a[i]) {
			min = a[i];
		}
	}
	return min;
}

COMUN_FUNC_STATICA natural comun_mcd(natural a, natural b) {
	natural r = COMUN_VALOR_INVALIDO;
	while (a && b) {
		natural tmp = b;
		b = a % b;
		a = tmp;
	}

	if (!a) {
		r = b;
	}
	if (!b) {
		r = a;
	}
	return r;
}

#define comun_compara_tipo(tipo) COMUN_FUNC_STATICA int comun_compara_##tipo(const void *pa, const void *pb) { \
		int r = 0; \
		tipo a = *(tipo *)pa; \
		tipo b = *(tipo *)pb; \
		if (a < b) { \
			r = -1; \
		} else { \
			if (a > b) { \
				r = 1; \
			} \
		} \
		return r; \
	}

comun_compara_tipo(natural)

COMUN_FUNC_STATICA natural comun_encuentra_divisores(natural n,
		natural *divisores, natural divisores_tam) {
	natural divisores_cnt = 0;
	natural i = 0;
	for (i = 1; i * i < n; i++) {
		if (!(n % i)) {
			assert_timeout(divisores_cnt < divisores_tam);
			divisores[divisores_cnt++] = i;
			assert_timeout(divisores_cnt < divisores_tam);
			divisores[divisores_cnt++] = n / i;
		}
	}

	if (i * i == n) {
		assert_timeout(divisores_cnt < divisores_tam);
		divisores[divisores_cnt++] = n / i;
	}
	qsort(divisores, divisores_cnt, sizeof(natural), comun_compara_natural);
	return divisores_cnt;
}

#endif

#if 1

//#define PRIMOS_NUM_MAX ((int)1E6)
#define PRIMOS_NUM_MAX 1081080
//#define PRIMOS_NUM_MAX 101
typedef struct primos_datos {
	natural primos_criba_tam;
	natural primos_criba[PRIMOS_NUM_MAX + 1];
	bool primos_criba_es_primo[PRIMOS_NUM_MAX + 1];

} primos_datos;

//#define PRIMOS_NUM_MAX ((int)101)

typedef void (*primos_criba_primo_encontrado_cb)(natural primo,
		natural idx_primo, void *cb_ctx);
typedef void (*primos_criba_compuesto_encontrado_cb)(natural primo,
		natural idx_primo, natural compuesto_origen, void *cb_ctx);

typedef void (*primos_criba_divisible_encontrado_cb)(natural primo,
		natural idx_primo, natural compuesto, void *cb_ctx);

typedef void (*primos_criba_no_divisible_encontrado_cb)(natural primo,
		natural idx_primo, natural compuesto, void *cb_ctx);

COMUN_FUNC_STATICA natural primos_criba_criba(natural limite,
		primos_criba_primo_encontrado_cb primo_cb,
		primos_criba_compuesto_encontrado_cb compuesto_cb,
		primos_criba_divisible_encontrado_cb divisible_encontrado_cb,
		primos_criba_no_divisible_encontrado_cb no_divisible_encontrado_cb,
		void *cb_ctx, primos_datos *pd) {
	bool *primos_criba_es_primo = pd->primos_criba_es_primo;
	natural *primos_criba = pd->primos_criba;
	comun_log_debug("primos asta %u", limite);
	assert_timeout(limite<=PRIMOS_NUM_MAX);
	natural i, j;
	for (i = 2; i <= limite; i++) {
		primos_criba_es_primo[i] = verdadero;
	}
	for (i = 2; i <= limite; i++) {
		if (primos_criba_es_primo[i]) {
			primos_criba[pd->primos_criba_tam++] = i;
			if (primo_cb) {
				primo_cb(i, pd->primos_criba_tam - 1, cb_ctx);
			}
		}
		for (j = 0; j < pd->primos_criba_tam && primos_criba[j] * i <= limite;
				j++) {
			primos_criba_es_primo[primos_criba[j] * i] = falso;
			if (compuesto_cb) {
				compuesto_cb(primos_criba[j], j, i, cb_ctx);
			}
			if (!(i % primos_criba[j])) {
				if (divisible_encontrado_cb) {
					divisible_encontrado_cb(primos_criba[j], j, i, cb_ctx);
				}
				break;
			} else {
				if (no_divisible_encontrado_cb) {
					no_divisible_encontrado_cb(primos_criba[j], j, i, cb_ctx);
				}
			}
		}
	}
	comun_log_debug("generados %u primos", pd->primos_criba_tam);
	return pd->primos_criba_tam;
}

#endif

#if 1
#define MORBIUS_MAX PRIMOS_NUM_MAX

typedef struct morbius_datos {
	int morbius[MORBIUS_MAX + 1];
} morbius_datos;

void morbius_divisible_encontrado_cb(natural primo, natural idx_primo,
		natural compuesto, void *cb_ctx) {
	morbius_datos *g = cb_ctx;

	g->morbius[compuesto * primo] = 0;
	comun_log_debug("divisible %u %d", compuesto * primo,
			g->morbius[compuesto * primo]);
}
void morbius_no_divisible_encontrado_cb(natural primo, natural idx_primo,
		natural compuesto, void *cb_ctx) {
	morbius_datos *g = cb_ctx;

	g->morbius[compuesto * primo] = g->morbius[compuesto] * -1;
	comun_log_debug("indivisible %u de %u %d", compuesto * primo, compuesto,
			g->morbius[compuesto * primo]);
}

void morbius_primo_encontrado_cb(natural primo, natural idx_primo, void *cb_ctx) {
	morbius_datos *g = cb_ctx;
	g->morbius[primo] = -1;
	comun_log_debug("primo enc %u %d", primo, g->morbius[primo]);
}
#endif

#if 1
COMUN_FUNC_STATICA entero_largo_sin_signo primalidad_mul_mod(
		entero_largo_sin_signo a, entero_largo_sin_signo b,
		entero_largo_sin_signo c) {
	entero_largo x = 0, y = a % c;
	while (b > 0) {
		if (b % 2 == 1) {
			x = (x + y) % c;
		}
		y = (y * 2) % c;
		b /= 2;
	}
	return x % c;
}

// TODO: Cambiar por iterativa
COMUN_FUNC_STATICA entero_largo_sin_signo primalidad_exp_mod(
		entero_largo_sin_signo a, entero_largo_sin_signo p,
		entero_largo_sin_signo m) {
	if (!p) {
		return 1;
	}
	if (p & 1) {
		return primalidad_mul_mod(a, primalidad_exp_mod(a, p - 1, m), m);
	}
	entero_largo x = primalidad_exp_mod(a, p >> 1, m);
	return primalidad_mul_mod(x, x, m);
}

// XXX: https://stackoverflow.com/questions/2509679/how-to-generate-a-random-integer-number-from-within-a-range
COMUN_FUNC_STATICA entero_largo_sin_signo primalidad_rand(
		entero_largo_sin_signo max) {
	entero_largo_sin_signo x = (((entero_largo_sin_signo) rand()) << 32)
			| rand();
//		comun_log_debug("num rand %llu - defec %llu = %llu y x %llu", num_rand, defect, num_rand-defect, x);
	return x % max;
}

COMUN_FUNC_STATICA entero_largo_sin_signo primalidad_rand_intervalo(
		entero_largo_sin_signo min, entero_largo_sin_signo max) {
//	comun_log_debug("rand intervalo min %llu max %llu", min, max);
	return (entero_largo_sin_signo) min + primalidad_rand(max - min);
}

COMUN_FUNC_STATICA bool primalidad_prueba_miller_rabbit(
		entero_largo_sin_signo n) {
	entero_largo_sin_signo a = primalidad_rand_intervalo(2, n - 2);
//	comun_log_debug("rand a %llu inter %llu-%llu", a, 2, n-2);
	entero_largo_sin_signo d = n - 1;
	while (!(d & 1)) {
		d >>= 1;
	}
//	comun_log_debug("d %llu", d);
	entero_largo_sin_signo x = primalidad_exp_mod(a, d, n);
//	comun_log_debug("x %llu", x);

	if (x == 1 || x == (n - 1)) {
		return verdadero;
	}
	while (d != (n - 1)) {
		x = primalidad_mul_mod(x, x, n);
		d <<= 1;
		if (x == 1) {
			return falso;
		}
		if (x == (n - 1)) {
			return verdadero;
		}
	}
	return falso;
}

COMUN_FUNC_STATICA bool primalidad_es_primo(entero_largo_sin_signo n, natural k) {
	if (n <= 1 || n == 4) {
		return falso;
	}
	if (n <= 3) {
		return verdadero;
	}

	while (k--) {
		if (!primalidad_prueba_miller_rabbit(n)) {
			return falso;
		}
	}
	comun_log_debug("%llu es primo", n);
	return verdadero;
}

#endif

COMUN_FUNC_STATICA natural stars_calcula_potencia_primo(
		entero_largo_sin_signo n, natural p,
		entero_largo_sin_signo *complemento_contribucion_primo) {
	natural i = 0;
	natural n_orig = n;
	while (!(n % p)) {
		n /= p;
		i++;
	}
	if (complemento_contribucion_primo) {
		*complemento_contribucion_primo = n;
	}
	comun_log_debug("potencia primo de %u en %u es %u", p, n_orig, i);
	return i;
}

COMUN_FUNC_STATICA bool stars_es_cuadratico(entero_largo_sin_signo n,
		entero_largo_sin_signo *raiz) {
	entero_largo_sin_signo sqr = sqrt(n);
	bool r = sqr * sqr == n;
	*raiz = 0;
	comun_log_debug("n %llu sqr %llu", n, sqr);
	assert_timeout(!r || primalidad_es_primo(sqr, 300));
	if (raiz) {
		*raiz = sqr;
	}
	return r;
}

COMUN_FUNC_STATICA entero_largo_sin_signo stars_calcula_contribucion_primos_mayores(
		entero_largo_sin_signo n, natural *num_primos_mayores,
		natural primer_primo_mayor_idx, primos_datos *pd) {
	entero_largo_sin_signo r = 0;
	*num_primos_mayores = COMUN_VALOR_INVALIDO;
	comun_log_debug("libre de cua de %llu", n);
	if (n == 1 || primalidad_es_primo(n, 300)) {
		if (n != 1) {
			r = n - 1;
		} else {
			r = 1;
		}
		*num_primos_mayores = (n != 1);
	} else {
		entero_largo_sin_signo raiz = 0;
		if (stars_es_cuadratico(n, &raiz)) {
			r = raiz * (raiz - 1);
			comun_log_debug("cuadratico r %llu", r);
		} else {
			assert_timeout_dummy(n!=1);
			natural primo = COMUN_VALOR_INVALIDO;
			for (natural i = primer_primo_mayor_idx; i < pd->primos_criba_tam;
					i++) {
				natural primo_act = pd->primos_criba[i];
				if (!(n % primo_act)) {
					primo = primo_act;
					break;
				}
			}

			assert_timeout(primo!=COMUN_VALOR_INVALIDO);
			entero_largo_sin_signo primo_complemento = n / primo;
			r = (primo_complemento - 1) * (primo - 1);
			*num_primos_mayores = 2;
		}
	}
	return r;
}

COMUN_FUNC_STATICA int stars_core(entero_largo_sin_signo n, primos_datos *pd) {
	if (n == 1) {
		return 1;
	}
//	natural raiz_cubica = pow(n, 1.0 / 3.0);
	natural raiz_cubica = cbrt(n);
	comun_log_debug("n %llu raiz cub %u", n, raiz_cubica);
	entero_largo_sin_signo factor_primos_mayores = n;
	entero_largo_sin_signo contribucion_primos_menores = 1;
	entero_largo_sin_signo contribucion_primos_mayores = 1;
	natural i = 0;
	for (i = 0; i < PRIMOS_NUM_MAX; i++) {
		natural primo = pd->primos_criba[i];
		if (primo > raiz_cubica) {
			break;
		}
		entero_largo_sin_signo potencia = stars_calcula_potencia_primo(
				factor_primos_mayores, primo, &factor_primos_mayores);
		if (potencia) {
			contribucion_primos_menores *= (entero_largo_sin_signo) (pow(primo,
					potencia) - pow(primo, potencia - 1));
		}
	}
	entero_largo_sin_signo factor_primos_menores = n / factor_primos_mayores;
	comun_log_debug("contribucion primos mayores %llu menores %llu",
			factor_primos_mayores, factor_primos_menores);
	contribucion_primos_mayores = stars_calcula_contribucion_primos_mayores(
			factor_primos_mayores, comun_calloc_local(natural), i, pd);
	comun_log_debug("contri menores %llu mayores %llu",
			contribucion_primos_menores, contribucion_primos_mayores);
	entero_largo_sin_signo r = contribucion_primos_menores
			* contribucion_primos_mayores;
	return r >> 1;
}

COMUN_FUNC_STATICA void stars_main() {
	primos_datos *pd = NULL;

	pd = calloc(1, sizeof(primos_datos));
	assert_timeout(pd);
	natural primos_tam = primos_criba_criba(PRIMOS_NUM_MAX,
	NULL, NULL, NULL,
	NULL, NULL, pd);
//	for (natural i = 1; i <= PRIMOS_NUM_MAX; i++) {
//		comun_log_debug("d[%u]=%llu", i, dd->num_divisores[i]);
//	}

//	for (natural i = 1; i <= PRIMOS_NUM_MAX; i++) {
//		entero_largo rc = stars_core(i, pd, dd);
//		entero_largo rs = dd->num_divisores[i];
//		comun_log_debug("d[%u]=%llu,%llu", i, rc, rs);
//		printf("d[%u]=%llu,%llu\n", i, rc, rs);
//		assert_timeout(rc == rs);
//	}

	entero_largo_sin_signo n = 0;
	while (scanf("%llu\n", &n) > 0 && n) {
		entero_largo_sin_signo r = stars_core(n, pd);
		comun_log_debug("%llu", r);
		printf("%llu\n", r);
	}

//	if (n <= stars_MAX_LINEAR) {
//		entero_largo_sin_signo rs = dd->num_divisores[n];
//		printf("d[%u]=%llu,%llu\n", (natural) n, r, rs);
//	}
}

int main(void) {
	stars_main();
	return EXIT_SUCCESS;
}
