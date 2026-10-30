"""Read-only fresh reconstruction and policy-name audit of selected native artifacts."""
from pathlib import Path
import importlib.util,hashlib,json,re,ast,datetime
HERE=Path(__file__).resolve().parent;ROUND=HERE.parents[1]
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
BASE=ROUND/'competition-state/source-private/official-53.lean'
POLICY=ROOT/'competitions/torchlean/candidates/r25-90m-20261029T064916Z/development/contract-port/policy-source/sandbox.py'
POLICY_SHA='ba8e1a0f23692928f080ad278c35b36493199fb90e3768f90710b85ffef84126'
def main():
    assert hashlib.sha256(POLICY.read_bytes()).hexdigest()==POLICY_SHA
    astree=ast.parse(POLICY.read_text(encoding='utf-8'));pattern=None
    for node in astree.body:
      if isinstance(node,ast.Assign) and any(isinstance(t,ast.Name) and t.id=='BANNED' for t in node.targets):pattern=ast.literal_eval(node.value.args[0])
    assert pattern;ban=re.compile(pattern)
    raw=BASE.read_bytes();base_defs=set(re.findall(r'(?m)^(?:@\[[^\n]+\]\s+)?(?:def|structure)\s+(\w+)',raw.decode()))
    cases=[('build_local_channel128.py','local-channel128','private/local-channel12853.lean','662f281410e23d84386b94be7797d7955d27bb676555e3a16085236deb34fb31'),('build_pointwise128_nat.py','pointwise128-nat','private/pointwise128-nat53.lean','5ecfdd8cd0073e37185d4f88126db886372429b10efb429f84210710557afe5d')]
    rows=[]
    for script,variant,path,expected in cases:
      pp=HERE/script;spec=importlib.util.spec_from_file_location('r28audit_'+variant.replace('-','_'),pp);mod=importlib.util.module_from_spec(spec);spec.loader.exec_module(mod)
      data=mod.transform(raw,53,variant);source=data.decode();actual=hashlib.sha256(data).hexdigest()
      assert actual==expected and data==(HERE/path).read_bytes()
      forbidden=[m.group(0) for m in ban.finditer(source)];assert not forbidden
      imports=re.findall(r'(?m)^import\s+(.+)$',source);assert imports==['ContractExact']
      defs=set(re.findall(r'(?m)^(?:@\[[^\n]+\]\s+)?(?:def|structure)\s+(\w+)',source))
      assert base_defs<=defs
      assert not re.search(r'(?m)^(?:lemma|theorem) correct\b',source)
      assert len(data)<=256000
      rows.append({'variant':variant,'sha256':actual,'bytes':len(data),'recipe_sha256':hashlib.sha256(pp.read_bytes()).hexdigest(),'matches_materialized_bytes':True,'imports':imports,'forbidden_names':forbidden,'all_original_runtime_declaration_names_retained':len(base_defs),'new_correct_declared':False,'remaining':'No Lean elaboration, original gate, machine code, runtime checksum or timing is established by this audit'})
    report={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'scope':'Static reconstruction and lexical policy-name preflight only, NOT the original verifier','policy_source_sha256':POLICY_SHA,'policy_current_evidence':'R28 CI1 summary protected_before validator/sandbox.py matches this exact digest','candidates':rows,'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}
    (HERE/'static-native-audit.json').write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report,indent=2))
if __name__=='__main__':main()
