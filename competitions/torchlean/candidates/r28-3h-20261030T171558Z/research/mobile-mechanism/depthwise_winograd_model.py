"""Single-channel spatial Winograd: signed64 split inverse range/correlation check.

Paper-bound/finite integer model only. No Kernel, benchmark, or caller assumption.
"""
from pathlib import Path
import random,json,hashlib,datetime
HERE=Path(__file__).resolve().parent
BT=[[1,0,-1,0],[0,1,1,0],[0,-1,1,0],[0,1,0,-1]]
GP=[[2,0,0],[1,1,1],[1,-1,1],[0,0,2]]
AT=[[1,1,1,0],[0,1,-1,-1]]
MASK=(1<<64)-1;R=1<<25;M=(1<<24)-1
def tr(a):return list(map(list,zip(*a)))
def mm(a,b):return [[sum(x*y for x,y in zip(row,col)) for col in zip(*b)] for row in a]
def wrap(a):
    a&=MASK
    return a-(1<<64) if a>>63 else a
def one(x,w):
    v=mm(mm(BT,x),tr(BT));u=mm(mm(GP,w),tr(GP))
    lo=[[v[i][j]%R*u[i][j] for j in range(4)] for i in range(4)]
    hi=[[v[i][j]//R*u[i][j] for j in range(4)] for i in range(4)]
    peaks=[]
    def inverse(a):
      first=[]
      for row in AT:
        rr=[]
        for j in range(4):
          total=0
          for i in range(4):
            total+=row[i]*a[i][j];assert wrap(total)==total;peaks.append(abs(total))
          rr.append(total)
        first.append(rr)
      result=[]
      for i in range(2):
        rr=[]
        for row in AT:
          total=0
          for j in range(4):
            total+=row[j]*first[i][j];assert wrap(total)==total;peaks.append(abs(total))
          rr.append(total)
        result.append(rr)
      return result
    l=inverse(lo);h=inverse(hi)
    result=[[l[i][j]+R*h[i][j] for j in range(2)] for i in range(2)]
    direct=[[sum(x[i+a][j+b]*w[a][b] for a in range(3) for b in range(3))*4 for j in range(2)] for i in range(2)]
    assert result==direct
    return max(peaks)
def main():
    rng=random.Random(0xD328);count=0;peak=0;pairs=0
    for sx in range(32):
      for sw in range(7):
        if sx+sw>31:continue
        pairs+=1
        xmax=M<<sx;wmax=M<<sw
        patterns=[([[xmax]*4 for _ in range(4)],[[wmax]*3 for _ in range(3)]),
          ([[(-1 if (i+j)%2 else 1)*xmax for j in range(4)] for i in range(4)],[[(-1 if (i+j)%2 else 1)*wmax for j in range(3)] for i in range(3)]),
          ([[-xmax]*4 for _ in range(4)],[[wmax]*3 for _ in range(3)])]
        for _ in range(12):
          x=[[rng.randrange(-xmax,xmax+1) for _ in range(4)] for _ in range(4)]
          w=[[rng.randrange(-wmax,wmax+1) for _ in range(3)] for _ in range(3)];patterns.append((x,w))
        for x,w in patterns:peak=max(peak,one(x,w));count+=1
    H=9*M*M*(1<<8);L=((1<<25)-1)*9*M*(1<<6)
    assert 9*H<(1<<63) and 9*L<(1<<62)
    assert 3*H<(1<<61) and 3*L<(1<<60)
    out={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'scope':'Paper range + finite integer transform model; not Lean, native performance, or all-input original gate. Random integers are a superset of binary32-aligned values, not producer coverage statistics.','range_domain':{'sx_plus_sw_max':31,'sw_max':6,'independent_depthwise_channels':1,'input_transform_l1':4,'weight_transform_l1':9,'inverse_output_terms':9,'split_bits':25},'bounds':{'per_product_low_abs_max':L,'per_product_high_abs_max':H,'inverse_low_abs_max':9*L,'inverse_high_abs_max':9*H,'high_margin_below_2pow63':(1<<63)-9*H,'row_high_abs_max':3*H,'row_low_abs_max':3*L,'row_cache_center':1<<61},'finite_checks':{'range_pairs':pairs,'tiles':count,'outputs':4*count,'mismatches':0,'largest_observed_abs_inverse_prefix':peak},'cost_boundary':'Dense original53 depthwise four outputs use72 split UInt64 multiplies; transform uses32 before setup/inverse/finish. Sparse original53 am already compacts weight support; around half weights gives36 old multiplies, so retain that strong path. No whole-model benefit inferred.','script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}
    (HERE/'depthwise-winograd-model.json').write_text(json.dumps(out,indent=2)+'\n');print(json.dumps(out,indent=2))
if __name__=='__main__':main()
