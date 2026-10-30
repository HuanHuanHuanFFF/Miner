"""Reconstruct a bounded native-only packed probe from exact public source27.

No third-party source is embedded or published. Only plain, unreferenced proof
declarations are removed. All pre-existing runtime definition bodies remain
byte-identical, except renaming the final baseline record. There is deliberately
NO Submission.correct for the new runtime. The original statement gate must
reject this diagnostic; original intake/policy and native timing remain useful.
"""
from __future__ import annotations
import argparse
from datetime import datetime,timezone
import hashlib,json,re
from pathlib import Path

BASE_SHA256="f92ee2c9a29de78dc434ad158b7141c0e4b5a67a5a198a353d59a4703481aa67"
STOP=re.compile(r"(?m)^(?:(?:@\[[^\n]*\]\s*)?(?:(?:noncomputable|private|protected|unsafe)\s+)*(?:def|theorem|lemma|structure|abbrev)\b|section\b|end\b|open\b|set_option\b|attribute\b|namespace\b)")
PLAIN_PROOF=re.compile(r"(?m)^(lemma|theorem) ([A-Za-z_][A-Za-z_0-9'.]*)\b")
RUNTIME=re.compile(r"(?m)^(?:@\[[^\n]*\]\s*)?(?:(?:noncomputable|private|protected|unsafe)\s+)*(?:def|structure|abbrev) ([A-Za-z_][A-Za-z_0-9'.]*)\b")


def spans(source,pattern):
    bounds=[m.start()for m in STOP.finditer(source)]
    return [(m,next((v for v in bounds if v>m.start()),len(source)))for m in pattern.finditer(source)]


def runtime_inventory(source):
    return {m.group(1):hashlib.sha256(source[m.start():end].rstrip().encode()).hexdigest()
            for m,end in spans(source,RUNTIME)}


def prune(source):
    removed=[]
    while True:
        cuts=[]
        for m,end in spans(source,PLAIN_PROOF):
            name=m.group(2)
            refs=len(re.findall(r"(?<![\w'])"+re.escape(name)+r"(?![\w'])",source))
            if name=="correct"or refs==1:
                raw=source[m.start():end].encode()
                cuts.append((m.start(),end))
                removed.append({"name":name,"bytes":len(raw),"sha256":hashlib.sha256(raw).hexdigest(),"reference_count":refs})
        if not cuts:return source,removed
        for start,end in reversed(cuts):source=source[:start]+source[end:]


def transform(raw,owned_root):
    assert hashlib.sha256(raw).hexdigest()==BASE_SHA256
    source=raw.decode();assert "\r"not in source
    before=runtime_inventory(source)
    source,removed=prune(source)
    after=runtime_inventory(source)
    assert before==after,"Runtime definition changed during proof pruning"
    assert source.count("def kernels:Kernels where")==1
    source=source.replace("def kernels:Kernels where","def retainedKernels:Kernels where")
    runtime=(owned_root/'PackedLinearRuntime.lean').read_text(encoding='utf-8')
    assert runtime.startswith('import ContractExact\n')
    runtime=runtime.removeprefix('import ContractExact\n')
    binding=(owned_root/'PackedBinding.lean.inc').read_text(encoding='utf-8').replace('Submission.kernels','Submission.retainedKernels')
    source += '\n'+runtime+'\n'+binding+'\nnamespace Submission\ndef kernels : ExactRuntime.Kernels := R27PackedExperiment.kernels\nend Submission\n'
    result=source.encode()
    assert len(result)<=256000
    assert [l for l in source.splitlines()if l.startswith('import ')]==['import ContractExact']
    assert not re.search(r'(?m)^(?:theorem|def) correct\b',source)
    return result,removed,before


def main():
    p=argparse.ArgumentParser();p.add_argument('--source',type=Path,required=True);p.add_argument('--output',type=Path,required=True);p.add_argument('--receipt',type=Path,required=True);a=p.parse_args()
    root=Path(__file__).resolve().parent
    result,removed,inventory=transform(a.source.read_bytes(),root)
    a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    receipt={'created_utc':datetime.now(timezone.utc).isoformat(),'state':'UNCOMPILED_NATIVE_ONLY_NO_SUBMISSION_CORRECT',
             'base_submission':27,'base_sha256':BASE_SHA256,'candidate_sha256':hashlib.sha256(result).hexdigest(),'candidate_bytes':len(result),
             'patch_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
             'owned_dependencies':{name:{'sha256':hashlib.sha256((root/name).read_bytes()).hexdigest(),'bytes':(root/name).stat().st_size}for name in['PackedLinearRuntime.lean','PackedBinding.lean.inc']},
             'retained_runtime_definitions':inventory,'removed_proof_declarations':removed,
             'entry':'Submission.kernels; two Mixer channel-linear calls changed for rows>=8; old GEMM/classifier retained',
             'proof_boundary':'NO Submission.correct. Runtime inventory preserved is not a proof of the new packed algorithm. Original statement gate must not be reported passed.',
             'publication':'Owned patch/metadata only; whole reconstructed source remains private'}
    a.receipt.write_text(json.dumps(receipt,indent=2),encoding='utf-8')
    print(json.dumps({k:receipt[k]for k in['state','candidate_sha256','candidate_bytes','patch_sha256']}|{'removed_proofs':len(removed),'retained_runtime_definitions':len(inventory)}))


if __name__=='__main__':main()
