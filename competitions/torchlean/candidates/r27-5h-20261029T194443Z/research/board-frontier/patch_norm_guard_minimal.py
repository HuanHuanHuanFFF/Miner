"""Owned proof-only packaging refinement for the already verified guard26 runtime.

No added helper or wider policy limits: qa<3*2^61 is sufficient because bias
magnitude<2^61 still implies qi<2^63. Whole third-party source stays private.
"""
from __future__ import annotations
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json
from pathlib import Path

HERE=Path(__file__).resolve().parent
ALLOWED={
 'e2c1f1f1ba52e32563fb193ceea7e2a271b989fd3ba2eb16cff747987879b521':'source12',
 '1bd6e15375a83e59ca1ec276fac0b2898cadd07abf560ef7140e1f6bf4463e8b':'native-layer-stats-v1-hb'
}

def once(text,old,new):
    assert text.count(old)==1,(old,text.count(old))
    return text.replace(old,new)

def transform(raw,submission=12,variant='guard26-minimal'):
    assert submission==12 and variant=='guard26-minimal'
    assert hashlib.sha256(raw).hexdigest()in ALLOWED
    source=raw.decode('utf-8')
    start=source.index('@[inline] def Ya7G ');end=source.index('\nend\n',start)
    body=once(source[start:end],'ks <= 8','ks <= 26');source=source[:start]+body+source[end:]
    start=source.index('lemma Ya7Ge ');end=source.index('\ndef MYbc ',start)
    proof=source[start:end]
    for old,new in [('ks ≤ 8','ks ≤ 26'),('ks.toNat ≤ 8','ks.toNat ≤ 26'),
                    ('2^ks.toNat <= 2^8','2^ks.toNat <= 2^26'),('2^36*2^8','2^36*2^26')]:
        proof=once(proof,old,new)
    assert proof.count('2^44')==3;proof=proof.replace('2^44','2^62')
    proof=once(proof,'have hqab:qa.toNat < 2^62:=','have hqab:qa.toNat < 3*2^61:=')
    result=(source[:start]+proof+source[end:]).encode()
    assert len(result)<=256000
    return result

def main():
    p=argparse.ArgumentParser();p.add_argument('--source',type=Path,required=True);p.add_argument('--output',type=Path,required=True);p.add_argument('--receipt',type=Path,required=True);p.add_argument('--verified-runtime',type=Path);a=p.parse_args()
    raw=a.source.read_bytes();result=transform(raw)
    match=None
    if a.verified_runtime:
        spec=importlib.util.spec_from_file_location('r27_inventory',HERE/'build_packed_probe.py');m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
        match=m.runtime_inventory(a.verified_runtime.read_text(encoding='utf-8'))==m.runtime_inventory(result.decode())
        assert match
    a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    r={'created_utc':datetime.now(timezone.utc).isoformat(),'state':'PROOF_PACKAGING_REFINEMENT_UNCOMPILED_NOT_NEW_GATE_PASS',
       'input_sha256':hashlib.sha256(raw).hexdigest(),'input_name':ALLOWED[hashlib.sha256(raw).hexdigest()],
       'candidate_sha256':hashlib.sha256(result).hexdigest(),'candidate_bytes':len(result),'delta_bytes':len(result)-len(raw),
       'builder_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
       'runtime_declaration_bytes_equal_to_verified_dced':match,
       'argument':'qqShift<2^61 and ra/D<=ra<2^62 imply qa<3*2^61. Adding |bias|<2^61 gives qi<2^63; doubling qi remains within UInt64.',
       'boundary':'Fresh full gate required for this exact proof source; do not inherit the dced certificate. Graft combination is a separate runtime and needs full validation.',
       'publication':'Owned patch/receipt only; whole source private'}
    a.receipt.write_text(json.dumps(r,indent=2),encoding='utf-8');print(json.dumps(r))

if __name__=='__main__':main()
