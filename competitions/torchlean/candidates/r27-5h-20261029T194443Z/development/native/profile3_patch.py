"""Narrow owned-profiler correction: source12 has3NMLP entrypoints, no Ya3."""
from pathlib import Path
import argparse
import ast
import hashlib
import json

PIN="03035270a3291d6b7bcba31e9d4611d23364937033c0e26c9528b84048e3cc8f"

def transform(data):
    assert hashlib.sha256(data).hexdigest()==PIN
    text=data.decode("utf-8")
    changes=[
        ("KERNELS={'YaV':'linear','Ya3':'gemm','Ybb2':'rmsnorm','MYbc':'layernorm'}", "KERNELS={'YaV':'linear','Ybb2':'rmsnorm','MYbc':'layernorm'}"),
        ("YaV|Ya3|Ybb2|MYbc", "YaV|Ybb2|MYbc"),
        ("assert len(matches)==4", "assert len(matches)==3"),
        ("assert len(metrics)==4", "assert len(metrics)==3"),
    ]
    for before,after in changes:
        assert text.count(before)==1,before
        text=text.replace(before,after,1)
    ast.parse(text)
    return text.encode("utf-8")

def main():
    p=argparse.ArgumentParser()
    p.add_argument("--source",type=Path,required=True)
    p.add_argument("--output",type=Path)
    a=p.parse_args()
    result=transform(a.source.read_bytes())
    if a.output:
        a.output.write_bytes(result)
    print(json.dumps({"scope":"OWNED_PROFILER_ONLY_NOT_CANDIDATE_OR_NATIVE_TEST", "input_sha256":PIN,
                      "output_sha256":hashlib.sha256(result).hexdigest(),"bytes":len(result),
                      "source12_entrypoints":["YaV","Ybb2","MYbc"],"changes":4},indent=2))

if __name__=="__main__":
    main()
