"""Proof-only repair of the six exact run40307208739 errors; frozen7e remains unchanged."""
from pathlib import Path
from datetime import datetime, timezone
from types import SimpleNamespace
import ast
import difflib
import hashlib
import importlib.util
import json
import re

HERE = Path(__file__).resolve().parent
PARENT = HERE.parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').exists())
ROUND = PARENT.parents[1]
OLD = PARENT / 'public-add-v1/Kernel.lean'
GATE = ROOT / 'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
LEXER = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T091810Z/astra-workers/source-budget/audit_budget.py'
FEEDBACK = ROUND / 'development-proof-f01-r17-dev-add-public1-40307208739.json'
sha = lambda b: hashlib.sha256(b).hexdigest()
def binding(p):
    b = p.read_bytes()
    return {'path': p.relative_to(ROOT).as_posix(), 'bytes': len(b), 'sha256': sha(b)}

raw = OLD.read_bytes()
assert sha(raw) == '7e1524c818285ce2c7721140fd0cff23560416abc6ea9a2c72ddf1be9a588be7'
feedback = json.loads(FEEDBACK.read_text(encoding='utf-8'))
log = ROOT / feedback['compiler_output']
assert sha(log.read_bytes()) == 'a8acd20063c2b4fe185c26021f3bfe9a59631aaffb1411ba3c918772bb724250'
old = raw.decode('utf-8'); new = old
changes = []
def replace(old_piece, new_piece, expected, label, basis):
    global new
    assert new.count(old_piece) == expected, (label, new.count(old_piece))
    offsets = [m.start() for m in re.finditer(re.escape(old_piece), new)]
    before = new
    new = new.replace(old_piece, new_piece)
    changes.append({'label': label, 'occurrences': expected, 'old': old_piece, 'new': new_piece,
                    'before_sha256': sha(before.encode()), 'after_sha256': sha(new.encode()),
                    'byte_offsets_before_change': [len(before[:i].encode()) for i in offsets], 'basis': basis})

# The two method/notation errors only occur at these exact proof lines.
replace('rw [Nat.shiftRight_eq_div_pow] at hr\n',
        'rw [Nat.shiftRight_eq\', Nat.shiftRight_eq_div_pow] at hr\n', 2,
        'sameNoCarry_and_oppNoCarry_method_bridge',
        'Parent relayed scalar-cost primary293d interface check: Nat.shiftRight_eq\' is the rfl method-to-notation bridge.')
replace('Bool.and_eq_true.mp hd', 'Bool.and_eq_true_iff.mp hd', 2,
        'sorted_spec_Bool_conjunction_projection',
        'Parent relayed scalar-cost primary293d Bool.lean check: and_eq_true_iff is Iff.of_eq(and_eq_true x y).')
replace('  have hbase : (gap - 1).toNat = gap.toNat - 1 := by\n'
        '    rw [UInt32.toNat_sub_of_le _ _ hgle]\n',
        '  have hbase : (gap - 1).toNat = gap.toNat - 1 := by\n'
        '    rw [UInt32.toNat_sub_of_le _ _ hgle]\n'
        '    rfl\n', 1, 'oppWordShift_literal_toNat_normalization',
        'Original full goal is gap.toNat - UInt32.toNat 1 = gap.toNat - 1; discharge this closed literal reduction by reflexivity.')
replace('    ← R2W01c.rawModel_eq_native32 x.raw.1, ← R2W01c.rawModel_eq_native32 y.raw.1,\n'
        '    halign]\n'
        '  exact packModel n shift e sign elo hlo hhi hs he helo hehi\n',
        '    ← R2W01c.rawModel_eq_native32 x.raw.1, ← R2W01c.rawModel_eq_native32 y.raw.1]\n'
        '  change Model.NativeBinary32.ofUInt32 (FastMul.mkW sign e (n.toFloat32.toUInt32 >>> shift)) =\n'
        '    Model.add (R2W01c.rawModel x.raw.1) (R2W01c.rawModel y.raw.1)\n'
        '  exact (packModel n shift e sign elo hlo hhi hs he helo hehi).trans halign.symm\n',
        1, 'addAligned_canonical_model_goal_and_transitivity',
        'Original full goal reports a semireducible Binary.format versus binary32 mismatch at the final rewrite. Re-establish the canonical model Eq type with change, then compose the two already-stated equalities instead of rewriting halign through that goal.')

# Exact reverse of all replacements proves no hidden edit was introduced.
inverse = new
for change in reversed(changes):
    assert inverse.count(change['new']) == change['occurrences']
    inverse = inverse.replace(change['new'], change['old'])
assert inverse.encode('utf-8') == raw

sp = importlib.util.spec_from_file_location('budget_lex', LEXER)
lex = importlib.util.module_from_spec(sp); sp.loader.exec_module(lex)
def declarations(text):
    clean = lex.lex(text)[0]
    bounds = [m.start() for m in lex.CMD.finditer(clean)] + [len(text)]
    out = []
    for m in lex.DECL.finditer(clean):
        end = next(i for i in bounds if i > m.start())
        piece = text[m.start():end]
        head = piece.split(':=', 1)[0]
        out.append((m['kind'], m['name'], piece, head))
    return out
before_decls, after_decls = declarations(old), declarations(new)
assert [(k,n) for k,n,_,_ in before_decls] == [(k,n) for k,n,_,_ in after_decls]
assert [(k,n,h) for k,n,_,h in before_decls] == [(k,n,h) for k,n,_,h in after_decls]
assert [(k,n,p) for k,n,p,_ in before_decls if k not in ['theorem','lemma']] == [
    (k,n,p) for k,n,p,_ in after_decls if k not in ['theorem','lemma']]
data = new.encode('utf-8')
assert len(data) <= 256000 and b'\r' not in data
out = HERE / 'Kernel.lean'; out.write_bytes(data)
patch = ''.join(difflib.unified_diff(old.splitlines(keepends=True), new.splitlines(keepends=True),
                                    fromfile='public-add-v1/Kernel.lean', tofile='public-add-v2/Kernel.lean'))
(HERE / 'proof-only-repair.patch').write_bytes(patch.encode('utf-8'))

assert sha(GATE.read_bytes()) == '1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
t = ast.parse(GATE.read_text(encoding='utf-8'))
env = {'re': re, 'Path': Path, 'Verdict': SimpleNamespace, '_MAX_BYTES':256000,
       'SLOTS': {'full': SimpleNamespace(contract='ContractTensor')}}
for name in ['OPTIONS','ATTRIBUTES','BANNED']:
    n=next(n for n in t.body if isinstance(n,ast.Assign) and any(isinstance(x,ast.Name) and x.id==name for x in n.targets))
    env[name]=re.compile(ast.literal_eval(n.value.args[0])) if name=='BANNED' else ast.literal_eval(n.value)
fs=[n for n in t.body if isinstance(n,ast.FunctionDef) and n.name in ['intake','policy','options']]
exec(compile(ast.Module(body=fs,type_ignores=[]),str(GATE),'exec'),env)
checks={'intake':env['intake'](out,SimpleNamespace(slot='full')),
        'policy':env['policy'](out,SimpleNamespace(slot='full')),
        'options':env['options'](new)}
assert all(v is None for v in checks.values())
old_manifest=json.loads((PARENT/'public-add-v1/manifest.json').read_text(encoding='utf-8'))
audit_old=PARENT/'public-add-v1/HelperAudit.lean.inc'
audit=HERE/'HelperAudit.lean.inc';audit.write_bytes(audit_old.read_bytes())
manifest={
    'created_utc':datetime.now(timezone.utc).isoformat(),
    'state':'SIX_REAL_ERRORS_PROOF_ONLY_REPAIR_READY_NOT_COMPILED',
    'candidate':binding(out),'margin':256000-len(data),'parent':binding(OLD),
    'feedback':binding(FEEDBACK),'original_full_output':binding(log),'changes':changes,
    'exact_inverse_to7e':True,'all_statement_headers_unchanged':True,
    'all_runtime_definitions_abbrevs_structures_instances_byte_identical':True,
    'helper_roots':old_manifest['helper_roots'],'public_gate_roots':old_manifest['public_gate_roots'],
    'audit':binding(audit),'audit_byte_identical_to_v1':True,
    'static_checks':checks,'canonical_LF':True,'frozen7e_unchanged':OLD.read_bytes()==raw,
    'frontend_evidence':'Scalar-cost fixed293d source validation relayed by parent. Its stated add-frontend-repair folder was not visible in this worker snapshot; do not invent a local receipt hash.',
    'source_pipeline':'Apply this exact patch to frozen public7e; do not rerun the v1 builder over old unsynchronized long-name fragments.',
    'compile':'NOT_RUN','kernel':'NOT_RUN','helper_audit':'NOT_RUN','full_gate':'NOT_RUN','performance':'UNKNOWN',
    'premise_or_algorithm_changes':False,'Git':False,'CI':False,'local_Lean':False,'tokens':'UNKNOWN'}
(HERE/'manifest.json').write_bytes((json.dumps(manifest,indent=2,ensure_ascii=False)+'\n').encode('utf-8'))
print(json.dumps({'candidate':manifest['candidate'],'margin':manifest['margin'],
                  'errors_targeted':6,'roots':len(manifest['helper_roots'])+len(manifest['public_gate_roots']),
                  'runtime_unchanged':True,'statements_unchanged':True,'checks':checks,'compile':'NOT_RUN'},indent=2))
