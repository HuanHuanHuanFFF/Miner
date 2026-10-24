"""Proof-only repair from original b15 failure; runtime definitions stay byte exact."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import importlib.util
import json
import re

HERE = Path(__file__).resolve().parent
CANDIDATES = HERE.parents[1]
ROOT = HERE.parents[4]
TARGET = CANDIDATES/'f01-d12-scalar-cold-nan-select-proof2'
PARENT_SHA = 'b15dd4116f79ccdbb1ef6ffd203f33bfe70abebcf9eb4b3146e21a3a20461325'


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--write',action='store_true')
    args=ap.parse_args()
    parent=(CANDIDATES/'f01-d12-scalar-cold-nan-select/Kernel.lean').read_bytes()
    assert sha(parent)==PARENT_SHA
    text=parent.decode('utf-8')
    operations=[]
    def replace(before,after,name):
        nonlocal text
        assert text.count(before)==1,name
        at=text.index(before)
        operations.append({'name':name,'character_offset_in_previous_stage':at,'before':before,'after':after,
                           'before_sha256':sha(before.encode()),'after_sha256':sha(after.encode())})
        text=text[:at]+after+text[at+len(before):]
    replace('  rw [hm]\n\ntheorem quietWord_eq_snan',
            '  rw [hm]\n  rfl\n\ntheorem quietWord_eq_snan',
            'reduce literal true equality in quietWord_eq remaining conditional')
    replace('  exact (Bool.and_eq_true.mp hu).1\n',
'''  have hh : rawNaN u = true ∧ ((u &&& 0x00400000) == 0) = true := by
    simpa only [Bool.and_eq_true] using hu
  exact hh.1
''','typed conjunction projection for quietWord_eq_snan')
    replace('        · simp only [ha, hb, hna, hnb, ite_false, Option.map_none]\n',
            '        · simp only [ha, hb, hna, hnb, Bool.false_eq_true, ite_false, Option.map_none]\n',
            'close all-false rawChoose coercion conditionals explicitly')
    replace('''  have h := (Bool.and_eq_true.mp hu).1
  exact beq_iff_eq.mp h
''','''  have hh : Model.NativeBinary32.expField u = 0xff ∧
      Model.NativeBinary32.fracField u ≠ 0 := by
    simpa only [rawNaN, Bool.and_eq_true, beq_iff_eq, bne_iff_ne] using hu
  exact hh.1
''','typed rawNaN conjunction with exact UInt32 exponent equality')
    replace('    exact Or.inl (rawNaN_exp a (Bool.and_eq_true.mp ha).1)\n',
'''    have hh : rawNaN a = true ∧ ((a &&& 0x00400000) == 0) = true := by
      simpa only [rawSNaN, Bool.and_eq_true] using ha
    exact Or.inl (rawNaN_exp a hh.1)
''','typed left signaling-NaN conjunction in rawChoose_nonfinite')
    replace('      exact Or.inr (rawNaN_exp b (Bool.and_eq_true.mp hb).1)\n',
'''      have hh : rawNaN b = true ∧ ((b &&& 0x00400000) == 0) = true := by
        simpa only [rawSNaN, Bool.and_eq_true] using hb
      exact Or.inr (rawNaN_exp b hh.1)
''','typed right signaling-NaN conjunction in rawChoose_nonfinite')
    raw=text.encode('utf-8')
    assert len(raw)<=256000 and 'Bool.and_eq_true.mp' not in text
    inverse=text
    for op in reversed(operations):
        at=op['character_offset_in_previous_stage']
        assert inverse[at:at+len(op['after'])]==op['after']
        inverse=inverse[:at]+op['before']+inverse[at+len(op['after']):]
    assert inverse.encode()==parent
    parser_path=CANDIDATES/'f01-r8-combined-result-guard/build.py'
    spec=importlib.util.spec_from_file_location('r12_proof2_inventory',parser_path)
    parser=importlib.util.module_from_spec(spec);spec.loader.exec_module(parser)
    before,after=parser.declarations(parent.decode()),parser.declarations(text)
    assert set(before)==set(after) and all(len(v)==1 for v in after.values())
    old_lines,new_lines=parent.decode().splitlines(keepends=True),text.splitlines(keepends=True)
    old_plain,new_plain=parser.strip_comments(parent.decode()).splitlines(),parser.strip_comments(text).splitlines()
    runtime={}
    old_starts=sorted(v[0] for v in before.values());new_starts=sorted(v[0] for v in after.values())
    for name,positions in before.items():
        old_row,new_row=positions[0],after[name][0]
        if not re.search(r'\b(def|abbrev)\b',old_plain[old_row-1]):
            continue
        def chunk(lines,starts,row):
            stop=next((x-1 for x in starts if x>row),len(lines))
            return ''.join(lines[row-1:stop]).encode()
        old_chunk,new_chunk=chunk(old_lines,old_starts,old_row),chunk(new_lines,new_starts,new_row)
        assert old_chunk==new_chunk,name
        runtime[name]={'sha256':sha(old_chunk),'bytes':len(old_chunk),'unchanged':True}
    export_types={}
    for short in ('add','add_spec','mul','mul_spec','sum','sum_spec','bmm','bmm_spec'):
        name='Submission.'+short
        signature=lambda lines,row:''.join(lines[row-1:]).split(':=',1)[0]
        assert signature(old_lines,before[name][0])==signature(new_lines,after[name][0])
        export_types[name]='UNCHANGED'
    report={'parent_sha256':PARENT_SHA,'candidate_sha256':sha(raw),'candidate_bytes':len(raw),
        'headroom_bytes':256000-len(raw),'inverse_parent_exact':True,'operations':operations,
        'runtime_definitions':runtime,'runtime_definition_count':len(runtime),'all_runtime_definitions_byte_identical':True,
        'declarations_unchanged_unique':True,'eight_exported_types':export_types,
        'original_failure':{'run':40069713432,'source_commit':'81a90fc6',
            'verdict_sha256':'d88f6b6291e8e9029b6569bde240fbfe5845a8aceb493d1facef7dd3d187df2f',
            'errors':'Literal Boolean coercion conditionals and Bool.and_eq_true.mp API; no runtime change'},
        'repair_acceptance':'NOT_RUN','resources_or_axioms_added':False}
    manifest={'candidate':TARGET.name,'candidate_file':'Kernel.lean','candidate_sha256':sha(raw),
        'candidate_bytes':len(raw),'created_at_utc':datetime.now(timezone.utc).isoformat(),
        'parent':'f01-d12-scalar-cold-nan-select','parent_sha256':PARENT_SHA,
        'mechanism':'Proof-only Lean4.34 Boolean conjunction API and literal-conditional closure repair; all b15 runtime definitions remain byte-identical.',
        'checks':{'inverse_parent_exact':True,'all_runtime_definitions_byte_identical':True,
            'runtime_definition_count':len(runtime),'declarations_unchanged_unique':True,'eight_exported_types':export_types},
        'original_failure':report['original_failure'],'state':'READY_FOR_STATEMENT',
        'proof_status':'NOT_RUN_PROOF2','validation_mode':'statement first, then original full gate',
        'leanchecker':'NOT_RUN','axiom_audit':'NOT_RUN','checksum':'NOT_RUN','full_gate':'NOT_RUN',
        'codegen':'NOT_RUN','performance':'UNKNOWN','resources_or_axioms_added':False,
        'formal_submission':'NOT_SUBMITTED','ci_owner':'Root','build_script_sha256':sha(Path(__file__).read_bytes())}
    if args.write:
        TARGET.mkdir(exist_ok=False)
        (TARGET/'Kernel.lean').write_bytes(raw)
        (TARGET/'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
        (TARGET/'exact-inverse.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
    else:
        assert (TARGET/'Kernel.lean').read_bytes()==raw
        assert json.loads((TARGET/'manifest.json').read_bytes())['candidate_sha256']==sha(raw)
    print(json.dumps({'candidate':TARGET.name,'sha256':sha(raw),'bytes':len(raw),'runtime_definitions_checked':len(runtime),
        'all_runtime_byte_identical':True,'static_checks':'PASS','actual_Lean':'NOT_RUN'},indent=2))


if __name__=='__main__':
    main()
