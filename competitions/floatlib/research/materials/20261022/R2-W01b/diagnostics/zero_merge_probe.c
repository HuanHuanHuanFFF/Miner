#define _POSIX_C_SOURCE 200809L
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <float.h>
#include <fenv.h>
#include <inttypes.h>
#include <xmmintrin.h>

/* This is one C surrogate experiment, not generated Lean code.
   All variants add every converted input in its original position. */
_Static_assert(sizeof(float) == 4, "binary32 size");
_Static_assert(FLT_RADIX == 2 && FLT_MANT_DIG == 24 && FLT_MAX_EXP == 128,
               "binary32 parameters");
_Static_assert(FLT_EVAL_METHOD == 0, "no excess evaluation precision");

enum { N = 1000, VECTORS = 96, CLASSES = 8, METHODS = 3, ROUNDS = 7 };
static const char *class_name[CLASSES] = {
    "lcg_dense", "lcg_relu_alternating", "lcg_wide", "random_relu50",
    "random_relu25", "random_relu75", "clustered_relu50", "random_relu_pmzero50"
};
static const char *method_name[METHODS] = { "external_ofbits", "old_zero_branch", "merged_guard" };
static uint32_t data[CLASSES][VECTORS][N];
static float scale_table[512];
static volatile uint32_t observed_sink;
extern float external_of_bits(uint32_t u);

static uint64_t monotime(void) {
    struct timespec t;
    if (clock_gettime(CLOCK_MONOTONIC, &t)) abort();
    return (uint64_t)t.tv_sec * UINT64_C(1000000000) + (uint64_t)t.tv_nsec;
}

static uint32_t bits(float x) {
    uint32_t u;
    memcpy(&u, &x, sizeof u);
    return u;
}

static uint32_t table_word(uint32_t j) {
    uint32_t e = j & 255u;
    uint32_t s = (j & 256u) << 23;
    return (24u <= e && e <= 254u) ? (s | ((e - 23u) << 23)) : s;
}

static int guard(uint32_t u) {
    const uint32_t a = u & UINT32_C(0x7fffffff);
    return a - 1u >= UINT32_C(0x0bffffff) && a < UINT32_C(0x7f800000);
}

static inline float table_product(uint32_t u) {
    const uint32_t m = (u & UINT32_C(0x007fffff)) | UINT32_C(0x00800000);
    return (float)m * scale_table[u >> 23];
}

static inline float old_convert(uint32_t u) {
    if (u == 0u) return 0.0f;
    const uint32_t e = (u >> 23) & 255u;
    if (24u <= e && e <= 254u) return table_product(u);
    return external_of_bits(u);
}

static inline float merged_convert(uint32_t u) {
    const uint32_t a = u & UINT32_C(0x7fffffff);
    if (a - 1u >= UINT32_C(0x0bffffff) && a < UINT32_C(0x7f800000))
        return table_product(u);
    return external_of_bits(u);
}

static uint32_t finish_finite(float s) {
    const uint32_t u = bits(s);
    if ((u & UINT32_C(0x7f800000)) == UINT32_C(0x7f800000)) {
        fputs("nonfinite sum: surrogate has no raw-payload fallback\n", stderr);
        abort();
    }
    return u;
}

__attribute__((noinline, noclone))
static uint32_t sum_external(const uint32_t *u) {
    float s = 0.0f;
    for (size_t i = 0; i < N; ++i) s = s + external_of_bits(u[i]);
    return finish_finite(s);
}

__attribute__((noinline, noclone))
static uint32_t sum_old(const uint32_t *u) {
    float s = 0.0f;
    for (size_t i = 0; i < N; ++i) s = s + old_convert(u[i]);
    return finish_finite(s);
}

__attribute__((noinline, noclone))
static uint32_t sum_merged(const uint32_t *u) {
    float s = 0.0f;
    for (size_t i = 0; i < N; ++i) s = s + merged_convert(u[i]);
    return finish_finite(s);
}

static uint32_t (*const method[METHODS])(const uint32_t *) = {
    sum_external, sum_old, sum_merged
};

/* Fresh synthetic seeds; the conversion functions never see a seed or a class. */
static uint32_t fresh_word(uint64_t *state) {
    uint64_t z = (*state += UINT64_C(0x9e3779b97f4a7c15));
    z = (z ^ (z >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
    z = (z ^ (z >> 27)) * UINT64_C(0x94d049bb133111eb);
    return (uint32_t)(z ^ (z >> 31));
}

static uint32_t dense_word(uint32_t w) {
    return (w & UINT32_C(0x807fffff)) | ((124u + (w >> 23) % 7u) << 23);
}

static uint32_t positive_odd_word(uint32_t w) {
    return (w & UINT32_C(0x007fffff)) | 1u | ((124u + (w >> 23) % 7u) << 23);
}

static void generate_data(void) {
    uint32_t lcg[3] = { UINT32_C(0x4d73a2c1), UINT32_C(0xb2c87f45), UINT32_C(0x681d3f97) };
    uint64_t random_state = UINT64_C(0x71934f28c6a51bed);
    for (size_t v = 0; v < VECTORS; ++v) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < 3; ++k) lcg[k] = lcg[k] * 1664525u + 1013904223u;
            data[0][v][i] = dense_word(lcg[0]);
            data[1][v][i] = (lcg[1] & 1u) ? (dense_word(lcg[1]) & UINT32_C(0x7fffffff)) : 0u;
            data[2][v][i] = (lcg[2] & UINT32_C(0x807fffff)) | ((102u + (lcg[2] >> 23) % 50u) << 23);
            uint32_t w = fresh_word(&random_state);
            data[3][v][i] = (w & 1u) ? positive_odd_word(w) : 0u;
            uint32_t w25 = fresh_word(&random_state), m25 = fresh_word(&random_state);
            uint32_t w75 = fresh_word(&random_state), m75 = fresh_word(&random_state);
            data[4][v][i] = (m25 & 3u) == 0u ? 0u : positive_odd_word(w25);
            data[5][v][i] = (m75 & 3u) != 0u ? 0u : positive_odd_word(w75);
            data[7][v][i] = data[3][v][i];
            if (data[7][v][i] == 0u) data[7][v][i] = fresh_word(&random_state) & UINT32_C(0x80000000);
        }
        size_t zero_count = 0;
        for (size_t i = 0; i < N; ++i) if (data[3][v][i] == 0u) ++zero_count;
        for (size_t i = 0; i < zero_count; ++i) data[6][v][i] = 0u;
        size_t j = zero_count;
        for (size_t i = 0; i < N; ++i) if (data[3][v][i] != 0u) data[6][v][j++] = data[3][v][i];
        if (j != N) abort();
    }
}

static FILE *open_output(const char *dir, const char *name) {
    char path[4096];
    if (snprintf(path, sizeof path, "%s/%s", dir, name) >= (int)sizeof path) abort();
    FILE *f = fopen(path, "w");
    if (!f) { perror(path); exit(2); }
    return f;
}

static void require(int test, const char *description) {
    if (!test) { fprintf(stderr, "FAIL %s\n", description); exit(3); }
}

static void check_word(uint32_t u, uint64_t *checked, FILE *examples) {
    const uint32_t a = u & UINT32_C(0x7fffffff);
    const int expected_guard = a == 0u || (a >= UINT32_C(0x0c000000) && a < UINT32_C(0x7f800000));
    const uint32_t ref = bits(external_of_bits(u));
    const uint32_t old = bits(old_convert(u));
    const uint32_t merged = bits(merged_convert(u));
    require(guard(u) == expected_guard, "admission equivalence");
    require(old == ref && merged == ref, "per-input conversion bits");
    if (examples) fprintf(examples, "%08" PRIx32 ",%d,%08" PRIx32 ",%08" PRIx32 ",%08" PRIx32 "\n", u, guard(u), ref, old, merged);
    ++*checked;
}

int main(int argc, char **argv) {
    const char *out = argc > 1 ? argv[1] : ".";
    const unsigned repetitions = argc > 2 ? (unsigned)strtoul(argv[2], 0, 10) : 80u;
    require(repetitions > 0u && repetitions <= 10000u, "bounded repetitions");
    const unsigned mxcsr = _mm_getcsr();
    require(fegetround() == FE_TONEAREST, "RN-even environment");
    require((mxcsr & ((1u << 15) | (1u << 6) | (3u << 13))) == 0u, "gradual subnormal environment");

    FILE *setup = open_output(out, "probe_setup.csv");
    fputs("item,value,unit\n", setup);
    fprintf(setup, "vectors_per_class,%u,count\nlength,%u,count\nclasses,%u,count\nrounds,%u,count\nrepetitions,%u,count\nmxcsr,%u,bits\n", VECTORS,N,CLASSES,ROUNDS,repetitions,mxcsr);
    uint64_t t0 = monotime();
    for (uint32_t j = 0; j < 512u; ++j) scale_table[j] = external_of_bits(table_word(j));
    uint64_t table_ns = monotime() - t0;
    fprintf(setup, "table_setup_once,%" PRIu64 ",ns\ntable_storage,2048,bytes\n", table_ns);
    t0 = monotime();
    generate_data();
    fprintf(setup, "data_setup_once,%" PRIu64 ",ns\n", monotime() - t0);
    fclose(setup);

    FILE *examples = open_output(out, "probe_conversion_cases.csv");
    fputs("input_bits,accepted,external_bits,old_bits,merged_bits\n", examples);
    uint64_t words_checked = 0;
    static const uint32_t boundary[] = {
        0u,1u,0x007fffffu,0x00800000u,0x0b7fffffu,0x0b800000u,0x0bfffffeu,
        0x0bffffffu,0x0c000000u,0x0c000001u,0x3f800000u,0x7f7ffffeu,
        0x7f7fffffu,0x7f800000u,0x7f800001u,0x7fc00000u,0x7fc12345u,0x7fffffffu
    };
    for (size_t i = 0; i < sizeof boundary / sizeof *boundary; ++i)
        for (uint32_t sign = 0; sign < 2; ++sign) check_word(boundary[i] | (sign << 31), &words_checked, examples);
    fclose(examples);
    static const uint32_t fractions[] = {0u,1u,2u,0x003fffffu,0x00400000u,0x007ffffeu,0x007fffffu};
    for (uint32_t sign = 0; sign < 2; ++sign)
        for (uint32_t exponent = 0; exponent < 256; ++exponent)
            for (size_t f = 0; f < sizeof fractions / sizeof *fractions; ++f)
                check_word((sign << 31) | (exponent << 23) | fractions[f], &words_checked, NULL);
    uint64_t validation_state = UINT64_C(0xa937e5f128bc460d);
    for (size_t i = 0; i < 100000; ++i) check_word(fresh_word(&validation_state), &words_checked, NULL);

    FILE *dist = open_output(out, "probe_distribution.csv");
    FILE *sums = open_output(out, "probe_vector_results.csv");
    fputs("class,elements,distinct_vectors,plus_zero,minus_zero,normal_band,accepted,fallback,zero_transitions\n", dist);
    fputs("class,vector,external_bits,old_bits,merged_bits\n", sums);
    for (size_t c = 0; c < CLASSES; ++c) {
        uint64_t plus = 0, minus = 0, normal = 0, accepted = 0, transitions = 0;
        for (size_t v = 0; v < VECTORS; ++v) {
            for (size_t prior = 0; prior < v; ++prior)
                require(memcmp(data[c][v], data[c][prior], sizeof data[c][v]) != 0, "distinct vectors");
            for (size_t i = 0; i < N; ++i) {
                uint32_t u = data[c][v][i], a = u & UINT32_C(0x7fffffff);
                plus += u == 0u; minus += u == UINT32_C(0x80000000);
                normal += a >= UINT32_C(0x0c000000) && a < UINT32_C(0x7f800000);
                accepted += guard(u);
                if (i) transitions += (a == 0u) != ((data[c][v][i-1] & UINT32_C(0x7fffffff)) == 0u);
                check_word(u, &words_checked, NULL);
            }
            uint32_t result[METHODS];
            for (size_t m = 0; m < METHODS; ++m) result[m] = method[m](data[c][v]);
            require(result[0] == result[1] && result[0] == result[2], "complete ordered sum bits");
            fprintf(sums, "%s,%zu,%08" PRIx32 ",%08" PRIx32 ",%08" PRIx32 "\n",class_name[c],v,result[0],result[1],result[2]);
            if (c == 6 || c == 7) require(result[0] == sum_external(data[3][v]), "related zero-distribution sum");
        }
        fprintf(dist,"%s,%u,%u,%" PRIu64 ",%" PRIu64 ",%" PRIu64 ",%" PRIu64 ",%" PRIu64 ",%" PRIu64 "\n",class_name[c],VECTORS*N,VECTORS,plus,minus,normal,accepted,(uint64_t)VECTORS*N-accepted,transitions);
    }
    fclose(dist); fclose(sums);

    FILE *timings = open_output(out, "probe_rounds.csv");
    fputs("round,class,position,method,repetitions,vectors,length,elapsed_ns,ns_per_element,checksum\n", timings);
    for (unsigned round = 0; round < ROUNDS; ++round) {
        for (unsigned ci = 0; ci < CLASSES; ++ci) {
            const unsigned c = (ci + round) % CLASSES;
            for (unsigned position = 0; position < METHODS; ++position) {
                const unsigned m = (round & 1u) ? (round + METHODS - position) % METHODS : (round + position) % METHODS;
                uint32_t check = UINT32_C(0x84f5a219);
                uint32_t (*fn)(const uint32_t *) = method[m];
                /* Warm every distinct vector once; all warm-up work is untimed. */
                for (unsigned v = 0; v < VECTORS; ++v) observed_sink ^= fn(data[c][v]);
                t0 = monotime();
                for (unsigned r = 0; r < repetitions; ++r) {
                    for (unsigned vi = 0; vi < VECTORS; ++vi) {
                        const unsigned v = (vi + round) % VECTORS;
                        check = (check ^ fn(data[c][v])) * UINT32_C(16777619);
                    }
                }
                const uint64_t dt = monotime() - t0;
                observed_sink = check;
                const double each = (double)dt / ((double)repetitions * VECTORS * N);
                fprintf(timings,"%u,%s,%u,%s,%u,%u,%u,%" PRIu64 ",%.9f,%08" PRIx32 "\n",round,class_name[c],position,method_name[m],repetitions,VECTORS,N,dt,each,check);
                fflush(timings);
            }
        }
    }
    fclose(timings);
    FILE *validation = open_output(out, "probe_validation.json");
    fprintf(validation,"{\n  \"conversion_words_checked\": %" PRIu64 ",\n  \"conversion_mismatches\": 0,\n  \"complete_sum_vectors\": %u,\n  \"sum_mismatches\": 0,\n  \"per_class_distinct_vectors\": %u,\n  \"table_layout\": \"flat_float32_512\",\n  \"table_setup_once_ns\": %" PRIu64 ",\n  \"raw_algorithm_payload_fallback\": \"NOT_MODELED\",\n  \"lean_execution\": \"NOT_RUN\",\n  \"final_sink\": %u\n}\n",words_checked,CLASSES*VECTORS,VECTORS,table_ns,observed_sink);
    fclose(validation);
    printf("PASS conversions=%" PRIu64 " complete_vectors=%u rounds=%u\n",words_checked,CLASSES*VECTORS,ROUNDS);
    return 0;
}
