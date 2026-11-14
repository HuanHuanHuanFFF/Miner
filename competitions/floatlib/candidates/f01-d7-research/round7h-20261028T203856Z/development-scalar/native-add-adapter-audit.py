"""Bind exact F7 statement-build C and inspect its exported typed ADD body."""
from pathlib import Path
import hashlib,json,re
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
OLD=ROOT/'competitions/floatlib/candidates/f01-d7-research/round6h-20261027T211247Z'
BASE=OLD/'ci-runs/40615975642/download-573a2192a3034461a77feee37a46297c/diagnostics/f01-d7-public-suite'
CAP=BASE/'public-suite/codegen/f01-r22-dev-nativecombo-public1/capture-e97eb11ef6b94512bf726410f2b9ac78'
sha=lambda p:hashlib.sha256(Path(p).read_bytes()).hexdigest()
def function(s,symbol):
    pattern=rf'(?m)^LEAN_EXPORT\s+([^;\n]+\b{re.escape(symbol)}\([^\n]*\))\{{'
    m=re.search(pattern,s);assert m,symbol
    start=s.index('{',m.start());depth=1;i=start+1
    while depth:
        if s[i]=='{':depth+=1
        elif s[i]=='}':depth-=1
        i+=1
    return m.group(1),s[start:i],s.count('\n',0,m.start())+1
def main():
    snapshot=json.loads((CAP/'snapshot.json').read_bytes())
    for item in snapshot['files']:
        p=CAP/item['artifact'];assert p.stat().st_size==item['bytes'] and sha(p)==item['sha256']
    compiled=CAP/snapshot['compiled_source']['artifact']
    assert sha(compiled)==snapshot['compiled_source']['sha256']=='f7ba2ddb12939f518e5beb60daf927d9d9d80d24262edd740eefd5e8e917cc03'
    c=(CAP/'file-0-Submission.c').read_text()
    sym='lp_competition_Submission_add'
    signature,body,line=function(c,sym)
    assert signature.startswith('uint32_t ') and signature.count('uint32_t')==3
    calls=re.findall(r'\b([A-Za-z_]\w*)\s*\(',body)
    arithmetic={k:calls.count(k) for k in ('lean_float32_add','lean_float32_to_bits','lean_float32_mul','lean_float32_of_bits')}
    assert arithmetic['lean_float32_add']==arithmetic['lean_float32_to_bits']==1
    adapter=[x for x in calls if any(k in x for k in ('ModelCodec','ofFloat32','toFloat32','ofUInt32','Code_toModel','Code_ofModel'))]
    assert adapter==[]
    _,box,_=function(c,sym+'___boxed')
    outer=json.loads((BASE/'native-assembly-index.json').read_bytes())
    outer_kernels=sorted({x['kernel_sha256'] for x in outer if 'kernel_sha256' in x})
    record={'status':'NO_MODEL_OR_WORD_ADAPTER_IN_EXACT_F7_TYPED_ADD_CAPTURE',
      'source_sha256':sha(compiled),'capture_snapshot_sha256':sha(CAP/'snapshot.json'),
      'captured_C_sha256':sha(CAP/'file-0-Submission.c'),'object_sha256':snapshot['objects'][0]['sha256'],
      'capture_directory':CAP.relative_to(ROOT).as_posix(),'public_ADD_C_line':line,'typed_signature':signature,
      'typed_body_sha256':hashlib.sha256(body.encode()).hexdigest(),'typed_calls':dict(sorted(__import__('collections').Counter(calls).items())),
      'native_arithmetic':arithmetic,'model_word_adapter_calls':adapter,
      'boxed_wrapper':{'unbox_uint32':box.count('lean_unbox_uint32('),'dec':box.count('lean_dec('),'box_uint32':box.count('lean_box_uint32(')},
      'outer_diagnostic_assembly_kernel_hashes':outer_kernels,
      'outer_assembly_is_F7':outer_kernels==[sha(compiled)],
      'decision':'The new raw-word theorem can simplify proof-facing API transport. It cannot claim to delete runtime Model/word adapters from F7; these were already erased. Do not buy CI or large proof on that premise.',
      'scope':'Actual original-gate statement-side C export, not a timed MainFull caller/object claim. Its typed body is raw uint32->table decode->native ADD->float32_to_bits. Full caller boxing and conversion elapsed shares remain UNKNOWN.'}
    (HERE/'native-add-adapter-audit.json').write_text(json.dumps(record,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({'status':record['status'],'source':record['source_sha256'],'line':line,'arithmetic':arithmetic,'outer_assembly_is_F7':record['outer_assembly_is_F7']}))
if __name__=='__main__':main()
