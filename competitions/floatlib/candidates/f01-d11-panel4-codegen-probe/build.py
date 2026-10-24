"""One unused Panel4 representation/codegen experiment on exact749b.
Default dry run. --write creates one frozen source and its exact increment;
--verify is read-only. No Lean, Git, CI, options or changes to wide candidates.
"""
from argparse import ArgumentParser
from datetime import datetime, timezone
from hashlib import sha256
from pathlib import Path
from types import SimpleNamespace
import ast,json,re

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[3]
PARENT=HERE.parent/'f01-d11-bmm-wide-backbone/Kernel.lean'
PARENT_SHA='749bc933597ec15b200e8146899f7a055e25b4eef425e156bca337a13c38ca28'
OLD_PROBE=HERE.parent/'f01-r11-wide4-codegen-probe/increment.lean'
OLD_PROBE_SHA='04ca30e0c26ae420d1f7991c6c4b7c48401177ca26a6463551171ed44770673f'
PARSER=HERE.parent/'f01-r8-combined-result-guard/build.py'
GATE=ROOT/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'


def sha(raw):return sha256(raw).hexdigest()


def functions(raw,names,env):
    nodes=[n for n in ast.parse(raw.decode()).body if isinstance(n,ast.FunctionDef) and n.name in names]
    assert {n.name for n in nodes}==set(names)
    exec(compile(ast.Module(body=nodes,type_ignores=[]),'<pinned helpers>','exec'),env)
    return env


def increment(probe):
    f40=probe[:probe.index(b'def wordLoop')]
    assert b'structure F40 where\n' in f40 and f40.count(b': Float32')==40
    lines=[f40.decode().rstrip(),'','end Submission.R11WideRows4','','namespace Submission.Panel4',
      'open FloatLib.Floats Competition','',
      '/-- One input packet for four rows at the same k; preparation is outside the MAC loop. -/',
      'structure F4 where','  r0 : Float32','  r1 : Float32','  r2 : Float32','  r3 : Float32','',
      'def wordLoop {n : Nat} (count : USize) (A : Vector F4 n)',
      '    (B : Vector Packed10.F10 n) (hn : count.toNat = n) (k : USize)']
    for col in range(10):lines.append('    ('+' '.join(f'c{col}r{row}' for row in range(4))+' : Float32)')
    lines.extend(['    : R11WideRows4.F40 :=','  if hk : k < count then',
      '    have hkn : k.toNat < n := by','      rw [← hn]',
      '      exact USize.lt_iff_toNat_lt.mp hk',
      '    let a := A.toArray.uget k (by simpa only [A.size_toArray] using hkn)',
      '    let v := B.toArray.uget k (by simpa only [B.size_toArray] using hkn)'])
    for row in range(4):lines.append(f'    let x{row} := a.r{row}')
    for col in range(10):lines.append(f'    let b{col} := v.s{col}')
    lines.append('    wordLoop count A B hn (k + 1)')
    for col in range(10):lines.append('      '+' '.join(f'(c{col}r{row} + x{row} * b{col})' for row in range(4)))
    names=[f'c{col}r{row}' for col in range(10) for row in range(4)]
    lines.extend(['  else ⟨'+', '.join(names)+'⟩','termination_by count.toNat - k.toNat',
      'decreasing_by all_goals exact Packed10Index.next_decreases (by assumption)','',
      '/-- Only the count is converted to a machine word; callers must prove it fits. -/',
      'def runDot (n : Nat) (A : Vector F4 n) (B : Vector Packed10.F10 n)',
      '    (hn : n < USize.size) : R11WideRows4.F40 :=',
      "  wordLoop (USize.ofNat n) A B (USize.toNat_ofNat_of_lt' hn) 0",
      '    '+' '.join(['Packed10.zero32']*40),'',
      '/-- Four original words are converted once per k into one F4 record. -/',
      'def packA (n base0 base1 base2 base3 : Nat) (Araw : Array Binary32) : Vector F4 n :=',
      '  Vector.ofFn fun k =>',
      '    ⟨ExecFloat.Binary.toFloat32 (Araw.getD (base0 + k.val) posZero),',
      '     ExecFloat.Binary.toFloat32 (Araw.getD (base1 + k.val) posZero),',
      '     ExecFloat.Binary.toFloat32 (Araw.getD (base2 + k.val) posZero),',
      '     ExecFloat.Binary.toFloat32 (Araw.getD (base3 + k.val) posZero)⟩','',
      'theorem packA_get (n base0 base1 base2 base3 : Nat) (Araw : Array Binary32) (k : Fin n) :',
      '    (packA n base0 base1 base2 base3 Araw).get k =',
      '      ⟨ExecFloat.Binary.toFloat32 (Araw.getD (base0 + k.val) posZero),',
      '       ExecFloat.Binary.toFloat32 (Araw.getD (base1 + k.val) posZero),',
      '       ExecFloat.Binary.toFloat32 (Araw.getD (base2 + k.val) posZero),',
      '       ExecFloat.Binary.toFloat32 (Araw.getD (base3 + k.val) posZero)⟩ := by',
      '  simp only [packA, Packed10.vector_get_ofFn]','',
      '/-- Prepare this panel before traversing all existing B column packets. -/',
      'def block (n p base0 base1 base2 base3 : Nat) (Araw : Array Binary32)',
      '    (packedB : Vector (Vector Packed10.F10 n) (Packed10.groups p))',
      '    (hn : n < USize.size) : Vector R11WideRows4.F40 (Packed10.groups p) :=',
      '  let panel := packA n base0 base1 base2 base3 Araw',
      '  Vector.ofFn fun g => runDot n panel (packedB.get g) hn','',
      'end Submission.Panel4',''])
    result='\n'.join(lines).encode()
    loop=result[result.index(b'def wordLoop'):result.index(b'termination_by')]
    assert loop.count(b'.uget k')==2 and loop.count(b' * b')==40 and loop.count(b' + x')==40
    assert all(x not in loop for x in [b'toFloat32',b'ofBits',b'.map ',b'getD',b'Vector.ofFn'])
    assert loop.count('⟨'.encode())==1 and loop.count('⟩'.encode())==1
    assert result.count(b'def wordLoop')==1 and b'R11WideRows4.wordLoop' not in result
    return result,f40


def construct():
    parent,probe=PARENT.read_bytes(),OLD_PROBE.read_bytes()
    assert sha(parent)==PARENT_SHA and len(parent)==223584
    assert sha(probe)==OLD_PROBE_SHA and len(probe)==4118
    inc,f40=increment(probe)
    data=parent+inc
    assert len(data)<=256000 and data[:len(parent)]==parent
    assert data[:-len(inc)]==parent
    parser_raw=PARSER.read_bytes();assert sha(parser_raw)=='58662bf7218de54978d999bfb424975732cf845708869e1d611dd712d7470f22'
    inv=functions(parser_raw,['strip_comments','declarations'],{'re':re})
    old,new=[inv['declarations'](value.decode()) for value in (parent,data)]
    assert not {name:lines for name,lines in new.items() if len(lines)>1}
    assert set(old)<=set(new)
    assert set(new)-set(old)=={'Submission.Panel4.'+name for name in ['wordLoop','runDot','packA','packA_get','block']}
    gate_raw=GATE.read_bytes();assert sha(gate_raw)=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
    assignments={t.id:n.value for n in ast.parse(gate_raw.decode()).body if isinstance(n,ast.Assign) for t in n.targets if isinstance(t,ast.Name)}
    env={'re':re,'Path':Path,'Verdict':object,'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')},
      'OPTIONS':ast.literal_eval(assignments['OPTIONS']),'ATTRIBUTES':ast.literal_eval(assignments['ATTRIBUTES']),
      'BANNED':re.compile(ast.literal_eval(assignments['BANNED'].args[0]))}
    env=functions(gate_raw,['policy','options'],env)
    assert env['policy'](SimpleNamespace(read_text=lambda:data.decode()),SimpleNamespace(slot='full')) is None
    receipt={'candidate':HERE.name,'candidate_sha256':sha(data),'candidate_bytes':len(data),'headroom_bytes':256000-len(data),
      'parent_sha256':PARENT_SHA,'increment_sha256':sha(inc),'increment_bytes':len(inc),'exact_F40_header_sha256':sha(f40),
      'source_probe_increment_sha256':OLD_PROBE_SHA,'builder_sha256':sha(Path(__file__).read_bytes()),
      'checks':{'complete_active_prefix_and_specs_unchanged':'PASS','full_inverse_to749b':'PASS','unique_namespace_and_declarations':'PASS',
        'one_40_chain_only':'PASS','loop_two_packet_uget':'PASS','loop_40_ordered_mul_then_add':'PASS',
        'loop_no_conversion_map_getD_or_intermediate_constructor':'PASS','block_packA_outside_column_ofFn':'PASS',
        'original_policy':'PASS','all_parent_author_notices_preserved':'PASS','resource_options':'UNCHANGED'},
      'validation_mode':'CODEGEN_ONLY','proof_status':'NOT_RUN_NEW_LOOP_AND_PREPARATION_TYPECHECK','full_gate':'NOT_RUN',
      'matrix_algorithm_acceptance':'NOT_APPLICABLE_NO_ACTIVE_PANEL_BMM','performance':'NOT_APPLICABLE_UNUSED_PANEL_LOOP',
      'generated_c_assembly':'NOT_RUN','formal_submission':'NOT_SUBMITTED'}
    inverse={'parent_sha256':PARENT_SHA,'candidate_sha256':sha(data),'offset':len(parent),
      'appended_text':inc.decode(),'appended_sha256':sha(inc),'inverse_recovers_exact_parent':True}
    return data,inc,receipt,inverse


def main():
    ap=ArgumentParser();m=ap.add_mutually_exclusive_group();m.add_argument('--write',action='store_true');m.add_argument('--verify',action='store_true');args=ap.parse_args()
    data,inc,receipt,inverse=construct()
    if args.verify:
        assert (HERE/'Kernel.lean').read_bytes()==data and (HERE/'increment.lean').read_bytes()==inc
    elif args.write:
        names=['Kernel.lean','increment.lean','manifest.json','static-checks.json','exact-inverse.json']
        assert not any((HERE/name).exists() for name in names),'Refuse overwrite'
        (HERE/'Kernel.lean').write_bytes(data);(HERE/'increment.lean').write_bytes(inc)
        manifest=dict(receipt,candidate_file='Kernel.lean',parent='f01-d11-bmm-wide-backbone',created_at_utc=datetime.now(timezone.utc).isoformat(),
          mechanism='One F4 A record per k prepared per four-row block, shared by all F10 B column groups. Unique40 scalar MAC chain reads one F4 and one F10 per k, creates F40 only at termination. Active749b entries untouched.',
          cost_scope='Four raw toFloat32/ofBits conversions belong to preparation per k, not MAC loop. One F4 construction per k in source; actual allocation/packing/lifetime and block reuse await captured C/asm. No global map in new helper.',
          missing='No Projects equivalence, active BMM entry, raw NaN finish, tail policy, giant-Nat fallback dispatch or complete lifecycle proof. Original raw A/B and full Bpack must be retained by any future entry. Keeping old global nativeA map too would duplicate preparation.',
          capture_required=['Panel4.wordLoop','Panel4.packA','Panel4.block','Panel4.runDot'],
          falsifier='Inspect same-object hot loop for direct four-lane A load, vector packing, spills, calls or allocation; separately include four ofBits and F4 creation, preparation-array/callback cost and destruction in any future whole-entry measurement.',
          ci_owner='root')
        for name,obj in [('manifest.json',manifest),('static-checks.json',receipt),('exact-inverse.json',inverse)]:
            (HERE/name).write_bytes((json.dumps(obj,ensure_ascii=False,indent=2)+'\n').encode())
    print(json.dumps(receipt,indent=2))


if __name__=='__main__':main()
