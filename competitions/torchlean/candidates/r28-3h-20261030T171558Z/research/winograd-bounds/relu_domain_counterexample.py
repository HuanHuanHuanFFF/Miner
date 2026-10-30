"""Exact 1D and 2D witnesses: moving ReLU before the inverse is not equivalent."""
from pathlib import Path
import json,hashlib,datetime
BT=[[1,0,-1,0],[0,1,1,0],[0,-1,1,0],[0,1,0,-1]]
G=[[2,0,0],[1,1,1],[1,-1,1],[0,0,2]]
AT=[[1,1,1,0],[0,1,-1,-1]]
def mm(a,b):return [[sum(x*y for x,y in zip(r,c)) for c in zip(*b)] for r in a]
def tr(a):return list(map(list,zip(*a)))
def tf(m,t):return mm(mm(t,m),tr(t))
def main():
 x=[1,0,2,0];w=[1,0,0]
 bx=[sum(a*b for a,b in zip(r,x)) for r in BT];gw=[sum(a*b for a,b in zip(r,w)) for r in G]
 orig=sum(bx[i]*gw[i] for i in [0,1,2])//2
 moved=sum(max(0,bx[i])*gw[i] for i in [0,1,2])//2
 d=[[v,0,0,0] for v in x];k=[[1,0,0],[0,0,0],[0,0,0]]
 v=tf(d,BT);u=tf(k,G)
 m=[[v[i][j]*u[i][j] for j in range(4)] for i in range(4)]
 bad=[[max(0,v[i][j])*u[i][j] for j in range(4)] for i in range(4)]
 good=tf(m,AT)[0][0]//4;wrong=tf(bad,AT)[0][0]//4
 assert (orig,moved,good,wrong)==(1,2,1,2)
 out={'state':'EXACT_INTEGER_COUNTEREXAMPLE_NOT_RUNTIME_TEST','at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'input_1d':x,'weight_1d':w,'input_transform':bx,'original_output':orig,'moved_relu_output':moved,'input_2d':d,'weight_2d':k,'output_2d':good,'moved_output_2d':wrong,'final_relu_does_not_fix':True,'scope':'Rejects moving activation into transform domain; ordinary exact Winograd remains valid','source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}
 Path(__file__).with_name('relu-domain-counterexample.json').write_text(json.dumps(out,indent=2)+'\n')
 print(json.dumps(out))
if __name__=='__main__':main()
