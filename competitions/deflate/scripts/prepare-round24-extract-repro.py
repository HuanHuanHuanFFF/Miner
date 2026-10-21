"""Repeat the actual extraction symptom and narrow helper versus call-site context."""
from pathlib import Path
import hashlib,json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24'
def fn(text,name):
    a=text.index('pub fn '+name+'(');b=text.index('{',a);depth=1;k=b+1
    while depth:
        depth+=(text[k]=='{')-(text[k]=='}');k+=1
    return text[a:k]+'\n'
def main():
    raw=(ROOT/'candidates/r24-609-buffer-frontier/parse.rs').read_text();common='\n'.join(fn(raw,n)for n in ['Z353','SFlen','SFdist','SFroom'])
    entries=[]
    for name,caller in [('sfroom-only',False),('sfroom-caller',True)]:
        text=common+(fn(raw,'SFfastadd') if caller else '')
        call='SFfastadd(&mut best,&mut codes,4,t,&ct)' if caller else 'SFroom(&best,&codes,t,&ct)'
        text+='''// Extraction-only diagnostic fixture. Not a submitted parser or proof.
pub fn parse(input:&[u8],out:&mut[u32])->usize {
 let t=16777216u32.wrapping_add(if input.len()>0{input[0]as u32}else{0});
 let mut best=[t,t,t,t];let mut codes=[0usize,1,2,3];let ct=[16u32;1024];
 let count='''+call+''';
 let mut n=0usize;while n<input.len() && n<out.len() && n<count{out[n]=input[n]as u32;n+=1;}n
}
'''
        path=E/'extraction-repro'/name;path.mkdir(parents=True,exist_ok=False)
        files={'parse.rs':text.encode(),'Parse.lean':b'import Lz77\n-- Extraction-only fixture; not a correctness proof.\n'}
        for f,b in files.items():(path/f).write_bytes(b)
        entries.append({'name':'debug-'+name,'path':path.relative_to(ROOT).as_posix(),'control':False,'debug_fixture':True,'anchor':'public609','hashes':{f:hashlib.sha256(b).hexdigest()for f,b in files.items()}})
    s=json.loads((E/'proof-p-extract.json').read_bytes());s['entries']=[e for e in s['entries']if e['control']or e['name']=='r24-609-buffer-frontier']+entries
    s.update(r24_debug_extract_fixture=True,r24_expected_candidates=3,extract_candidates=['r24-609-buffer-frontier']+[e['name']for e in entries],description='R24 S repeat fullL extraction and two strictly scoped reduced fixtures. Reproducer sources under evidence are not candidates, performance results or fullproofs. Diagnose determinism and helper/call-context dependence before fixing.')
    ns=[e['name']for e in s['entries']];s['screen_orders']=[ns];(E/'repro-s-extract.json').write_bytes((json.dumps(s,indent=2)+'\n').encode())
    plan={'symptom':'P returned extraction exit1 for L after102.6s with an empty Aeneas log; O succeeded in the same job. No Lean proof was executed for either.',
        'red_command':'ROUND4_SPEC=proof-p-extract ROUND4_SPEC_DIR=evidence/round24 $DEFLATE_ROOT/.venv/bin/python scripts/research-round5.py',
        'observed_output':'RESEARCH_EXTRACTION r24-609-buffer-frontier 1 PROOF_NOT_RUN; inline-slot exit0 with Types/Funs/Constants retained.',
        'phase':'Reproduce and minimize. No root cause asserted from the empty log.',
        'minimum':'Repeat exactfullL, helper-only fixture, actualcaller+helper fixture on one preparedrunner; original stageextract returns and artifacts define pass/fail.',
        'bounded_exception':'Local seconds-only loop would violate the heavy-toolchain-on-runner rule. Reuse one runner setup; reduced fixtures are expected to be small but timing is measured, not promised.',
        'decision':'RepeatedL failure with reducedfailure localizes a seam for ranked causal tests. If reducedcases pass, keep largercontext or resource dependence open. If unchangedL passes, investigate non-determinism and use exactsuccessfulFuns for proof interface only.',
        'cost_cap_runner_minutes':55,'proof_status':'NOT_RUN','not_submittable':'Both reducedfixtures intentionally do not establish the full parser obligation and cannot use standard/gate routing.',
        'evidence':'evidence/round24/<run>/repro-s-extract/diagnostics/research5'};(E/'preflight-s.json').write_bytes((json.dumps(plan,indent=2)+'\n').encode());print('S_REPRODUCERS_FROZEN')
if __name__=='__main__':main()
