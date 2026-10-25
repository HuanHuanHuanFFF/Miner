"""Map original compiler errors to exact-source declarations, without running Lean."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import json
import re
import subprocess

OUT=Path(__file__).resolve().parent
ROOT=OUT.parents[4]
ap=argparse.ArgumentParser();ap.add_argument('--run',type=int,required=True);args=ap.parse_args()
sha=lambda b:hashlib.sha256(b).hexdigest()
reports=sorted(OUT.glob(f'development-proof-*-{args.run}.json'))
assert reports
result=[]
math_names=('R14BiasRNE','R14SmallShiftBias','R14WordAddAlignment','R14WordAddRounding',
            'R14NatNormal','R14ExponentAlgebra','R14NativeProduct','R14ExponentShift')
for report_path in reports:
    report=json.loads(report_path.read_bytes())
    if not report.get('compiler_output'):continue
    output=ROOT/report['compiler_output'];raw=output.read_bytes()
    assert sha(raw)==report['compiler_output_sha256']
    relative='competitions/floatlib/candidates/'+report['candidate']+'/Kernel.lean'
    source=subprocess.check_output(['git','show',report['source_commit']+':'+relative],cwd=ROOT)
    assert sha(source)==report['kernel_sha256']
    lines=source.decode().splitlines();namespace='';stack=[];declarations=[]
    for index,line in enumerate(lines,1):
        if match:=re.match(r'^namespace\s+([A-Za-z_][A-Za-z0-9_.]*)',line):
            stack.append(namespace);namespace=(namespace+'.' if namespace else '')+match[1]
        elif re.match(r'^section\b',line):stack.append(namespace)
        elif re.match(r'^end(?:\s|$)',line):
            if stack:namespace=stack.pop()
        elif match:=re.match(r'^(?:@\[[^\n]*\]\s*)?(?:private\s+|protected\s+)?(?:theorem|lemma|def|abbrev)\s+([A-Za-z_][A-Za-z0-9_\'.]*)',line):
            declarations.append((index,(namespace+'.' if namespace else '')+match[1]))
    errors={}
    for block in re.split(r'(?=error: work/Submission\.lean:)',raw.decode('utf-8','replace')):
        match=re.match(r'error: work/Submission\.lean:(\d+):(\d+):\s*(.*)',block,re.S)
        if not match:continue
        line,col=int(match[1]),int(match[2])
        message=re.split(r'\n(?:warning: |Some required targets logged failures:|error: build failed)',match[3],maxsplit=1)[0].strip()
        key=(line,col,message)
        if key in errors:errors[key]['occurrences']+=1;continue
        declaration=next((name for start,name in reversed(declarations) if start<=line),'UNKNOWN')
        owner='research' if any('.'+name+'.' in declaration for name in math_names) or declaration.endswith('.raw_add_model') else 'development'
        errors[key]=dict(line=line,column=col,declaration=declaration,owner=owner,occurrences=1,
                         source_context=[dict(line=n,text=lines[n-1]) for n in range(max(1,line-2),min(len(lines),line+2)+1)],
                         message=message)
    result.append(dict(candidate=report['candidate'],kernel_sha256=report['kernel_sha256'],
                       source_commit=report['source_commit'],source_path=relative,
                       original_output=report['compiler_output'],original_output_sha256=report['compiler_output_sha256'],
                       statement_pass=report['statement_pass'],errors=list(errors.values())))
record=dict(at_utc=datetime.now(timezone.utc).isoformat(),run=args.run,candidates=result,
            scope='Original byte-hashed build output and immutable Git source only. Repeated identical errors deduplicated with counts; ownership is a routing hint, never permission. No compilation, repair or correctness claim.')
path=OUT/f'development-compiler-error-map-{args.run}.json';assert not path.exists()
path.write_bytes((json.dumps(record,ensure_ascii=False,indent=2)+'\n').encode())
lines=[f'# CI {args.run} 精确源码错误索引','',
       '原始日志和失败源未修改。这里只去重并定位声明，修复后必须重新编译。','']
for item in result:
    lines.extend([f"## {item['candidate']}",f"源码：`{item['kernel_sha256']}`；提交：`{item['source_commit']}`。",''])
    for error in item['errors']:
        headline=error['message'].splitlines()[0]
        lines.append(f"- {error['owner']} · L{error['line']}:{error['column']} · `{error['declaration']}` · {headline}（{error['occurrences']}次）")
    lines.extend(['',f"完整错误：JSON同名文件；原日志 `{item['original_output']}`。",''])
path.with_suffix('.md').write_bytes(('\n'.join(lines)+'\n').encode())
print(json.dumps([dict(candidate=r['candidate'],unique_errors=len(r['errors']),research=sum(e['owner']=='research' for e in r['errors'])) for r in result]))
