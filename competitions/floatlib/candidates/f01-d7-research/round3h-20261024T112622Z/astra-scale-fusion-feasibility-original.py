"""Ten-minute paper/word-model feasibility screen; no new Kernel or native execution."""
from pathlib import Path
from datetime import datetime,timezone
import ast,hashlib,json,random
HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[4]
ORACLE=ROOT/'competitions/floatlib/research/astra-collab-20261023-r7/nonfinite-oracle.py'
KERNEL=ROOT/'competitions/floatlib/candidates/f01-d12-scalar-combined/Kernel.lean'
sha=lambda b:hashlib.sha256(b).hexdigest()
raw=ORACLE.read_bytes();assert sha(raw)=='3dfaeec2bde1364a4f06abd292f0ba265376da79e678d3827aa88bd33219ad72'
needed={'exp','frac','nan','snan','inf','zero','canon','choose','unpack','rounded','mul'}
tree=ast.parse(raw);env={};exec(compile(ast.Module(body=[n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name in needed],type_ignores=[]),str(ORACLE),'exec'),env)
mul=env['mul'];M=1<<23
word=lambda e,m,sign=0:(sign<<31)|(e<<23)|(m-M)
def scale_word(s,sign=0):
    # Existing scaleBits on synthetic index(s-150) plus original XOR sign.
    e=s-150
    return (sign<<31)|((e-23)<<23) if 24<=e<=254 else sign<<31
def test(ex,ey,mx,my,sx,sy):
    a,b=word(ex,mx,sx),word(ey,my,sy)
    middle=mul(word(150,mx),word(150,my))
    scale=scale_word(ex+ey,sx^sy)
    fused=mul(middle,scale);direct=mul(a,b)
    assert fused==direct,(hex(a),hex(b),hex(fused),hex(direct))
    assert 47<=env['exp'](fused)<=254
    return a,b,middle,scale,fused
mantissas=[M,M+1,M+2,M+3,3*(1<<22),3*(1<<22)+2,3*(1<<22)+6,2*M-2,2*M-1]
sums=[174,175,255,299,300,379,380]
trace=hashlib.sha256();count=0;ties_even=ties_odd=carry=0
for s in sums:
    for ex in sorted({max(1,s-254),min(254,s-1),s//2}):
        ey=s-ex
        for mx in mantissas:
            for my in mantissas:
                for sx in range(2):
                    for sy in range(2):
                        row=test(ex,ey,mx,my,sx,sy);count+=1
                        for v in row:trace.update(v.to_bytes(4,'little'))
                        p=mx*my;shift=p.bit_length()-24;q,rem=divmod(p,1<<shift);half=1<<(shift-1)
                        ties_even+=rem==half and q%2==0;ties_odd+=rem==half and q%2==1
                        carry+=q+int(rem>half or(rem==half and q%2))==1<<24
rng=random.Random(202610241326)
for _ in range(2048):
    s=rng.randint(174,380);ex=rng.randint(max(1,s-254),min(254,s-1));ey=s-ex
    row=test(ex,ey,rng.randrange(M,2*M),rng.randrange(M,2*M),rng.randrange(2),rng.randrange(2));count+=1
    for v in row:trace.update(v.to_bytes(4,'little'))
upper=test(190,190,2*M-1,2*M-1,0,0);assert upper[-1]==0x7f7ffffe
carry_witness=test(190,190,M+1,2*M-2,0,0)
lower_wrong={'s':173,'a':hex(word(86,M)),'b':hex(word(87,M)),
    'original':hex(mul(word(86,M),word(87,M))),'existing_table_scale':hex(scale_word(173)),
    'wrong_extended_fusion':hex(mul(mul(word(150,M),word(150,M)),scale_word(173)))}
assert lower_wrong['original']!=lower_wrong['wrong_extended_fusion']
assert ORACLE.read_bytes()==raw
rec=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='PAPER_DERIVATION_AND_FINITE_WORD_MODEL_NOT_LEAN_PROOF',
    start_utc='2026-10-24T13:26:52Z',scope='Read-only bounded feasibility; no candidate, Lean, nativeFloat32, benchmark, CI, Float64 cast or new axiom.',
    current_kernel_sha256=sha(KERNEL.read_bytes()),oracle_sha256=sha(raw),script_sha256=sha(Path(__file__).read_bytes()),
    domain='Both raw exponents ex,ey in1..254 and174<=s=ex+ey<=380; mx,my=2^23+fraction. Signs arbitrary. Outside domain retains original operation.',
    proposal='RN32(RN32(Float32(mx)*Float32(my))*signed2^(s-300)); both UInt32-toFloat32 mantissa conversions are exact. Two nativeFloat32 multiplies and one existing scaleTable lookup; no generic reassociation assertion.',
    mathematics=[
      'Exact real product is sign*(mx*my)*2^(s-300), with P=mx*my in[2^46,(2^24-1)^2]. First multiplication rounds P to24 significant bits, where h=floorlog2P is46 or47 and the right shift is h-23.',
      'Let R=RNE(P/2^(h-23)), carry=[R=2^24], Mnorm=2^23 if carry elseR. The original normal rounder returns sign, exponent h+s+carry-173, fraction Mnorm-2^23.',
      'The first rounded product is Mnorm*2^(h+carry-23). Multiplication by exact signed2^(s-300) merely changes its exponent if the final word stays normal finite. The same original rounding shift/parity decides R, so no second precision rounding occurs in this domain.',
      'Lower bound: final magnitude>=2^46*2^(174-300)=2^-80, far above minNormal2^-126. The scale itself is normal because q=s-300 ranges-126..80.',
      'Upper380 is SAFE: Pmax=(2^24-1)^2=2^48-2^25+1. Its rounded value is2^48-2^25, so the largest scaled output at380 is2^128-2^105, raw0x7f7ffffe. The generic h=47 carry-to2^48 region is unreachable for these two24bit mantissas. Restricting to379 is unnecessary for overflow safety.',
      'A carry from h=46 to47 is possible: (2^23+1)*(2^24-2)=2^47-2 rounds to2^47. At s380 this yields2^127, still finite. A formal proof must retain this carry branch.',
      'The existing table index is j=(s-150)+256*sign, in24..230 or280..486. scaleBits(j) encodes sign|((s-173)<<23), exactly signed2^(s-300). Synthetic input word(j<<23) satisfies current NormalBand, so existing scaleAt/scale decode machinery applies.',
      'The lower174 bound is tied to this existing table: at173 its index23 returns signedzero, even though the desired power2 is a representable subnormal. Do not weaken the guard without a new table/decode proof.',
      'No zero/subnormal/NaN/Inf outputs arise under the stated input domain; sign is simply XOR. Beyond380 some outputs overflow, so the finite exact-product bridge can no longer be used unconditionally even if a broader scaling theorem might still be true.'
    ],
    reusable_Lean_assets=[
      'Current Kernel R2W01c.mantissa_native_decode: exact UInt32 mantissa-to-native model value.',
      'R2W01b.scaleAt_eq/scaleTable_size/tableIndex_toNat_lt and R2W01c.scale_native_decode: same-width signed power2 lookup; synthetic word/index arithmetic still needs proof.',
      'R2W01c.native_mul_eq_of_raw_model_mul_eq and native_mul_eq_of_decoded_raw_model_mul_eq: finite-input native multiplication bridge with no cross-width cast.',
      'R2W01cModel.mul_eq_of_finite_value/mul_eq_of_scale_decodes: suitable for exact SECOND scaling once the rounded intermediate and finite target are decoded; NOT sufficient to claim the first48bit product is exact.',
      'FastMul.roundP_eq/rseAny_eq/impl_eq/mul_spec: existing word-rounding route to actual model multiplication. A normal-domain word identity can avoid needing a generic library power2-rounding theorem.'
    ],
    missing_formal_steps=[
      'Prove P bounds, h46/47, ties-even quotient/carry bounds, and the stronger maximum excluding h47 carry; no UInt64 wrap.',
      'Identify the actual first native product with the rounded word at ex=ey=150. Its value is roundedP, not exactP.',
      'Prove the normal roundProduct exponent-translation identity: same rounding of P for scale298 and scale(s-2), then exact final scale product. This is the first minimal proof target; still NOT_COMPILED.',
      'Prove combined synthetic-index/sign mapping and native finiteness; bridge second exact scaling and final Binary32 bits to original ExecFloat.mul; retain all outside-domain fallbacks.',
      'Audit transitive axioms/full original obligations and actual lowering/complete timing for any future integration. Fewer multiplies does not establish whole gain; domain guards, table access and live registers may dominate.'
    ],
    history='Bounded search of candidate manifests/research notes found no same same-width mantissa-product+combined-scale route or full timing result. R4 numericdecode, R6 integer normalmul and blockedF64 cast are distinct mechanisms; absence of a local hit is not novelty proof.',
    finite_check=dict(cases=count,directed_tie_even=ties_even,directed_tie_odd=ties_odd,directed_carry=carry,random_cases=2048,seed=202610241326,trace_sha256=trace.hexdigest(),max380=[hex(v) for v in upper],h46_carry380=[hex(v) for v in carry_witness],outside_table_guard_counterexample=lower_wrong,
      limitation='Both sides use a frozen source-derived exact integer oracle. This tests selected boundaries and random words, not all2^46 mantissa pairs, Lean/native execution, an independent hardware oracle or performance.'),
    decision='Mathematically plausible and same-width bridge assets exist; NOT formally closed. First prove the normal roundProduct scaling identity/first-product decode in a future bounded proof probe. Keep8661 as current CI priority; no new candidate now.')
(HERE/'astra-scale-fusion-feasibility.json').write_text(json.dumps(rec,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
print(json.dumps(dict(cases=count,upper380=rec['finite_check']['max380'],carry=rec['finite_check']['h46_carry380'],outside173=lower_wrong,state=rec['state']),indent=2))
