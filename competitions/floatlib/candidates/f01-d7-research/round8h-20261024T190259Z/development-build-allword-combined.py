"""Seal the source-sized combined draft; full Lean verification stays mandatory."""
from pathlib import Path
from datetime import datetime, timezone
import ast
import hashlib
import json
import re

OUT=Path(__file__).resolve().parent
ROOT=OUT.parents[4]
C=ROOT/'competitions/floatlib/candidates'
sha=lambda b:hashlib.sha256(b).hexdigest()
records=[json.loads((OUT/name).read_bytes()) for name in (
    'development-proof-fixedpoint-inventory1.json',
    'development-unreferenced-declarations-inventory1.json',
    'development-local-dependency-graph1.json')]
current=(ROOT/records[0]['source']).read_bytes()
assert sha(current)=='9a6913ee4da828ab83f78254bd0a1accd136b3274fdc80d8ecba45c2b7d6612a'
def replay(raw,rows):
    text=raw.decode();position=0;parts=[]
    for row in rows:
        lo,hi=row['character_start'],row['character_end']
        block=text[lo:hi].encode()
        assert lo>=position and sha(block)==row['sha256'] and len(block)==row['bytes']
        parts.append(text[position:lo]);position=hi
    parts.append(text[position:])
    return ''.join(parts).encode()
for item in records:
    assert sha(current)==item['source_sha256']
    if 'rounds' in item:
        for stage in item['rounds']:
            assert sha(current)==stage['parent_sha256']
            current=replay(current,stage['rows'])
            assert sha(current)==stage['result_sha256']
    else:current=replay(current,item['removed'])
    assert sha(current)==item['result_sha256'] and current==(ROOT/item['result']).read_bytes()
assert sha(current)=='423f64592f998469a8d06ab0c749cddae42e7352d5f701e61a82d2428d11b8a4'
# The common raw decoder was removed from the second NatNormal namespace.
# Its ordinary theorem docstring cannot be left attached to the closing `end`.
orphan=b'/-- Unlike the old NormalBand helper, this covers every normal raw exponent1..254. -/\nend Submission.R14NatNormal'
assert current.count(orphan)==1
result=current.replace(orphan,b'end Submission.R14NatNormal')
prior=OUT/'development-proof-fixedpoint-inventory.py'
nodes=[n for n in ast.parse(prior.read_bytes()).body if isinstance(n,ast.FunctionDef) and n.name=='mask']
env={};exec(compile(ast.Module(body=nodes,type_ignores=[]),str(prior),'exec'),env)
clean,docs=env['mask'](result.decode())
orphan_docs=[]
for start,end in docs:
    rest=clean[end:].lstrip()
    if re.match(r'^(?:end|set_option|open|import)\b',rest):
        orphan_docs.append(dict(line=result[:len(result.decode()[:start].encode())].count(b'\n')+1,next=rest.splitlines()[0]))
assert not orphan_docs,orphan_docs
assert not re.search(r'\b(?:axiom|sorry|admit|unsafe|extern|implemented_by|native_decide)\b',clean)
assert len(result)<=256000 and result.count(b'import ContractTensor')==1
assert result.index(b'R14WordAdd.guardedAdd addBeforeWord x y')<result.index(b'theorem add_eq :')
assert result.index(b'R14ExponentShift.guardedMul mulBeforeExponent x y')<result.index(b'theorem mul_eq :')
folder=C/'f01-r14-dev-allword-combined1'
assert not folder.exists();folder.mkdir();(folder/'Kernel.lean').write_bytes(result)
add_meta=json.loads((C/'f01-r14-dev-word-add-entry1/manifest.json').read_bytes())
record=dict(candidate=folder.name,candidate_file='Kernel.lean',candidate_sha256=sha(result),
            candidate_bytes=len(result),bytes_remaining=256000-len(result),created_at_utc=datetime.now(timezone.utc).isoformat(),
            validation_mode='full-gate',proof_status='COMPLETE_SOURCE_ATTEMPT_STATIC_DEPENDENCY_PRUNING_NOT_COMPILED',performance='NOT_RUN',
            parents=[dict(candidate='f01-r14-dev-word-add-entry1',sha256='a2342948257d2e2e2011f0fe941bd2b692e70604b915734f4538b5efd1e69372'),
                     dict(candidate='f01-r14-dev-combined-headroom3',sha256='d2b8a436c051c035d1e206f1b8bdec03c2840c0324e459436bb886e5fae32274')],
            components=add_meta['components'],
            derivation=[dict(path=(OUT/n).relative_to(ROOT).as_posix(),sha256=sha((OUT/n).read_bytes())) for n in (
                'development-combined-add-mul-composition1.json','development-proof-fixedpoint-inventory1.json',
                'development-unreferenced-declarations-inventory1.json','development-local-dependency-graph1.json')],
            additional_structural_repair=dict(reason='Remove duplicate decoder docstring left immediately before end after common-proof reuse.',
                                              removed_sha256=sha(orphan.split(b'\n')[0]+b'\n'),removed_bytes=len(current)-len(result)),
            mechanism='Actual public UInt32/UInt64 narrow normal add and pure UInt64 normal mul, with shared exact normal-rounding/word-field support, plus thin-column B preparation and p<=8 direct BMM. Original ordered fallbacks and original SUM remain.',
            proof_capacity='Reuse common add/mul math; replay exact proof-only deletion stages then a conservative local-name reachability proposal, including unused recursive helper islands. No remaining runtime definition bodies changed by pruning; unused definitions were removed. Local graph is not the Lean elaborator.',
            source_identity='Original277331B composed analysis, both independent candidate parents, all original math fragments and every deletion slice/hash remain available. One dangling copied theorem docstring removed structurally; no attribution changed.',
            acceptance='All four complete original obligations, helper axiom audit/replay, actual-caller C/assembly, full paired discovery and two frozen independent confirmations are NOT_RUN. No score, champion replacement or inherited component gain is claimed.')
(folder/'manifest.json').write_bytes((json.dumps(record,ensure_ascii=False,indent=2)+'\n').encode())
(OUT/'development-allword-combined-build1.json').write_bytes((json.dumps(record,ensure_ascii=False,indent=2)+'\n').encode())
print(json.dumps({k:record[k] for k in ('candidate','candidate_sha256','candidate_bytes','bytes_remaining','proof_status')}))
