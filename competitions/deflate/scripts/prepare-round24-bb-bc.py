"""Freeze actual-interface and timing checks for the latest controlled compositions."""
from pathlib import Path
import json,hashlib
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24'
def save(name,data):
    p=E/(name+'.json');assert not p.exists();p.write_bytes((json.dumps(data,indent=2)+'\n').encode())
def main():
    items=[('r24-609-span-items','38101740543','span-ax-native'),('r24-609-stack-packed','38102490596','compose-az-native'),('r24-609-fast-adaptive','38102490596','compose-az-native')];entries=[];audits=[]
    for name,run,batch in items:
        path=ROOT/'candidates'/name;m=json.loads((path/'manifest.json').read_bytes());p=E/run/batch/'diagnostics/r13-encoder/encoder.json';j=json.loads(p.read_bytes());assert j['source_hashes'][name]==m['hashes'];entries.append({'name':name,'path':path.relative_to(ROOT).as_posix(),'control':False,'hashes':m['hashes'],'anchor':'public609','comparison_baseline':'once'});audits.append({'candidate':name,'native':p.relative_to(ROOT).as_posix(),'sha256':hashlib.sha256(p.read_bytes()).hexdigest()})
    s=json.loads((E/'proof-au-extract.json').read_bytes());s['entries']=[e for e in s['entries']if e['control']]+entries;s['extract_candidates']=[e['name']for e in entries];s['screen_orders']=[[e['name']for e in s['entries']]];s['description']='BB actualinterfaces for native-equal spanitems, actualApackedfaststack, and restored69Bqualityfastadaptive. SeparatefromLean/fullgate; preparebeforefinalconfirmation reserve.'
    save('proof-bb-extract',s);save('preflight-bb',{'gap':'Three survivingnativechecked sources have noactualcombinedinterfaces forproofmigration.','change':'Originalextraction ofexactRust only, noacceptanceclaimfor inheritedLean.','minimum':'Threeoriginalintake/static/extract stages andretainedFuns/logs.','decision':'Useactualinterfacesforselectedfinalpairs; postponeunused proofeffort onregressions.','cost_cap_runner_minutes':55,'native_audits':audits,'evidence':'evidence/round24/<run>/proof-bb-extract/diagnostics/research5'})
    s=json.loads((E/'screen-aw.json').read_bytes());s['entries']=[e for e in s['entries']if e['control']and e['name']not in ['buffer-stack','adaptive-x']]
    base=json.loads((E/'compose-az-native.json').read_bytes());s['entries'] +=[e for e in base['entries']if e['name']=='fast-stack' or not e['control']]
    path=ROOT/'candidates/r24-609-stack-adaptive-proof1';m=json.loads((path/'manifest.json').read_bytes());s['entries'].append({'name':'buffer-adaptive','path':path.relative_to(ROOT).as_posix(),'control':True,'hashes':m['hashes'],'anchor':'public609'})
    ns=[e['name']for e in s['entries']];s['screen_orders']=[ns,ns[::-1]];s['description']='BC twoactualcompositions: addAQcostpacking tofaststack, orrestoreXquality withoutLinteraction. Actualfaststackparent, ATbufferadaptive,607supplement and609primary/shadow allretained. Originaltotal-time only.'
    save('screen-bc',s);save('preflight-bc',{'gap':'AZpacked retained28tokens/output; fastadaptive retainedX69Bqualityonall28files,8Bbetter thanAT. Actualtime andfrontierinteraction unknown.','change':'Twoactualcompositions,sameoriginal11reps2oppositeblocks, actualfaststackandATparents,607/609/609shadow.','minimum':f'{len(ns)}methods x2pairedblocks; retainperfileoriginaltotal times, identity andenvironment.','decision':'Latest-snapshot individual/jointunderallanchors. No componentgainaddition; freezebestusefulpairs andfullgate/newindependentconfirmation.','cost_cap_runner_minutes':65,'native_audits':audits[1:],'evidence':'evidence/round24/<run>/screen-bc/gate'})
    print('BB_BC_READY',len(ns))
if __name__=='__main__':main()
