"""Cheap archive repair for actual batch6 compactor parse errors.

The reciprocal mechanism failed its native screen. No further performance or
gate request is made. Keep this separate from frozen9654/c688 source bytes.
"""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json,types
HERE=Path(__file__).resolve().parent
def sha(data):return hashlib.sha256(data).hexdigest()
def transform(raw,submission=23,variant='reciprocal23-archive-parse-v4'):
 assert submission==23 and variant=='reciprocal23-archive-parse-v4'
 frozen=(HERE/'public23_reciprocal_v3.py').read_bytes()
 assert sha(frozen)=='080584fa0e222c95db517c92802177a405810aaca5020178f9934d08da3c9bb6'
 code=frozen.decode()
 anchor="    exec(compile(source,m.__file__,'exec'),m.__dict__)"
 replacement='''    # Preserve whitespace between application head and parenthesized arguments.
    old_line='        body=re.sub(r"\\\\s*([\\\\[\\\\]{}()])\\\\s*",r"\\\\1",body)'
    new_lines='        body=re.sub(r"([\\\\[({])\\\\s+",r"\\\\1",body)\\n        body=re.sub(r"\\\\s+([\\\\])}])",r"\\\\1",body)'
    assert source.count(old_line)==1
    source=source.replace(old_line,new_lines)
    exec(compile(source,m.__file__,'exec'),m.__dict__)'''
 assert code.count(anchor)==1
 code=code.replace(anchor,replacement)
 m=types.ModuleType('r27_archive_v4');m.__file__=str(HERE/'public23_reciprocal_v3.py')
 exec(compile(code,m.__file__,'exec'),m.__dict__)
 return m.transform(raw,23,'row-reciprocal23-v3')

if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--source',type=Path,required=True);p.add_argument('--receipt',type=Path,required=True)
 a=p.parse_args();result=transform(a.source.read_bytes())
 sp=importlib.util.spec_from_file_location('r27_archive_policy',HERE/'patch_public.py')
 m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
 receipt={'at_utc':datetime.now(timezone.utc).isoformat(),'candidate_sha256':sha(result),'candidate_bytes':len(result),
  'state':'ARCHIVE_ONLY_PARSE_REPAIR_NOT_COMPILED_NOT_QUEUED','policy':m.policy_check(result),
  'repair':'Only own helper compactor whitespace: retain spaces before parenthesized applications and binders, per actual2632/2728/2730 parser errors',
  'cascade':'Unknown R27D.v and Ya7Ge q/r rewrite failures may follow the parser failure; not claimed fixed without compilation',
  'budget':'No further reciprocal gate/performance queue requested; native cost c688 failed current43 screen',
  'proof':'Standalone v4 helper013a four roots accepted in40967910604, separate from this full actual source',
  'publication':'Own recipe/receipt only; full source private/ephemeral'}
 a.receipt.write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8');print(json.dumps(receipt,indent=2))
