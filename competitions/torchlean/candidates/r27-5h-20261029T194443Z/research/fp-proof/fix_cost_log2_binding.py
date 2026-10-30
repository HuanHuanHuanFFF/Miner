from pathlib import Path
import json,hashlib,importlib.util,re,sys
from datetime import datetime,timezone
sys.dont_write_bytecode=True
H=Path(__file__).parent;ROOT=Path.cwd();parent=H.parent/'fp-cost';helper=parent/'LazyFPOnly.lean';original=helper.read_bytes();assert hashlib.sha256(original).hexdigest()=='7cc98e2bea5096e486800075e3f192589b9b1c35f277fe5af344b7fbf7626b21'
s=original.decode('utf-8');marker='namespace Submission.R24PortableF64\n';assert s.count(marker)==1;assert len(re.findall(r'\blog2word\b',s))==2
addition='''
@[inline] def log2word (word : UInt64) : UInt64 :=
  UInt64.ofNat word.toNat.log2
'''
fixed=s.replace(marker,marker+addition,1).encode();p=H/'cost-fix/LazyFPOnly-log2word.lean';p.write_bytes(fixed);fh=hashlib.sha256(fixed).hexdigest()
base=H.parent.parent/'competition-state/source-private/submission12-Kernel.lean';base13=H.parent.parent/'competition-state/source-private/submission13-Kernel.lean';assert not re.search(r'\blog2word\b',base.read_text(encoding='utf-8'));assert not re.search(r'\blog2word\b',base13.read_text(encoding='utf-8'))
patch=parent/'patch_fp_only.py';spec=importlib.util.spec_from_file_location('r27_fp_parent_readonly',patch);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
class OwnBytes:
 def read_bytes(self):return fixed
m.HELPER=OwnBytes();m.HELPER_SHA=fh
candidate=m.transform(base.read_bytes(),12,'fp-only-lazy')
r=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='STATIC_NAME_BINDING_GAP_FIX_READY_NOT_LEAN_CONFIRMED',priority='READ_BEFORE_FP_COST_FREEZE',original_helper=helper.relative_to(ROOT).as_posix(),original_helper_sha256=hashlib.sha256(original).hexdigest(),finding='Two unqualified log2word calls, no declaration inownedhelper or exactbase12/base13; no matching declaration incheckedpinnedcontract andsavedFloatLibsource. Complete importedLeanenvironment has not been queried, so missing-name compilerfailure is not yet observed.',fixed_helper=p.relative_to(ROOT).as_posix(),fixed_helper_sha256=fh,fixed_helper_bytes=len(fixed),added_definition='Submission.R24PortableF64.log2word (word:UInt64) :UInt64 := UInt64.ofNat word.toNat.log2',runtime_intent='Explicit bound for intended Nat.log2 implementation; no changed bitchecker/radius expression or added semantic premise.',reconstructed_candidate_sha256=hashlib.sha256(candidate).hexdigest(),reconstructed_candidate_bytes=len(candidate),full_source_saved=False,owner_action='ParentR/D may copy ownedfixedhelper bytes toauthoritativehelper, then updateHELPER_SHA, patchSHA andcandidateSHA inrequests/frozenrecipe asoneversionedchange. Do not mutate alreadyrunning source.',verification='STATIC_ONLY_LEAN_NATIVE_NOT_RUN',formal_submission=False,local_compile=False)
(H/'NATIVE-COST-STATIC-BLOCKER.json').write_text(json.dumps(r,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
p=H/'HANDOFF.md';text=p.read_text(encoding='utf-8');anchor='\n- **接受链**';urgent='\n- **P0 成本源绑定核查**：父7cc98e2b helper有2处log2word调用但自身/精确12/13与已存contract未见定义；已备自有显式绑定补丁，`NATIVE-COST-STATIC-BLOCKER.json`给新helper/完整carrier哈希。未改父目录、未Lean验证；请成本源freeze前核对/采用后更新整套pins。\n';assert anchor in text;text=text.replace(anchor,urgent+anchor,1);p.write_text(text,encoding='utf-8')
p=H/'CI-REQUEST.json';q=json.loads(p.read_bytes());q['read_before_fp_native_cost_dispatch']='NATIVE-COST-STATIC-BLOCKER.json';q['updated_at_utc']=datetime.now(timezone.utc).isoformat();p.write_text(json.dumps(q,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
p=H/'status.json';q=json.loads(p.read_bytes());q.update(updated_at_utc=datetime.now(timezone.utc).isoformat(),state='ACTIVE_THIN_COST_SYMBOL_FIX_READY',active_work='Prepared explicit log2word definition patch forparentcosthelper; static missing-binding issue notyetLeanconfirmed. Key/Real/preparecore accepted13roots; actualchecker/numericsteps pending.');p.write_text(json.dumps(q,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(r,ensure_ascii=False,indent=2))
