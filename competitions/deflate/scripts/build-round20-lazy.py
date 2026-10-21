"""Complete a mechanism-level chain/lookahead comparison, not a depth sweep."""
from pathlib import Path
import importlib.util,json,re
ROOT=Path(__file__).resolve().parents[1]

def main():
    sp=importlib.util.spec_from_file_location('w',ROOT/'scripts/build-round18-start.py');w=importlib.util.module_from_spec(sp);sp.loader.exec_module(w)
    entries=[]
    for parent,name,chain in [('r18-539-csv-lazy-content','r20-539-csv-chainlazy',True),('r20-539-csv-singlehead','r20-539-csv-headlazy',False)]:
        p=ROOT/'candidates'/parent;r,l=[(p/f).read_text()for f in ('parse.rs','Parse.lean')]
        for row in [10,16,18]:
            pattern=rf'(pub fn p135_row{row}\(input:&\[u8\],out:&mut\[u32\]\)->usize\{{pc_run1'+('c'if chain else'')+r'::<32768>\(input,out,\d+,)0(,1000000,4294967295)'
            r,n=re.subn(pattern,lambda m:m[1]+'258'+m[2],r);assert n==1
        e=w.write_candidate(name,parent,r,l,
          'Enable existing lookahead/lazy parsing in content-routed generic text engines10/16/18, '+('retaining the predecessor chain.'if chain else'using only the primary head table.'),
          'Together with CSV18 and first-batch singlehead this separates predecessor search, lazy parse decisions and their interaction. Only two missing mechanism combinations; no numeric parameter sweep. Total encoder cost may fall if token count/quality improves, or search may dominate.',
          {'parent':'candidates/'+parent+'/manifest.json','source':'references/round18-public-539/source-receipt.json'})
        e.update(anchor='public539',comparison_baseline='csv18',native_decode_reference='public539');entries.append(e)
    s=json.loads((ROOT/'evidence/round20/probe-a-native.json').read_bytes());s['entries']=[e for e in s['entries']if e.get('control')]+entries;s['native_encoder_references']=['public539','csv18'];s['description']='D original28file encoding/decode for two missing cells of chain-versus-lookahead mechanism comparison. Quality gains must translate to total time/frontier position;20minute cap. Existing generic parameterized proof is a draft until exact full gate.';ns=[e['name']for e in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    (ROOT/'evidence/round20/probe-d-native.json').write_text(json.dumps(s,indent=2)+'\n')
    (ROOT/'evidence/round20/preflight-d.json').write_text(json.dumps({'gap':'A narrow speed window alone is not a stable top1 route. Need quality improvement with minimal additional total time. Head-only removes quality but may save search; lookahead offers an independent parse-choice mechanism.','change':'Two factorial cells: chain+lazy and head-only+lazy, versus already measured chain/no-lazy and head-only/no-lazy.','minimum':'Original encoder28files, perfile bytes and tokens, decode and source hashes.','decision':'Keep meaningful quality improvements for original total-time timing; no quality benefit halts that exact mechanism. Native counts alone do not prove speed.','cap_runner_minutes':20,'evidence':'evidence/round20/<run>/probe-d-native/diagnostics','proof_risk':'No new functions, original parameterized PC contracts; exact pair still requires new extraction and original gate.'},indent=2)+'\n')
    print([e['name']for e in entries])
if __name__=='__main__':main()
