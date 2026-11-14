#!/usr/bin/env python3
"""Complete original word-model spatial convolution, including bias/sign/odd tiles.

Not a Lean candidate, proof, native benchmark or alternate official validator.
Reuses R27's exact binary32 rounder for both paths; independently checks the exact
pre-rounding integer against direct products. Only previously public seed42 inputs.
"""
from pathlib import Path
import hashlib,importlib.util,json,time
P=Path(__file__).resolve().parent
def load(name,path):
 s=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
C=load('own_census_spatial',P/'cnn_zero_census.py');F=C.F
W=load('own_word_spatial',P/'verify_spatial_winograd.py')
MASK=(1<<64)-1;MASK128=(1<<128)-1
def signed128(a):
 v=(a[0]<<64)|a[1]
 return v-(1<<128) if a[0]>>63 else v
def words(v):return ((v>>64)&MASK,v&MASK)
def add(a,b):
 lo=(a[1]+b[1])&MASK
 return ((a[0]+b[0]+int(lo<a[1]))&MASK,lo)
def sub(a,b):
 return ((a[0]-b[0]-int(a[1]<b[1]))&MASK,(a[1]-b[1])&MASK)
def div4(a):
 assert a[1]&3==0
 lo=(a[1]>>2)|((a[0]<<62)&MASK)
 hi=(a[0]>>2)|((-(a[0]>>63)<<62)&MASK)
 result=(hi,lo)
 assert signed128(result)*4==signed128(a)
 return result
def combine_split(a0,a1):
 l=(a1<<25)&MASK;lo=(l+a0)&MASK
 hi=((a1>>39)+((-(a1>>63)<<25)&MASK)-(a0>>63)+int(lo<l))&MASK
 result=(hi,lo)
 assert signed128(result)==W.s64(a0)+(1<<25)*W.s64(a1)
 return result
def transformed_dot(vs,us,counts):
 result=(0,0)
 for begin in range(0,len(vs),8):
  al=ah=0;exactlo=exacthi=0
  for v,u in zip(vs[begin:begin+8],us[begin:begin+8]):
   ev=v+(1<<58);eu=u+(1<<35)
   assert 0<ev<1<<59 and 0<eu<1<<36
   low=ev&((1<<25)-1);high=((ev>>25)-(1<<33))&MASK
   weight=(eu-(1<<35))&MASK
   al=(al+low*weight)&MASK;ah=(ah+high*weight)&MASK
   exactlo+=low*u;exacthi+=(v//(1<<25))*u
   assert W.s64(al)==exactlo and W.s64(ah)==exacthi
   counts['word_products']+=2
  result=add(result,combine_split(al,ah));counts['block_merges']+=1
 assert signed128(result)==sum(v*u for v,u in zip(vs,us))
 return result
def inverse(m):
 rows=[]
 for r in range(4):
  rows.append([add(add(m[r][0],m[r][1]),m[r][2]),sub(sub(m[r][1],m[r][2]),m[r][3])])
 return [[add(add(rows[0][c],rows[1][c]),rows[2][c]) for c in range(2)],
         [sub(sub(rows[1][c],rows[2][c]),rows[3][c]) for c in range(2)]]
def get(inp,cin,h,w,c,y,x):
 return inp[(c*h+y)*w+x] if 0<=c<cin and 0<=y<h and 0<=x<w and (c*h+y)*w+x<len(inp) else 0
def zero_sign(inp,weights,bias,cin,h,w,o,y,x):
 if bias[o]!=0x80000000:return False
 for c in range(cin):
  for dy in range(3):
   for dx in range(3):
    a=get(inp,cin,h,w,c,y+dy-1,x+dx-1);b=weights[o*(cin*9)+c*9+dy*3+dx]
    if F.fields(a)[1]*F.fields(b)[1]!=0 or not ((a^b)>>31):return False
 return True
def conv_word(inp,cin,h,w,cout,weights,bias,relu=False):
 k=cin*9;hit,guard=C.guard11(inp,weights,bias,k)
 assert hit,'This word model operates only on the original numerical narrow guard'
 xm=guard['xm'];wm=[]
 for (wl,_),b in zip(guard['weight_exp_bounds'],bias):
  wm.append(126+F.fields(b)[2]-xm if wl==511 else C.yk(wl))
 keyx=list(map(F.key,inp));keyw=list(map(F.key,weights))
 # Input alignment is global, as in source11. Zero terms need no exponent premise.
 X=[v//(1<<xm) for v in keyx]
 assert all(v%(1<<xm)==0 for v in keyx)
 weights_transformed=[]
 for o in range(cout):
  row=keyw[o*k:(o+1)*k]
  aligned=[v//(1<<wm[o]) for v in row]
  assert all(v%(1<<wm[o])==0 for v in row)
  weights_transformed.append([W.transform([aligned[c*9+r*3:c*9+r*3+3] for r in range(3)],W.G) for c in range(cin)])
 out=[None]*(cout*h*w)
 counts={'word_products':0,'block_merges':0,'tiles':0,'outputs':0,'zero_numerators':0,'negative_zero_outputs':0,'odd_clipped_outputs':0}
 for y in range(0,h,2):
  for x in range(0,w,2):
   v=[]
   for c in range(cin):
    patch=[[X[(c*h+yy)*w+xx] if 0<=yy<h and 0<=xx<w else 0 for xx in range(x-1,x+3)] for yy in range(y-1,y+3)]
    v.append(W.transform(patch,W.BT))
   for o in range(cout):
    u=weights_transformed[o]
    m=[[transformed_dot([a[i][j] for a in v],[a[i][j] for a in u],counts) for j in range(4)] for i in range(4)]
    tile=inverse(m);counts['tiles']+=1
    B0=xm+wm[o]
    bfull=F.key(bias[o])<<149
    assert bfull%(1<<B0)==0
    biasword=words(bfull//(1<<B0))
    for dy in range(2):
     for dx in range(2):
      if y+dy>=h or x+dx>=w:
       counts['odd_clipped_outputs']+=1;continue
      body=div4(tile[dy][dx]);total=add(body,biasword);total_int=signed128(total)
      raw=sum(F.key(get(inp,cin,h,w,c,y+dy+r-1,x+dx+s-1))*keyw[o*k+c*9+r*3+s]
              for c in range(cin) for r in range(3) for s in range(3))+bfull
      assert total_int*(1<<B0)==raw,'Bias/scaling/direct numerator mismatch'
      if total_int==0:
       counts['zero_numerators']+=1
       word=0x80000000 if zero_sign(inp,weights,bias,cin,h,w,o,y+dy,x+dx) else 0
      else:word=F.round_ratio(total_int,1,B0-298)
      if relu and word>>31:word=0
      counts['negative_zero_outputs']+=int(word==0x80000000)
      out[(o*h+y+dy)*w+x+dx]=word;counts['outputs']+=1
 assert all(x is not None for x in out)
 return out,counts

def main():
 began=time.time();records=[];original_conv=C.conv
 def compare(inp,cin,n,cout,w,b):
  result,stats=original_conv(inp,cin,n,cout,w,b)
  if stats['guard_hit_model']:
   actual,counts=conv_word(inp,cin,n,n,cout,w,b)
   assert actual==result
   records.append({'shape':[cin,n,n,cout],'input_checksum':C.hasharr(inp),'expected_checksum':C.hasharr(result),'word_checksum':C.hasharr(actual),'counts':counts})
  return result,stats
 C.conv=compare
 # Previously public seed42; varied shape profiles were already read before any confirmation.
 for profile in ['legacy','scale','boundary']:
  for kind in ['normal','wide','sparse']:
   C.run(42,kind,profile,1)
 specials=[]
 # All products are negative zero, including padded inputs. Keep original full sign replay.
 inp=[0]*25;inp[12]=0x3f800000
 for relu in [False,True]:
  out,c=conv_word(inp,1,5,5,1,[0x80000000]*9,[0x80000000],relu)
  assert out==[0 if relu else 0x80000000]*25
  specials.append({'name':'all_negative_zero_products','relu':relu,'counts':c,'checksum':C.hasharr(out)})
 # Parent's actual raw-word overflow shape now uses two safe blocks rather than15 unblocked.
 inp=([0x4c7fffff]*24+[0x3cffffff])*15
 out,c=conv_word(inp,15,5,5,1,[0x3cffffff]*135,[0])
 direct,_=original_conv(inp,15,5,1,[0x3cffffff]*135,[0])
 assert out==direct
 specials.append({'name':'parent15_channel_counterexample_corrected_by_block8','counts':c,'checksum':C.hasharr(out),'output_1_1':f'{out[6]:08x}'})
 # Bias after exact /4 is essential; this catches inserting bias at the scaled-transform level.
 out,c=conv_word([0x3f800000]*9,1,3,3,1,[0x3f800000]*9,[0x3f800000])
 direct,_=original_conv([0x3f800000]*9,1,3,1,[0x3f800000]*9,[0x3f800000])
 assert out==direct and out[4]==0x41200000
 specials.append({'name':'one_bias_added_after_exact_div4','counts':c,'center_word':f'{out[4]:08x}'})
 # Exact cancellation must produce +0, unlike the all-negative-zero case above.
 out,c=conv_word([0x3f800000]*9,1,3,3,1,[0x3f800000]*9,[0xc1100000])
 assert out[4]==0
 specials.append({'name':'nonzero_products_cancel_bias_to_positive_zero','counts':c,'center_word':f'{out[4]:08x}'})
 # Smallest subnormal products can round to signed zero without an exact-zero numerator.
 for relu in [False,True]:
  out,c=conv_word([0x80000001]*9,1,3,3,1,[0x00000001]*9,[0],relu)
  assert out==[0 if relu else 0x80000000]*9 and c['zero_numerators']==0
  specials.append({'name':'negative_nonzero_underflow','relu':relu,'counts':c,'checksum':C.hasharr(out)})
 out,c=conv_word([0x7f7fffff]*9,1,3,3,1,[0x7f7fffff]*9,[0])
 assert out==[0x7f800000]*9
 specials.append({'name':'finite_product_sum_overflows_to_positive_infinity','counts':c,'checksum':C.hasharr(out)})
 out,c=conv_word([0x3f800000]*6,1,2,3,1,[0x3f800000]*9,[0xbf800000])
 assert out==[0x40400000,0x40a00000,0x40400000]*2
 specials.append({'name':'non_square_odd_width_and_negative_bias','counts':c,'checksum':C.hasharr(out)})
 receipt={'state':'COMPLETE_PYTHON_WORD_PIPELINE_MATCHES_EXACT_DIRECT_NUMERATORS','old_public_seed':42,'profiles':['legacy','scale','boundary'],'batch':1,'guarded_convolution_calls':len(records),'matched_outputs':sum(x['counts']['outputs'] for x in records),'records':records,'special_cases':specials,'rounding_dependency':'Both paths reuse the same hashed R27 round_ratio; pre-rounding integer equality is independently asserted before using that shared rounder. Signed-zero replay modeled from original inputs/weights/bias.','model_hash':hashlib.sha256(C.MODEL.read_bytes()).hexdigest(),'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'resource_elapsed_seconds':time.time()-began,'not_claimed':['compiled Lean','actual new runtime','all12 gate','native cost','champion result']}
 (P/'spatial-word-pipeline-receipt.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8')
 print(json.dumps({k:receipt[k] for k in ['state','guarded_convolution_calls','matched_outputs','special_cases','resource_elapsed_seconds','not_claimed']},indent=2))
if __name__=='__main__':main()
