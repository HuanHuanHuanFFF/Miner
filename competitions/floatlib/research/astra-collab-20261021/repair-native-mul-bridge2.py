from pathlib import Path
import hashlib,json,datetime
HERE=Path(__file__).resolve().parent
p=HERE/'native-mul-bridge-proof1.lean'
assert hashlib.sha256(p.read_bytes()).hexdigest()=='b9ee20a719266d95e6a02d3f361f9a25c46aac84ca08cc7455cc4648931b3647'
s=p.read_text(encoding='utf8')
old='''  split_ifs at hdecode
  · simp only [Option.some.injEq, Numerics.Dyadic.mk.injEq] at hdecode
    exact absurd hdecode.2.1.symm hmantissa.ne'
  · simp only [Option.some.injEq, Numerics.Dyadic.mk.injEq] at hdecode
    exact Or.inl hdecode.2.2.symm.le
  · simp only [Option.some.injEq, Numerics.Dyadic.mk.injEq] at hdecode
    refine Or.inr ?_
    rw [← hdecode.2.1, pow2_eq_two_pow]
    exact Nat.le_add_right _ _'''
new='''  split_ifs at hdecode
  · have hm := congrArg FloatLib.Numerics.Dyadic.significand (Option.some.inj hdecode)
    dsimp only at hm
    exact absurd hm.symm hmantissa.ne'
  · have he := congrArg FloatLib.Numerics.Dyadic.exponent (Option.some.inj hdecode)
    dsimp only at he
    exact Or.inl he.symm.le
  · have hm := congrArg FloatLib.Numerics.Dyadic.significand (Option.some.inj hdecode)
    dsimp only at hm
    refine Or.inr ?_
    rw [← hm, pow2_eq_two_pow]
    exact Nat.le_add_right _ _'''
assert s.count(old)==1
s=s.replace(old,new)
q=HERE/'native-mul-bridge-proof2.lean'
q.write_text(s,encoding='utf8',newline='\n')
print(json.dumps({'path':str(q),'sha256':hashlib.sha256(q.read_bytes()).hexdigest(),'bytes':q.stat().st_size,'created_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'status':'TARGETED_PROOF_REPAIR_NOT_COMPILED'},indent=2))
