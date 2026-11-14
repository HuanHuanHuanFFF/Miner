"""Generate a native numerical validator only, never a timing driver.

Each emitted callback has two closed static arguments. Tier selection happens
in this generator, not in a captured runtime Bool.
"""
from pathlib import Path
import argparse,hashlib,json
HERE=Path(__file__).resolve().parent
def build(tiered=False):
    fixtures=HERE/'portable-f64-dot-fixtures.json';raw=fixtures.read_bytes()
    assert hashlib.sha256(raw).hexdigest()=='b146a148a8fed7eb528e42d8ce1388ed7e7ca4a5e6cf8b4b55b75f1503c5e1ac'
    f=json.loads(raw)
    full='Submission.R24ExactDotTiered.fullv2' if tiered else 'Submission.R24ExactDotCost.full'
    warm='Submission.R24ExactDotTiered.prepared2v2' if tiered else 'Submission.R24ExactDotCost.prepared2'
    source='''import Submission
/- Numerical oracle only. Combined preparation here is outside any timer;
   this executable must not be relabeled as a complete lifecycle benchmark. -/
namespace R24PortableDotOracle
structure Fixture where
  name : String
  a : String
  b : String
  expected : UInt32
  fastExpected : UInt32
def fixtures : Array Fixture := #[
'''
    rows=[]
    for c in f['cases']:
        rows.append('  { name := '+json.dumps(c['name'])+', a := '+json.dumps(','.join(map(str,c['x'])))+
            ', b := '+json.dumps(','.join(map(str,c['y'])))+', expected := '+str(c['expected'])+', fastExpected := '+str(c['fast_result'])+' }')
    source+=',\n'.join(rows)+'\n]\n'
    source+='''def parseWords (s : String) : Array UInt32 :=
  if s.isEmpty then #[] else
    (s.splitOn ",").toArray.map (fun x => UInt32.ofNat ((x.toNat?).getD 0))
structure Operand where
  exactData : Submission.R24ExactDotCost.Operand
  fp : Submission.R24PortableF64.Prepared
def prepare (raw : Array UInt32) : Operand :=
  ⟨Submission.R24ExactDotCost.prepareOperand raw, Submission.R24PortableF64.prepare raw⟩
@[noinline] def coldExact (a b : Array UInt32) : UInt32 := __FULL__ a b
@[noinline] def coldFp (a b : Array UInt32) : UInt32 :=
  let q := Submission.R24PortableF64.attemptCold a b
  if q == 0 then __FULL__ a b else q
@[noinline] def warmExact (a b : Operand) : UInt32 := __WARM__ a.exactData b.exactData
@[noinline] def warmFp (a b : Operand) : UInt32 :=
  let q := Submission.R24PortableF64.attemptPrepared a.fp b.fp
  if q == 0 then __WARM__ a.exactData b.exactData else q
end R24PortableDotOracle
open R24PortableDotOracle
def main : IO UInt32 := do
  let mut failed := false
  let mut count := 0
  let mut accepted := 0
  for f in fixtures do
    let a := parseWords f.a
    let b := parseWords f.b
    let ca := prepare a
    let cb := prepare b
    let coldAttempt := Submission.R24PortableF64.attemptCold a b
    let warmAttempt := Submission.R24PortableF64.attemptPrepared ca.fp cb.fp
    let c0 := coldExact a b
    let c1 := coldFp a b
    let w0 := warmExact ca cb
    let w1 := warmFp ca cb
    let ok := coldAttempt == f.fastExpected && warmAttempt == f.fastExpected &&
      c0 == f.expected && c1 == f.expected && w0 == f.expected && w1 == f.expected
    if !ok then failed := true
    if warmAttempt != 0 then accepted := accepted + 1
    count := count + 1
    IO.println s!"F64_DOT_CHECK|{f.name}|{f.expected.toNat}|{f.fastExpected.toNat}|{coldAttempt.toNat}|{warmAttempt.toNat}|{c0.toNat}|{c1.toNat}|{w0.toNat}|{w1.toNat}|{ok}"
  IO.println s!"F64_DOT_ORACLE|{count}|{accepted}|{failed}"
  return if failed then 1 else 0
'''
    source=source.replace('__FULL__',full).replace('__WARM__',warm)
    out=HERE/('PortableDotTieredOracleV2Main.lean' if tiered else 'PortableDotOracleV2Main.lean')
    data=source.encode()
    if out.exists():assert out.read_bytes()==data,'Frozen oracle requires a new version'
    else:out.write_bytes(data)
    assert source.count('@[noinline] def')==4 and 'Bool)' not in source
    report={'status':'GENERATED_NATIVE_NUMERICAL_ORACLE_NOT_RUN','path':out.name,'bytes':len(data),'sha256':hashlib.sha256(data).hexdigest(),
        'fixture_sha256':hashlib.sha256(raw).hexdigest(),'fixture_cases':len(f['cases']),'expected_fast_accepts':sum(bool(c['fast_result']) for c in f['cases']),
        'baseline':full,'prepared_baseline':warm,'callbacks':['coldExact','coldFp','warmExact','warmFp'],
        'callback_shape':'Four distinct noinline closed static twoargument callbacks; no captured Bool.',
        'scope':'Native numerical validator only; combined preparer is not a lifecycle timing boundary. Actual C/Lean/native run pending root composition.'}
    report_path=out.with_suffix('.json')
    if report_path.exists():assert json.loads(report_path.read_bytes())==report
    else:report_path.write_bytes((json.dumps(report,indent=2)+'\n').encode())
    return report
if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('--tiered',action='store_true');args=p.parse_args();print(json.dumps(build(args.tiered),indent=2))
