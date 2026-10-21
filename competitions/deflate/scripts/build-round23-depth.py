"""One third-match probe aimed at actual quality headroom, not repeated delay tuning."""
from pathlib import Path
import importlib.util,json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round23'

def main():
    sp=importlib.util.spec_from_file_location('w',ROOT/'scripts/build-round18-start.py');w=importlib.util.module_from_spec(sp);sp.loader.exec_module(w)
    p=ROOT/'candidates/r22-595-chain-halfhead';r,l=[(p/f).read_text() for f in ('parse.rs','Parse.lean')]
    old='pc_run1c::<32768>(input,out,6,0,1000000,4294967295,1,4)';assert r.count(old)==1
    r=r.replace(old,old.replace(',1,4)',',2,4)'))
    e=w.write_candidate('r23-595-chain3',p.name,r,l,'Enable the existing second predecessor for route6: primaryplus two older candidates, allbytevalidated. Keep32768heads, skip6,lazy0, fold, minimum4 and allotherroutes.','R22 established -7238B onexactnew595 route6 but the quality point is still about0.0247formalpercentagepoints above612. EarlierDNA and539consumer tests used differentactualparents; this adds one real match-search capability to frozen595combination, not an arbitrary delay or table parameter sweep.',{'parent':'candidates/r22-595-chain-halfhead/manifest.json','component_evidence':'evidence/round22/final-analysis.json','original_source':'references/round21-public-595/source-receipt.json','ownership':'Existing PCgeneric chain engine inherited, originalheaders preserved.'})
    e.update(anchor='public595',comparison_baseline='combo',native_decode_reference='combo')
    s=json.loads((ROOT/'evidence/round22/probe-i-native.json').read_bytes())
    s['entries']=[en for en in s['entries'] if en['name'] in ('probe3','r3-432-fast3','public432','public514','public595','public595-shadow')]
    parent=w.control('combo',p.relative_to(ROOT).as_posix(),'595');parent.pop('formal_id');parent['anchor']='public595'
    s['entries']+=[parent,e]
    for k in list(s):
        if k.startswith('r22_'):del s[k]
    s.update(r23_mode='native',r23_expected_candidates=1,native_encoder_references=['public595','combo'],snapshot_pages='evidence/round23/official-start/pareto-pages.json',description='R23 C exactlyoneadditional older candidate onactualfrozen595combo. Original28fileencoder,token/outputidentity and independentdecode first; qualitythen total-time. Originalproofdraft neverconfersnewpairacceptance.')
    names=[en['name'] for en in s['entries']];s['screen_orders']=[names,names[::-1]]
    (E/'depth-c-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode())
    plan={'gap':'Frozencombo has onehigh and onezero timingblock, quality36.552formalconditional above61236.527. Needrealquality headroom rather than no-opdelay.','substantial_change':'Oneadditional bytevalidated older candidate in route6 via existing generic chain machinery on thisactualnewparent; no changes toclassification,encoder orotherbudgets.','minimum':'Actual28file encode/decode plus matchedtokens/output againstfrozencombo and595.','decision':'Ifrealqualitygain changesfrontieropportunity, allocate originalpairedtime and fullgate withremainingbudget. Ifpublicoutputsunchanged, donotbuy atargetedslowing experiment; preservefinite evidence and spend on exactcombo confirmation/diagnosis.','cost_cap_minutes':10,'evidence':'evidence/round23/<run>/depth-c-native/diagnostics','parent_prior':'evidence/round22/38070943123/screen-k/gate','proof_migration':'Samegeneric theorem text only; freshoriginal gate remainsmandatory.'}
    (E/'preflight-c.json').write_bytes((json.dumps(plan,indent=2)+'\n').encode());print(e)

if __name__=='__main__':main()
