from pathlib import Path
import hashlib,json
h=Path(__file__).resolve().parent
sha=lambda b:hashlib.sha256(b).hexdigest()
a=(h.parent/'f01-r11-wide4-codegen-probe/Kernel.lean').read_bytes()
b=(h/'projection.lean').read_bytes()
assert sha(a)=='eb9e76393b13448bd031134035706d3b05ce08b018f7d81dd5614db0c9ac007f'
assert sha(b)=='afd8d0bf8598f2f7eb612d2b53f8c318a8f4eb0b6eec41502c135db060774291'
x=a+b'\n'+b
m=json.loads((h/'manifest.json').read_bytes())
assert (h/'Kernel.lean').read_bytes()==x and sha(x)==m['candidate_sha256'] and len(x)==m['candidate_bytes']<=256000
print(json.dumps({'static_prefix_and_exact_asset':'PASS','sha256':sha(x),'bytes':len(x),'new_Lean':'NOT_RUN'}))
