"""One exact full-length D forward offer expansion; no budget or threshold sweep."""
from pathlib import Path
import argparse
import hashlib
import importlib
import json

ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'references/round24-public-552'
TARGET=ROOT/'candidates/r26-b-552-dense-forward'
PAIR={'parse.rs':'5adaaeac471b86128778bf6b67f786542f5c8e079adbf1160f0502309f7befb9',
      'Parse.lean':'51b5ea83cbad026c044b5c7812c9189231f5273cc0902342c850af02a1c0b592'}
NEW='''pub fn d_fill_nextl(lsym: &[u8; 512], nextl: &mut [u16; 512], flen: usize) {
    // One quality/time exchange: visit every length in each already offered interval.
    let mut l=0usize;
    while l<512{nextl[l]=(l+1)as u16;l+=1;}
}'''


def sha(raw):return hashlib.sha256(raw).hexdigest()


def generate():
    raw={name:(BASE/name).read_bytes() for name in PAIR}
    assert {name:sha(data) for name,data in raw.items()}==PAIR
    source=raw['parse.rs'].decode();fn=importlib.import_module('prepare-round24-extract-repro').fn
    old=fn(source,'d_fill_nextl');assert source.count('d_fill_nextl(')==2
    rust=source.replace(old,NEW,1).encode()
    assert rust.decode().replace(NEW,old,1).encode()==raw['parse.rs']
    importlib.import_module('r26-b-fix-shared-cache').spans(rust.decode())
    files={'parse.rs':rust,'Parse.lean':raw['Parse.lean']}
    receipt=json.loads((BASE/'source-receipt.json').read_bytes())
    manifest={'candidate':TARGET.name,'parent':BASE.relative_to(ROOT).as_posix(),'formal_parent_id':'552',
        'parent_hashes':PAIR,'hashes':{name:sha(data) for name,data in files.items()},'bytes':{name:len(data) for name,data in files.items()},
        'source_author_hotkey':receipt['author_hotkey'],'source_receipt':'references/round24-public-552/source-receipt.json',
        'source_receipt_sha256':sha((BASE/'source-receipt.json').read_bytes()),
        'mechanism':'D forward nextl becomes l+1 for all table entries: each existing candidate-provided lo..hi interval visits every length, rather than sparse code endpoints above flen8/16. This intentionally expands the graph and may change paths/prices/statistics/encoder quality.',
        'scope':'Only d_fill_nextl body. No new matcher/candidate/search/record format, no array/ring/chunk/price rule/route/budget/secondDP/encoder changes. Original fback/backward-endpoint logic and directskip paths retained.',
        'bounds':'Recovered l in original lo..hi with3<=l<=hi<=258, prefix of a byte-matched forward candidate or its original byte-checked backward extension at the same distance. fback100 truncated ranges also use nextl and become dense, while their full-endpoint relax_one stays unchanged. nextl[l]=l+1 progresses; lc modulo512, arrival modulo8192; livewindow258/CHUNK4096 reset rules unchanged.',
        'cost':'All added per-length ring comparisons/stores paid. OldB8 6.62M omitted terms is prior-trajectory workload context, not actualcandidate count, speed bound or output prediction. ActualfullD profile first.',
        'history':'R10routecfg explicitly retainedflen16/notfullreconstruction; R7seed1 endpoint frontend losesquality vsblock1 full frontend and totalcost tradeoff. No reuse claim of their measuredgain. Long-domain event proposal remainsNO_GO.',
        'quality_status':'UNKNOWN_UNTIL_ORIGINAL28ENCODER; expectedtokens differ, notequivalent optimization',
        'proof_status':'UNADAPTED_PARENT_DRAFT; DpNextl strictlyincreasing invariant still targeted, actualextractedloop signature/fullgate pending ifvaluable',
        'performance_status':'NOT_RUN; nativepureDphase costs first, no originalpaired performance',
        'formal_status':'NOT_SUBMITTED; formal/private/reward UNKNOWN','source_reversal':'Restore one functionbody -> byte-exact pinned552, checked locally.'}
    files['manifest.json']=(json.dumps(manifest,indent=2)+'\n').encode()
    assert all(len(value)<=524288 for name,value in files.items() if name!='manifest.json')
    return files,manifest


def main():
    parser=argparse.ArgumentParser();parser.add_argument('--check',action='store_true');args=parser.parse_args()
    files,manifest=generate();TARGET.mkdir(exist_ok=True)
    for name,raw in files.items():
        path=TARGET/name
        if args.check:assert path.read_bytes()==raw
        else:assert not path.exists() or path.read_bytes()==raw;path.write_bytes(raw)
    print(json.dumps({'candidate':TARGET.name,'hashes':manifest['hashes'],'bytes':manifest['bytes']}))


if __name__=='__main__':main()
