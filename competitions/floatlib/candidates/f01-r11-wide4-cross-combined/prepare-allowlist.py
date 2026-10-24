"""Normalize the exact reviewed receipt, retaining the complete outer1039 bytes."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
HERE=Path(__file__).resolve().parent
CS=HERE.parent
ROOT=CS.parents[2]
R=CS/'f01-d7-research/round7h-20261023T193125Z'
SOURCE=CS/'f01-r11-wide4-inline-proof3/Kernel.lean'
REVIEW=R/'review-wide-math-comment-allowlist.json'
REVIEW_SHA='b5b802869b4af6f1aab551a511817bf4b56975a741447427582589a0d9d20ff8'
sha=lambda b:hashlib.sha256(b).hexdigest()
raw=SOURCE.read_bytes();review_bytes=REVIEW.read_bytes()
assert sha(review_bytes)==REVIEW_SHA
d=json.loads(review_bytes)
assert len(raw)==253315 and sha(raw)==d['source']['sha256']=='28b819120cd3aaa1f19038f66042a9ceffe0c9329baab20fe223e98d151ce00b'
for dep in d['dependencies']:
    b=(ROOT/dep['path']).read_bytes()
    assert len(b)==dep['bytes'] and sha(b)==dep['sha256']
assert d['allow_count']==137 and d['allow_bytes']==12112 and d['all_retained_comment_count']==73
assert d['source_or_helper_mutated'] is False and d['compressed_source_written'] is False
assert [e for e in d['comment_decisions'] if e['decision']=='ALLOW_PURE_MATH']==d['allowlist']
outer=raw.rfind(b'namespace Submission\nopen FloatLib.Floats Competition\n\n/-- Both short-circuiting scans')
assert len(raw[outer:])==1039 and sha(raw[outer:])=='b135a8eef0606c7356dc12d5956115d3832aa5cddb5dc5e71e5030380c76062e'
def normalize(e,kind):
    a,z=e['start'],e['end'];b=raw[a:z]
    assert sha(b)==e['original_sha256'] and b.decode()==e['original_text']
    assert e['replacement_text']==''
    return {'start':a,'end':z,'sha256':sha(b),'text':b.decode(),'replacement':'','kind':kind,
            'preserves_author_license_source_runtime_obligations':True,
            'review_reason':e.get('reason','Original physical whitespace-only group outside all comments; no new blank lines counted.')}
edits=[normalize(e,'reviewed_math_comment') for e in d['allowlist']]
assert all(e['end']<=outer for e in edits)
skipped=[]
for e in d['optional_original_blank_groups']:
    assert not raw[e['start']:e['end']].strip()
    if e['end']<=outer:edits.append(normalize(e,'ordinary_blank_line'))
    else:skipped.append(e)
protected=[]
for e in d['comment_decisions']:
    if e['decision']=='ALLOW_PURE_MATH':continue
    b=raw[e['start']:e['end']]
    assert sha(b)==e['original_sha256'] and b.decode()==e['original_text']
    protected.append({'start':e['start'],'end':e['end'],'sha256':sha(b),'text':b.decode(),'reason':e['reason']})
protected.append({'start':outer,'end':len(raw),'sha256':sha(raw[outer:]),'text':raw[outer:].decode(),
                  'reason':'D explicitly requires entire outer Underflow namespace/entry/spec1039B byte-identical.'})
out={'schema':1,'source_sha256':sha(raw),'review_state':'MANUALLY_REVIEWED_EXACT_ALLOWLIST',
     'technical_review_origin':str(REVIEW),'technical_review_sha256':REVIEW_SHA,
     'review_method':d['review_method'],'authority':'D-authorized technical paragraph review by Luna; not a claim of separate human approval.',
     'created_at_utc':datetime.now(timezone.utc).isoformat(),'edits':sorted(edits,key=lambda e:e['start']),
     'protected':protected,'skipped_outer_blank_groups':skipped,
     'removed_math_comment_bytes':12112,'removed_blank_bytes':sum(e['end']-e['start'] for e in edits if e['kind']=='ordinary_blank_line'),
     'scope':'Apply exact reviewed source slices before composition; original outer1039 remains whole. No code/token/indent changes, no widening of allowlist.'}
dest=HERE/'reviewed-allowlist.json'
assert not dest.exists()
dest.write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'canonical_file':str(dest),'sha256':sha(dest.read_bytes()),'math_bytes':out['removed_math_comment_bytes'],
                  'blank_bytes':out['removed_blank_bytes'],'skipped_outer_blank_bytes':sum(e['bytes'] for e in skipped),'edits':len(edits)}))
