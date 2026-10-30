#!/usr/bin/env python3
"""Fresh-directory recipe dependency and byte reconstruction check, no compilation."""
from pathlib import Path
import ast,datetime,hashlib,importlib.util,json,shutil
P=Path(__file__).resolve().parent
def load(name,path):
 s=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
def main():
 stamp=datetime.datetime.now(datetime.timezone.utc).strftime('%Y%m%dT%H%M%SZ')
 out=P/'private'/('portability-preflight-'+stamp);out.mkdir(parents=True,exist_ok=False)
 out.resolve().relative_to(P.resolve())
 raw=(P.parents[1]/'competition-state/source-private/official-11.lean').read_bytes()
 assert hashlib.sha256(raw).hexdigest()=='ea6f582fc7a416b8860adb5c71fe3ab670dd4add01999fac7190993110f605a3'
 ready=json.loads((P/'READY.json').read_text())
 candidates=[{'candidate':'zero-pair11','recipe':'build_zero_pair.py','dependencies':{},'variant':'zero-pair11','sha256':'c6a4da975e84f9b00d606d63f2aeec77bf05e10534fe1267463dffbdff6d23f4','bytes':252334},ready['alternate_native_only'],ready['spatial_native_only']]
 results=[]
 for c in candidates:
  target=out/c['candidate'];target.mkdir()
  needed=set(c['dependencies'])|{c['recipe']};copied={}
  for name in sorted(needed):
   src=P/name;dest=target/name;dest.resolve().relative_to(out.resolve())
   data=src.read_bytes();digest=hashlib.sha256(data).hexdigest()
   if name in c['dependencies']:assert digest==c['dependencies'][name]
   if name==c['recipe'] and c.get('recipe_sha256'):assert digest==c['recipe_sha256']
   dest.parent.mkdir(parents=True,exist_ok=True);dest.write_bytes(data);copied[name]=digest
  module=load('fresh_'+c['candidate'].replace('-','_'),target/c['recipe'])
  result=module.transform(raw,11,c['variant'])
  assert len(result)==c['bytes'] and hashlib.sha256(result).hexdigest()==c['sha256']
  assert len(result)<=256000 and result.decode('utf-8').encode('utf-8')==result
  results.append({'candidate':c['candidate'],'sha256':c['sha256'],'bytes':len(result),'copied_dependencies':copied,'fresh_directory_rebuild':'PASS'})
 parsed=[]
 for f in sorted(P.glob('*.py')):
  ast.parse(f.read_text(encoding='utf-8'),filename=str(f));parsed.append(f.name)
 report={'state':'FRESH_DIRECTORY_REBUILD_AND_PYTHON_SYNTAX_PASS','at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'results':results,'current_python_files_ast_parsed':parsed,'compiler_native_gate':'NOT_RUN','private_artifacts':'Only own dependency copies/pycache retained in ignored private portability directory; complete downloaded source not copied there. Generated source verified in memory only.','script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}
 (P/'portability-preflight-receipt.json').write_bytes((json.dumps(report,indent=2)+'\n').encode())
 print(json.dumps(report,indent=2))
if __name__=='__main__':main()
