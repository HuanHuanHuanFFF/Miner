"""Requested final cheap representation discriminator; frozen C is unchanged."""
from pathlib import Path
import datetime
import hashlib
import json
import re
from cost_source_preflight import align, block16, round_c, signed, MASK64

HERE=Path(__file__).resolve().parent


def extend(w):
    assert 0<=w<1<<32
    return ((w^0x80000000)-0x80000000)&MASK64


def run():
    header=HERE/'integer_cost_fixture.h'
    arrays={name:[int(x,16) for x in re.findall(r'0x([0-9a-f]{8})u',body)]
            for name,n,body in re.findall(r'static uint32_t (\w+)\[(\d+)\] = \{(.*?)\};',header.read_text(),re.S)}
    records=[]
    for case in range(2):
        x,lx,sx=align(arrays[f'input_{case}']);n=len(x)
        assert sx<=7 and all(abs(signed(q,64))<1<<31 for q in x)
        xu=[q&0xffffffff for q in x]
        ex=[extend(q) for q in xu]
        assert ex==x
        w=arrays[f'weight_{case}'];bias=arrays[f'bias_{case}'];expected=arrays[f'expected_{case}']
        for j in range(80):
            y,ly,sy=align(w[j*n:(j+1)*n]);assert sy<=7
            assert all(abs(signed(q,64))<1<<31 for q in y)
            yu=[q&0xffffffff for q in y];ey=[extend(q) for q in yu]
            assert ey==y
            total=block16(ex,ey)
            bw=bias[j];e=(bw>>23)&255;mant=(bw&0x7fffff)+(0x800000 if e else 0)
            shift=max(e-1,0)+149-lx-ly
            b=mant<<shift
            if bw>>31:b=-b
            out=round_c(total+b,lx+ly-298)
            assert out==expected[j]
            records.append({'case':case,'output':j,'spans':[sx,sy],
                            'both_signed31_guard':True,'both_word_roundtrips':True,
                            'word_equal':True,'relu_word':0 if out>>31 else out})
    boundary_words=[0,1,0x3fffffff,0x40000000,0x7ffffffe,0x7fffffff,
                    0x80000000,0x80000001,0xbfffffff,0xc0000000,0xfffffffe,0xffffffff]
    boundary=[]
    for w in boundary_words:
        q=extend(w);integer=w if w<1<<31 else w-(1<<32)
        assert signed(q,64)==integer
        boundary.append({'u32':w,'extended_u64':q,'signed_integer':integer,'equal':True})
    # Complete reduced-width instance of the same XOR/sub identity; not a
    # replacement for the all-UInt32 mathematical argument or Lean proof.
    for w in range(256):
        q=((w^128)-128)&65535
        assert signed(q,16)==(w if w<128 else w-256)
    out={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
         'status':'FINITE_WORD_REPRESENTATION_CHECK_NOT_LEAN_OR_NATIVE',
         'identity':'((zeroExtend64(w32) xor 2^31) - 2^31) mod2^64 = signed32(w32) mod2^64',
         'typical_narrow_dots':len(records),'signed31_guard_accepts':sum(r['both_signed31_guard'] for r in records),
         'operand_word_access_roundtrips':len(records)*2*608,
         'records':records,'boundary_words':boundary,'reduced_width_exhaustive_cases':256,
         'additional_source_ops_per_MAC':{'xor64':2,'sub64':2,'operand_unboxes':2},
         'source_ops_not_instruction_or_timing_count':True,
         'wide_ungrouped':'Original term93bit rejection unchanged; no new acceptance claim.',
         'source_hashes':{p.name:hashlib.sha256(p.read_bytes()).hexdigest()
                          for p in (Path(__file__),HERE/'cost_source_preflight.py',header,HERE/'integer_cost_probe_relu.c')},
         'limits':['Array UInt32 on64-bit runtime has8-byte object/immediate slots, not4-byte packed storage.',
                   'No frozen C source changed, no CI/native/Lean launched.',
                   'Compiler may optimize xor/sub into sign-extension, but no generated-code claim is made.']}
    (HERE/'signextend32-probe.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({k:out[k] for k in ('status','typical_narrow_dots','signed31_guard_accepts','operand_word_access_roundtrips','additional_source_ops_per_MAC')}))


if __name__=='__main__':run()
