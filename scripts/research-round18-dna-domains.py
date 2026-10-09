"""Actual public DNA alphabet and original mixed-hash collision diagnostic."""
from pathlib import Path
from collections import Counter
import hashlib,json,os

def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    path=Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1/genome.fasta';raw=path.read_bytes();four=set(b'ACGT');six=set(b'ACGTN\n');sets={};counts=Counter();unique=set()
    for i in range(max(0,len(raw)-7)):
        seq=raw[i:i+6];domain='four'if all(b in four for b in seq)else'six_only'if all(b in six for b in seq)else'other';counts[domain]+=1;unique.add(seq)
        key=((int.from_bytes(seq,'big')*0x9E3779B97F4A7C15)&((1<<64)-1))>>48
        bucket=sets.setdefault(key,{});bucket[seq]=domain
    report={'status':'VERIFIED_PUBLIC_GENOME_PREFIX_COUNTS','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'input_sha256':hashlib.sha256(raw).hexdigest(),'raw_bytes':len(raw),'byte_counts':{str(k):v for k,v in sorted(Counter(raw).items())},'prefix_domain_counts':dict(counts),'distinct_six_byte_prefixes':len(unique),'original_hash_occupied_buckets':len(sets),'original_extra_distinct_prefixes_in_collision_buckets':sum(len(v)-1 for v in sets.values()),'original_buckets_mixing_four_and_other_domains':sum('four'in v.values()and any(d!='four'for d in v.values())for v in sets.values()),'scope':'Untimed actual public-prefix census and the original arithmetic hash. Counts do not measure dynamic overwrite frequency, parse quality, speed, private transfer or payability.'}
    out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r18-dna-domains';out.mkdir(parents=True);(out/'counts.json').write_text(json.dumps(report,indent=2)+'\n');print(json.dumps({k:v for k,v in report.items()if k!='byte_counts'}))

if __name__=='__main__':main()
