"""Freeze the unchanged A2 boundary rule against the newly measured641parent."""
from pathlib import Path
import ast
import hashlib
import json

ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'scripts/r26-a-boundary.py'
BASE_SHA='5e29a066e78d7e223d321d18baf60baa014c602dfc1105c25f6a1f47fadb1310'
FIXTURE=ROOT/'evidence/round26/38176193246/quality-a3-native/diagnostics/r13-encoder/encoder.json'
DEST=ROOT/'scripts/r26-a-boundary641.py'
OUT=ROOT/'evidence/round26/route-a'


def sha(raw):return hashlib.sha256(raw).hexdigest()
def dump(p,v):p.write_bytes((json.dumps(v,indent=2)+'\n').encode())
def once(s,a,b):assert s.count(a)==1,(a,s.count(a));return s.replace(a,b)


INSTRUMENT = r'''
def instrument(raw):
    data,bodies=HELP.instrument(raw,SRC)
    text=data.decode()
    for name in ['pc_run1','pc_run1c']:
        start=text.index('pub fn '+name+'<')
        opening=text.index('{',start)
        text=text[:opening+1]+'r26_callpc();'+text[opening+1:]
    extra='\nstatic R26_PC_CALLS: std::sync::atomic::AtomicU64=std::sync::atomic::AtomicU64::new(0);\nfn r26_callpc(){R26_PC_CALLS.fetch_add(1,std::sync::atomic::Ordering::Relaxed);}\npub fn r26_pc_take()->u64{R26_PC_CALLS.swap(0,std::sync::atomic::Ordering::Relaxed)}\n'
    result=(text+extra).encode()
    assert (text.replace('r26_callpc();','')).encode()==data
    return result,bodies

'''


def main():
    raw=BASE.read_bytes();assert sha(raw)==BASE_SHA
    fixture=json.loads(FIXTURE.read_bytes());assert fixture['status']=='VERIFIED_FINITE_NATIVE_ORIGINAL_ENCODER_BYTES'
    source={'path':'references/round26-public-641','stem':'p135','row_count':20,
            'hashes':fixture['source_hashes']['public641'],'fixture':FIXTURE.relative_to(ROOT).as_posix(),
            'fixture_sha256':sha(FIXTURE.read_bytes()),'fixture_kind':'native'}
    for f,h in source['hashes'].items():assert sha((ROOT/source['path']/f).read_bytes())==h
    text=raw.decode()
    text=once(text,"SRC = HELP.SOURCES['combo']",'SRC = '+repr(source))
    text=once(text,'PC_ROWS = [0,1,3,5,6,7,8,9]','PC_ROWS = [0,5,7,10,12,14,16,17,18,19]')
    assert text.count("HELP.expected_rows('combo',SRC)")==2
    text=text.replace("HELP.expected_rows('combo',SRC)","HELP.expected_rows('public641',SRC)")
    text=once(text,'observed,bodies=HELP.instrument(raw,SRC)','observed,bodies=instrument(raw)')
    text=once(text,'observer_raw,_=HELP.instrument(original.read_bytes(),SRC)','observer_raw,_=instrument(original.read_bytes())')
    text=once(text,"assert bodies['p125_row'+str(row)].startswith('pc_run1')","assert 'pc_run1' in bodies['p135_row'+str(row)]")
    text=once(text,'def preflight(spec=None):',INSTRUMENT+'def preflight(spec=None):')
    text=once(text,"spec.get('r26_a_boundary')","spec.get('r26_a_boundary641')")
    text=once(text,'  let active=[0usize,1,3,5,6,7,8,9].contains(&row);','  let pc_calls=observer::r26_pc_take();assert!(pc_calls<=1);let active=pc_calls>0;')
    text=once(text,'println!("R26_BOUNDARY_ROW {} {} {} {} {} {}",index,name,label,ts.len(),bytes.len(),row);','println!("R26_BOUNDARY_ROW {} {} {} {} {} {} {}",index,name,label,ts.len(),bytes.len(),row,active as u8);')
    text=once(text,'_,index,file,label,nt,nb,route=line.split();','_,index,file,label,nt,nb,route,active=line.split();')
    text=once(text,"'active_pc':int(route)in PC_ROWS}","'active_pc':active=='1'}\n                assert not row['active_pc'] or row['route_row'] in PC_ROWS")
    text=text.replace('r26-a-boundary-build','r26-a-boundary641-build').replace("/'r26-a-boundary'","/'r26-a-boundary641'")
    # The output path includes round4-receipts as one string.
    text=text.replace('round4-receipts/r26-a-boundary','round4-receipts/r26-a-boundary641')
    text=text.replace('boundary-preflight.json','boundary641-preflight.json').replace('Frozen exact combo tokens','Frozen exact public641 tokens')
    ast.parse(text)
    assert not DEST.exists(),'Frozen diagnostic scripts are immutable'
    DEST.write_bytes(text.encode())
    request={'status':'VERIFIED_STATIC_TRANSFER_GENERATION_NOT_NATIVE','hook_flag':'r26_a_boundary641',
             'hook_command':'python3 scripts/r26-a-boundary641.py','native_encoder':False,'gate_candidates':[],'extract_candidates':[],
             'expected_artifact':'diagnostics/r26-a-boundary641/receipt.json','same_boundary_rule_as':'scripts/r26-a-boundary.py',
             'base_script_sha256':BASE_SHA,'actual_engine_gate':'Observed calls ofpc_run1/pc_run1c; composite row16dx1branch is excluded.',
             'dependencies':{p:sha((ROOT/p).read_bytes())for p in [DEST.relative_to(ROOT).as_posix(),'scripts/research-round25-len3-price.py',source['fixture'],source['path']+'/parse.rs']},
             'runtime_seconds':{'compile':240,'run':240}}
    dump(OUT/'boundary641-ci-request.json',request)
    print(json.dumps(request,indent=2))


if __name__=='__main__':main()
