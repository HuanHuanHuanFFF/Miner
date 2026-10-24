"""One exact-word falsifier for confusing local numeric and original raw replay bases."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json,sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent
CS=HERE.parent.parent
path=CS/'f01-r11-crossrow-p2-pack12/model-check.py'
sp=importlib.util.spec_from_file_location('model',path)
m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m);o=m.o
batch,rows,n,p=2,5,5,11
A=[0x3f800000]*(batch*rows*n)
B=[0x3f800000]*(batch*n*p)
first=4*(rows//4);b=1;tailrow=0;j=0
rawbase=(b*rows+first+tailrow)*n
localbase=tailrow*n
A[0]=0x7fc00011
A[rawbase]=0xffc00022
tail=[o.canon(x) for x in A[(b*rows+first)*n:(b*rows+rows)*n]]
s=0
for k in range(n):
    s=o.native_model(o.add,s,o.native_model(o.mul,tail[localbase+k],o.canon(B[(b*n+k)*p+j])))
assert o.nan(s)
correct=o.dot([A[rawbase+k] for k in range(n)],[B[(b*n+k)*p+j] for k in range(n)])
wrong=o.dot([A[localbase+k] for k in range(n)],[B[(b*n+k)*p+j] for k in range(n)])
assert correct!=wrong
report={'at_utc':datetime.now(timezone.utc).isoformat(),'shape':[batch,rows,n,p],
        'batch_index':b,'first_tail_row':first,'local_numeric_base':localbase,'original_raw_A_base':rawbase,
        'native_result_hex':hex(s),'correct_original_raw_replay_hex':hex(correct),
        'wrong_local_base_replay_hex':hex(wrong),'detects_wrong_raw_base':True,
        'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'oracle_sha256':m.EXPECTED,
        'scope':'Finite source-derived word-model falsifier only, not Lean/native execution or independent oracle. It demonstrates why a canonical native NaN cannot justify replay from a local numeric offset.'}
(HERE/'astra-tail-raw-base-counterexample.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
print(json.dumps(report))
