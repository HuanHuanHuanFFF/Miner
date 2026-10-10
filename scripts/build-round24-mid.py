"""Transfer the proven SF module to two different public middle-budget parsers."""
from pathlib import Path
import importlib,json,re
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start')
def main():
    module=ROOT/'candidates/r19-sf-nooverlap'
    mr=(module/'parse.rs').read_text();ml=(module/'Parse.lean').read_text()
    rust_tail=mr[mr.index('// R18 transfers the public591 SFshape stage;'):]
    lean_tail=ml[ml.index('namespace R18SF'):]
    entries=[]
    for ident in ['552','532']:
        p=ROOT/f'references/round24-public-{ident}';r,l=[(p/f).read_text() for f in ('parse.rs','Parse.lean')]
        assert r.count('pub fn parse(input:')==1 and 'pub fn Z377(' not in r and 'pub fn SFshape(' not in r
        r=r.replace('pub fn parse(input:', 'pub fn r18_base(input:',1)+'\n'+rust_tail
        # Retain every nested engine theorem; only the final top-level parser
        # declaration is renamed to serve the compositional wrapper.
        at=l.rfind('theorem parse_spec (');assert at>=0
        suffix=l[at:];assert suffix.count('slot.parse')==2 and suffix.rstrip().endswith('end Submission')
        suffix=suffix.replace('theorem parse_spec (','@[local step]\ntheorem r18_base_spec (',1).replace('slot.parse','slot.r18_base')
        suffix=suffix[:suffix.rfind('end Submission')]
        l=l[:at]+suffix+'\n'+lean_tail
        e=w.write_candidate(f'r24-{ident}-sf-middle',f'public{ident}',r,l,
            'Compose exact public middle-budget base parser with the previously verified content-gated SF seam refiner. Existing base routes, search and cost tables are preserved; append one refiner with original exact final cost acceptance and rechecked output emission.',
            'R19 measured SF on the stronger, slower603-family base. This tests lower-cost public552 and532 bases at different frontier positions rather than another micro-parameter retry on609. Component quality/time is not assumed additive and the old gate is not inherited.',
            {'base_source':f'references/round24-public-{ident}/source-receipt.json','refiner_source':'candidates/r19-sf-nooverlap/manifest.json','refiner_prior':'docs/rounds/round19.md','ownership':'All original source, proof authors and comments retained; this is a compositional derivative.'})
        e.update(anchor='public'+ident,comparison_baseline='public'+ident,native_decode_reference='public'+ident);entries.append(e)
    s=json.loads((E/'quality-b-native.json').read_bytes());s['entries']=[x for x in s['entries']if x['name']in('probe3','r3-432-fast3','public432','public514')]
    for ident in ['552','532','443']:
        c=w.control('public'+ident,f'references/round24-public-{ident}',ident);s['entries'].append(c)
        if ident!='443':
            shadow=dict(c);shadow['name']=c['name']+'-shadow';shadow.pop('formal_id');s['entries'].append(shadow)
    s['entries']+=entries;s.update(r24_expected_candidates=2,native_encoder_references=['public552','public532','public443'],description='R24 H different middle-frontier bases: exact552/532 plus inherited contentSF. Three actual public baselines, original28-fileencode/decode, fresh exactcombined proof required. Lower-cost base may have more useful quality headroom; transfer is a hypothesis.')
    ns=[x['name']for x in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    (E/'mid-h-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode())
    plan={'gap':'Fastfamily gains remainedzero; highqualityonce609 needs muchmore speed. Keep a distinct middle-frontier route where a smaller quality improvement may change allocation.',
        'change':'Combine an actual lower-cost public base552or532 with the already validatedSF module; compare real composite bytes and retain all baseauthor configuration. Public443 is an additional lower-time baseline, not a newcandidate.',
        'minimum':'Original28-file encoder and independentdecode of two real composites plus552/532/443; inspect per-file size effects before whole timing or proof.',
        'decision':'Useful quality/time opportunity under current official geometry earns original pairedtiming. Noqualityimprovement meansdo not assumeSF transfer succeeds. If qualityrecovers but workgrows, use actualtiming rather than addcomponent gains.',
        'cost_cap_runner_minutes':15,'proof':'Renamed original top-level base theorem plus inheritedSF theorem module; exactcombined extraction/fullgate NOT_RUN.',
        'evidence':'evidence/round24/<run>/mid-h-native/diagnostics','limits':'Different public-to-private family transfers remain conditional; neither previousfamily coefficients nor newbaseline publicbytes guarantee formal results.'}
    (E/'preflight-h.json').write_bytes((json.dumps(plan,indent=2)+'\n').encode());print(json.dumps(entries))
if __name__=='__main__':main()
