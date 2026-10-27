"""Exact df5c replacement, saved as low-priority reserve, not a CI request."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').exists())
parent=ROOT/'competitions/floatlib/candidates/f01-d12-scalar-combined/Kernel.lean'
raw=parent.read_bytes();assert hashlib.sha256(raw).hexdigest()=='df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172'
start=raw.index(b'/-- The word guards make the selector equal to the old rounder on every input. -/')
end=raw.index(b'\n\n\nopen FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32',start)
old=raw[start:end];fragment_raw=(HERE/'TightLiteralRSE-fragment.lean').read_bytes();new=fragment_raw.rstrip(b'\n')
result=raw[:start]+new+raw[end:]
assert result.replace(new,old)==raw and len(result)<=256000
(HERE/'Kernel-tight-literal-rse.lean').write_bytes(result)
screen=json.loads((HERE/'tight-rse-screen2.json').read_bytes())
rows=[]
for r in screen['runs']:
    g=r['groups'].values()
    rows.append({'run':r['run'],'nonzero_new_hits':sum(c.get('tight_hits',0) for c in g),
       'zero_products_at_three_scales':sum(c.get(f'scale{s}_zero_product',0) for c in r['groups'].values() for s in (124,125,126)),
       'sample_pairs':sum(c['samples'] for c in r['groups'].values())})
record={'status':'OPTIONAL_LOW_PRIORITY_RESERVE_NOT_COMPILED','created_at_utc':datetime.now(timezone.utc).isoformat(),
 'parent_sha256':hashlib.sha256(raw).hexdigest(),'candidate':'Kernel-tight-literal-rse.lean',
 'candidate_sha256':hashlib.sha256(result).hexdigest(),'candidate_bytes':len(result),
 'fragment_sha256':hashlib.sha256(fragment_raw).hexdigest(),
 'integrated_fragment_sha256':hashlib.sha256(new).hexdigest(),
 'fragment_transform':'Only strip terminal LF before insertion, then retain original parent separator bytes',
 'old_roundSelect_block_sha256':hashlib.sha256(old).hexdigest(),
 'reverse_patch_byte_exact':True,'old_roundLow_and_123_proof_unchanged':True,
 'runtime_scope':'Only LowScale.roundSelect; scalar low branch and any BMM raw replay that calls Submission.mul can be affected',
 'guards':[{'scale':124,'product_lt':'2^48','literal_shift':25},{'scale':125,'product_lt':'2^47','literal_shift':24},{'scale':126,'product_lt':'2^46','literal_shift':23}],
 'sample_evidence':rows,'Lean':'NOT_RUN','full_gate':'NOT_RUN','performance':'UNKNOWN',
 'decision':'Do not enqueue on exposure evidence alone. 9/31/23 new nonzero hits per21504 sampled mul calls versus322/37/112 zero products already cheap. Root decides only with actual D budget/cost evidence.',
 'prior_history':'No identical tight/literal case found in targeted research and candidate source search. f01-mul-rse-threshold is a different failed RNE formula and is not reused.'}
(HERE/'tight-literal-rse-manifest-v2.json').write_text(json.dumps(record,indent=2)+'\n',encoding='utf-8')
print(json.dumps(record))
