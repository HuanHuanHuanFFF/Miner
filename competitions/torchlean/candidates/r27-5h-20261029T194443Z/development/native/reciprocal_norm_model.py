"""Caller discriminator using the shared exact finite norm formula model.

Only three division/remainder pairs are replaced in an AST clone; the original
shared model is read-only. No Lean/native build, scoring or independent holdout.
"""
from pathlib import Path
from datetime import datetime,timezone
from collections import Counter
import ast
import copy
import hashlib
import importlib.util
import json
import sys
import time

sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent
FRONTIER=HERE.parent.parent/"research/board-frontier"
sys.path.insert(0,str(FRONTIER))
import norm_frontier as nf
import norm_path_check as paths

spec=importlib.util.spec_from_file_location("r27_reciprocal_finite",HERE/"reciprocal_model.py")
rec=importlib.util.module_from_spec(spec);spec.loader.exec_module(rec)

def pair(numerator,denominator,reciprocal):
    if not denominator:
        return 0,numerator
    q=rec.mul_high(numerator,reciprocal)
    r=(numerator-q*denominator)&rec.MASK64
    return (q+1,r-denominator) if denominator<=r else (q,r)

def quotient(a,d,r):
    return pair(a,d,r)[0]

def remainder(a,d,r):
    return pair(a,d,r)[1]

class ExactPairRewrite(ast.NodeTransformer):
    def __init__(self):
        self.counts=Counter()
    def visit_BinOp(self,node):
        node=self.generic_visit(node)
        if isinstance(node.right,ast.Name) and node.right.id=="D" and isinstance(node.op,(ast.FloorDiv,ast.Mod)):
            name="quotient" if isinstance(node.op,ast.FloorDiv) else "remainder"
            self.counts[name]+=1
            return ast.copy_location(ast.Call(ast.Name(name,ast.Load()),
                [node.left,node.right,ast.Name("cached_reciprocal",ast.Load())],[]),node)
        return node

def make_model():
    source=(FRONTIER/"norm_path_check.py").read_bytes()
    original=next(x for x in ast.parse(source).body if isinstance(x,ast.FunctionDef) and x.name=="fast_word")
    function=copy.deepcopy(original)
    function.name="fast_word_reciprocal"
    function.args.args.append(ast.arg(arg="cached_reciprocal"))
    rewrite=ExactPairRewrite()
    function=rewrite.visit(function)
    assert rewrite.counts=={"quotient":3,"remainder":3},rewrite.counts
    module=ast.fix_missing_locations(ast.Module(body=[function],type_ignores=[]))
    ns={"nf":nf,"finish_normal":paths.finish_normal,"quotient":quotient,"remainder":remainder}
    exec(compile(module,"<r27-owned-reciprocal-formula-clone>","exec"),ns)
    return ns[function.name],rewrite.counts,hashlib.sha256(source).hexdigest()

def main():
    started=time.monotonic()
    model,rewrites,source_hash=make_model()
    results=[];counts=Counter();stream=hashlib.sha256();negative_control=None
    seed=27051001
    for profile in["typical","boundary"]:
        i,h,h2=nf.dimensions(seed,profile)
        for kind in["normal","wide","sparse"]:
            for rows in[1,8]:
                x=nf.gen(kind,rows*i,seed+999)
                x=nf.linear(x,rows,i,h,nf.weights(kind,seed,1,i,h*i),nf.bias(seed,2,h),True)
                x=nf.norm(x,rows,h,nf.scale(seed+3,h))
                x=nf.linear(x,rows,h,h2,nf.weights(kind,seed,4,h,h2*h),nf.bias(seed,5,h2),True)
                gain=nf.scale(seed+6,h2);bias=nf.bias(seed,7,h2)
                row_info=[]
                for row in range(rows):
                    words=x[row*h2:(row+1)*h2]
                    keys=list(map(nf.key,words));S=sum(keys);Q=sum(v*v for v in keys)
                    dw=nf.sqrt_ratio(h2*Q-S*S+h2*h2*nf.key(nf.EPS)*(1<<149),h2*h2<<298)
                    b0=min((nf.fields(w)[2] for w in words if nf.fields(w)[1]),default=255)
                    first=sum(s*(m<<max(0,e-b0)) for s,m,e in map(nf.fields,words))
                    denominator=h2*nf.fields(dw)[1]
                    reciprocal=rec.MASK64//denominator if denominator else 0
                    row_info.append((dw,b0,first,denominator,reciprocal))
                cell_counts=Counter()
                for row,(dw,b0,first,denominator,reciprocal) in enumerate(row_info):
                    for col in range(h2):
                        args=(h2,x[row*h2+col],gain[col],bias[col],b0,first,dw,8)
                        original=paths.fast_word(*args)
                        actual=model(*args,reciprocal)
                        assert actual==original,(profile,kind,rows,row,col,args,original,actual)
                        cell_counts[actual[1]]+=1
                        stream.update(json.dumps([profile,kind,rows,row,col,actual],separators=(",",":")).encode()+b"\n")
                        if negative_control is None and rows>1 and original[0] is not None:
                            wrong=row_info[(row+1)%rows][4]
                            if wrong!=reciprocal:
                                try:
                                    corrupted=model(*args,wrong)
                                    detected=corrupted!=original
                                    observation=corrupted
                                except Exception as error:
                                    detected=True;observation=type(error).__name__
                                if detected:
                                    negative_control={"kind":"wrong_row_cached_reciprocal","args":args,
                                        "denominator":denominator,"correct_reciprocal":reciprocal,
                                        "wrong_reciprocal":wrong,"expected":original,"observed":observation,
                                        "detected":True}
                counts.update(cell_counts)
                results.append({"profile":profile,"kind":kind,"rows":rows,"shape":[i,h,h2,10],"counts":dict(cell_counts),
                                "row_preparations":rows,"denominator_bits":[v[3].bit_length() for v in row_info]})
    report={"scope":"FINITE_ACTUAL_CALLER_FORMULA_ONLY_NOT_LEAN_NATIVE_SCORE_OR_HOLDOUT",
            "at_utc":datetime.now(timezone.utc).isoformat(),"seed":seed,"cells":results,"totals":dict(counts),
            "rewritten_AST_operations":dict(rewrites),"shared_formula_source_sha256":source_hash,
            "shared_generator_source_sha256":hashlib.sha256((FRONTIER/"norm_frontier.py").read_bytes()).hexdigest(),
            "own_runtime_model_sha256":hashlib.sha256((HERE/"reciprocal_model.py").read_bytes()).hexdigest(),
            "result_stream_sha256":stream.hexdigest(),"negative_control":negative_control,
            "model_execution_seconds":time.monotonic()-started,"native_speed":"UNKNOWN"}
    (HERE/"reciprocal-norm-model.json").write_text(json.dumps(report,indent=2)+"\n",encoding="utf-8")
    print(json.dumps({"cells":len(results),"totals":dict(counts),"negative_control":negative_control,
                      "seconds":report["model_execution_seconds"]},indent=2))

if __name__=="__main__":
    main()
