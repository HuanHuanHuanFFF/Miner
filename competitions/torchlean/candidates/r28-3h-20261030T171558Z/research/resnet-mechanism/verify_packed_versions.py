#!/usr/bin/env python3
"""Rebuild the retained prototype and corrected version; verify the exact source delta."""
from pathlib import Path
import difflib,hashlib,importlib.util,json
P=Path(__file__).resolve().parent
def main():
    raw=(P.parents[1]/'competition-state/source-private/official-11.lean').read_bytes()
    variants=[
      ('v1',P/'history/packed-v1/build_packed_support.py','packed-support11','6bf92e5fa5367e2143fb2d02bae466781be540761bba50b0375ae7fc7c472539'),
      ('v2',P/'build_packed_support.py','packed-support11-v2','a498d9b70f9892a671943c6a726c36e2e745baae33fb986b899012ccf3f8b6c2')]
    results={};sources={}
    for name,file,variant,expected in variants:
      spec=importlib.util.spec_from_file_location('owned_'+name,file)
      module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)
      result=module.transform(raw,11,variant)
      assert hashlib.sha256(result).hexdigest()==expected
      sources[name]=result
      results[name]={'bytes':len(result),'sha256':expected}
    diff=list(difflib.unified_diff(sources['v1'].decode().splitlines(),sources['v2'].decode().splitlines(),n=0))
    assert len([x for x in diff if x.startswith('+') and not x.startswith('+++')])==3
    assert len([x for x in diff if x.startswith('-') and not x.startswith('---')])==2
    receipt={'state':'BYTE_REBUILT_BOTH_VERSIONS_AND_EXACT_DELTA_CHECKED','versions':results,'diff':diff,'scope':'Only original owned runtime lines shown; whole sources remain private','not_claimed':['Lean compilation','native execution','all12 for prototype'],'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}
    (P/'packed-v2-change-review.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(receipt,indent=2))
if __name__=='__main__':main()
