"""Bounded historical source/C intake for the raw-A4 scalar-accumulator question.
No candidate generation, toolchain invocation, or CI dispatch.
"""
from pathlib import Path
from datetime import datetime, timezone
import hashlib,json,re

OUT=Path(__file__).resolve().parent
ROOT=OUT.parents[6]
CAND=ROOT/'competitions/floatlib/candidates'
RESEARCH=CAND/'f01-d7-research'
def sha(x):return hashlib.sha256(x).hexdigest()

def decls(text):
    starts=list(re.finditer(r'(?m)^(?:@\[[^\n]*\]\s*)?(?:private\s+)?(?:partial\s+)?def\s+(\w+)',text))
    for i,m in enumerate(starts):
        end=re.search(r'(?m)^(?:theorem|private theorem|namespace|end |(?:@\[[^\n]*\]\s*)?(?:private\s+)?def)\s*',text[m.end():])
        stop=m.end()+end.start() if end else len(text)
        block=text[m.start():stop]
        yield m.group(1),block

def main():
    matches={}
    paths=sorted(CAND.glob('f01-*/Kernel.lean'))
    for path in paths:
        data=path.read_bytes()
        try:text=data.decode('utf-8-sig')
        except UnicodeDecodeError:continue
        for name,block in decls(text):
            header=block.split(':=',1)[0]
            nfloat=0
            for names in re.findall(r'\(([^():]*?)\s*:\s*Float32\)',header):
                nfloat+=len(names.split())
            raw_sites=len(re.findall(r'(?:ExecFloat\.Binary\.toFloat32|Float32\.ofBits|R19Temporal\.read\s+A)',block))
            if nfloat>=8 and raw_sites>=4:
                digest=sha(block.encode())
                row=matches.setdefault(digest,{'declaration':name,'scalar_float_parameters':nfloat,
                    'raw_conversion_text_sites':raw_sites,'declaration_sha256':digest,
                    'sources':[],'header':header[:1600],
                    'raw_address_lines':[x.strip() for x in block.splitlines() if 'toFloat32' in x or 'ofBits' in x or 'R19Temporal.read A' in x][:16]})
                row['sources'].append(str(path.relative_to(ROOT)))
    references=[
      'round3h-20261025T091810Z/astra-workers/matrix-architecture/cost-review-401854.json',
      'round6h-20261024T051445Z/astra-typed-within-codegen-1224003.json',
      'round6h-20261024T051445Z/astra-general-panel-codegen-1224010.json',
      'round9h-20261026T194639Z/development-workers/anchor-323/dual-ci15-review/review.json',
      'round9h-20261026T194639Z/astra-workers/matrix-structure/temporal-codegen-review.json',
      'round7h-20261023T193125Z/review-raw-a-codegen.json',
      'round45m-20261027T074758Z/research/row-broadcast/accepted.json',
    ]
    receipts=[]
    for rel in references:
        path=RESEARCH/rel
        data=path.read_bytes()
        receipts.append({'path':str(path.relative_to(ROOT)),'sha256':sha(data),'bytes':len(data)})
    result={'at_utc':datetime.now(timezone.utc).isoformat(),'phase_start_utc':'2026-10-27T22:11:31Z',
      'phase_deadline_utc':'2026-10-27T22:26:31Z','direct_candidate_kernel_count':len(paths),
      'scan_rule':'Textual def body with >=8 explicitly grouped Float32 scalar parameters and >=4 direct conversion or known R19Temporal.read A sites; other helper-hidden conversions and non-Kernel drafts can be missed.',
      'matches':list(matches.values()),'evidence_receipts':receipts,
      'scope':'Historical read-only intake; no conclusion of exhaustive absence or novelty; no candidate/CI/Lean.'}
    (OUT/'scalar-resident-survey.json').write_text(json.dumps(result,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({'kernels':len(paths),'unique_matching_declarations':len(matches),
      'matches':[{'name':v['declaration'],'float_params':v['scalar_float_parameters'],'raw_sites':v['raw_conversion_text_sites'],'first_source':v['sources'][0],'versions':len(v['sources'])} for v in matches.values()],
      'receipts':len(receipts)},ensure_ascii=False))

if __name__=='__main__':main()
