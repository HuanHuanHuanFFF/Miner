"""CI-only endprobe plan/record preservation and byte-validity diagnostics.

Final tokens may change. This is not a token-equivalence or performance test.
"""
from pathlib import Path
import hashlib
import importlib.util
import json
import os

from round4 import ROOT, save, validate

_spec = importlib.util.spec_from_file_location("r9_phase_helpers", ROOT / "scripts/research-round9-phases.py")
_helper = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(_helper)
run_logged = _helper.run_logged
failure_receipt = _helper.failure_receipt

HARNESS = r'''
#![allow(dead_code,unused_variables)]
#[path="reference.rs"] mod reference;
#[path="candidate.rs"] mod candidate;
fn decode(s:&[u8],ts:&[u32])->bool{let mut out=Vec::with_capacity(s.len());for &t in ts{if t<256{out.push(t as u8)}else{if t<16777216{return false}let v=t-16777216;let d=(v/256+1)as usize;let l=(v%256+3)as usize;if d>32768||d>out.len()||l>258||out.len()+l>s.len(){return false}for _ in 0..l{let b=out[out.len()-d];out.push(b)}}}out==s}
fn nodes(rs:&[u32])->Vec<(usize,usize,usize)>{let mut out=Vec::new();let mut e=rs.len();while e>=2{let k=rs[e-1]as usize;let p=rs[e-2]as usize;assert!(k<=e-2);let a=e-2-k;out.push((p,a,e-2));e=a}assert_eq!(e,0);out.reverse();assert!(out.windows(2).all(|w|w[0].0<w[1].0));out}
fn check_case(s:&[u8],case:usize,synthetic:bool){
    let cls=reference::route_class(s)%16;
    let mut a=vec![0u32;s.len()];let mut b=vec![0u32;s.len()];
    let an=reference::parse(s,&mut a);let bn=candidate::parse(s,&mut b);
    assert!(an<=s.len()&&bn<=s.len());assert!(decode(s,&a[..an]));assert!(decode(s,&b[..bn]));
    if reference::CLASS_TAB[cls][0]!=2 {assert_eq!(&a[..an],&b[..bn],"non-D route changed")}
    let actual_d=reference::CLASS_TAB[cls][0]==2;
    if s.len()<16 || (!synthetic && !actual_d){
        println!("R10_ENDPROBE {{\"case\":{},\"synthetic\":{},\"bytes\":{},\"direct_D\":false,\"decode\":true,\"same_tokens\":{}}}",case,synthetic,s.len(),a[..an]==b[..bn]);return
    }
    let row=if synthetic{case%11}else{reference::CLASS_TAB[cls][1]%16};let k=reference::D_KNOBS[row];
    let(mut old_plan,mut old_rs,mut new_plan,mut new_rs)=(Vec::new(),Vec::new(),Vec::new(),Vec::new());
    reference::d_parse(s,&mut old_plan,&mut old_rs,k[0],k[1],k[2],k[3],k[4],k[5],k[8],k[9],k[10],k[11],k[12],k[13],k[14],k[15]);
    candidate::d_parse(s,&mut new_plan,&mut new_rs,k[0],k[1],k[2],k[3],k[4],k[5],k[8],k[9],k[10],k[11],k[12],k[13],k[14],k[15]);
    assert_eq!(old_plan,new_plan,"original first plan changed");
    let old=nodes(&old_rs);let new=nodes(&new_rs);let mut allowed=Vec::new();
    for &(p,a,b) in &old{if b>a{let l=(old_rs[b-1]%512)as usize;if l>=k[4]&&l>=3{let end=p+l;let j=end-2;if j<s.len()-8&&j>p{allowed.push(j)}}}}
    assert!(allowed.windows(2).all(|w|w[0]<w[1]),"derived long-jump tail positions overlap");
    let(mut oi,mut extras,mut candidates,mut max_lengths,mut extended_bytes)=(0,0,0,0,0);
    for &(p,a,b) in &new{
        if oi<old.len()&&old[oi].0==p{let(_,oa,ob)=old[oi];assert_eq!(&old_rs[oa..ob],&new_rs[a..b],"old candidate payload changed");oi+=1}
        else{
            assert!(oi==old.len()||p<old[oi].0,"old node missing or reordered");
            assert!(allowed.binary_search(&p).is_ok(),"extra node not at an original true_end-2");
            assert!(b>a,"extra empty node");extras+=1;let mut last=2;
            for &r in &new_rs[a..b]{let l=(r%512)as usize;let d=((r>>9)%32768)as usize+1;let t=(r>>24)as usize;
                assert!(l>last&&reference::check(s,p,l,d),"invalid extra candidate bytes");
                assert!(t<=p&&l+t<=258&&reference::check(s,p-t,l+t,d),"invalid extra backward extension");
                candidates+=1;extended_bytes+=t;last=l;
            }
            max_lengths+=last-2;
        }
    }
    assert_eq!(oi,old.len(),"lost suffix of original rs");
    println!("R10_ENDPROBE {{\"case\":{},\"synthetic\":{},\"bytes\":{},\"direct_D\":true,\"row\":{},\"decode\":true,\"same_tokens\":{},\"first_plan_equal\":true,\"original_nodes_preserved\":true,\"extra_positions_valid\":true,\"extra_bytes_valid\":true,\"original_nodes\":{},\"new_nodes\":{},\"eligible_tail_positions\":{},\"extra_nodes\":{},\"extra_candidates\":{},\"extra_supported_lengths\":{},\"extra_backward_bytes\":{}}}",case,synthetic,s.len(),row,a[..an]==b[..bn],old.len(),new.len(),allowed.len(),extras,candidates,max_lengths,extended_bytes);
}
fn sample(n:usize,mode:usize)->Vec<u8>{let text=b"The quick brown fox, record 0123456789; fn result(value) { return value + 1; }\n";let mut z=987654321u64;let mut v=Vec::with_capacity(n);for i in 0..n{z^=z<<13;z^=z>>7;z^=z<<17;v.push(match mode%6{0=>(z>>24)as u8,1=>text[i%text.len()],2=>if z%79==0{(z%95+32)as u8}else{text[i%text.len()]},3=>if i%2==0{0xbf}else{z as u8},4=>if z%31==0{z as u8}else{0},_=>b"ACGT\n"[(z%5)as usize]})}v}
fn main(){for(index,file)in std::env::args_os().skip(1).enumerate(){let s=std::fs::read(file).unwrap();check_case(&s,index,false)}let mut case=0;for n in [16,17,31,258,259,1023,16385,32767,32768,32769,65535,65536,65537,131073]{for mode in 0..6{let s=sample(n,mode);check_case(&s,case,true);case+=1}}}
'''


def main():
    assert os.environ.get("GITHUB_ACTIONS") == "true" and os.environ.get("RUNNER_OS") == "Linux"
    assert os.environ.get("GITHUB_REPOSITORY") == "HuanHuanHuanFFF/Miner"
    spec = validate(os.environ["ROUND4_SPEC"])
    if not spec.get("endprobe_diagnostics"):
        print("ROUND10_ENDPROBE_NOT_REQUESTED")
        return
    reference = next(e for e in spec["entries"] if e["name"] == "r9-block-scalar")
    candidate = next(e for e in spec["entries"] if e["name"] == "r10-forward-endprobe")
    build = Path(os.environ["RUNNER_TEMP"]) / "round10-endprobe-build"
    output = Path(os.environ["RUNNER_TEMP"]) / "round4-receipts/endprobe-diagnostics"
    build.mkdir(exist_ok=True)
    output.mkdir(parents=True, exist_ok=True)
    for name, entry in (("reference", reference), ("candidate", candidate)):
        raw = (ROOT / entry["path"] / "parse.rs").read_bytes()
        assert hashlib.sha256(raw).hexdigest() == entry["hashes"]["parse.rs"]
        (build / f"{name}.rs").write_bytes(raw)
    (build / "main.rs").write_text(HARNESS)
    files = sorted(p for p in (Path(os.environ["DEFLATE_ROOT"]) / "data/benchmark/corpus-stage1").iterdir() if p.is_file())
    assert len(files) == 28 and sum(p.stat().st_size for p in files) == 15930000
    report = {"status": "PENDING", "run_id": os.environ["GITHUB_RUN_ID"], "git_sha": os.environ["GITHUB_SHA"],
              "reference_sha256": reference["hashes"]["parse.rs"], "candidate_sha256": candidate["hashes"]["parse.rs"],
              "scope": "Finite exact first-plan and original-node preservation, valid extra positions/match bytes/backward extensions, and final token decode. Not final-token equivalence, optimality or performance.",
              "corpus": [{"file": p.name, "bytes": p.stat().st_size, "sha256": hashlib.sha256(p.read_bytes()).hexdigest()} for p in files]}
    save(output / "endprobe.json", report)
    with failure_receipt(report, output / "endprobe.json"):
        binary = build / "endprobe-check"
        proc = run_logged(["rustc", "+nightly-2026-08-18", "--edition=2021", "-O", "-C", "overflow-checks=yes", str(build / "main.rs"), "-o", str(binary)], output / "build.log", 180)
        report["compile_exit"] = proc.returncode
        if proc.returncode:
            raise RuntimeError("Endprobe diagnostic Rust compilation failed; retained build.log")
        proc = run_logged([str(binary), *map(str, files)], output / "runtime.log", 420)
        report["runtime_exit"] = proc.returncode
        rows = [json.loads(line.removeprefix("R10_ENDPROBE ")) for line in proc.stdout.splitlines() if line.startswith("R10_ENDPROBE ")]
        assert proc.returncode == 0 and len(rows) == 112
        assert len([r for r in rows if not r["synthetic"]]) == 28
        assert len([r for r in rows if r["synthetic"]]) == 84
        assert all(r["decode"] for r in rows)
        assert all(r["first_plan_equal"] and r["original_nodes_preserved"] and r["extra_positions_valid"] and r["extra_bytes_valid"] for r in rows if r["direct_D"])
        totals = {kind: {key: sum(r.get(key, 0) for r in rows if r["synthetic"] == (kind == "synthetic")) for key in ("eligible_tail_positions", "extra_nodes", "extra_candidates", "extra_supported_lengths", "extra_backward_bytes")} for kind in ("public", "synthetic")}
        report.update(status="VERIFIED_FINITE_ENDPROBE_DIAGNOSTIC", records=rows, totals=totals)
        save(output / "endprobe.json", report)
        print("ROUND10_ENDPROBE", json.dumps({"status": report["status"], "cases": len(rows), "totals": totals}))


if __name__ == "__main__":
    main()
