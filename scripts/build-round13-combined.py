"""One controlled composition of verified representation and measured recovery."""
from pathlib import Path
import argparse,hashlib,importlib.util,json

ROOT=Path(__file__).resolve().parents[1];BASE=ROOT/'candidates/r13-514-abs15';NAME='r13-514-abs15-rescue'

def sha(b):return hashlib.sha256(b).hexdigest()

def generate():
    origin=json.loads((BASE/'manifest.json').read_bytes());raw={f:(BASE/f).read_bytes()for f in('parse.rs','Parse.lean')};assert {f:sha(v)for f,v in raw.items()}==origin['hashes']
    loader=importlib.util.spec_from_file_location('r13_recovery_builder',ROOT/'scripts/build-round13-rescue.py');m=importlib.util.module_from_spec(loader);loader.loader.exec_module(m)
    helper=m.HELPER.replace('CONDITION','g.0>=3 && g.0>=minl && pc_gain(g.0,g.1)>0').replace('prev: &[u32;32768]','prev: &[u16;32768]')
    assert helper.count('prev[c%32768]as usize')==2;helper=helper.replace('prev[c%32768]as usize','r13_prev_unwrap(c,prev[c%32768])')
    original=raw['parse.rs'].decode();a=original.index('pub fn pc_run1c<const H: usize>');b=original.index('/// Structured binaries (class 3)',a);old=original[a:b];body=old
    before='            let f = pc_probe_m(input, c, cw, p, km);';after='            let f = r13_pc_find_rescue(input,&prev,c,cw,p,km,dp,minl);';assert body.count(before)==1;body=body.replace(before,after,1)
    before='''                let cl = r13_prev_unwrap(c, prev[c % 32768]);
                let g = pc_f_deepen(input, &prev, c, cl, p, f.0, f.1, dp, minl);
                let mut l = g.0;
                let mut d = g.1;'''
    after='''                let mut l = f.0;
                let mut d = f.1;''';assert body.count(before)==1;body=body.replace(before,after,1)
    rust=original[:a]+body+original[b:];marker='/// `pc_run1` with chain links and `pc_f_deepen` at every match of at least `minl` bytes.';assert rust.count(marker)==1;rust=rust.replace(marker,helper+marker,1);assert rust.replace(helper,'',1).replace(body,old,1)==original
    files={'parse.rs':rust.encode(),'Parse.lean':raw['Parse.lean']};manifest={**origin,'candidate':NAME,'parent':'r13-514-abs15','comparison_baseline':'r13-514-abs15','hashes':{f:sha(v)for f,v in files.items()},'parent_variant_hashes':origin['hashes'],
        'mechanism':'Gain-filtered one-predecessor recovery uses the proven modularU16 hint representation. Original primary-success deepening preserved. Both components previously isolated; actual composition measured anew.',
        'difference_from_previous':'Current co-measurement suggests a small representation effect but standard signal is unconfirmed; standalone recovery improves size but costs0.23% time. Joint cache/recovery interaction UNKNOWN; no gains added as a claim.',
        'native_relation':'decode_only','proof_status':'VERIFIED_PARENT_PAIR_NOT_COMPOSITION; new find helper unadapted; exact original gate required',
        'performance_status':'UNKNOWN; exact native encoder first, then standard paired time only if worthwhile','formal_submission_sent':False,
        'stop_condition':'Any decode failure stops. No viable conditional boundary after actual total-time/size closes this one composition; no iterative combination search in this window.'}
    files['manifest.json']=(json.dumps(manifest,indent=2)+'\n').encode();return files

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args();files=generate();p=ROOT/'candidates'/NAME
    if args.check:assert all((p/f).read_bytes()==v for f,v in files.items())
    else:
        assert not p.exists();p.mkdir()
        for f,v in files.items():(p/f).write_bytes(v)
    print(json.dumps({'candidate':NAME,'hashes':{f:sha(v)for f,v in files.items()},'status':'COMPOSITION_DRAFT_NOT_RUN'}))

if __name__=='__main__':main()
