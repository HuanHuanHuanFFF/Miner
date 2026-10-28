"""Replay R22's fixed evidence checks with only the nested lookup map; no Lean."""
from pathlib import Path
import hashlib,json
here=Path(__file__).resolve().parent
oldpath=here.parents[1]/'round6h-20261027T211247Z/research/verify-collected-statement.py'
old=oldpath.read_text(encoding='utf-8');new=old
maps={"source=directory/'inputs'":"scope=directory/'diagnostics/f01-d7-public-suite/public-suite'\nsource=scope/'inputs'",
      "diag=directory/'diagnostics'":"diag=scope/'diagnostics'",
      "v=json.loads((directory/(name+":"v=json.loads((scope/(name+"}
for a,b in maps.items():assert new.count(a)==1;new=new.replace(a,b)
(here/'component-verifier-map.json').write_text(json.dumps(dict(original_path=str(oldpath),original_sha256=hashlib.sha256(oldpath.read_bytes()).hexdigest(),mapped_sha256=hashlib.sha256(new.encode()).hexdigest(),lookup_substitutions=3,all_original_evidence_checks_unchanged=True),indent=2)+'\n')
exec(compile(new,str(oldpath),'exec'),{'__name__':'__main__','__file__':str(here/'verify-component-originals.py')})
