"""Bounded proof-repair candidate: runtime identical to timed-out zero53.

Creates exact actual-source prefixes for a public-runner elaboration discriminator.
No local Lean build, changed premise, candidate measurement or claimed repair.
"""
from pathlib import Path
import hashlib,importlib.util,json,argparse,datetime,re
HERE=Path(__file__).resolve().parent
OLD=HERE/'build_zero_mobile.py';OLD_SHA='88f651e2b226d4810a062650b1b72c2d5f6091211e0312e58e0627ef699e221b'
BASE=HERE.parents[1]/'competition-state/source-private/official-53.lean'
BASE_SHA='3dbe2f708299e6ee13e512a0f639eae681497ffaf01132330d92071581f7a9cb'
HELPERS='''lemma r28Z9 (w:ق):Y9 0x200000000000000 w=0:=by
 simp only[Y9,show ((0x200000000000000:ق)&&&0x1FFFFFF)=0 from by decide,UInt64.zero_mul]
lemma r28Z1 (w:ق):cq1 0x200000000000000 w=0:=by
 simp only[cq1,show (((0x200000000000000:ق)>>>25)-0x100000000)=0 from by decide,UInt64.zero_mul]
'''

def load_old():
    assert hashlib.sha256(OLD.read_bytes()).hexdigest()==OLD_SHA
    spec=importlib.util.spec_from_file_location('r28zeroOriginal',OLD);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m

def fixed(raw):
    old=load_old();s=old.transform(raw,53,'zero-both').decode()
    mark='@[specialize] def qCtx7 ';assert s.count(mark)==1;s=s.replace(mark,HELPERS+mark)
    before='''   · simp only [dif_pos hz]
     simpa [hz,Y9,cq1] using qCtx8 n fa fb fc B C bw cw cb0 cb1 hc0 hc1 z0 z1 a b c d (k+1)'''
    after='''   · rw[dif_pos hz]
     conv_rhs => simp only[hz,r28Z9,r28Z1,UInt64.add_zero]
     exact qCtx8 n fa fb fc B C bw cw cb0 cb1 hc0 hc1 z0 z1 a b c d (k+1)'''
    assert s.count(before)==1;s=s.replace(before,after)
    before='''   · simp only [dif_pos hz]
     simpa [hz.1,hz.2,Y9,cq1] using qCtx14 n f g w B bw cb hc z0 z1 a b c d (k+1)'''
    after='''   · rw[dif_pos hz]
     conv_rhs => simp only[hz.1,hz.2,r28Z9,r28Z1,UInt64.add_zero]
     exact qCtx14 n f g w B bw cb hc z0 z1 a b c d (k+1)'''
    assert s.count(before)==1;s=s.replace(before,after)
    result=s.encode();assert len(result)<=256000,len(result)
    return result

def prefix(raw,mode):
    old=load_old()
    if mode=='baseline-q8':s=raw.decode();marker='@[specialize] def qCtx9 ';root='qCtx8'
    elif mode=='timeout-q7':s=old.transform(raw,53,'zero-both').decode();marker='lemma qCtx8 ';root='qCtx7'
    elif mode=='timeout-q8':s=old.transform(raw,53,'zero-both').decode();marker='@[specialize] def qCtx9 ';root='qCtx8'
    elif mode=='repair-q8':s=fixed(raw).decode();marker='@[specialize] def qCtx9 ';root='qCtx8'
    elif mode=='repair-q14':s=fixed(raw).decode();marker='@[inline] def qCtx15 ';root='qCtx14'
    else:raise ValueError(mode)
    assert s.count(marker)==1;s=s[:s.index(marker)]+'\nend Submission\n'
    return s.encode(),root

def transform(raw,submission,variant):
    assert submission==53 and hashlib.sha256(raw).hexdigest()==BASE_SHA
    if variant=='zero-both-proof-v2':return fixed(raw)
    return prefix(raw,variant)[0]

def main():
    p=argparse.ArgumentParser();p.add_argument('--base',type=Path,default=BASE);p.add_argument('--variant');p.add_argument('--output',type=Path);a=p.parse_args();raw=a.base.read_bytes()
    if a.variant:
      assert a.output;data=transform(raw,53,a.variant);a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(data);print(hashlib.sha256(data).hexdigest());return
    outdir=HERE/'private/zero-proof-diagnostic';outdir.mkdir(parents=True,exist_ok=True);rows=[]
    for mode in ['baseline-q8','timeout-q7','timeout-q8','repair-q8','repair-q14','zero-both-proof-v2']:
      data=transform(raw,53,mode);dest=outdir/(mode+'.lean');dest.write_bytes(data)
      rows.append({'variant':mode,'sha256':hashlib.sha256(data).hexdigest(),'bytes':len(data),'local_path':str(dest),'root':('Submission.'+prefix(raw,mode)[1]) if mode!='zero-both-proof-v2' else 'Submission.correct'})
    before=load_old().transform(raw,53,'zero-both').decode();after=fixed(raw).decode()
    rx=re.compile(r'(?m)^(?:@\[[^\n]*?\]\s+)?(?:def|structure)\s+(\w+)')
    def chunks(s):
      cmd=re.compile(r'(?m)^(?:@\[[^\n]*?\]\s+)?(?:def|lemma|theorem|structure|local|set_option|end)\b');ms=list(cmd.finditer(s));out={}
      for i,m in enumerate(ms):
        name=rx.match(s,m.start())
        if name:out[name[1]]=s[m.start():ms[i+1].start() if i+1<len(ms) else len(s)]
      return out
    same=chunks(before)==chunks(after);assert same
    receipt={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'base_sha256':BASE_SHA,'timed_out_candidate_sha256':hashlib.sha256(before.encode()).hexdigest(),'recipe_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'dependency_sha256':OLD_SHA,'runtime_declaration_chunks_byte_identical':same,'runtime_declaration_count':len(chunks(before)),'artifacts':rows,'state':'UNCOMPILED_PROOF_ONLY_REPAIR_HYPOTHESIS; do bounded prefixes before another full600s gate','diagnostic_first_pair':['baseline-q8','repair-q8'],'if_repair_prefix_times_out':'Run timeout-q7 to isolate modified recursive definition from equality lemma; retain baseline walltime before interpreting any120s cutoff','policy':'Whole prefix source stays private/runner-only; reconstruct from official53 fetch plus own scripts'}
    (HERE/'zero-proof-v2-receipt.json').write_text(json.dumps(receipt,indent=2)+'\n');print(json.dumps(receipt,indent=2))
if __name__=='__main__':main()
