#!/usr/bin/env python3
"""Exact finite interpreter of the preferred mixed-zero source domain.
No Lean/native execution. Oldpublicseed42 and targeted semantic edge cases only.
"""
from pathlib import Path
import hashlib,importlib.util,json,re,time,types
P=Path(__file__).resolve().parent
def load(name,file):
 s=importlib.util.spec_from_file_location(name,file);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
M=load('mixed_spatial_builder',P/'build_spatial_mixed_zero.py')
R=M.parent()
V=load('mixed_spatial_model',P/'verify_spatial_runtime.py');C=V.C;F=V.F
_MODEL_RUNTIME=None
def contexts(inp,ci,n,co,w,b):
    hit,g=C.guard11(inp,w,b,ci*9)
    if ci>8 or ci==0 or n==0 or n%2 or co<4:return None,'shape'
    if any(wl==511 for wl,_ in g['weight_exp_bounds']):return None,'all_zero_row'
    if not hit:return None,'original_narrow'
    xm=g['xm'];rows=[]
    for (wl,_),bias in zip(g['weight_exp_bounds'],b):
      wm=C.yk(wl);e=xm+wm;sh=126+F.fields(bias)[2]-e
      if not(2<=e<=1000 and (F.fields(bias)[1]==0 or sh<=76)):return None,'rebase_bias'
      rows.append((wm,e-2))
    return (xm,rows),'admitted'
def normalized_runtime_for_expression_parser():
    global _MODEL_RUNTIME
    if _MODEL_RUNTIME is not None:return _MODEL_RUNTIME
    text=M.runtime().decode()
    for old,new in R.RENAMES.items():text=re.sub(r'\b'+new+r'\b',old,text)
    _MODEL_RUNTIME=text.replace(' (','(').replace(') ',')').replace('=> ','=>').replace('R8Ctx','R8T')
    return _MODEL_RUNTIME
def main():
    t=time.time();rt=M.runtime()
    assert M.REM not in rt and M.AFTER in rt
    V.B=types.SimpleNamespace(runtime=normalized_runtime_for_expression_parser)
    V.contexts=contexts
    original=C.conv;records=[];fallback={}
    def compare(inp,ci,n,co,w,b):
      expected,stats=original(inp,ci,n,co,w,b)
      actual,why,counts=V.actual_runtime_model(inp,ci,n,co,w,b)
      if actual is None:fallback[why]=fallback.get(why,0)+1
      else:
        assert actual==expected
        records.append({'shape':[ci,n,n,co],'input_checksum':C.hasharr(inp),'expected_checksum':C.hasharr(expected),'model_checksum':C.hasharr(actual),'counts':counts,'zero_weight_count':sum(F.fields(x)[1]==0 for x in w)})
      return expected,stats
    C.conv=compare
    for profile in ['legacy','scale','boundary']:
      for kind in ['normal','wide','sparse']:C.run(42,kind,profile,1)
    # Every weight row has one nonzero coefficient. A local zero dot can still be -0.
    inp=[0]*16;inp[0]=0x80000000;inp[15]=0x3f800000
    row=[0x80000000]*9;row[4]=0x3f800000
    result,why,counts=V.actual_runtime_model(inp,1,4,4,row*4,[0x80000000]*4)
    assert why=='admitted'
    assert all(result[o*16]==0x80000000 and result[o*16+15]==0x3f800000 for o in range(4))
    edge={'state':'MIXED_ZERO_ROW_RAW_SIGN_REPLAY_PASS','counts':counts,'first_word_each_channel':[f'{result[o*16]:08x}' for o in range(4)],'last_word_each_channel':[f'{result[o*16+15]:08x}' for o in range(4)]}
    reject_w=row*4;reject_w[9:18]=[0]*9
    ctx,reason=contexts(inp,1,4,4,reject_w,[0]*4)
    assert ctx is None and reason=='all_zero_row'
    bad_w=(row*4).copy();bad_w[0]=0x7f800000
    ctx,nonfinite_reason=contexts(inp,1,4,4,bad_w,[0]*4)
    assert ctx is None and nonfinite_reason=='original_narrow'
    raw=(P.parents[1]/'competition-state/source-private/official-11.lean').read_bytes()
    result=M.transform(raw,11,'spatial11-mixed-native')
    r={'state':'PREFERRED_MIXED_ZERO_SOURCE_MODEL_MATCHES','source_sha256':hashlib.sha256(result).hexdigest(),'bytes':len(result),'runtime_sha256':hashlib.sha256(rt).hexdigest(),'recipe_sha256':hashlib.sha256((P/'build_spatial_mixed_zero.py').read_bytes()).hexdigest(),'old_public_seed':42,'profiles':['legacy','scale','boundary'],'admitted_calls':len(records),'matched_outputs':sum(x['counts']['outputs'] for x in records),'admitted_calls_containing_zero_weights':sum(x['zero_weight_count']>0 for x in records),'fallback_calls':fallback,'records':records,'mixed_signed_zero_edge':edge,'all_zero_row_rejected':True,'nonfinite_used_weight_rejected':True,'big_nat_partial_stores_observed':sum(x['counts']['big_nat_partial_stores'] for x in records),'resource_elapsed_seconds':time.time()-t,'scope':'Actual emitted transform/inverse expressions normalized ONLY inside the Python expression interpreter; actual Lean retains legal application spaces. Guard mirrorsBW.min!=511. Pre-round integer equality checked before shared final rounder.','not_claimed':['Lean parser/elaboration acceptance','all12 proof','native timing','champion result'],'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}
    (P/'spatial-mixed-model-receipt.json').write_bytes((json.dumps(r,indent=2)+'\n').encode())
    print(json.dumps({k:r[k] for k in ['state','source_sha256','admitted_calls','matched_outputs','admitted_calls_containing_zero_weights','fallback_calls','mixed_signed_zero_edge','all_zero_row_rejected','nonfinite_used_weight_rejected','big_nat_partial_stores_observed','resource_elapsed_seconds']},indent=2))
if __name__=='__main__':main()
