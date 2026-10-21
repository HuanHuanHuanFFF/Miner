"""Test whether the observed four-slot overflow hides useful match choices."""
from pathlib import Path
import importlib,json,re
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start');fn=importlib.import_module('prepare-round24-extract-repro').fn
def main():
    p=ROOT/'candidates/r24-609-once';r=(p/'parse.rs').read_text();l=(p/'Parse.lean').read_text()
    # Only the six named collector/selection functions change, not depth, routes,
    # solver prices, encoder or other literal4/8 constants elsewhere.
    changes={}
    for n in ['SFsmalladd','SFsmallkeep','SFsmallmatches','SFfastadd','SFfastkeep','SFmorematches']:
        old=fn(r,n);s=old
        if n.startswith('SFsmall'):
            s=s.replace('[u32;8]','[u32;16]').replace('[0u32;8]','[0u32;16]')
            s=s.replace('%8','%16').replace('%4','%8').replace('add(4)','add(8)')
            s=s.replace('<4','<8')
        else:
            s=s.replace('[u32;4]','[u32;8]').replace('[usize;4]','[usize;8]').replace('[0u32;4]','[0u32;8]').replace('[0usize;4]','[0usize;8]')
            s=s.replace('%4','%8').replace('<4','<8')
        assert s!=old,n;assert r.count(old)==1;r=r.replace(old,s);changes[n]={'old':old,'new':s}
    e=w.write_candidate('r24-609-wide-frontier',p.name,r,l,'Retain up to eight distinct distance-code choices in both SF collectors, then apply their original price/length dominance filter. Search depth and quality objective stay unchanged.','L observed over3million four-slot overflows; its replacement policy recovered11actual bytes. This tests whether preserving additional distinct choices yields enough quality to compensate later solver and cache cost. One predeclared capacity expansion, not a sweep.',{'parent':p.name,'opportunity':'evidence/round24/38084061512/buffer-l-native/diagnostics/r24-buffer/receipt.json','proof':'DRAFT: collector array types, modulo bounds and loop limits changed. Original full gate mandatory.'})
    e.update(anchor='public609',comparison_baseline='once',native_decode_reference='once')
    s=json.loads((E/'groups-n-native.json').read_bytes());s.pop('r24_group_counts');s.update(description='V first actual native byte/decode measurement of eight-slot collectors. No timing or proof inference; current score geometry must justify any next run.')
    s['entries']=[x for x in s['entries']if x['control']]+[e];ns=[x['name']for x in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    for name,d in [('wide-v-native',s),('preflight-v',{'gap':'Need a real quality shift as well as speed; L replacement gave a small positive position but is far below10/15. Overflow counts include many dominated choices and cannot predict bytes.','change':'Double distinct-code retention capacity only in two named SF collectors; retain search and filtering policy.','minimum':'Original28-file encoder/decode; compare per-file sizes to actualonce. Recompute low-cost latest-frontier sensitivity using actual newsize before timing.','decision':'If quality does not create useful reward headroom, stop. If useful, measure added total-time cost before any promotion. Better bytes may cross the low-reward endpoint, so monotonicity is not assumed.','cost_cap_runner_minutes':15,'evidence':'evidence/round24/<run>/wide-v-native/diagnostics','proof_status':'DRAFT'}),('wide-v-source-diff',changes)]:
        out=E/(name+'.json');assert not out.exists();out.write_bytes((json.dumps(d,indent=2)+'\n').encode())
    print(e['name'])
if __name__=='__main__':main()
