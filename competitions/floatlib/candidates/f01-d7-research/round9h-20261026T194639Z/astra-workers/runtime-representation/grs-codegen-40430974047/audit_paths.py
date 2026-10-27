"""Read original C/ASM and enumerate explicit complete representative paths. No timing."""
from pathlib import Path
import datetime,hashlib,importlib.util,json,re
HERE=Path(__file__).resolve().parent
W=HERE.parent
ROOT=next(p for p in HERE.parents if (p/'DEVELOPMENT.md').exists())
ROUND=W.parent.parent
SUITE=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40430974047/download-08d56bf17d524b209ff9058819a9b0c8/diagnostics/f01-d7-public-suite/public-suite'
NEW=SUITE/'diagnostics/f01-r19-dev-grs-add-runtime2'
B2=SUITE/'diagnostics/f01-r19-dev-route-profile2'
H=lambda b:hashlib.sha256(b).hexdigest()
def imp(n,p):
 s=importlib.util.spec_from_file_location(n,p);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
cc=imp('selected',W/'compare_classifier_codegen.py')
a=imp('pathhelpers',W/'direct-bias-7489-cost/audit_codegen.py')

def bind(p,expected=None):
 b=p.read_bytes();h=H(b)
 if expected:assert h==expected,(p,h,expected)
 return {'path':str(p.relative_to(ROOT)).replace('\\','/'),'bytes':len(b),'sha256':h}

def main():
 bindings=[];indexes={}
 for label,d,expected in [('GRS',NEW,'77377f8b373988545c557aa6f5cd5edfd82ec772bb643a404a15e26e02d627af'),('B2',B2,'622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58')]:
  candidate='f01-r19-dev-grs-add-runtime2' if label=='GRS' else 'f01-r19-dev-route-profile2'
  bindings.append(bind(SUITE/'inputs'/candidate/'Kernel.lean',expected))
  for file in ['candidate-c-index.json','native-assembly-index.json']:
   bindings.append(bind(d/file));idx=json.loads((d/file).read_text())
   for row in idx:
    if 'kernel_sha256' in row:assert row['kernel_sha256']==expected
    bindings.append(bind(d/row['file'],row['sha256']))
   if file.startswith('native'):indexes[label]=idx
 for file in ['diagnostic-only-verdict.json','helper-axioms.raw','helper-audit.json','replay.log']:
  bindings.append(bind(NEW/file))
 verdict=json.loads((NEW/'diagnostic-only-verdict.json').read_text())
 assert verdict['passed'] and verdict['diagnostic_only'] and verdict['ratio'] is None
 replay=(NEW/'replay.log').read_text();assert 'Submission replays cleanly' in replay and 'VerifyFull replays cleanly' in replay
 roots=re.findall(r"^'([^']+)' depends on axioms: \[([^]]+)\]",(NEW/'helper-axioms.raw').read_text(),re.M)
 assert len(roots)==7 and all(set(v.split(', '))<=set(['propext','Classical.choice','Quot.sound']) for _,v in roots)
 nsrc,_=cc.load(NEW,'77377f8b373988545c557aa6f5cd5edfd82ec772bb643a404a15e26e02d627af');bsrc,_=cc.load(B2,'622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58')
 assert nsrc['MainFull']==bsrc['MainFull']
 nsel,bsel=cc.select(nsrc),cc.select(bsrc);assert bsel['add']['unboxed']=='lp_competition_main___lam__0'
 entry=cc.extract(nsrc['Submission'],'lp_competition_Submission_R19GRS32Add_diagnosticEntry')
 cparts={'diagnosticEntry.c':entry+'\n','B2-selected-ADD.c':bsel['add']['body']+'\n'}
 assert 'v_mid_15056_ = lean_float32_to_bits(v___x_15055_);' in entry
 assert 'v___x_15055_ = lean_uint32_to_float32(v___y_15053_);' in entry
 grsbody=a.asm_body(NEW/'native-loop-7.asm.txt','lp_competition_Submission_R19GRS32Add_diagnosticEntry')
 b2body=a.asm_body(B2/'native-loop-10.asm.txt','lp_competition_main___lam__0')
 grs=a.instructions(grsbody);b2=a.instructions(b2body)
 cparts.update({'diagnosticEntry.asm.txt':grsbody,'B2-selected-ADD.asm.txt':b2body})
 common=[(0,0x2a),(0x5c,0x7c),(0x119,0x153)]
 short=[(0x155,0x184)];sign=[(0x186,0x198)];same=[(0x19e,0x1a0)];opp=[(0x35c,0x35e)]
 nonzero=[(0x364,0x38d)];hit=[(0x3b4,0x3cf),(0x47d,0x48b)]
 definitions={
  'GRS-short-same-hit':(grs,common+short+sign+same+nonzero+hit,0,('0x3f800000','0x3f800000')),
  'GRS-short-opposite-hit':(grs,common+short+sign+opp+nonzero+hit,0,('0x3fc00000','0xbf800000')),
  'GRS-long-same-hit':(grs,common+sign+same+nonzero+hit,0,('0x5f800000','0x3f800000')),
  'GRS-long-opposite-hit':(grs,common+sign+opp+nonzero+hit,0,('0x5f800000','0xbf800000')),
  'GRS-zero':(grs,common+short+sign+opp+[(0x47b,0x48b)],0,('0x3f800000','0xbf800000')),
  'GRS-early-x-miss-table-fallback':(grs,[(0,0x2a),(0x2c,0x4a),(0xb4,0xfa),(0x1a5,0x1da),(0x465,0x476)],1,('0x00000000','0x3f800000')),
  'GRS-early-y-miss-table-fallback':(grs,[(0,0x2a),(0x5c,0x7c),(0x82,0x98),(0x257,0x29d),(0x2b5,0x2e7),(0x465,0x476)],1,('0x3f800000','0x00000000')),
  'GRS-postE-miss-table-fallback':(grs,common+short+sign+same+nonzero+[(0x38f,0x3a5),(0x3d4,0x41b),(0x432,0x476)],1,('0x7f7fffff','0x7f7fffff')),
  'GRS-postE-miss-bitcodec-fallback':(grs,common+short+sign+opp+nonzero+[(0x38f,0x3a5),(0x3a7,0x3b2),(0x3fc,0x430),(0x45c,0x476)],1,('0x00800001','0x80800000')),
  'B2-table-nonNaN':(b2,[(0,0x29),(0x37,0x7d),(0x94,0xd4)],1,('0x3f800000','0x3f800000')),
  'B2-bitcodecs-nonNaN':(b2,[(0,0x35),(0x60,0x92),(0xc0,0xd4)],1,('0x00800001','0x80800000'))}
 paths={}
 for name,(rows,ranges,tail,witness) in definitions.items():
  selected=a.path_rows(rows,ranges);shape=a.shape(selected)
  shape.update(ranges_inclusive=[[hex(x),hex(y)] for x,y in ranges],external_tail_codec_count=tail,
    native_codec_transfers=len(shape['calls'])+tail,witness_words=witness,witness_scope='Source/manual control-path classification, not native execution')
  paths[name]=shape;cparts[name+'.asm.txt']='\n'.join(r['line'] for r in selected)+'\n'
  if name.endswith('-hit'):
   assert shape['opcodes'].get('cvtsi2ss')==1 and len(shape['calls'])==1
   assert not any(op in shape['opcodes'] for op in ['addss','mulss'])
   assert len(shape['stack_data'])==2
  if name=='GRS-zero':assert not shape['calls'] and not shape['floating_point'] and len(shape['stack_data'])==1
 assert paths['GRS-short-same-hit']['pushes']==['rbp','r15','r14','r13','r12','rbx']
 assert len(paths['B2-table-nonNaN']['pushes'])==3 and not paths['B2-table-nonNaN']['stack_data']
 history=json.loads((W/'grs-add-cost-frontier/history-and-cost.json').read_text())
 for row in history['R16']['C_sources']:bindings.append(bind(Path(row['path']),row['sha256']))
 r16d=Path(history['R16']['C_sources'][1]['path']).parent
 r16,_=cc.load(r16d,'f7f4702f9191061bb70a274610c9b735967ce4460ca2ef6ae121b9264fad18dd');r16sel=cc.select(r16)['add']
 assert r16sel['unboxed']=='lp_competition_main___lam__2'
 assert H((r16sel['body']+'\n').encode())==history['R16']['selected_body_sha256']
 artifacts=[]
 for name,text in cparts.items():
  p=HERE/name;p.write_text(text,encoding='utf-8',newline='\n');artifacts.append(bind(p))
 result={'utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'status':'VERIFIED_DIAGNOSTIC_COMPLETE_CODE_PATHS_NO_TIMING','run':40430974047,
  'source_commit':'f421185689a8af2d3751e873ef85a2514ba52ade','kernel_sha256':'77377f8b373988545c557aa6f5cd5edfd82ec772bb643a404a15e26e02d627af',
  'statement_and_two_replays':'PASS','seven_roots':dict(roots),'new_public_ADD_equivalence':'MISSING','new_runtime_timing':'UNKNOWN',
  'public_MainFull_byte_identical_to_same_run_B2':True,'selected_ADD':{k:v for k,v in bsel['add'].items() if k!='body'},
  'paths':paths,'bindings':bindings,'artifacts':artifacts,
  'external_transfer_caveat':'ASM dump omits relocation records. GRScall0x373 is lean_float32_to_bits from correspondingC; B2jmp0xd4 and GRSjmp0x476 are externaltailcodec transfers, NOT internal branches into the displayed next address. Do not follow them to NaN/zero blocks.',
  'raw_ELF_rehashed':False,'object_hashes_from_index':{k:sorted(set(x['object_sha256'] for x in rows if 'object_sha256' in x)) for k,rows in indexes.items()},
  'R16_boundary':{'source_sha256':history['R16']['input_sha256'],'selected':{k:v for k,v in r16sel.items() if k!='body'},'accepted_shape':'OneU32cast+toBits already present, no table/FPaddmul; optimized scalarASM absent','negative_ADD_vs_B2':1.87392268417},
  'decision':'Do not start expensive publicADD proof in this window solely from this codegen. Retain frozen compiled probe; cost advantage unresolved. Any next discriminator must compare complete diagnosticEntry and B2 including all guards, misses and identical preparation, not leaf or instruction count.',
  'toolchain':'Lean4.34.0/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b, fixedclang-O3, unchanged official4b7',
  'CI_dispatched':False,'source_changed':False}
 (HERE/'audit.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8',newline='\n')
 print(json.dumps({'paths':{n:{'pushes':len(s['pushes']),'stack_data_ops':len(s['stack_data']),'calls':len(s['calls']),'tail_codec':s['external_tail_codec_count'],'cast':s['opcodes'].get('cvtsi2ss',0),'varshifts':len(s['variable_shifts'])} for n,s in paths.items()},'audit_sha256':H((HERE/'audit.json').read_bytes())},indent=2))

if __name__=='__main__':main()
