"""Finite source-bound machine-index falsifier. No Float32/Lean/native execution."""
from pathlib import Path
import hashlib
import itertools
import json
import re

HERE = Path(__file__).resolve().parent
ZERO = ('PAD_ZERO',)
sha = lambda b: hashlib.sha256(b).hexdigest()


def wiring(raw):
    s = raw.decode()
    hot = s.split('def wordLoop ', 1)[1].split('structure TileBounds ', 1)[0]
    mapping = re.findall(r'\(q(\d)(\d) \+ f(\d) \* b\.s(\d)\)', hot)
    assert mapping == [(str(r), str(c), str(r), str(c)) for c in range(2) for r in range(4)]
    assert hot.count('A.uget (a') == 4 and hot.count('cache.uget cursor hb') == 1
    assert '.getD' not in hot and '.push' not in hot and '.map' not in hot
    assert '(k + 1) (cursor + stride) nextB' in hot
    assert s.count('let cache := R22Pair8.packB batch n p B.toArray') == 1
    assert 'if h : n < USize.size ∧ A.toArray.size < USize.size ∧ cache.size < USize.size then' in s
    assert 'else if h : 1 < n ∧ 4 ≤ m ∧ 2 ≤ p then core' in s
    assert 'else Submission.bmm batch m n p A B' in s
    old = (HERE.parent / 'development-resident8/Resident8.lean.inc').read_text(encoding='utf-8')
    take = lambda t: re.sub(r'\s+', '', t.split('match r with',1)[1].split('\ndef tiles ',1)[0]).replace('(0:UInt32)','0')
    assert take(s) == take(old), 'finish/Words body differs'
    tail = 'RowStream.emit ((m % 4) * p) (fun j => NativeFinal.dot n\n    ((b * m + m / 4 * 4 + j.val / p) * n) (b * n * p + j.val % p) p A B) out'
    assert tail in old and tail in s
    assert not re.search(r'\b(sorry|axiom|unsafe|extern|implemented_by)\b', s)


def ref(batch, m, n, p):
    return [((b*m+r)*n, b*n*p+j,
        tuple(((b*m+r)*n+k, b*n*p+k*p+j) for k in range(n)))
        for b in range(batch) for r in range(m) for j in range(p)]


def run(shape, word, mutation=None):
    batch, m, n, p = shape
    g = (p+1)//2
    acount, ccount = batch*m*n, batch*n*g
    shape_hit = n>1 and m>=4 and p>=2
    native_hit = n<word and acount<word and ccount<word
    if mutation == 'ignore_cache_guard': native_hit = n<word and acount<word
    if mutation == 'ignore_A_guard': native_hit = n<word and ccount<word
    if not shape_hit or not native_hit:
        return ref(*shape), 0, False
    cache = [(b*n*p+k*p+2*c, b*n*p+k*p+2*c+1 if 2*c+1<p else ZERO)
             for b in range(batch) for k in range(n) for c in range(g)]
    out, wraps = [], 0
    for b in range(batch):
        for block in range(m//4):
            bases = [((b*m+4*block)*n+r*n)%word for r in range(4)]
            if mutation == 'A3_base': bases[3] = bases[2]
            tiles = []
            for c in range(g):
                cur = (b*n*g+c)%word
                if mutation == 'B_start': cur = (b*n*g+2*c)%word
                k, count = 0, n%word
                if mutation == 'short_count': count = (n-1)%word
                q = [[[] for _ in range(2)] for _ in range(4)]
                while k<count:
                    assert cur<len(cache), ('cache bound',shape,word,cur)
                    bp = cache[cur]
                    for r in range(4):
                        ai = (bases[r]+k)%word
                        assert ai<acount, ('A bound',shape,word,ai)
                        for col in range(2): q[r][col].append((ai,bp[col]))
                    k = (k+1)%word
                    cur = (cur+g+(1 if mutation=='B_stride' else 0))%word
                # An unused final cursor may wrap. No read occurs after k=count.
                if b*n*g+c+n*g>=word: wraps += 1
                tiles.append(q)
            for r in range(4):
                for j in range(p):
                    out.append(((b*m+4*block+r)*n,b*n*p+j,tuple(tiles[j//2][r][j%2])))
        for r in range(4*(m//4),m):
            for j in range(p):
                out.append(((b*m+r)*n,b*n*p+j,
                    tuple(((b*m+r)*n+k,b*n*p+k*p+j) for k in range(n))))
    return out, wraps, True


def main():
    src = (HERE / 'IndexedResident8.lean.inc').read_bytes()
    wiring(src)
    code_mutations = {
        'MAC_A_lane': (b'q31 + f3 * b.s1', b'q31 + f2 * b.s1'),
        'MAC_B_lane': (b'q20 + f2 * b.s0', b'q20 + f2 * b.s1'),
        'finish_raw_base': (b'finish n (baseA + 3 * n) baseB',b'finish n baseA baseB'),
        'duplicate_guard_field': (b'cache.size < USize.size then',b'A.toArray.size < USize.size then'),
        'native_cursor_update': (b'(cursor + stride) nextB',b'(cursor + 1) nextB')}
    source_caught = {}
    for name,(before,after) in code_mutations.items():
        assert before in src
        try: wiring(src.replace(before,after,1))
        except AssertionError: source_caught[name]=True
        else: raise AssertionError(name)
    shapes = list(itertools.product(range(4),range(12),range(7),range(10)))
    words = (16,32,64,256,2**32,2**64)
    special = [(1,4,3,9),(1,4,2,15),(1,4,16,2),(1,4,17,2),(2,4,3,5)]
    all_shapes = shapes+special
    runs, native, fallback, wraps, first_wrap = 0,0,0,0,None
    for word in words:
        for shape in all_shapes:
            out,w,hit = run(shape,word)
            assert out==ref(*shape),(shape,word)
            runs+=1; native+=hit; fallback+=not hit; wraps+=w
            if w and first_wrap is None: first_wrap={'shape':shape,'word_size':word,'wrapped_terminal_cursors':w}
    assert first_wrap is not None
    model_caught = {}
    for name in ('ignore_cache_guard','ignore_A_guard','A3_base','B_start','B_stride','short_count'):
        for word in words:
            for shape in all_shapes:
                try: bad = run(shape,word,name)[0]!=ref(*shape)
                except AssertionError: bad=True
                if bad:
                    model_caught[name]={'caught':True,'shape':shape,'word_size':word};break
            if name in model_caught:break
        assert name in model_caught,name
    manifest=json.loads((HERE/'indexed8-source-manifest.json').read_bytes())
    assert manifest['fragment_sha256']==sha(src)
    result={'status':'FINITE_MACHINE_ADDRESS_AND_SOURCE_WIRING_PASS',
        'fragment_sha256':sha(src),'kernel_sha256':manifest['sha256'],'runs':runs,
        'shapes':len(all_shapes),'word_sizes':words,'native_runs':native,'Nat_or_shape_fallback_runs':fallback,
        'terminal_wraps':wraps,'first_terminal_wrap':first_wrap,'source_mutations':source_caught,
        'address_mutations':model_caught,
        'limits':'Finite symbolic model only. No Float32/NaN/Lean/native/register/cost claim. Toy word sizes stress proof/cursor wrap; real word sizes also checked.'}
    (HERE/'indexed8-address-screen.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(result))


if __name__=='__main__':main()
