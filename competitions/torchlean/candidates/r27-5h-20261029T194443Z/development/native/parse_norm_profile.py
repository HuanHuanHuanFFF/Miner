"""Strict small parser for owned per-layer diagnostic output; never a scorer."""
from pathlib import Path
from collections import defaultdict
from statistics import median
import argparse
import hashlib
import itertools
import json

HEADER="R27_PROFILE\tseed\tprofile\tkind\tbatch\tlayer\tlabel\trepetition\twarmup\tns\tchecksum"

def parse(raw,seed,repetitions):
    groups=defaultdict(list);seen=set();header_count=0
    for line in raw.decode("utf-8").splitlines():
        if not line.startswith("R27_PROFILE\t"):
            continue
        if line==HEADER:
            header_count+=1;continue
        fields=line.split("\t")
        assert len(fields)==11,fields
        _,s,profile,kind,batch,layer,label,rep,warmup,ns,checksum=fields
        values=list(map(int,[s,batch,layer,rep,ns,checksum]))
        s,batch,layer,rep,ns,checksum=values
        assert s==seed and 0<=rep<=repetitions and warmup in {"true","false"}
        assert (warmup=="true")== (rep==0) and ns>0 and 0<=checksum<1<<32
        key=(profile,kind,batch,layer)
        assert key+(rep,) not in seen
        seen.add(key+(rep,))
        groups[key].append({"repetition":rep,"warmup":rep==0,"ns":ns,"checksum":checksum,"label":label})
    assert header_count==1,header_count
    cells=[]
    for profile,kind,batch in itertools.product(["typical","scale","boundary"],["normal","wide","sparse"],[1,8]):
        layers=[]
        for layer,family in enumerate(["linear","rmsnorm","linear","layernorm","linear"]):
            samples=sorted(groups.pop((profile,kind,batch,layer)),key=lambda x:x["repetition"])
            assert [x["repetition"] for x in samples]==list(range(repetitions+1))
            assert len({x["checksum"] for x in samples})==1
            labels={x["label"] for x in samples}
            assert len(labels)==1 and next(iter(labels)).split(":")[0]==family
            measured=[x["ns"] for x in samples if not x["warmup"]]
            layers.append({"layer":layer,"family":family,"label":samples[0]["label"],
                           "median_ns":median(measured),"min_ns":min(measured),"max_ns":max(measured),
                           "raw_samples":samples})
        total=sum(x["median_ns"] for x in layers)
        cells.append({"profile":profile,"kind":kind,"batch":batch,"layers":layers,
                      "sum_layer_medians_ns":total,
                      "layernorm_fraction":layers[3]["median_ns"]/total,
                      "rmsnorm_fraction":layers[1]["median_ns"]/total,
                      "scope":"Layer diagnostic, including hash/lifetime; sum is NOT original wholemodel timing"})
    assert not groups,groups.keys()
    return {"raw_rows":len(seen),"cells":cells}

def main():
    p=argparse.ArgumentParser()
    p.add_argument("--input",type=Path,required=True)
    p.add_argument("--metadata",type=Path,required=True)
    p.add_argument("--seed",type=int,default=27102901)
    p.add_argument("--repetitions",type=int,default=7)
    p.add_argument("--output",type=Path,required=True)
    a=p.parse_args()
    metadata=json.loads(a.metadata.read_bytes())
    for key in ["candidate_sha256","benchmark_identity","cpu_identity","profile_source_sha256"]:
        assert isinstance(metadata.get(key),str) and len(metadata[key])==64,key
    raw=a.input.read_bytes();report=parse(raw,a.seed,a.repetitions)
    report.update(scope="OWNED_LAYER_COST_DISCRIMINATOR_NOT_OFFICIAL_SCORE_OR_CURRENT_CHAMPION_COMPARISON",
                  metadata=metadata,input_sha256=hashlib.sha256(raw).hexdigest(),
                  parser_sha256=hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
                  output_boundary="hash/outputlifetime inside layer interval; preparationProfile outside; independent layer invocations",
                  native_complete_model_gain="UNKNOWN")
    a.output.write_text(json.dumps(report,indent=2)+"\n",encoding="utf-8")
    print(json.dumps({"cells":len(report["cells"]),"raw_rows":report["raw_rows"]},indent=2))

if __name__=="__main__":
    main()
