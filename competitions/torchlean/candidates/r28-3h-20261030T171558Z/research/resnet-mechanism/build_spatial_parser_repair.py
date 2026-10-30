#!/usr/bin/env python3
"""Rebuild the same spatial algorithm with valid application spacing and short names.
Never edits an old frozen source. Native-only; no new correctness theorem.
"""
from pathlib import Path
import hashlib,importlib.util,json,re
P=Path(__file__).resolve().parent
BASE_SHA='ea6f582fc7a416b8860adb5c71fe3ab670dd4add01999fac7190993110f605a3'
PINS={
 'history/spatial-v0-oversize/build_spatial11.py':'d96205b64b9d9f51e7ba2584b21bbf6efad102baaa5b59ad0bf92a684d837496',
 'compact11.py':'8863afd1e3d0ec254ad0ac5a55250e18916848c6a6e6ee340a3f9c517a11c167'}
RENAMES=dict(zip(['R8C','R8X','R8Z','R8Q','R8J','R8A','R8S','R8Ctx','R8B','R8F','R8W','R8I','R8D','R8O','R8Run','R8Conv'],['rC','rX','rZ','rQ','rJ','rA','rS','rT','rB','rF','rW','rI','rD','rO','rR','rV']))
def load(name,file):
 spec=importlib.util.spec_from_file_location(name,file);module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module);return module
def runtime():
 for file,digest in PINS.items():assert hashlib.sha256((P/file).read_bytes()).hexdigest()==digest,file
 module=load('spatial_original_spaced_generator',P/'history/spatial-v0-oversize/build_spatial11.py')
 s=module.runtime()
 assert s.startswith('/- Original spatial native-only diagnostic. No new Submission.correct. -/\n')
 s=s[s.index('\n')+1:]
 for before,after in [(' bw:UInt32\n',''),(',signOf bw,bw⟩',',signOf bw⟩'),('Yf b[o]!==0','Yf b[o]! ==0'),('Yf w!=0','Yf w !=0')]:
  assert s.count(before)==1,before;s=s.replace(before,after)
 constants={'0x4000000000000000':'R8C','0x400000000000000':'R8X','0x200000000000000':'R8Z','0x800000000':'R8Q'}
 for literal,name in constants.items():s=s.replace(literal,name)
 s=''.join(f'@[inline] def {name}:UInt64:={literal}\n' for literal,name in constants.items())+s
 for old,new in RENAMES.items():
  assert not re.search(r'\b'+new+r'\b',s),new
 for old,new in RENAMES.items():s=re.sub(r'\b'+old+r'\b',new,s)
 return s
def transform(raw,submission,variant):
 assert submission==11 and variant=='spatial11-native-v3'
 assert hashlib.sha256(raw).hexdigest()==BASE_SHA
 s=raw.decode();start=s.index('def kernels:Kernels where');tail=s[start:]
 record=tail[:tail.index('theorem correct:')].replace('conv:=⟨Ybp,dwQ⟩','conv:=⟨rV,dwQ⟩')
 old=re.sub(r'\bkernels\b','R8K',tail);old=re.sub(r'\bcorrect\b','R8P',old)
 for name in RENAMES.values():
  assert not re.search(r'(?m)^(?:@\[[^\n]*\]\s*)?(?:def|lemma|theorem|structure|abbrev)\s+'+name+r'\b',s)
 assembled=s[:start]+old[:old.rfind('end Submission')]+'\n'+runtime()+'\n'+record+'end Submission\n'
 compact=load('spatial_valid_spacing_compact',P/'compact11.py')
 result=compact.compact(assembled.encode(),strict_base=False)
 assert len(result)<=256000,len(result)
 assert b'theorem correct:' not in result
 return result
def main():
 raw=(P.parents[1]/'competition-state/source-private/official-11.lean').read_bytes()
 result=transform(raw,11,'spatial11-native-v3')
 (P/'private/spatial11-native-v3.lean').write_bytes(result)
 (P/'SpatialRuntime-v3.lean.inc').write_bytes(runtime().encode())
 r={'state':'PARSER_BOUNDARIES_REPAIRED_NATIVE_ONLY_UNCOMPILED','variant':'spatial11-native-v3','source_sha256':hashlib.sha256(result).hexdigest(),'bytes':len(result),'recipe_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'dependencies':PINS,'runtime_sha256':hashlib.sha256(runtime().encode()).hexdigest(),'renames':RENAMES,'changes':'Restore original required function-argument whitespace, repair sole unseparated !=, alpha-rename only owned runtime functions/constants to short fresh names. Same arithmetic/cache/guards/outputorder; old sources retained.','new_entry':'Submission.rV','declares_correct':False,'full_gate':False,'compile_native':'NOT_RUN','invalid_predecessors':['8e5b27c0','f59a9b41'],'parser_source':'Lean4.34 Term.argument at line891 requires checkWsBefore; Parser.Basic checkWsBeforeFn checks actual trailing whitespace.','new_math_claim':False}
 (P/'spatial-parser-repair-receipt.json').write_bytes((json.dumps(r,indent=2)+'\n').encode());print(json.dumps(r,indent=2))
if __name__=='__main__':main()
