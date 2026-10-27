"""One exact source proposal, never writes a Kernel or dispatches CI."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,difflib,re,importlib.util
HERE=Path(__file__).resolve().parent
CS=HERE.parent.parent
PARENT=CS/'f01-r11-crossrow-short-shared/Kernel.lean'
raw=PARENT.read_bytes();sha=lambda b:hashlib.sha256(b).hexdigest()
assert sha(raw)=='7cad7df494da6004b9e4b202f4d09b838ef8d4b79ba6fe934eea7287784fea28'
text=raw.decode();frag=(HERE/'astra-finish-self-bridge.lean').read_bytes().decode()
assert 'namespace Submission.R11FinishWord' not in text
a=text.index('namespace Submission.R11CrossRows')
new=text[:a]+frag+'\n\n'+text[a:]
start=new.index('def finish8 (',new.index('namespace Submission.R11CrossRows'));end=new.index('\ntheorem finish8_word',start)
old_finish=new[start:end]
new_finish,count=re.subn(r'\(Packed10\.finish ([^\n]+?)\)\.raw\.1',r'R11FinishWord.finishWord \1',old_finish)
assert count==8
new=new[:start]+new_finish+new[end:]
old_proof='simp [finish8, wordAt, select4, lane, laneIndex, rebuild]'
new_proof='simp [finish8, R11FinishWord.finishWord_eq_raw, wordAt, select4, lane, laneIndex, rebuild]'
assert new.count(old_proof)==1
new=new.replace(old_proof,new_proof)
inverse=new.replace(new_proof,old_proof).replace(new_finish,old_finish).replace(frag+'\n\n','',1)
assert inverse.encode()==raw
data=new.encode();assert len(data)<=256000
sp=importlib.util.spec_from_file_location('r11_policy',CS/'f01-r11-crossrow-p2-pack12-proof2/build.py')
c=importlib.util.module_from_spec(sp);sp.loader.exec_module(c);c.static_check(new)
patch=''.join(difflib.unified_diff(text.splitlines(keepends=True),new.splitlines(keepends=True),fromfile='a/Kernel.lean',tofile='b/Kernel.lean'))
(HERE/'astra-native-word-finish.patch').write_bytes(patch.encode())
report={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'SOURCE_PATCH_ONLY_WAIT_CURRENT_R11_C_AND_ROOT_COST_DECISION',
        'parent_sha256':sha(raw),'prospective_source_sha256':sha(data),'prospective_bytes':len(data),'source_margin':256000-len(data),
        'helper_file':'astra-finish-self-bridge.lean','helper_sha256':sha(frag.encode()),'patch_file':'astra-native-word-finish.patch','patch_sha256':sha(patch.encode()),
        'change':'Only R11finish8 uses native selfBEq and rawUInt32return; sameoldABI alreadyUInt32, expected difference is removalof foreign isnan classifier call. Original exactrawreplay retained.',
        'proof':'Reuse R7W04.nonNaN_eq_not_isNaN already in acceptedparent; localfinishWord_eq_raw transports actualPacked10.finish; originalfinish8_word reconnectsall8outputs.',
        'inverse_parent':'BYTE_EXACT','Kernel_written':False,'new_Lean':'NOT_RUN','generated_C':'NOT_RUN','performance':'UNKNOWN',
        'parked':'Pure word-return ABI rename is PARK because prioractualcallee alreadyUInt32; native-canonical-word alternative retainedonly asmathdraft, notsecondpatch.',
        'scope':'No newKernel,CI,sourceoptions,extern,grid orwebtask. Do not claimthispatch passed915 orremovedheapobjects.'}
(HERE/'astra-native-word-finish-patch.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:report[k] for k in ['state','prospective_source_sha256','prospective_bytes','source_margin','Kernel_written']}))
