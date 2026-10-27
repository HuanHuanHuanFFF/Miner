"""Supplemental same-batch standalone ASM; never substitute for MainFull ASM."""
from pathlib import Path
import importlib.util,json,hashlib,re,difflib,datetime
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'DEVELOPMENT.md').exists())
R=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40395429076/download-01d3ee43e7ff4ae088ca57488a71a0b2/diagnostics/f01-d7-public-suite/public-suite/diagnostics'
sp=importlib.util.spec_from_file_location('comparison',HERE/'compare_classifier_codegen.py');mod=importlib.util.module_from_spec(sp);sp.loader.exec_module(mod)
sha=lambda b:hashlib.sha256(b).hexdigest()
old,oldrecords=mod.load(R/'f01-r19-dev-b2-index1','9f7f96d71c153681c6a2500fd229e0627cd2ea38a3ad375afdeee25a1657eee1')
new,newrecords=mod.load(R/'f01-r19-dev-eager-classifier1','cc9268820d3c9b3c4e664d6a659a12ef259c7c8443db61980a686cad974ea5a5')
base,base_records=mod.load(mod.BASE,'622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58')
assert old['MainFull']==base['MainFull']
def asm(folder,symbol):
    rows=json.loads((folder/'native-assembly-index.json').read_text())
    row=next(r for r in rows if r.get('symbol')==symbol)
    data=(folder/row['file']).read_bytes();assert sha(data)==row['sha256']
    t=data.decode();m=re.search(r'^0+ <'+re.escape(symbol)+r'>:\n',t,re.M);assert m
    tail=t[m.end():];n=re.search(r'^Disassembly of section |^[0-9a-f]+ <',tail,re.M)
    body=tail[:n.start()] if n else tail
    return body.strip(),row
out=HERE/'classifier-standalone-40395429076';out.mkdir(exist_ok=True);rows={}
for op in ['add','mul','nativeMul']:
    symbol='lp_competition_Submission_'+op
    bo=mod.extract(base['Submission'],symbol);co=mod.extract(old['Submission'],symbol)
    assert mod.normalize(bo)==mod.normalize(co),op
    a,ra=asm(R/'f01-r19-dev-b2-index1',symbol);b,rb=asm(R/'f01-r19-dev-eager-classifier1',symbol)
    diff='\n'.join(difflib.unified_diff(a.splitlines(),b.splitlines(),fromfile='retained-scalar-in-index1',tofile='eager-classifier',lineterm=''))
    (out/(op+'.diff')).write_text(diff+'\n',encoding='utf-8')
    (out/(op+'-old.asm.txt')).write_text(a+'\n',encoding='utf-8');(out/(op+'-new.asm.txt')).write_text(b+'\n',encoding='utf-8')
    rows[op]={'retained_scalar_C_body_same_after_variable_normalization':True,'ASM_text_equal':a==b,
      'old':ra,'new':rb,'diff_file':str(out/(op+'.diff')),'changed_text_lines':sum(1 for l in diff.splitlines() if l.startswith(('+','-')) and not l.startswith(('+++','---')))}
r={'utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'state':'SUPPLEMENTAL_STANDALONE_ASM_ONLY',
 'old_control':'B2-index1 differs in BMM, but original MainFull C is byte-identical to retained B2 and each compared scalar C body is checked equal modulo local variables.',
 'old_sources':oldrecords,'new_sources':newrecords,'comparisons':rows,
 'limitations':'The scalar ASM is from Submission, not the actual selected MainFull callbacks. Diagnostic object hashes are indexed original records; objects are not retained for new rehash. No relocation/byte data in these objdump outputs. This does not establish public timing or MainFull machine identity.'}
(out/'review.json').write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:{'same':v['ASM_text_equal'],'changed_text_lines':v['changed_text_lines']} for k,v in rows.items()}))
