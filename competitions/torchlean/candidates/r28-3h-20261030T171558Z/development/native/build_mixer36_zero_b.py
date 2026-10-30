"""Owned complete-source recipe: skip zero shared B in native paired MD2.

This keeps every source36 matrix preparation and fallback. Sparse prepared
weights have decoded B=0, so both exact accumulators remain unchanged and the
two A reads, products, shifts and carry chains can be skipped together.
"""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,json,re
HERE=Path(__file__).resolve().parent
PIN="595a90fa2b6bc5d3657434fae7d1292b27910ef653da2b7f409ed9c34c956e2b"
def sha(b):return hashlib.sha256(b).hexdigest()
def once(s,a,b):assert s.count(a)==1,(a,s.count(a));return s.replace(a,b,1)
def proof_punctuation(source):
    starts=list(re.finditer(r"(?m)^(?:@\[[^\n]*\]\s*)?(?:def|lemma|theorem|structure|abbrev|section|end|open|namespace|set_option)\b",source))
    chunks=[];last=0;changes=[]
    for i,m in enumerate(starts):
        end=starts[i+1].start() if i+1<len(starts) else len(source)
        piece=source[m.start():end]
        if not re.match(r"(?:@\[[^\n]*\]\s*)?(?:lemma|theorem)\b",piece):continue
        # Commas/semicolons delimit tokens; indentation and application spaces stay.
        compact=re.sub(r"[ \t]+(?=[,;])|(?<=[,;])[ \t]+","",piece)
        if compact!=piece:
            chunks.extend([source[last:m.start()],compact]);last=end
            changes.append({"line":source.count("\n",0,m.start())+1,"saved_bytes":len(piece.encode())-len(compact.encode())})
    chunks.append(source[last:]);return "".join(chunks),changes
def compact_proof_names(source):
    declarations=re.findall(r"(?m)^(?:@\[[^\n]*\]\s*)?(?:lemma|theorem)\s+([\w']+)",source)
    tokens=set(re.findall(r"[\w']+",source));renames={};saving=0
    ranked=[]
    for name in declarations:
        if name=="correct" or len(name.encode())<=3:continue
        count=len(re.findall(r"(?<![\w.'?!])"+re.escape(name)+r"(?![\w.'?!])",source))
        ranked.append(((len(name.encode())-3)*count,name,count))
    target=max(0,len(source.encode())-255950)
    if target==0:return source,{},0
    for gain,name,count in sorted(ranked,reverse=True):
        if saving>=target:break
        index=len(renames)
        while (fresh:=f"z{index:02}") in tokens:index+=1
        tokens.add(fresh);renames[name]=fresh;saving+=(len(name.encode())-len(fresh))*count
    expr=re.compile(r"(?<![\w.'?!])("+"|".join(map(re.escape,renames))+r")(?![\w.'?!])")
    result=expr.sub(lambda m:renames[m.group()],source)
    assert len(source.encode())-len(result.encode())==saving
    return result,renames,saving
def build(raw):
    assert sha(raw)==PIN
    source=raw.decode();begin=source.index("def MD2 ");end=source.index("\ndef MVj ",begin)
    body=source[begin:end]
    marker="  let w:=(B.uget k (by have:=υ.mp hk;omega))ڈ-4611686018427387904\n"
    addition="  if w=0 then MD2 X W b inW outW relu i j n A1 A2 B hA1 hA2 hB d1 d2 lo1 lo2 bw h1 l1 h2 l2 (k+1) out else\n"
    body=once(body,marker,marker+addition)
    after=body.index(marker)+len(marker)+len(addition)
    otherwise=body.index("\n else\n",after)
    # The nonzero branch remains the original body at one more indentation level.
    body=body[:after]+"\n".join(" "+line for line in body[after:otherwise].split("\n"))+body[otherwise:]
    body=once(body,"decreasing_by exact ZI n k hk","decreasing_by all_goals exact ZI n k hk")
    source=source[:begin]+body+source[end:]
    old="  rw [MD2,MD,MD];simp only [dif_pos h0];exact ih (k+1) _ _ _ _ א"
    new="""  rw [MD2,MD,MD];simp only [dif_pos h0];dsimp only
  split
  . rename_i hw
    simpa [hw] using ih (k+1) h1 l1 h2 l2 א
  . exact ih (k+1) _ _ _ _ א"""
    source=once(source,old,new)
    source,changes=proof_punctuation(source)
    source,renames,name_saving=compact_proof_names(source)
    result=source.encode();assert len(result)<=256000
    return result,{"base_sha256":PIN,"runtime_changed":["MD2"],"proof_changed_semantically":["ZMD2"],
                   "proof_punctuation_saved_bytes":sum(x["saved_bytes"] for x in changes),"proof_punctuation_declarations":len(changes),
                   "proof_names_renamed":renames,"proof_name_saved_bytes":name_saving,
                   "runtime":"Zero decoded shared B takes direct tail recursion before A1/A2 loads; nonzero branch original paired128 work. Original native source36 smallK GEMM/linear/nativeadd/LN and all fallbacks stay.",
                   "proof":"ZMD2 zero branch simplifies both scalar MD steps and applies the same induction hypothesis; actualall12 theorem unchanged but exact new gate not run",
                   "possible_cost":"Predictable B!=0 branch on dense data; skips two A reads/two products/two shifts/two carry chains for sparse B. Native code/speed UNKNOWN.",
                   "publication":"Ownrecipe/receipts only; whole upstream and reconstructed Kernel private/ephemeral"}
def transform(raw,submission=36,variant="mixer36-zero-b"):
    assert submission==36 and variant=="mixer36-zero-b"
    return build(raw)[0]
if __name__=="__main__":
    p=argparse.ArgumentParser();p.add_argument("--source",type=Path,required=True);p.add_argument("--output",type=Path);p.add_argument("--receipt",type=Path,required=True)
    a=p.parse_args();result,meta=build(a.source.read_bytes())
    if a.output:a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"candidate_sha256":sha(result),"candidate_bytes":len(result),"free_bytes":256000-len(result),"recipe_sha256":sha(Path(__file__).read_bytes()),**meta,"state":"ACTUAL_ALL12_DECLARED_NOT_COMPILED","gate":"UNKNOWN","native_speed":"UNKNOWN"}
    a.receipt.write_text(json.dumps(out,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
    print(json.dumps({k:out[k] for k in ["candidate_sha256","candidate_bytes","free_bytes","recipe_sha256","state","proof_punctuation_saved_bytes"]}))
