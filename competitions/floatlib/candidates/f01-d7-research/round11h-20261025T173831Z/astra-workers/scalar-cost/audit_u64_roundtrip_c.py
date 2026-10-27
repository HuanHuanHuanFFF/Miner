"""Bind Lean diagnostic C to its input; extract actual suite callback and numeric roundtrip chains.
Read-only inputs. Writes only to a NEW --out directory. No compiler, runner, C execution or timing.
The range annotations are semantic source bounds, NEVER claims about Clang optimizations.
"""
from pathlib import Path
from collections import defaultdict, Counter
import argparse, hashlib, json, re
from datetime import datetime, timezone

def sha(b): return hashlib.sha256(b).hexdigest()
def identity(p):
    b=p.read_bytes();return {'path':str(p.resolve()),'bytes':len(b),'sha256':sha(b)}
def masked(s):
    return re.sub(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'',
        lambda m: re.sub(r'[^\n]',' ',m.group()),s,flags=re.S)
def functions(s,module):
    code=masked(s);out={}
    for m in re.finditer(r'(?m)^(?:LEAN_EXPORT|static)[^\n;{}]*?\b(\w+)\s*\(([^;\n]*)\)\s*\{',code):
        a=code.index('{',m.start());b=a+1;depth=1
        while depth and b<len(code): depth+=(code[b]=='{')-(code[b]=='}');b+=1
        if depth:raise ValueError('Unbalanced generated C function '+m.group(1))
        text=s[m.start():b]
        out[m.group(1)]={'module':module,'line':s.count('\n',0,m.start())+1,'text':text,
            'sha256':sha(text.encode()),'bytes':len(text.encode())}
    return out
def calls(text):
    return Counter(n for n in re.findall(r'\b(\w+)\s*\(',masked(text))
        if n not in {'if','while','switch','sizeof','return','for'})
def select_suite(main_source,funcs,op):
    if '_lean_main' not in funcs:return {'state':'UNKNOWN','reason':'No _lean_main definition in supplied C'}
    s=funcs['_lean_main']['text'];matches=list(re.finditer(r'\b(\w*Bench_Suite_run)\s*\(([^;\n]+)\)',s))
    if len(matches)!=1:return {'state':'UNKNOWN','reason':'Expected exactly one Bench.Suite.run call','calls':len(matches)}
    m=matches[0];args=[a.strip() for a in m.group(2).split(',')]
    arg=args[{'add':0,'mul':1,'sum':2,'bmm':3}[op]]
    assignments=list(re.finditer(r'\b'+re.escape(arg)+r'\s*=\s*\(\(lean_object\*\)\((\w+)\)\)',s[:m.start()]))
    if not assignments:return {'state':'UNKNOWN','reason':'Suite argument closure assignment not recognized','argument':arg}
    closure=assignments[-1].group(1)
    cm=re.search(re.escape(closure)+r'_value\s*=\s*\{[^;]*?\.m_fun\s*=\s*\(void\*\)(\w+)',main_source,re.S)
    if not cm:return {'state':'UNKNOWN','reason':'Static closure initializer not recognized','closure':closure}
    boxed=cm.group(1);unboxed=boxed.removesuffix('___boxed')
    if boxed not in funcs or unboxed not in funcs or (boxed!=unboxed and unboxed not in calls(funcs[boxed]['text'])):
        return {'state':'UNKNOWN','reason':'Boxed to unboxed connection not established','boxed':boxed}
    return {'state':'BOUND_GENERATED_C_ONLY','operation':op,'argument':arg,'closure':closure,
        'boxed':boxed,'unboxed':unboxed,'line':funcs[unboxed]['line']}

def numeric_chains(text):
    """Conservative local SSA inspection. Unknown/merged calls never become invented bounds."""
    code=masked(text);defs=defaultdict(list)
    for m in re.finditer(r'(?m)^\s*(\w+)\s*=\s*([^;\n]+);',code):defs[m.group(1)].append(m.group(2).strip())
    def unique(v):return defs[v][0] if len(defs.get(v,[]))==1 else v
    def literal(v):
        x=re.sub(r'[uUlL]+$','',v.strip())
        return int(x,0) if re.fullmatch(r'(?:0[xX][0-9a-fA-F]+|[0-9]+)',x) else None
    def parse(v):
        m=re.fullmatch(r'(\w+)\((.*)\)',v)
        return (m.group(1),[a.strip() for a in m.group(2).split(',')]) if m else (None,[])
    def rng(v,seen=frozenset()):
        n=literal(v)
        if n is not None:return [n,n]
        if v in seen or len(seen)>30:return None
        expr=unique(v)
        if expr!=v:return rng(expr,seen|{v})
        f,args=parse(v)
        if not f:return None
        if f in ('lean_uint32_to_uint64','lean_uint64_to_uint32'):
            r=rng(args[0],seen|{v})
            return r if r and (f.endswith('to_uint64') or r[1]<2**32) else None
        if f in ('lean_uint32_land','lean_uint64_land'):
            rs=[rng(a,seen|{v}) for a in args]
            constants=[r[0] for r in rs if r and r[0]==r[1]]
            return [0,min(constants)] if constants else None
        if f in ('lean_uint32_lor','lean_uint64_lor'):
            a,b=(rng(x,seen|{v}) for x in args)
            if not a or not b:return None
            if a[0]==a[1]:a,b=b,a
            if b[0]==b[1] and a[0]==0 and a[1]&(a[1]+1)==0 and b[0]&a[1]==0:
                return [b[0],a[1]+b[0]]
            return [0,2**max(a[1],b[1]).bit_length()-1]
        if f=='lean_uint64_mul':
            a,b=(rng(x,seen|{v}) for x in args)
            if a and b and a[1]*b[1]<2**64:return [a[0]*b[0],a[1]*b[1]]
        return None
    def rounded(n):
        k=max(0,n.bit_length()-24)
        if k==0:return n
        q,r=divmod(n,1<<k);h=1<<(k-1)
        return (q+(r>h or (r==h and q&1)))<<k
    rows=[]
    for m in re.finditer(r'(?m)^\s*(\w+)\s*=\s*(lean_float32_to_(?:uint64|int64))\((\w+)\);',code):
        value,reverse,arg=m.groups();fwd,args=parse(unique(arg));p_range=None;form='UNKNOWN'
        if fwd in ('lean_uint64_to_float32','lean_int64_to_float32') and args:p_range=rng(args[0])
        if fwd=='lean_uint64_to_float32':form='B_UNSIGNED_INTEGER_PRODUCT'
        if fwd=='lean_int64_to_float32':form='SIGNED_FORWARD_VARIANT'
        if fwd=='lean_float32_mul' and len(args)==2:
            form='A_TWO_U32_CASTS_FP_PRODUCT';rr=[]
            for x in args:
                name,aa=parse(unique(x));rr.append(rng(aa[0]) if name=='lean_uint32_to_float32' and aa else None)
            if all(r and r[1]<=2**24 for r in rr):p_range=[rr[0][0]*rr[1][0],rr[0][1]*rr[1][1]]
        R=[rounded(p_range[0]),rounded(p_range[1])] if p_range else None
        line=text.count('\n',0,m.start())+1;lines=text.splitlines()
        rows.append({'reverse_result':value,'reverse_primitive':reverse,'form':form,'forward_expression':unique(arg),
          'forward_primitive':fwd,'relative_line':line,'visible_integer_input_bound':p_range,
          'semantic_RNE24_value_bound':R,
          'range_below_2pow63':R[1]<2**63 if R else 'UNKNOWN',
          'reverse_source_callee':'external lean_float32_isnan inside the inline primitive' if reverse=='lean_float32_to_int64' else 'no external subcall in fixed inline primitive; 0/2^64 clamp comparisons',
          'note':'Bounds are inferred from visible integer masks/multiply and specified RNE; compiler propagation/elimination UNKNOWN.',
          'snippet':'\n'.join(lines[max(0,line-14):line+12])})
    return rows

def self_test():
    sample='''uint32_t u; uint32_t v;
mask = 8388607;
hidden = 8388608;
a0 = lean_uint32_land(u, mask);
a = lean_uint32_lor(a0, hidden);
b0 = lean_uint32_land(v, mask);
b = lean_uint32_lor(b0, hidden);
aa = lean_uint32_to_uint64(a);
bb = lean_uint32_to_uint64(b);
p = lean_uint64_mul(aa, bb);
f = lean_uint64_to_float32(p);
r = lean_float32_to_uint64(f);
'''
    rows=numeric_chains(sample)
    assert len(rows)==1 and rows[0]['visible_integer_input_bound']==[2**46,(2**24-1)**2]
    assert rows[0]['semantic_RNE24_value_bound']==[2**46,2**48-2**25]
    unknown=numeric_chains('f = lean_uint64_to_float32(external_p);\nr = lean_float32_to_uint64(f);')
    assert unknown[0]['visible_integer_input_bound'] is None
    wiring='''static const lean_closure_object slot93_value = {.m_fun = (void*)renamed_op___boxed};
LEAN_EXPORT uint32_t renamed_op(uint32_t a, uint32_t b){ return a; }
LEAN_EXPORT lean_object* renamed_op___boxed(lean_object* a, lean_object* b){ return renamed_op(a,b); }
LEAN_EXPORT lean_object* _lean_main(){
callback = ((lean_object*)(slot93));
result = lp_competition_Bench_Suite_run(other, callback, sum, bmm);
return result;
}
'''
    ff=functions(wiring,'MainFull');sel=select_suite(wiring,ff,'mul')
    assert sel['unboxed']=='renamed_op' and sel['closure']=='slot93'
    assert select_suite('',{},'mul')['state']=='UNKNOWN'
    print(json.dumps({'state':'PARSER_SELF_TEST_PASS_NOT_CODEGEN','tests':4,'known_bound':rows[0]['visible_integer_input_bound']}))

def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--diag',type=Path);ap.add_argument('--input',type=Path);ap.add_argument('--expected-sha')
    ap.add_argument('--operation',choices=['add','mul','sum','bmm'],default='mul')
    ap.add_argument('--focus-pattern',default='R17NumericMulInteger');ap.add_argument('--out',type=Path)
    ap.add_argument('--self-test',action='store_true');a=ap.parse_args()
    if a.self_test:self_test();return
    if any(x is None for x in [a.diag,a.input,a.expected_sha,a.out]):ap.error('--diag/--input/--expected-sha/--out required')
    ki=identity(a.input)
    if ki['sha256']!=a.expected_sha:raise ValueError('Input hash mismatch')
    index_path=a.diag/'candidate-c-index.json';index=json.loads(index_path.read_bytes());funcs={};sources=[];main_source=''
    for row in index:
        p=a.diag/row['file'];i=identity(p)
        if i['sha256']!=row['sha256'] or row['kernel_sha256']!=a.expected_sha:raise ValueError('C/input binding mismatch: '+str(p))
        s=p.read_bytes().decode();sources.append({**i,'module':row['module'],'capture_scope':row.get('scope','UNKNOWN')})
        if row['module']=='MainFull':main_source=s
        for name,f in functions(s,row['module']).items():
            if name in funcs:raise ValueError('Duplicate generated function: '+name)
            funcs[name]=f
    selection=select_suite(main_source,funcs,a.operation)
    reachable=set();queue=[selection['unboxed']] if selection['state']=='BOUND_GENERATED_C_ONLY' else []
    while queue and len(reachable)<32:
        n=queue.pop(0)
        if n in reachable:continue
        reachable.add(n)
        queue.extend(k for k in calls(funcs[n]['text']) if k in funcs and k!=n and k not in reachable)
    targets=[]
    if selection['state']=='BOUND_GENERATED_C_ONLY':targets.append(selection['unboxed'])
    targets+=sorted(n for n in funcs if a.focus_pattern and re.search(a.focus_pattern,n) and not n.endswith('___boxed'))
    targets=list(dict.fromkeys(targets));a.out.mkdir(parents=True,exist_ok=False)
    reports=[]
    for n in targets:
        f=funcs[n];c=calls(f['text']);islands=numeric_chains(f['text'])
        (a.out/(n+'.c')).write_bytes(f['text'].encode())
        reports.append({k:f[k] for k in ['module','line','sha256','bytes']}|{'symbol':n,'C_header':f['text'].splitlines()[0],
          'scope':'selected suite callback' if n==selection.get('unboxed') else ('reachable generated helper; branch not established' if n in reachable else 'diagnostic/helper; not shown reachable from suite callback'),
          'primitive_static_sites':{k:v for k,v in c.items() if k.startswith('lean_')},
          'generated_callees':[k for k in c if k in funcs and k!=n],
          'roundtrip_chains':islands,'whole_body_toBits_sites':c.get('lean_float32_to_bits',0),
          'Nat_or_heap_or_apply_sites':{k:v for k,v in c.items() if k.startswith(('lean_nat_','lean_alloc_','lean_apply_','lean_big_')) or k in ['lean_box_uint64','lean_box_float32','lean_uint64_to_nat','lean_uint32_to_nat']},
          'warning':'All counts are static sites, including alternative fallback branches. Primitive names in C are not by themselves external calls.'})
    asm=[];asmindex=a.diag/'native-assembly-index.json'
    if asmindex.exists():
        for row in json.loads(asmindex.read_bytes()):
            if row.get('kind')!='actual-built-object-disassembly':continue
            p=a.diag/row['file'];i=identity(p)
            if i['sha256']!=row['sha256'] or row.get('kernel_sha256')!=a.expected_sha:raise ValueError('ASM binding mismatch')
            if row.get('symbol') not in targets:continue
            lines=p.read_text().splitlines()
            hints=[{'line':j+1,'text':x} for j,x in enumerate(lines) if re.search(r'call|jmp|R_X86_64|cvt|comis|subss|addss|5f000000|5f800000|8000000000000000|9223372036854775808|18446744073709551616',x,re.I)]
            asm.append({**i,'symbol':row['symbol'],'object_sha256_from_index':row.get('object_sha256'),
              'capture_scope':row.get('scope','UNKNOWN'),'hints_only':hints[:120]})
    report={'created_utc':datetime.now(timezone.utc).isoformat(),'state':'BOUND_STATIC_EXTRACTION_COMPLETE',
      'input':ki,'C_index':identity(index_path),'sources':sources,'suite_selection':selection,'functions':reports,
      'selected_callback_has_DIRECT_numeric_roundtrip':any(f['symbol']==selection.get('unboxed') and f['roundtrip_chains'] for f in reports) if selection['state']=='BOUND_GENERATED_C_ONLY' else 'UNKNOWN',
      'selected_generated_reachability':{'functions':sorted(reachable),'truncated_at_32':bool(queue),'scope':'C call-graph reachability includes cold branches; not dynamic execution'},
      'reachable_reviewed_roundtrip_functions':[f['symbol'] for f in reports if f['symbol'] in reachable and f['roundtrip_chains']],
      'ASM_for_targets':asm,'clamp_elimination':'UNKNOWN_FROM_C; inspect accepted-path optimized object/IR and constants',
      'unsigned_2pow63_adjustment':'UNKNOWN_UNLESS_BOUND_ASM_INSPECTED; hint absence is not proof of elimination',
      'timed_ELF_identity':'UNKNOWN unless separately bound; capture scope above preserved',
      'fixed_runtime_interpretation':{'UInt64_to_Float32':'static inline C cast; possible unsigned lowering at2^63 is not shown by this C site',
       'Float32_to_UInt64':'static inline 0<=a and a<2^64 clamp plus unsigned cast; no external subcall in fixed header',
       'Float32_to_Int64':'static inline body includes an external lean_float32_isnan call, then signed clamps/cast',
       'lean_box_uint64':'heap-allocating helper, unlike tagged UInt32 boxes on64-bit; presence must be traced to the actual path'},
      'limitations':'No C execution or compiler used. Diagnostic/helper code is not the official timed callback. Source semantic ranges do not turn Lean proof hypotheses into optimizer assumptions. No speed prediction.'}
    (a.out/'audit.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({'state':report['state'],'selection':selection,'functions':len(reports),'roundtrip_chains':sum(len(r['roundtrip_chains']) for r in reports),'bound_target_ASM':len(asm),'report':str(a.out/'audit.json')},indent=2))

if __name__=='__main__':main()
