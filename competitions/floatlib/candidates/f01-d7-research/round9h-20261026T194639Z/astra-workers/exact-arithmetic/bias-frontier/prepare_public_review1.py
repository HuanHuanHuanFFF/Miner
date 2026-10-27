from pathlib import Path
import json,hashlib,difflib
D=Path(__file__).resolve().parent
O=D/'public-proof-review1';O.mkdir(exist_ok=True)
H=lambda b:hashlib.sha256(b).hexdigest()
old="FastMul.toUInt32_eq,UInt32.toNat_ofNat',Nat.mod_eq_of_lt (by omega)]\n  change (s.toNat-127+(highWord p).toNat)"
new="FastMul.toUInt32_eq,UInt32.toNat_ofNat',\n    Nat.mod_eq_of_lt (show (highWord p).toNat < 4294967296 by omega)]\n  change (s.toNat-127+(highWord p).toNat)"
rows=[]
for name in ['Kernel-direct-bias-public-v1.lean','MathOutlet-interface-v1.lean','TypedOutlet.lean.inc']:
 p=D/name;b=p.read_bytes();s=b.decode();assert s.count(old)==1
 t=s.replace(old,new);out=O/name;out.write_text(t,encoding='utf8',newline='\n')
 patch=''.join(difflib.unified_diff(s.splitlines(True),t.splitlines(True),fromfile=name,tofile='review1/'+name))
 (O/(name+'.patch')).write_text(patch,encoding='utf8',newline='\n')
 assert t.replace(new,old)==s
 rows.append({'file':name,'before_sha256':H(b),'bytes':len(out.read_bytes()),'sha256':H(out.read_bytes())})
for name in ['HelperAudit-public-direct-bias.lean.inc','HelperAudit-math-outlet.lean.inc']:
 (O/name).write_bytes((D/name).read_bytes())
m={'state':'PROOF_ONLY_STATIC_REVIEW_REPAIR_NOT_RUN_HOLD','reason':'exponentWord_nat has nested moduli: unconstrained rw may discharge the outer modulus first. Explicitly target highWord.toNat modulo in the first step, leaving the later outer step as written. This is source inspection, not an observed Lean error.',
 'rows':rows,'same_runtime':True,'same_guards':True,'same_assumptions':True,'same_roots':48,'inverse_exact':True,
 'statement':'NOT_RUN','replay':'NOT_RUN','axioms':'NOT_RUN','performance':'NOT_RUN','resource1':'7b03 remains HOLD and is not incorporated'}
(O/'manifest.json').write_text(json.dumps(m,indent=2)+'\n',encoding='utf8',newline='\n')
(O/'HANDOFF.md').write_text('''# Public outlet：单行 proof-only 静态修订

只把 exponentWord_nat 第一处 Nat.mod_eq_of_lt 明确限定到 highWord.toNat，避免嵌套模数的 rw 先命中外层。不是实际 Lean 错误反馈，也不宣称修复通过。原 v1 完整源/接口/片段保留；逆补丁精确恢复。

运行体、guard、假设、48 根和全输入公共规格均不变；7b03 仍 HOLD，旧 quotient proof 未修改。此副本为后续编译优先源，原 prefix 诊断先行；manifest 给完整文件名/哈希/大小。没有编译、重放或计时证据。
''',encoding='utf8',newline='\n')
print(json.dumps(rows,indent=2))
