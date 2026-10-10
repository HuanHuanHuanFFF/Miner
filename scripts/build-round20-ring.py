"""One bounded predecessor-retention tradeoff after secondary usefulness counts."""
from pathlib import Path
import importlib.util,json
ROOT=Path(__file__).resolve().parents[1]
def main():
    sp=importlib.util.spec_from_file_location('w',ROOT/'scripts/build-round18-start.py');w=importlib.util.module_from_spec(sp);sp.loader.exec_module(w)
    p=ROOT/'candidates/r20-539-csv-prev16-proof1';r,l=[(p/f).read_text()for f in ('parse.rs','Parse.lean')]
    assert r.count('[0u16; 32768]')==2
    r=r.replace('[u16; 32768]','[u16; 16384]').replace('[0u16; 32768]','[0u16; 16384]')
    for v in ['i','c','c2']:r=r.replace(f'prev[{v} % 32768]',f'prev[{v} % 16384]')
    # Keep the coordinate reconstruction modulus and real DEFLATE window32768.
    assert ' & 32767' in r and 'prev[c % 32768]'not in r
    l=l.replace('Array Std.U16 32768#usize','Array Std.U16 16384#usize')
    e=w.write_candidate('r20-539-csv-ring16k',p.name,r,l,
      'Halve only the16-bit predecessor-retention ring from32768 to16384 slots. Full-width head table,32KiB legal distance, low15-bit hint reconstruction and checked matcher remain. Older secondary hints may be overwritten earlier.',
      'UntimedI found second candidates useful across all short-length bins; no large negligible-benefit length region justified pruning. This changes cache footprint/retention rather than disabling those queries. One capacity intervention, not a grid sweep; native quality loss decides continued investment.',
      {'parent':'candidates/r20-539-csv-prev16-proof1/VERIFICATION.json','opportunity_counts':'evidence/round20/38051458977/count-i-native/diagnostics/r20-secondary/counts.json','source':'references/round18-public-539/source-receipt.json'})
    e.update(anchor='public539',comparison_baseline='prev16base',native_decode_reference='public539')
    s=json.loads((ROOT/'evidence/round20/probe-d-native.json').read_bytes());s['entries']=[v for v in s['entries']if v.get('control')]
    c=w.control('prev16base','candidates/r20-539-csv-prev16-proof1','539');c.pop('formal_id');c['anchor']='public539';s['entries']+=[c,e];s['native_encoder_references']=['public539','csv18','prev16base'];ns=[v['name']for v in s['entries']];s['screen_orders']=[ns,ns[::-1]];s['description']='L one cache-retention intervention motivated byI. Original28file encoder/decode comparesexactCSV18andprev16.15minute cap. Preserve legal32KiBwindow; aliases are validated hints. Meaningful quality retained earns real timing, broad size loss pauses before proof.'
    (ROOT/'evidence/round20/probe-l-native.json').write_text(json.dumps(s,indent=2)+'\n')
    (ROOT/'evidence/round20/preflight-l.json').write_text(json.dumps({'gap':'Singlehead saves time but loses quality. U16 preservesquality but speeduncertain. I counted~931ksecondaryqueries with~110kselectedlonger matches; length-only pruning has no clear large low-value region.','change':'Halve retained predecessor slots to fit32KiB; keepheads, search anddistanceverification.','minimum':'Actualoriginalencoder on28files anddecodedoutputs, sameoldprev16andCSV18references.','decision':'Onlyretainedqualitywith plausible smaller-cache value receivespairedtotal-time. Lostqualitycannotbeignored to claimfasterdominance.','cap_runner_minutes':15,'proof':'Onlypredecessorarraytypes/indiceschanged; existingproofdraftadapted, notaccepteduntil originalfullgate.','scope':'This is one bounded retention tradeoff; no guarantee for unseeninputs.'},indent=2)+'\n')
    print(e['name'])
if __name__=='__main__':main()
