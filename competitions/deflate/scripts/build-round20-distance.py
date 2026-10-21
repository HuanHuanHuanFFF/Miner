"""Require a longer secondary match to compensate its encoded distance cost."""
from pathlib import Path
import importlib.util,json
ROOT=Path(__file__).resolve().parents[1]
def main():
    sp=importlib.util.spec_from_file_location('w',ROOT/'scripts/build-round18-start.py');w=importlib.util.module_from_spec(sp);sp.loader.exec_module(w)
    p=ROOT/'candidates/r18-539-csv-lazy-content';r,l=[(p/f).read_text()for f in ('parse.rs','Parse.lean')]
    old='if m > l && m >= minl {';assert r.count(old)==1
    r=r.replace(old,'if m > l && m >= minl && pc_gain(m, d2) > pc_gain(l, d) {')
    e=w.write_candidate('r20-539-csv-distance',p.name,r,l,
      'The existing second-predecessor search accepts a longer match only if its existing PC approximate coded gain also exceeds the current nearer match. Search coverage and byte validation remain unchanged.',
      'Earlier EF32 results showed longer matches can inflate distance cost, but that different engine did not test this PC secondary-choice condition. Here one comparator is changed; lazy parsing remains disabled on generic text to isolate the mechanism.',
      {'parent':'candidates/r18-539-csv-lazy-content/manifest.json','prior':'docs/rounds/round13.md','source':'references/round18-public-539/source-receipt.json'})
    e.update(anchor='public539',comparison_baseline='csv18',native_decode_reference='public539')
    s=json.loads((ROOT/'evidence/round20/probe-d-native.json').read_bytes());s['entries']=[e for e in s['entries']if e.get('control')]+[e];s['description']='F one distance-aware secondary match comparator;28 original encoding/decode,15minute cap. Positive quality or fewer tokens without large quality loss earns paired timing. No raw match-length proxy or fullgate claim.';ns=[e['name']for e in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    (ROOT/'evidence/round20/probe-f-native.json').write_text(json.dumps(s,indent=2)+'\n')
    (ROOT/'evidence/round20/preflight-f.json').write_text(json.dumps({'gap':'Need low-overhead quality improvement in the fast family. A longer match may be farther and cost more to encode; current PC secondary selection considers length only.','change':'One encoded-gain comparator applied only after the existing longer/minlength checks.','minimum':'One full original encoder/decode run; compare perfile bytes and tokens against exactCSV18.','decision':'Improved real bytes retains this route; quality loss with no countervailing evidence pauses it before expensive proof. Any retained candidate must pass original total timing.','cap_runner_minutes':15,'proof':'Original f_try matchedness contract remains; existing gain_spec must be rechecked after new extraction.','evidence':'evidence/round20/<run>/probe-f-native/diagnostics'},indent=2)+'\n')
    print(e['name'])
if __name__=='__main__':main()
