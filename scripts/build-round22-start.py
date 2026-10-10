"""Bounded transfer onto the newly released previous top1, retaining exact attribution."""
from pathlib import Path
import json,importlib.util
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round22'
def main():
 sp=importlib.util.spec_from_file_location('w',ROOT/'scripts/build-round18-start.py');w=importlib.util.module_from_spec(sp);sp.loader.exec_module(w)
 p=ROOT/'references/round21-public-595';r,l=[(p/f).read_text()for f in ('parse.rs','Parse.lean')];variants=[]
 compact=r.replace('[u32; 32768]','[u16; 32768]').replace('[0u32; 32768]','[0u16; 32768]').replace('prev[i % 32768] = head[a];','prev[i % 32768] = head[a] as u16;').replace('prev[c2 % 32768] as usize','c2.wrapping_sub(c2.wrapping_sub(prev[c2 % 32768] as usize) & 32767)').replace('prev[c % 32768] as usize','c.wrapping_sub(c.wrapping_sub(prev[c % 32768] as usize) & 32767)')
 # This released parent has one auxiliary ring;539had two (PC and PIM).
 assert compact.count('[0u16; 32768]')==1
 proof=l.replace('Array Std.U32 32768#usize','Array Std.U16 32768#usize')
 variants.append(('r22-595-prev16',compact,proof,'Transfer actual16bit predecessor representation with bytechecked hint reconstruction onto newly public595; generictext routes remain original595headonly, so active auxiliary consumers differ from539.'))
 old='pc_run1::<65536>(input,out,6,0,1000000,4294967295)';assert r.count(old)==1
 variants.append(('r22-595-halfhead',r.replace(old,'pc_run1::<32768>(input,out,6,0,1000000,4294967295)'),l,'Halve only the enlargedprimary table of original595genericroute6. Preserve its skip/search/routing; isolate capacity tradeoff on this releasedparent, no truncatedhead arithmetic.'))
 old='let m = pc_common_from(s, c2, p, cap, 0);';assert compact.count(old)==1
 new='let m = if cap >= 8 {let cw=pc_be8(s,c2);let pw=pc_be8(s,p);pc_xlen(s,c2,p,cw ^ pw)} else {pc_common_from(s,c2,p,cap,0)};'
 variants.append(('r22-595-prev16-word8',compact.replace(old,new),proof,'Combine595compact auxiliary representation with exactbyte word8 prefix extension already nativevalidated on539; actualcombinedbytes/time still require newvalidation.'))
 entries=[]
 for name,rust,lean,mechanism in variants:
  existing=ROOT/'candidates'/name
  if existing.exists():
   assert (existing/'parse.rs').read_bytes()==rust.encode() and (existing/'Parse.lean').read_bytes()==lean.encode()
   en={'name':name,'path':'candidates/'+name,'control':False,'hashes':json.loads((existing/'manifest.json').read_bytes())['hashes']}
  else:en=w.write_candidate(name,p.name,rust,lean,mechanism,'Earlieroldparent tests do not establish newly released595route composition. Source became public after612dominated595; compare a few controlled representations/capacity, not repeated whole539 settings.',{'public_source':'references/round21-public-595/source-receipt.json','source_comparison':'evidence/round21/public-refresh-mid/595-vs514.diff','authorship':'Original595/514/590 authors retained; no claim of wholeparser invention.'})
  en.update(anchor='public595',comparison_baseline='public595',native_decode_reference='public595');entries.append(en)
 s=json.loads((ROOT/'evidence/round21/probe-a-native.json').read_bytes());s['entries']=[e for e in s['entries']if e['name']in('probe3','r3-432-fast3','public432','public514')];s['entries'].append(w.control('public595','references/round21-public-595','595'));sh={**s['entries'][-1],'name':'public595-shadow'};sh.pop('formal_id');s['entries'].append(sh);s['entries']+=entries;s['native_encoder_references']=['public595'];s['r22_expected_candidates']=3;s['r22_mode']='native';s['r22_role']='discovery';s.pop('r21_mode',None);s.pop('r21_role',None);s['snapshot_pages']='evidence/round22/official-start/pareto-pages.json';s['description']='R22 A newly public595parent originalencode/decode and3 bounded transfers;15mincap, retainallactualquality and proofdraft.';ns=[e['name']for e in s['entries']];s['screen_orders']=[ns,ns[::-1]];(E/'probe-b-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode())
 (E/'preflight-b.json').write_bytes((json.dumps({'gap':'New612dominatedoldtop595, now ordinarysourceAPI makes595available. Needrealimprovement fromexactfast releasedparent, current10%regionmust bereplayed.','new_condition':'Releasedexact595code, 2rowchanges andclassifierannotation versus514; differs broadly from539wrapper. First-time actualreuse onthisparent.','changes':[{'candidate':v[0],'mechanism':v[3]}for v in variants],'minimum':'Full28file originalencoder/decode against exact595and514; observedqualitythenjointspeedgeometry.','decision':'Credibletradeoff receivesoriginalpairedK plusfreshfullgate andindependentruns withinremainingwindow. No imaginedprivateguarantee; losingqualitydoesnotautomaticallydiscardfastcandidate.','cap_runner_minutes':15,'research_cutoff_utc':'2026-10-10T17:17:07+00:00','final_reserve_minutes':20},indent=2)+'\n').encode());print([e['name']for e in entries])
if __name__=='__main__':main()
