from pathlib import Path
import json,importlib.util,sys,hashlib
from datetime import datetime,timezone
sys.dont_write_bytecode=True
H=Path(__file__).parent;P=H/'census/formula_snapshot.py';spec=importlib.util.spec_from_file_location('fixed_cell_exact_model',P);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);rows=[]
for E in [2,127,253]:
 mant=1<<23;den=1<<(E+148);num=(8*mant-3)<<(E+145)
 hl=den*(2*mant-1)<2*num;hu=2*num<den*(2*mant+1);target=E<<23;actual=m.round_ratio(num,1,-298)
 assert hl and hu and actual==target-1 and actual!=target
 rows.append(dict(E=E,mant=mant,num=str(num),den=str(den),strict_uniform_bounds_hold=True,target_word=hex(target),actual_word=hex(actual),excluded_by_nonpower_guard=True))
r=dict(at_utc=datetime.now(timezone.utc).isoformat(),status='EXACT_INTEGER_NEGATIVE_CONTROL_FOR_DROPPED_PREMISE',examples=rows,scope='Disproves extending newuniformfixed-scale lemma tozero fractionwithoutchangingcellgeometry. Doesnotdisproveoriginalfullchecker, whosepower midpoint isasymmetric andcorrectlyexcludes thesetargetcells.',source_sha256=hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),model_sha256=hashlib.sha256(P.read_bytes()).hexdigest(),native_or_Lean=False)
(H/'fixed-scale/power-premise-negative-control.json').write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8');print(json.dumps({'cases':len(rows),'all_expected_previous_words':True,'scope':r['scope']}))
# Normalize evidence field names in summary; raw results remain unchanged.
p=H/'NARROW-DOMAIN-CENSUS-AND-FIXED-SCALE.json';d=json.loads(p.read_bytes())
for row in d['narrow_guard_results']:
 raw=H/'census'/f"fp-census-narrow-{row['root']}.json";record=json.loads(raw.read_bytes());row['result_path']=raw.relative_to(Path.cwd()).as_posix();row['result_sha256']=row.pop('source_sha256');row['replay_source_sha256']=record['source_sha256']
d['negative_control']='fixed-scale/power-premise-negative-control.json';p.write_text(json.dumps(d,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
