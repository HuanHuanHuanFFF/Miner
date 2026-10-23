"""Three proof-only repairs from exact run40024012440, with byte-exact inverse."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,ast,hashlib,importlib.util,json,re
HERE=Path(__file__).resolve().parent
CS=HERE.parent
ROOT=HERE.parents[3]
PARENT=CS/'f01-r11-crossrow-p2-pack12/Kernel.lean'
EXPECTED='4bdd1e7db35cd85e17d06511721d5dbf7f654ec12e58633264b08a086ec54fa0'
LOG=CS/'f01-mul-log2-proof1/ci-runs/40024012440/download-18576082dd8c4d46b8692478553e4074/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r11-crossrow-p2-pack12/full-build-output.txt'
VERDICT=LOG.parents[2]/'f01-r11-crossrow-p2-pack12-verdict.json'
def sha(b):return hashlib.sha256(b).hexdigest()
def repair(text):
    replacements=[]
    def inside(theorem,end_marker,old,new):
        nonlocal text
        a=text.index('theorem '+theorem,text.index('namespace Submission.R11CrossRows'));z=text.index(end_marker,a)
        block=text[a:z];assert block.count(old)==1
        changed=block.replace(old,new)
        replacements.append({'theorem':theorem,'old':block,'new':changed})
        text=text[:a]+changed+text[z:]
    inside('lane_update','\ndef packGeneral',
           'rcases h with rfl|rfl|rfl|rfl|rfl|rfl|rfl|rfl <;> rfl',
           'rcases h with rfl|rfl|rfl|rfl|rfl|rfl|rfl|rfl <;>\n    simp [lane, update, inputA, inputB]')
    inside('dot8_lane','\ndef laneIndex',
           '  simpa only [lane_zero] using\n    natLoop_lane n p a0 a1 a2 a3 b0 b1 b2 b3 A B 0 zero8 l',
           '  have h := natLoop_lane n p a0 a1 a2 a3 b0 b1 b2 b3 A B 0 zero8 l\n  rw [lane_zero] at h\n  simpa only [zero8] using h')
    inside('rowWord_eq','\ndef core (batch',
           '  unfold rowWord words\n  rw [Packed10.vector_get_ofFn, blockRows_word]',
           '  unfold rowWord words\n  dsimp only\n  rw [Packed10.vector_get_ofFn, blockRows_word]\n  dsimp only')
    return text,replacements
def static_check(text):
    gate=ROOT/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
    assert sha(gate.read_bytes())=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
    tree=ast.parse(gate.read_text())
    def value(name):return next(n.value for n in tree.body if isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id==name for t in n.targets))
    assert not re.compile(ast.literal_eval(value('BANNED').args[0])).search(text)
    assert [l for l in text.splitlines() if re.search(r'\bimport\b',l)]==['import ContractTensor']
    env={'re':re,'OPTIONS':ast.literal_eval(value('OPTIONS'))}
    fn=next(n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name=='options')
    exec(compile(ast.Module(body=[fn],type_ignores=[]),str(gate),'exec'),env)
    assert env['options'](text) is None
    attrs=ast.literal_eval(value('ATTRIBUTES'))
    for group in re.findall(r'@\[([^\]]*)\]',text):
        for item in group.split(','):assert item.split()[-1] in attrs
    sp=importlib.util.spec_from_file_location('r8_inventory',CS/'f01-r8-combined-result-guard/build.py')
    inv=importlib.util.module_from_spec(sp);sp.loader.exec_module(inv);decls=inv.declarations(text)
    for n in ['add','add_spec','mul','mul_spec','sum','sum_spec','bmm','bmm_spec']:assert len(decls['Submission.'+n])==1
def main():
    ap=argparse.ArgumentParser();ap.add_argument('--write',action='store_true');args=ap.parse_args()
    raw=PARENT.read_bytes();assert sha(raw)==EXPECTED
    original=raw.decode();new,replacements=repair(original);data=new.encode()
    assert len(data)<=256000;static_check(new)
    inverse=new
    for r in reversed(replacements):
        assert inverse.count(r['new'])==1;inverse=inverse.replace(r['new'],r['old'])
    assert inverse.encode()==raw
    assert len(replacements)==3
    vd=json.loads(VERDICT.read_text());assert vd['passed'] is False and vd['stage']=='statement'
    manifest={'candidate':HERE.name,'candidate_file':'Kernel.lean','candidate_sha256':sha(data),'candidate_bytes':len(data),
              'created_at_utc':datetime.now(timezone.utc).isoformat(),'parent':PARENT.parent.name,'parent_sha256':EXPECTED,
              'repair':'Only lane_update numeral/projection simp; dot8_lane zero8 explicit normalization; rowWord_eq let/Fin projection reduction before/after rewrites.',
              'runtime_definition_bytes':'UNCHANGED_BY_EXACT_INVERSE_OUTSIDE_THREE_THEOREM_BLOCKS',
              'trigger_run':40024012440,'trigger_validation_mode':'statement-only','trigger_verdict_sha256':sha(VERDICT.read_bytes()),
              'trigger_log_sha256':sha(LOG.read_bytes()),'validation_mode':'full-gate','proof_status':'NOT_RUN_EXACT_PROOF2',
              'full_gate':'NOT_RUN','performance':'UNKNOWN','formal_submission':'NOT_SUBMITTED','build_script_sha256':sha(Path(__file__).read_bytes()),
              'scope':'No runtime change, resource option increase, source pruning, or unobserved web conditional patch. Original failure retained.'}
    review={'manifest':manifest,'changed_theorems':[r['theorem'] for r in replacements],'replacements':replacements,
            'inverse_parent_sha256':sha(inverse.encode()),'static_policy':'PASS','size_margin':256000-len(data)}
    if args.write:
        assert not (HERE/'Kernel.lean').exists() and not (HERE/'manifest.json').exists()
        (HERE/'Kernel.lean').write_bytes(data)
        for name,obj in [('manifest.json',manifest),('proof-repair-review.json',review)]:
            (HERE/name).write_text(json.dumps(obj,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    else:
        assert (HERE/'Kernel.lean').read_bytes()==data
        assert json.loads((HERE/'manifest.json').read_text())['candidate_sha256']==sha(data)
    print(json.dumps({'sha256':sha(data),'bytes':len(data),'margin':256000-len(data),'inverse_exact':True,'static':'PASS','Lean':'NOT_RUN'}))
if __name__=='__main__':main()
