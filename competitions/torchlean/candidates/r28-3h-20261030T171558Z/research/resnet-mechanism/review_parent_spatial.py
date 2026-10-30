#!/usr/bin/env python3
"""Independent parent-witness replay using this role's separate transform/model code."""
import hashlib,importlib.util,json
from pathlib import Path
P=Path(__file__).resolve().parent
def load(name,file):
 s=importlib.util.spec_from_file_location(name,file);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
def main():
 parent=P.parent/'winograd-bounds/block-bounds-result.json';receipt=json.loads(parent.read_text());witness=receipt['block15_witness']
 W=load('spatial_own',P/'verify_spatial_winograd.py');C=load('census_own',P/'cnn_zero_census.py');F=C.F
 hi=int(witness['raw_input_hi'],16);lo=int(witness['raw_input_low'],16);weight=int(witness['raw_all_weights'],16)
 inp=([hi]*24+[lo])*15;weights=[weight]*135;bias=[0]
 ok,guard=C.guard11(inp,weights,bias,135);assert ok
 sx=F.fields(hi)[2]-F.fields(lo)[2];sw=0;xm=F.fields(lo)[2];wm=F.fields(weight)[2]
 X=F.fields(hi)[1]<<sx;U=F.fields(weight)[1]
 v=W.transform([[X]*4 for _ in range(4)],W.BT)
 u=W.transform([[U]*3 for _ in range(3)],W.G)
 exact=[[15*v[i][j]*u[i][j] for j in range(4)] for i in range(4)]
 wrong=[[W.word_block([v[i][j]]*15,[u[i][j]]*15) for j in range(4)] for i in range(4)]
 ev=W.transform(exact,W.AT);wv=W.transform(wrong,W.AT)
 assert all(a%4==0 for row in ev+wv for a in row)
 body=ev[0][0]//4;bad=wv[0][0]//4
 expected=F.round_ratio(body,1,xm+wm-298);incorrect=F.round_ratio(bad,1,xm+wm-298)
 assert f'{expected:08x}'==witness['exact_output_word']
 assert f'{incorrect:08x}'==witness['naive_unblocked_output_word']
 assert str(body)==witness['exact_aligned_body'] and str(bad)==witness['wrong_naive_aligned_body']
 M=(1<<24)-1;H=9*M*M*(1<<8);rows=[]
 for f in range(7):
  for g in range(32-f):
   vmax=4*M*(1<<g);umax=9*M*(1<<f)
   bound=((vmax+(1<<25)-1)//(1<<25))*umax
   assert bound<=H
   rows.append(bound)
 assert max(rows)==H and 14*H<1<<63 and 15*H>1<<63
 # Parent center2^58 gives a positive immediate Nat and exact high split offset2^33.
 for x in [-(1<<57)+1,-1,0,1,(1<<57)-1]:
   p=x+(1<<58)
   assert 0<p<1<<59 and (p>>25)-(1<<33)==x//(1<<25) and p% (1<<25)==x% (1<<25)
 out={'state':'ACCEPT_PARENT_1746_AND_1752_WITH_SCOPE_BOUNDARIES','parent_receipt_sha256':hashlib.sha256(parent.read_bytes()).hexdigest(),'independent_model_inputs':'raw words from parent receipt, own matrix transform and own prior exact binary32 rounding model','actual_source11_guard':'NOT_EXECUTED; separately coded finite guard model accepts all rows','modeled_guard':guard,'source_fields':{'sx':sx,'sw':sw,'xm':xm,'wm':wm},'all_four_exact_outputs':[f'{F.round_ratio(a//4,1,xm+wm-298):08x}' for row in ev for a in row],'all_four_naive_outputs':[f'{F.round_ratio(a//4,1,xm+wm-298):08x}' for row in wv for a in row],'max_high':str(H),'block14_bound':str(14*H),'block15_bound':str(15*H),'center_2pow58_decode':'finite boundary checks PASS; algebra is exact because2^58 divisible by2^25','decision':'Keep block8 and original narrow/shape fallback for any future spatial prototype;14 is safe but does not improve current cin<=8 source profiles. No new CI or actual candidate changes.','script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}
 (P/'parent-spatial-review.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8');print(json.dumps(out,indent=2))
if __name__=='__main__':main()
