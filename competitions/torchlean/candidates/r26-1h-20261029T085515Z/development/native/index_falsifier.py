"""Finite address/term-order checks for actual prepared cache layouts only."""
from pathlib import Path
import json
import random
import time
HERE = Path(__file__).resolve().parent

def natdiv(a, b):
    return a // b if b else 0

def window(sh, y, x, t):
    ci, h, w, co, kh, kw, stride, pad = sh
    c = natdiv(t, kh * kw)
    dy = natdiv(t, kw) % kh if kh else 0
    dx = t % kw if kw else t
    yy, xx = y * stride + dy, x * stride + dx
    if yy < pad or xx < pad or max(yy - pad, 0) >= h or max(xx - pad, 0) >= w:
        return ('zero',)
    return ('input', (c * h + yy - pad) * w + xx - pad)

def conv(sh):
    ci, h, w, co, kh, kw, stride, pad = sh
    ho = natdiv(max(h + 2 * pad - kh, 0), stride) + 1
    wo = natdiv(max(w + 2 * pad - kw, 0), stride) + 1
    hw, k = ho * wo, ci * kh * kw
    count = 0
    for q in range(co * hw):
        o, y, x = q // hw, (q // wo) % ho, q % wo
        p = q % hw
        old = [window(sh, y, x, t) for t in range(k)] + [('one',)]
        new = [window(sh, p // wo, p % wo, t) for t in range(k)] + [('one',)]
        old_w = [('weight', o * k + t) for t in range(k)] + [('bias', o)]
        new_w = [('weight', (q // hw) * k + t) for t in range(k)] + [('bias', q // hw)]
        assert old == new and old_w == new_w
        count += 1
    k = kh * kw
    for q in range(ci * hw):
        c, y, x = q // hw, (q // wo) % ho, q % wo
        old = [window(sh, y, x, c * k + t) for t in range(k)] + [('one',)]
        new = [window(sh, y, x, c * k + t) for t in range(k)] + [('one',)]
        assert old == new
        count += 1
    return count

def dense(rows, inw, outw):
    count = 0
    for q in range(rows * outw):
        i, j = q // outw, q % outw
        left = [('X', i * inw + t) for t in range(inw)] + [('one',)]
        right = [('W', j * inw + t) for t in range(inw)] + [('bias', j)]
        cached_left = [('X', (q // outw) * inw + t) for t in range(inw)] + [('one',)]
        cached_right = [('W', (q % outw) * inw + t) for t in range(inw)] + [('bias', q % outw)]
        assert left == cached_left and right == cached_right
        count += 1
    return count

def gemm(batch, m, k, n):
    count = 0
    for q in range(batch * m * n):
        beta, i, j = q // (m * n), (q // n) % m, q % n
        olda = [(beta * m + i) * k + t for t in range(k)]
        oldb = [(beta * k + t) * n + j for t in range(k)]
        r, c = beta * m + i, beta * n + j
        newa = [r * k + t for t in range(k)]
        newb = [((c // n) * k + t) * n + c % n for t in range(k)]
        assert olda == newa and oldb == newb
        count += 1
    return count

def main():
    began = time.monotonic()
    rng = random.Random(26029)
    conv_shapes = 0
    outputs = 0
    zero_extents = 0
    for _ in range(800):
        sh = tuple(rng.randrange(4) for _ in range(8))
        outputs += conv(sh)
        conv_shapes += 1
        zero_extents += sh[0] == 0 or sh[3] == 0
    dense_shapes = gemm_shapes = 0
    for rows in range(5):
        for inw in range(5):
            for outw in range(5):
                outputs += dense(rows, inw, outw)
                dense_shapes += 1
    for batch in range(4):
        for m in range(4):
            for k in range(5):
                for n in range(4):
                    outputs += gemm(batch, m, k, n)
                    gemm_shapes += 1
    report = {'scope': 'Finite symbolic address and term-order reproduction only; no Lean/native or all-input proof',
              'conv_and_depthwise_shapes': conv_shapes, 'dense_shapes': dense_shapes,
              'gemm_shapes': gemm_shapes, 'output_sequences_checked': outputs,
              'conv_shapes_with_zero_channel_extent': zero_extents,
              'failures': [], 'elapsed_seconds': time.monotonic() - began}
    (HERE / 'index-falsifier.json').write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(report, indent=2))

if __name__ == '__main__':
    main()
