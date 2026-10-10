"""Remove the backward-fold stage, keeping already validated forward matches."""
from pathlib import Path
import importlib.util,json
ROOT=Path(__file__).resolve().parents[1]
def main():
    sp=importlib.util.spec_from_file_location('w',ROOT/'scripts/build-round18-start.py');w=importlib.util.module_from_spec(sp);sp.loader.exec_module(w)
    es=[]
    for parent,name in [('r18-539-csv-lazy-content','r20-539-csv-nofold'),('r20-539-csv-singlehead','r20-539-csv-head-nofold')]:
        p=ROOT/'candidates'/parent;r,l=[(p/f).read_text()for f in ('parse.rs','Parse.lean')]
        a=r.index('pub fn pc_fold_w(');brace=r.index('{',a);end=r.index('\n#[inline(always)]',brace);assert r[brace:end].rstrip().endswith('}')
        r=r[:brace]+'{\n    (nt0, p0, l0)\n}\n'+r[end:]
        a=l.index('theorem fold_w_spec ');body=l.index(' := by',a)+len(' := by');end=l.index('\ndef LazyInv ',body)
        l=l[:body]+'\n  rw [slot.pc_fold_w]\n  step*\n  all_goals exact ⟨hdec, hm, rfl, le_refl _⟩\n'+l[end:]
        e=w.write_candidate(name,parent,r,l,
          'Remove PC backward-fold precheck and token rewind stage, retaining the already valid forward match unchanged. '+('Applied on frozen head-only text parent.'if parent.endswith('singlehead')else'Applied on originalCSV18 chain parent.'),
          'R17 disabled folding on a different DNA PC route; this tests the broad539 PC family and its interaction with head-only text. Goal is a real larger speed margin if compression remains useful, not an arbitrary delay or scoring-only change. Extra tokens/encoder costs may invalidate the idea.',
          {'parent':'candidates/'+parent+'/manifest.json','prior':'docs/rounds/round17.md','source':'references/round18-public-539/source-receipt.json'})
        e.update(anchor='public539',comparison_baseline='csv18',native_decode_reference='public539');es.append(e)
    s=json.loads((ROOT/'evidence/round20/probe-d-native.json').read_bytes());s['entries']=[e for e in s['entries']if e.get('control')]+es;s['description']='O stage-removal boundary: PC backward folding on chain andhead-only parents. Full28fileoriginalencoder/decode,15mincap. Token/byte inflation can erase parser savings; timing only if tradeoff retains useful top1-impact space. Preparedidentitylemma remainsdraft until freshoriginalgate.';ns=[e['name']for e in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    (ROOT/'evidence/round20/probe-o-native.json').write_text(json.dumps(s,indent=2)+'\n')
    (ROOT/'evidence/round20/preflight-o.json').write_text(json.dumps({'gap':'Singlehead speed edge is comparable to same-source noise; need a larger real speed/quality tradeoff to make595impact repeatable.','change':'Remove an entire backward-fold stage on twoalreadydistinctparents; preservevalidforwardmatches and originalencoder.','minimum':'28file bytes,tokens,decode fromactualRust; native output does not establishspeed.','decision':'Retainedusefulquality earnsone pairedtimebatch; severe tokeninflationorqualityloss pauses thisstage-removal approach. No automatic promotion fromlessparserwork.','cap_runner_minutes':15,'proof':'Identityfold result follows originalDecandMatchAtpremises; draftedlemma exact fullgateunrun.','evidence':'evidence/round20/<run>/probe-o-native/diagnostics'},indent=2)+'\n')
    print([e['name']for e in es])
if __name__=='__main__':main()
