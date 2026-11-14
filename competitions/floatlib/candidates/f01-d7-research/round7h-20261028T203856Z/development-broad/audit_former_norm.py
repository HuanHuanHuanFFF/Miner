"""Source-bound call/representation audit; never copies former2 bodies."""
from pathlib import Path
import hashlib
import json
import re

HERE=Path(__file__).resolve().parent
SOURCE=HERE.parent/'source-snapshot/former-champion-2.Kernel.lean'
EXPECTED='cea4422fb6d3bd613b306127e7017331560875ddb840a7f2e174f6c03bdb480f'

def main():
    raw=SOURCE.read_bytes();assert hashlib.sha256(raw).hexdigest()==EXPECTED
    lines=raw.decode().splitlines(keepends=True)
    pattern=re.compile(r'^\s*(?:@\[[^\]]*\]\s*)?(def|lemma|theorem|structure)\s+([A-Za-z0-9_\.\']+)')
    starts=[(i,m.group(1),m.group(2)) for i,line in enumerate(lines) if (m:=pattern.match(line))]
    bodies={}
    for k,(i,kind,name) in enumerate(starts):
        end=starts[k+1][0] if k+1<len(starts) else len(lines)
        if kind in ('def','structure'):bodies[name]=(i,end,''.join(lines[i:end]))
    selected=('kernels','kernels0','YaN','YaM','Yn','Yw','Ybb','Ybc','YaE','Y8','Y2','Y6','Y7','YaD','sqW','Ya7','Yba','YN','Ya8','Ya9','YaV','Ya3','Ybp','dwQ','cdQ','QPa','YaU','YaC','Ya2','QY6G','YS','YS6','YE','YL','YD','Ybo','YaQ','YaR','YaS')
    nodes={}
    for name in selected:
        assert name in bodies,name
        i,end,body=bodies[name]
        calls=[n for n in selected if n!=name and re.search(r'(?<![A-Za-z0-9_\'])'+re.escape(n)+r'(?![A-Za-z0-9_\'])',body)]
        nodes[name]={'line_start':i+1,'line_end':end,'body_sha256':hashlib.sha256(body.encode()).hexdigest(),'calls_within_selected':calls,
            'Array_replicate_18':body.count('Array.replicate 18'),'addLimbs64_occurrences':body.count('addLimbs64'),
            'limbValA_occurrences':body.count('limbValA'),'sqrtLower_occurrences':body.count('sqrtLower'),
            'UInt64_alias_in_body':'┞' in body,'explicit_Nat_divisions':body.count('/D'),'explicit_Nat_remainders':body.count('%D')}
    attributes=[{'line':i+1,'text':line.strip()} for i,line in enumerate(lines) if re.search(r'csimp|implemented_by|extern|unsafe|^attribute',line)]
    model_counts={}
    for key,filename,groupkey,normkey in [('mixer_firstnorm','mixer-firstnorm-results.json','groups','rows'),('nmlp','nmlp-coverage-results.json','results','norms')]:
        p=HERE/filename
        if p.is_file():
            groups=json.loads(p.read_bytes())[groupkey];rows=[r for g in groups for r in g[normkey]]
            model_counts[key]={'rows':len(rows),'Q_value_bits_gt63':sum(r['Q_bits']>63 for r in rows),'S_value_bits_gt63':sum(r['S_bits']>63 for r in rows),'T_value_bits_gt63':sum(r['T_bits']>63 for r in rows),
                'interpretation':'Mathematical values only. They would require non-small Nat representation on the standard64-bit path; not observed GMP call counts.'}
    report={'source':str(SOURCE),'source_sha256':EXPECTED,'source_bytes':len(raw),'scope':'Verified source text/call names only. C/ASM and cost UNKNOWN; no candidate implementation.',
        'final_fields':{'core':'kernels0.core -> YaN/YaM -> Yn/Yw ->18-limb Acc','dense':'YaV/Ya3 -> QPa/YaU/Ya2 -> bounded word loops','conv':'Ybp/dwQ -> cdQ -> native word routes or YaC fallback','norm':'Ybb/Ybc -> integer limb moments and downstream specialized rounding'},
        'nodes':nodes,'override_attributes_found':attributes,'model_big_nat_representation':model_counts,
        'ledger':[
          {'status':'SOURCE_VERIFIED','work':'Y6/Y7 contain18-slot Nat arrays and addLimbs64. YaE/Y8 convert them using limbValA. These are final selected stable norm paths.'},
          {'status':'SOURCE_VERIFIED','work':'Norm final rounding is already specialized: Ya7->YN and Yba->Ya9/Ya8/YN. A claim that norm has no word optimization would be false.'},
          {'status':'PAPER_ONLY_NOT_IMPLEMENTED','work':'Guarded scalar S128/Q192 would remove moment ArrayNat initialization/update, separate sum/square traversal and limbValA; word nQ-S² avoids converting back for that algebra.'},
          {'status':'LIMITATION','work':'A moments-only port that converts word Q/S back to Nat before unchanged YaD still incurs conversion/root/GMP work. It cannot claim an end-to-end GMP-free norm.'},
          {'status':'PAPER_ONLY_NOT_IMPLEMENTED','work':'For the public-source first Mixer norm, epsilon-aligned numerator is <2^139, denominator n² fits12bits, so192-bit squared-cell root verification can avoid YaD log/div/sqrt on accepted guesses. Output numerator <2^95 enables128-bit final ratio certificate.'},
          {'status':'UNKNOWN','work':'Actual native allocation/RC/spill/GMP counts, current champion5 implementation and whole time. Coverage theorems do not establish implementation or speed.'}
        ]}
    (HERE/'former2-norm-callgraph.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({'source_sha256':EXPECTED,'norm_chain':{n:nodes[n] for n in ('Ybb','Ybc','YaE','Y8','Y6','Y7','YaD','Ya7','Yba')},'overrides':attributes,'value_representations':model_counts},indent=2))

if __name__=='__main__':main()
