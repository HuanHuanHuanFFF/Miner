"""Old-seen exact CNN replay: availability of fused negative BN/ReLU finish.

Consumes the other role's owned finite model read-only; no native/Lean run and
no mutation of its files. The original reference outputs remain the oracle.
"""
from pathlib import Path
from datetime import datetime,timezone
from collections import Counter
import hashlib,importlib.util,json,time,sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent;ROUND=HERE.parents[1]
def main():
    began=time.monotonic();path=ROUND/"research/resnet-mechanism/cnn_zero_census.py"
    spec=importlib.util.spec_from_file_location("r28_native_bn_census",path);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
    original=m.bn;F=m.F;rows=[];context={};MASK64=(1<<64)-1
    def observe(inp,c,hw,seed,layer,relu):
        assert time.monotonic()-began<20,"20 second lightweight model cap"
        g=F.scale((seed+7*layer)&0xffffffff,c);b=F.bias(seed,layer,c);counts=Counter(outputs=len(inp),relu_outputs=len(inp) if relu else 0)
        for i,x in enumerate(inp):
            sx,mx,ix=F.fields(x);sg,my,iy=F.fields(g[i//hw]);sb,mz,iz=F.fields(b[i//hw])
            mp=mx*my;p=ix+iy;iq=iz+149;k=iq if mp==0 else p if mz==0 else min(p,iq)
            dp,dq=p-k,iq-k
            finite=((x>>23)&255)!=255 and ((g[i//hw]>>23)&255)!=255 and ((b[i//hw]>>23)&255)!=255
            if not (finite and 0<=dp<=14 and 0<=dq<=38):continue
            counts["source11_Ysx_fast_outputs"]+=1
            ss=(sx*sg*(mp<<dp)+sb*(mz<<dq))&MASK64
            exact=F.key(x)*F.key(g[i//hw])+(F.key(b[i//hw])<<149)
            if relu and ss>>63:
                assert exact<0
                counts["fused_negative_finish_outputs"]+=1
        out=original(inp,c,hw,seed,layer,relu)
        rows.append({**context,"layer":layer,"relu":relu,"c":c,"hw":hw,"counts":dict(counts),"unchanged_reference_output_checksum":m.hasharr(out)})
        return out
    m.bn=observe;cells=[]
    expected=json.loads((ROUND/"research/resnet-mechanism/cnn-zero-census-legacy.json").read_text())["rows"]
    expected={(r["kind"],r["batch"]):[v["output_checksum"] for v in r["layers"]] for r in expected}
    for kind in ["normal","wide","sparse"]:
        for batch in [1,4]:
            context.clear();context.update(kind=kind,batch=batch,profile="legacy",seed=42);mark=len(rows)
            result=m.run(42,kind,"legacy",batch)
            assert [v["output_checksum"] for v in result["layers"]]==expected[(kind,batch)]
            cells.append({**context,"convolution_checksums_oldseen_match":True,"BN_stages":rows[mark:]})
    totals=Counter()
    for row in rows:totals.update(row["counts"])
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"wall_seconds":time.monotonic()-began,"status":"OLDSEEN_FINITE_EXACT_FORMULA_ONLY","source_model_sha256":hashlib.sha256(path.read_bytes()).hexdigest(),"cells":cells,"totals":dict(totals),
         "mechanism":"Within original source11 finite/width guard, negative native64 FMA total and relu=true can return+0 before Lt/Lq/log/round/pack. Source53 already exposes this mechanism; a source11 native cost prototype preserves original positive Ge hint.",
         "boundary":"BN output hit counts are not cost or wholemodel gain. Stage3relu=false unchanged. Root originalprofile BN11.7-13.1% ofinstrumentedentries only. No frozenconfirmation data or localnativebuild."}
    (HERE/"BN11-CLIP-CENSUS.json").write_text(json.dumps(out,indent=2)+"\n",encoding="utf-8")
    print(json.dumps({"wall_seconds":out["wall_seconds"],"cells":len(cells),"totals":out["totals"]}))
if __name__=="__main__":main()
