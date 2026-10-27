from pathlib import Path
import hashlib,json,re,datetime
r=Path(__file__).resolve().parent
cpath=r/"code-excerpts/lp_competition_Submission_mul.c"
b=cpath.read_bytes()
idx=json.loads((r/"source-index.json").read_text())
f=next(x for x in idx["functions"] if x["name"]=="lp_competition_Submission_mul")
assert hashlib.sha256(b).hexdigest()==f["sha256"]
ls=b.decode().splitlines();offset=f["first_line"]-1
terms={
"outer_exsum_guard":"v___x_6850_ = lean_uint32_dec_lt(v___x_6848_, v___x_6849_);",
"special_x":"v___x_6887_ = lean_uint32_dec_le(v___x_6884_, v___x_6886_);",
"special_y":"v___x_6889_ = lean_uint32_dec_le(v___x_6884_, v___x_6888_);",
"special_result_dispatch":"v___jp_6865_:",
"sign_x":"v___x_6868_ = lean_uint32_land(v_x_6357_, v___x_6867_);",
"sign_y":"v___x_6862_ = lean_uint32_land(v_y_6358_, v___x_6861_);",
"sign_xor_lowering":"v___jp_6854_:",
"fraction_x":"v_xFraction_6840_ = lean_uint32_land(v_x_6357_, v___x_6839_);",
"fraction_y":"v_yFraction_6841_ = lean_uint32_land(v_y_6358_, v___x_6839_);",
"mantissa_x_zero_exp":"v___x_6843_ = lean_uint32_dec_eq(v_ex_6802_, v___x_6842_);",
"mantissa_y_zero_exp":"v___x_6832_ = lean_uint32_dec_eq(v_ey_6804_, v___x_6831_);",
"scale_x_zero_exp":"v___x_6823_ = lean_uint64_dec_eq(v___x_6821_, v___x_6822_);",
"scale_y_zero_exp":"v___x_6813_ = lean_uint64_dec_eq(v___x_6811_, v___x_6812_);",
"product":"v___x_6770_ = lean_uint64_mul(v___y_6766_, v___y_6768_);",
"scale_sum":"v___x_6771_ = lean_uint64_add(v___y_6765_, v___y_6769_);",
"selector_product_lt_2pow48":"v___x_6773_ = lean_uint64_dec_lt(v___x_6770_, v___x_6772_);",
"selector_scale_le123":"v___x_6775_ = lean_uint64_dec_le(v___x_6771_, v___x_6774_);",
"roundLow_product_zero":"v___x_6777_ = lean_uint64_dec_eq(v___x_6770_, v___x_6776_);",
"roundLow_zero_return":"return v___x_6800_;",
"roundP_product_zero":"v___x_6757_ = lean_uint64_dec_eq(v___y_6752_, v___x_6756_);",
"roundP_zero_return":"return v___x_6761_;",
"fastLog2_first_shift_NOT_REACHED_ON_ZERO":"v___x_6759_ = lean_uint64_shift_right(v___y_6752_, v___x_6758_);",
"rse_first_subtract_NOT_REACHED_ON_ZERO":"v___x_6779_ = lean_uint64_sub(v___x_6778_, v___x_6771_);"
}
rows=[]
for name,term in terms.items():
    hits=[i+1 for i,l in enumerate(ls) if l==term]
    assert len(hits)==1,(name,hits)
    rows.append(dict(meaning=name,excerpt_line=hits[0],original_C_line=hits[0]+offset,text=term))
ranges=[(1,61),(1246,1332),(1438,1463),(1464,1674)]
parts=[]
for lo,hi in ranges:
    parts.append(f"/* Exact source excerpt lines {lo}-{hi}; original C lines {lo+offset}-{hi+offset}. */")
    parts.extend(f"{i+offset}: {ls[i-1]}" for i in range(lo,min(hi,len(ls))+1))
(r/"zero-route-numbered-excerpts.txt").write_text("\n".join(parts)+"\n",encoding="utf-8")
rec=dict(state="SOURCE_CONTROL_FLOW_AUDIT_ONLY",at_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),
original_C=idx["original_C"],function_sha256=f["sha256"],source_map=rows,
domain="(ex+ey<128) and at least one raw magnitude equals0; incremental after cutoff84 is85<=ex+ey<=127",
paths=[
dict(domain="zero x finite normal with companion exponent85..124",scale="companion exponent-1=84..123",rounder="roundLow",zero_test="v___x_6777_",returns="v___x_6800_/v___x_6801_",log2=False,rse=False,float_primitive=False),
dict(domain="zero x finite normal with companion exponent125..127",scale="companion exponent-1=124..126",rounder="roundP",zero_test="v___x_6757_",returns="v___x_6761_/v___x_6762_",log2=False,rse=False,float_primitive=False)],
decision="A raw-zero guard inside old low arm can bypass visible finite-core preparation and selector work; it does not save log2/RNE/native conversions on existing zero cases. Runtime effect UNKNOWN.",
external_calls_on_described_C_path="None observed: only lean UInt32/UInt64 static-inline primitives, branch/goto and constant returns. Transitive and optimized machine execution not measured.",
performance="NOT_RUN",candidate="NOT_CREATED",compile="NOT_RUN")
(r/"zero-route-c-audit.json").write_text(json.dumps(rec,ensure_ascii=False,indent=2)+"\n",encoding="utf-8")
print(json.dumps(dict(state=rec["state"],mapped_sites=len(rows),candidate_sha256=idx["candidate_sha256"],original_C_sha256=idx["original_C"]["sha256"],paths=rec["paths"]),ensure_ascii=False,indent=2))

