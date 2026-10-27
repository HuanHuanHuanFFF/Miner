"""One source-level type ascription; preserve exact original evidence and runtime tokens."""
from pathlib import Path
from types import SimpleNamespace
import ast,datetime,difflib,hashlib,json,re
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'DEVELOPMENT.md').exists())
ROUND=HERE.parent.parent.parent
H=lambda b:hashlib.sha256(b).hexdigest()
BASE=ROOT/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
OLD_FRAGMENT=HERE.parent/'grs-add-cost-frontier/Runtime-grs32-add.lean.inc'
OLD_FULL=ROUND/'astra-grs-add-runtime-only.lean'
SUITE=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40428306094/download-c800c9d7532147a99a39807e35f52f19/diagnostics/f01-d7-public-suite/public-suite'
DIAG=SUITE/'diagnostics/f01-r19-dev-grs-add-runtime1'

def bind(p,expected=None):
 b=p.read_bytes();h=H(b)
 if expected:assert h==expected,(p,h,expected)
 return {'path':str(p.relative_to(ROOT)).replace('\\','/'),'bytes':len(b),'sha256':h}

def main():
 original_manifest=json.loads((ROUND/'astra-grs-add-runtime-only.json').read_text())
 original_input=SUITE/'inputs/f01-r19-dev-grs-add-runtime1/Kernel.lean'
 bindings=[bind(BASE,'622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'),
  bind(OLD_FRAGMENT,'e4833e4e8b41c7fe50cb8dfa91dbd639fc4cc6aa926fb7b5498e4dda1a2be45a'),
  bind(OLD_FULL,'35347e37e2c8d593d868c80522659b4fb18bda7604fc830a9f14eb7d39be33c5'),
  bind(original_input,'35347e37e2c8d593d868c80522659b4fb18bda7604fc830a9f14eb7d39be33c5'),
  bind(DIAG/'full-build-output.txt','f39743788488176f9a2f65c4118b8864e8758272e72aabd3a86dc02b4ccf8bdf'),
  bind(DIAG/'diagnostic-only-verdict.json','9eb09fcf59fd47dd074852779baf9e042adb06191694aac8bd1524d89de58485'),
  bind(SUITE/'provenance.json')]
 b=BASE.read_bytes();old=OLD_FRAGMENT.read_bytes();full=OLD_FULL.read_bytes()
 assert full==b+old==original_input.read_bytes()
 log=(DIAG/'full-build-output.txt').read_text()
 marker='error: work/Submission.lean:6629:24: failed to synthesize instance of type class'
 assert marker in log and 'HAnd UInt32 ℕ ?m.226' in log
 substantive=[x for x in log.splitlines() if x.startswith('error: work/Submission.lean:')]
 assert substantive==[marker]
 failed_line=full.decode().splitlines()[6628]
 before=b'(hi &&& 0x80000000)'
 after=b'(hi &&& (0x80000000 : UInt32))'
 assert before.decode() in failed_line and old.count(before)==1
 fixed=old.replace(before,after,1);fixed_full=b+fixed
 assert fixed.replace(after,before,1)==old and fixed_full.replace(after,before,1)==full
 assert len(fixed)-len(old)==11
 assert old.count(b'fallback x y')==fixed.count(b'fallback x y')==2
 assert (0x80000000 < 2**32) and int('80000000',16)==2147483648
 frag=HERE/'Runtime-grs32-add-type-repair1.lean.inc';kernel=HERE/'Kernel-grs-add-runtime-repair1.lean'
 frag.write_bytes(fixed);kernel.write_bytes(fixed_full)
 patch=''.join(difflib.unified_diff(full.decode().splitlines(True),fixed_full.decode().splitlines(True),fromfile='3534-original/Kernel.lean',tofile='typed-repair1/Kernel.lean'))
 reverse=''.join(difflib.unified_diff(fixed_full.decode().splitlines(True),full.decode().splitlines(True),fromfile='typed-repair1/Kernel.lean',tofile='3534-original/Kernel.lean'))
 (HERE/'forward.patch').write_text(patch,encoding='utf-8',newline='\n')
 (HERE/'inverse.patch').write_text(reverse,encoding='utf-8',newline='\n')
 roots=original_manifest['roots'];assert len(roots)==len(set(roots))==7
 helper=HERE/'HelperAudit-grs-add-runtime-repair1.lean.inc'
 helper.write_text('\n'.join('#print axioms '+r for r in roots)+'\n',encoding='utf-8',newline='\n')
 excerpt='\n'.join(log[log.index(marker):].splitlines()[:4])+'\n'
 (HERE/'actual-error-excerpt.txt').write_text(excerpt,encoding='utf-8',newline='\n')
 # Original official static policy functions only; no Lean, runner, flags or gate edits.
 gate=HERE.parent/'static-dispatch-frontier/primary/gate-4b7.py'
 bindings.append(bind(gate,'1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'))
 tree=ast.parse(gate.read_text());env={'re':re,'Path':Path,'Verdict':SimpleNamespace,'_MAX_BYTES':256000,'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')}}
 for name in ['OPTIONS','ATTRIBUTES','BANNED']:
  n=next(n for n in tree.body if isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id==name for t in n.targets))
  env[name]=re.compile(ast.literal_eval(n.value.args[0])) if name=='BANNED' else ast.literal_eval(n.value)
 fs=[n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name in ['intake','policy','options']]
 exec(compile(ast.Module(body=fs,type_ignores=[]),str(gate),'exec'),env)
 checks={'intake':env['intake'](kernel,SimpleNamespace(slot='full')),'policy':env['policy'](kernel,SimpleNamespace(slot='full')),'options':env['options'](fixed_full.decode())}
 assert all(v is None for v in checks.values()),checks
 assert not b'\r' in fixed_full and not fixed_full.startswith(b'\xef\xbb\xbf')
 # Recheck preserved originals after writing only this separate directory.
 for row in bindings:assert H((ROOT/row['path']).read_bytes())==row['sha256']
 out={'utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'state':'MINIMAL_TYPE_ASCRIPTION_COPY_NOT_RUN',
  'original_failure':{'run':40428306094,'source_commit':'a92abea11a0a21e76df44a1a93114801dd3085a8','line':6629,'column':24,'class':'HAnd UInt32 Nat ?m.226','failed_line':failed_line,'substantive_errors':1},
  'change':{'before':before.decode(),'after':after.decode(),'bytes_added':11,'inverse_exact':True,'only_type_ascription_added':True,'literal_value':2147483648},
  'fragment':bind(frag),'kernel':bind(kernel),'helper':bind(helper),'roots':roots,
  'B2_prefix_bytes':len(b),'B2_prefix_exact':True,'old_sources_preserved':True,'bindings':bindings,
  'static_policy_only':checks,'toolchain':'Lean4.34.0 / 293d5d0c0c3f3dded4688b3ccd6a33939ac5102b; official4b7 unchanged',
  'public_dispatch':'All four entries/specs remain exact B2; diagnosticEntry alone calls GRS guardedAdd.',
  'semantic_boundary':'Old fragment did not elaborate; no Lean equivalence theorem is asserted. Removing this exact annotation recovers every original token. Algorithm, normal guard, sticky guard, T, postE and ordered fallback are unchanged.',
  'statement':'NOT_RUN','kernel_replay':'NOT_RUN','axioms':'NOT_RUN','codegen':'NOT_RUN','new_ADD_equivalence':'MISSING','fullgate':'NOT_RUN','performance':'UNKNOWN',
  'CI_dispatched':False,'local_Lean':False}
 (HERE/'manifest.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8',newline='\n')
 print(json.dumps({'fragment':out['fragment'],'kernel':out['kernel'],'roots':len(roots),'static_policy':'PASS','manifest_sha256':H((HERE/'manifest.json').read_bytes())},indent=2))

if __name__=='__main__':main()
