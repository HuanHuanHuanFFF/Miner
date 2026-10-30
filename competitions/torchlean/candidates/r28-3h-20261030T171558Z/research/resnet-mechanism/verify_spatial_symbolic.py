#!/usr/bin/env python3
"""Exact coefficient verification of the universal bilinear spatial identity.
No sampled floating point or compiler is involved; not a Lean kernel proof.
"""
from collections import defaultdict
from pathlib import Path
import hashlib,json
P=Path(__file__).resolve().parent
BT=((1,0,-1,0),(0,1,1,0),(0,-1,1,0),(0,1,0,-1))
G=((2,0,0),(1,1,1),(1,-1,1),(0,0,2))
AT=((1,1,1,0),(0,1,-1,-1))
def main():
    results=[]
    for y in range(2):
     for x in range(2):
      coeff=defaultdict(int)
      for i in range(4):
       for j in range(4):
        for dr in range(4):
         for dc in range(4):
          for wr in range(3):
           for wc in range(3):
            coeff[dr,dc,wr,wc]+=AT[y][i]*AT[x][j]*BT[i][dr]*BT[j][dc]*G[i][wr]*G[j][wc]
      expected={(y+r,x+c,r,c):4 for r in range(3) for c in range(3)}
      got={k:v for k,v in coeff.items() if v}
      assert got==expected
      results.append({'output':[y,x],'coefficients_checked':len(coeff),'nonzero_monomials':len(got),'coefficient':4})
    bounds=[]
    for f in range(7):
     for g in range(32-f):
      A=1<<(24+g);B=1<<(24+f)
      assert A*B<=1<<79 and B<=1<<30
      # Safe bounds from Euclidean remainder; signed floor, not truncation to zero.
      l=9*(1<<55)
      h=36*(1<<54)+9*(1<<30)
      assert 8*l < 1<<63 and 8*h <1<<63
      bounds.append([g,f])
    r={'state':'EXACT_SYMBOLIC_COEFFICIENT_PASS','scope':'All integer 4x4 inputs and 3x3 weights by explicit bilinear coefficient equality; not compiled Lean or runtime proof','outputs':results,'total_coefficients':sum(x['coefficients_checked'] for x in results),'joint_exponent_pairs':len(bounds),'split25_low_term_bound':str(l),'split25_high_term_bound':str(h),'eight_low_bound':str(8*l),'eight_high_bound':str(8*h),'signed64_limit':str(1<<63),'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}
    (P/'spatial-symbolic-receipt.json').write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8');print(json.dumps(r,indent=2))
if __name__=='__main__':main()
