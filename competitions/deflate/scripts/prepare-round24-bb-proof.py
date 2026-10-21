"""Migrate the latest compositions from BB's actual extracted interfaces."""
from pathlib import Path
import argparse,hashlib,importlib,json,re
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start');tree=importlib.import_module('prepare-round24-tree-proof')
def block(f,n):
    m=re.search(r'(?m)^def '+re.escape(n)+r'(?:\s|\()',f);assert m,n;a=m.start();b=f.find('\n/--',a);return f[a:b if b>=0 else None]
def make(parent):
    p=ROOT/'candidates'/parent;r=(p/'parse.rs').read_text();base=ROOT/'candidates/r24-609-root-word-price-proof1';assert json.loads((base/'VERIFICATION.json').read_bytes())['status']=='VERIFIED_EXACT_ORIGINAL_PUBLIC_GATE_PASSED';l=(base/'Parse.lean').read_text()
    fp=E/'38102983632/proof-bb-extract/diagnostics/research5'/parent/'Funs.lean';f=fp.read_text();d=json.loads((fp.parent.parent/'research.json').read_bytes())['extractions'][parent];assert d['extraction_accepted']and d['source_sha256']==hashlib.sha256(r.encode()).hexdigest();audit={}
    if parent.endswith('stack-packed'):
        old=(E/'38102363209/gate-a-packed-proof1/exact-gate/exact-gate/extracted/Funs.lean').read_text();names=re.findall(r'(?m)^def ((?:Z184|Z307|Z314|APprices)[\w.]*)\b',old)
        for n in names:assert re.sub(r'\s+',' ',block(f,n))==re.sub(r'\s+',' ',block(old,n)),n
        a,_,_=tree.decl(l,'u104');a=l.rfind('@[step]',0,a);l=l[:a]+importlib.import_module('prepare-round24-au-proof').AP+l[a:];l,changes=importlib.import_module('repair-round24-packed-proof').fix_orders(l);audit={'same_extracted_changed_kernel_definitions':names,'actual_argument_order_rewrites':changes};expected=4864126
    else:
        assert parent.endswith('fast-adaptive')
        for n,chain,pat,newpat in [('SFsmallmatches_loop0_loop0_spec','q.2.2.2','⟨best1, count1, q1, k1⟩','⟨best1, count1, q1, k1, longest1⟩'),('SFmorematches_loop0_loop0_spec','q.2.2.2.2','⟨best1, codes1, count1, q1, k1⟩','⟨best1, codes1, count1, q1, k1, longest1⟩')]:
            actual=block(f,n.removesuffix('_spec'));assert '(limit : Std.Usize) (longest : Std.Usize)'in actual
            a,b,part=tree.decl(l,n);assert part.count('(k : Std.Usize):')==1;part=part.replace('(k : Std.Usize):','(k limit longest : Std.Usize):').replace('q k ⦃','q k limit longest ⦃').replace('depth.val - '+chain+'.val','limit.val - '+chain+'.1.val').replace(pat,newpat);l=l[:a]+part+l[b:]
        expected=4864057;audit={'method':'Same limit/longest state migration as accepted AT; oldfaststack fastadd interface retained and realBB params checked.'}
    assert len(l.encode())<=524288;return r,l,fp,expected,audit
def main():
    ap=argparse.ArgumentParser();ap.add_argument('parent',choices=['r24-609-stack-packed','r24-609-fast-adaptive']);ap.add_argument('--freeze',action='store_true');a=ap.parse_args();r,l,fp,expected,audit=make(a.parent)
    if not a.freeze:print(json.dumps({'status':'DRAFT_NOT_LEAN_CHECKED','parent':a.parent,'proof_bytes':len(l.encode()),'audit':audit}));return
    name=a.parent+'-proof1';e=w.write_candidate(name,a.parent,r,l,'Proof-only migration from realBBinterfaces, retaining the acceptedfaststack proof and explicitlymigrating changed ownedpricearrays oradaptivechainloopstates.','Same measuredRust, noautomaticgate inheritance ornewoptimizationcandidate.',{'extraction':fp.relative_to(ROOT).as_posix(),'Funs_sha256':hashlib.sha256(fp.read_bytes()).hexdigest(),'audit':audit,'proof':'DRAFT untilfreshoriginalfullgate.'});label='gate-'+a.parent.removeprefix('r24-609-')+'-proof1'
    for n,d in [(label,{'r24_mode':'gate','candidate':name,'path':e['path'],'files':e['hashes'],'expected_public_output_bytes':expected}),('preflight-'+label,{'gap':'Actualcompositionnativequality andBBextraction pass; no completeoriginalacceptance fornewexactpair.','change':'Onlyexactproofmigration, actualownedarrayorder ornewloopstate; originalRust, verifierand900sLeanlimit unchanged.','minimum':'Originalfullgate includingfreshre-extraction, statement/obligation, axiomwhitelist andoriginalroundtrip.','decision':'Bindacceptedpaironly; independentconfirmation requires frozenexactfiles. Retainfailures forboundedproofrepair.','cost_cap_runner_minutes':50,'evidence':f'evidence/round24/<run>/{label}/exact-gate'})]:
        p=E/(n+'.json');assert not p.exists();p.write_bytes((json.dumps(d,indent=2)+'\n').encode())
    print(name,e['hashes'])
if __name__=='__main__':main()
