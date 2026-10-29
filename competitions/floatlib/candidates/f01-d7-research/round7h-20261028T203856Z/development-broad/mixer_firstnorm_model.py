"""Finite model of Mixer's first, uncompressed norm input; no target kernel."""
from pathlib import Path
import hashlib
import importlib.util
import json

HERE=Path(__file__).resolve().parent
s=importlib.util.spec_from_file_location('r24_nmlp_model',HERE/'nmlp_coverage_model.py');m=importlib.util.module_from_spec(s);s.loader.exec_module(m)

def dimensions(seed,profile):
    r=m.lcg(8,seed^0x5bd1e995)
    if profile=='boundary':return 9+2*(r[6]%5),15+2*(r[7]%10)
    if profile=='scale':return 20+2*(r[6]%7),12+r[7]%9
    return 8+r[6]%9,16+4*(r[7]%9)

def main():
    seed=24292317;groups=[]
    for profile in ('typical','scale','boundary'):
        T,C=dimensions(seed,profile)
        for kind in ('normal','wide','sparse'):
            inputs=m.gen(kind,T*C,seed+999);g=m.gains(seed+1,C);b=m.biases(seed,2,C);rows=[];out=[]
            for r in range(T):
                outputs,stats=m.norm(inputs[r*C:(r+1)*C],g,b,True);out.extend(outputs);rows.append(dict(row=r,**stats))
            checksum=2166136261
            for w in out:checksum=((checksum^w)*16777619)&0xffffffff
            groups.append({'profile':profile,'kind':kind,'tokens':T,'channels':C,'rows':rows,
                'layer128_rows':sum(r['layer128'] for r in rows),'layer192_rows':sum(r['layer192'] for r in rows),
                'output_words':len(out),'outputs_certified':sum(r['outputs_certified'] for r in rows),'python_firstnorm_checksum':f'{checksum:08x}'})
    report={'scope':'Own-seed first layer of current public Mixer profile topology only. No later layers, native checksum match, timing or probability. Initial inputs go directly to layernorm, unlike nMLP.',
        'source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'nmlp_helper_sha256':hashlib.sha256((HERE/'nmlp_coverage_model.py').read_bytes()).hexdigest(),
        'certificate_helper_sha256':hashlib.sha256((HERE/'certificates.py').read_bytes()).hexdigest(),'seed':seed,'groups':groups}
    (HERE/'mixer-firstnorm-results.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({'summary':[{'profile':g['profile'],'kind':g['kind'],'T':g['tokens'],'C':g['channels'],'layer128_rows':g['layer128_rows'],'layer192_rows':g['layer192_rows'],'outputs_certified':g['outputs_certified'],'output_words':g['output_words']} for g in groups]},indent=2))

if __name__=='__main__':main()
