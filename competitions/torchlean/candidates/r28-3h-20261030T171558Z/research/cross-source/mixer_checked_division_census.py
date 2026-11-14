"""Revisit an unmeasured R27 certificate with new measured Mixer LN share.

The old integer-mulHigh reciprocal lost native cost. The checked Float proposal
was never timed and was held because NMLP normalization share was small. This
is a finite applicability/cost-shape check, not a performance retry or proof.
"""
from pathlib import Path
from datetime import datetime,timezone
import collections
import hashlib
import importlib.util
import json
import sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path);module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module);return module


model=load('mixer_division',HERE/'mixer_path_model.py');m=model.m
oldword=HERE.parents[2]/'r27-5h-20261029T194443Z/research/word-proof'
cert=load('old_u32_certificate',oldword/'checked_division_u32_model.py')


def main():
    total=collections.Counter();records=[];cell_name=None;row_values=set();original_guard=m.guard_state;original_norm=m.norm
    def observe(n,w,gw,bw,b0,S1,dw,cap):
        state,ks=original_guard(n,w,gw,bw,b0,S1,dw,cap)
        if cap==26 and state not in ['row_guard','input_span']:
            sw,mw,iw=m.fields(w);_,mg,ig=m.fields(gw);_,_,ib=m.fields(bw);_,md,idd=m.fields(dw)
            cv=abs(n*sw*(mw<<max(0,iw-b0))-S1);d=n*md;r0=(cv%d)*mg
            pairs=[('cv',cv),('r0',r0)]
            if state=='inner_fast':pairs.append(('ra',(r0%d)<<(b0+ig-min(b0+ig,ib+idd))))
            row_values.add((cell_name,n,b0,S1,dw,d))
            for stage,a in pairs:
                got,branch=cert.proposal_path(a,d,1.0/float(d))
                assert got==divmod(a,d)
                # Quotient-only implementation recovers remainder without a tuple.
                q=got[0];assert q*d<=a and a-q*d==got[1]
                total['pairs']+=1;total[stage+'_pairs']+=1;total[branch]+=1
                total['wide_denominator']+=d>=1<<32
                total['quotient_ge_u32']+=q>=1<<32
                if len(records)<16:records.append({'cell':cell_name,'stage':stage,'a':a,'d':d,'q':q,'branch':branch})
        return state,ks
    def norm(x,rows,n,g,b=None,census=None):
        total['norm_rows']+=rows;total['norm_outputs']+=rows*n
        c={'rows':0,'stats_fast_nlt256':0,'row_lengths':collections.Counter(),'ks_distribution':collections.Counter(),**{f'cap{k}':collections.Counter()for k in [8,26,28]}}
        return original_norm(x,rows,n,g,b,census=c)
    m.guard_state=observe;m.norm=norm
    req=json.loads((model.r.E/'fp-word-conv6-26102901-request.json').read_bytes());measured=json.loads((model.r.E/'fp-word-conv6-26102901-measurement.json').read_bytes())['result'];checked=0
    for w in req['workloads']:
        for kind in ['normal','wide','sparse']:
            cell_name=f"{w['id']}|mixer:b1:{kind}";c=model.Census();out=model.r.run_cell('mixer',w['seed'],w['profile'],kind,c)
            assert model.r.fnv(out)==measured['rounds'][0]['cells'][cell_name]['candidate_checksum'];checked+=1
    total['distinct_observed_row_contexts']=len(row_values)
    result={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'OLD_SEEN_MIXER_CHECKED_DIVISION_APPLICABILITY_NOT_NATIVE',
      'source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'certificate_model_sha256':hashlib.sha256((oldword/'checked_division_u32_model.py').read_bytes()).hexdigest(),
      'native_matching_oldcells':checked,'totals':total,'examples':records,
      'new_premise':'CI3reference36 nowmeasures LayerNorm22.0-45.5percent of4entry exclusive time; oldR27NMLP ROIhold doesnot transfer directly. Not an exactwholemodelshare.',
      'mechanism':'Perrow1/D Float proposes UInt32 q; exact32x32 widened product and Euclidean rangecheck certify q, neighbor proposals then originaldivision fallback. Remainder=a-q*d avoids runtimepairallocation. AnyFloatproposal is correct aftercheck; cacheidentity affectsspeed only.',
      'old_negative_scope':'R27c688 integer reciprocal withfourpartial-product mulHigh measured1.024986x public23; thisFloatcertificate was not measured. No gain is inferred from this distinction.',
      'limits':['Host Float proposal/hitcount not native timing','All18cells sameoldcohort, not confirmation','Existing R27helper uncompiled; allinput/full12 integration andbytebudget OPEN','No additionalCI request; newcost must use norm26 control or accurately include its existinggain']}
    (HERE/'mixer-checked-division-census.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8');print(json.dumps({'cells':checked,'totals':total},indent=2))


if __name__=='__main__':main()
