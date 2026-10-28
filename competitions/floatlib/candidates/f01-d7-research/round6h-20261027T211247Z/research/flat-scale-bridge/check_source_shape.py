from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re

HERE=Path(__file__).resolve().parent
ROUND=HERE.parents[1]
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').exists())
RUNTIME=ROUND/'development-flat-scale/FlatScale.lean.inc'
raw=RUNTIME.read_bytes();text=raw.decode()
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
expected='82ebf77c97d26d3ccfc0b9c085ec47cb5a140803233141a8d1e00bcfc5fda63f'
assert hashlib.sha256(raw).hexdigest()==expected
fields=[int(x) for x in re.findall(r'^  x([0-9]+) : Float32$',text,re.M)]
assert fields==list(range(128))
blocks=[]
for g in range(4):
    body=re.search(r'def block'+str(g)+r' : Block :=\s*([^\n]+)',text).group(1)
    seeds=[int(x) for x in re.findall(r'seed ([0-9]+)',body)]
    assert seeds==list(range(128*g,128*(g+1)))
    blocks.append({'group':g,'first_seed':seeds[0],'last_seed':seeds[-1],'count':len(seeds)})
selector=[(int(a),int(b)) for a,b in re.findall(r'^  \| ([0-9]+) => b\.x([0-9]+)$',text,re.M)]
assert selector==[(i,i) for i in range(128)]
assert '  | _ => Packed10.zero32' in text
for j in range(512):
    g=j>>7;s=j&127
    assert g<4 and s<128 and 128*g+s==j
base=ROOT/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
parts=['FlatScaleBridge.lean.inc','SmallPickDiscriminator.lean.inc']
out={'checked_utc':datetime.now(timezone.utc).isoformat(),'state':'SOURCE_STRUCTURE_AND_FINITE_INDEX_CHECK_ONLY',
 'runtime_sha256':expected,'runtime_bytes':len(raw),'field_count':len(fields),'blocks':blocks,
 'selector_field_mapping_count':len(selector),'index_cases_checked':512,
 'files':{f:{'bytes':(HERE/f).stat().st_size,'sha256':sha(HERE/f)} for f in parts},
 'B2_plus_runtime_and_current_fragments_bytes':base.stat().st_size+len(raw)+sum((HERE/f).stat().st_size for f in parts),
 'not_assembled':True,'full_block_helper':'NOT_GENERATED','Lean':'NOT_RUN',
 'scope':'Checks literal structure/seed numbering andintegerpartition only; noFloat32evaluation, kernelproof orselector performance.'}
(HERE/'source-shape-check.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps(out,indent=2))
