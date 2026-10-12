"""R26 A: one frozen symbol-coverage rule and one distance-activation rule.

Preparation is lightweight token arithmetic. Only the runner executes the pinned
original encoder; this is an untimed decision experiment, not a parser result.
"""
from pathlib import Path
import argparse
import hashlib
import importlib
import json
import os
import struct
import subprocess
import sys
import zlib

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / 'evidence/round25/38132193695/counts-k2-native/diagnostics/r25-tiny-encoder'
OUT = ROOT / 'evidence/round26/route-a/replay'
HELP = importlib.import_module('research-round25-tiny-encoder')
FILES = HELP.FILES
LABELS = ['combo', 'strong', 'fixed5', 'coverage5', 'distance12']
PARSER = ROOT / 'candidates/r25-astra-tiny-pc8-proof1/parse.rs'
PARSER_SHA = '5c20b99cf52ac8e2f047b4e2e83be974b1f9b1f21b23d54ccccb25c58b891f00'
LBASE = [3,4,5,6,7,8,9,10,11,13,15,17,19,23,27,31,35,43,51,59,67,83,99,115,131,163,195,227,258]
DBASE = [1,2,3,4,5,7,9,13,17,25,33,49,65,97,129,193,257,385,513,769,1025,1537,2049,3073,4097,6145,8193,12289,16385,24577]


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def dump(path, value):
    path.write_bytes((json.dumps(value, indent=2) + '\n').encode())


def decode(tokens):
    data = bytearray()
    for token in tokens:
        if token < 256:
            data.append(token)
        else:
            assert 16777216 <= token < 25165824
            value = token - 16777216
            distance, length = value // 256 + 1, value % 256 + 3
            assert distance <= len(data)
            for _ in range(length):
                data.append(data[-distance])
    return bytes(data)


def pack(tokens):
    return b''.join(struct.pack('<I', t) for t in tokens)


def code(value, bases):
    return max(i for i, base in enumerate(bases) if base <= value)


def transform(tokens, data, label):
    coverage = [0] * 29
    for t in tokens:
        if t >= 16777216:
            length = (t - 16777216) % 256 + 3
            coverage[code(length, LBASE)] += length
    # The inherited 4-byte probe's shortest match symbol and 258 are mandatory. Remaining three are
    # chosen by covered raw bytes, then lowest code index. No output is queried.
    chosen = sorted([1, 28] + sorted([i for i in range(28) if i != 1], key=lambda i: (-coverage[i], i))[:3])
    allowed_codes = chosen if label == 'coverage5' else [8,12,18,25,28]
    allowed = [n for n in range(3,259) if code(n,LBASE) in allowed_codes]
    lens = [max((n for n in allowed if n <= r), default=0) for r in range(259)]
    result, events, used, position = [], [], set(), 0
    for t in tokens:
        if t < 256:
            result.append(t)
            position += 1
            continue
        value = t - 16777216
        distance, length = value // 256 + 1, value % 256 + 3
        dc = code(distance, DBASE)
        start, left, pieces = position, length, []
        accepted = label != 'distance12' or dc in used or length >= 12
        if label == 'distance12':
            if accepted:
                result.append(t)
                pieces.append(length)
                position += length
                left = 0
                used.add(dc)
        else:
            while lens[left] >= 3:
                n = lens[left]
                result.append(16777216 + (distance - 1) * 256 + n - 3)
                pieces.append(n)
                position += n
                left -= n
        result.extend(data[position:position+left])
        position += left
        events.append({'position':start,'length':length,'distance':distance,'distance_code':dc,
                       'accepted':accepted,'pieces':pieces,'literal_tail':left})
    assert position == len(data) and decode(result) == data
    detail = {'source_length_coverage':coverage, 'selected_length_codes':allowed_codes if label != 'distance12' else None,
              'literal_tail_bytes':sum(e['literal_tail'] for e in events), 'matches_in':len(events),
              'matches_out':sum(len(e['pieces']) for e in events), 'events':events}
    if label == 'distance12':
        activation = []
        for dc in sorted({e['distance_code'] for e in events}):
            es = [e for e in events if e['distance_code'] == dc]
            rejects = [e for e in es if not e['accepted']]
            accepts = [e for e in es if e['accepted']]
            activation.append({'code':dc,'state':'never_enabled' if not accepts else 'delayed' if rejects else 'immediate',
                               'rejected_matches':len(rejects),'rejected_span':sum(e['length'] for e in rejects),
                               'accepted_matches':len(accepts),'accepted_span':sum(e['length'] for e in accepts)})
        detail['activation'] = activation
    return result, detail


def prepare():
    receipt = json.loads((BASE / 'receipt.json').read_bytes())
    assert receipt['status'] == 'VERIFIED_UNTIMED_ORIGINAL_OBSERVER_BYTES_DECODE_AND_PRIOR_IDENTITY'
    assert receipt['codec_sha256'] == HELP.CODEC_SHA and receipt['token_sha256'] == HELP.TOKEN_SHA
    assert sha(PARSER.read_bytes()) == PARSER_SHA
    parser_text = PARSER.read_text()
    assert 'if n==12000 {return 23;}' in parser_text and 'if n==28000 {return 22;}' in parser_text
    assert 'else if k==23{p125_row12(input,out)}' in parser_text
    OUT.mkdir(parents=True, exist_ok=True)
    rows = []
    for file in FILES:
        frozen = {}
        for source in ['combo','tiny_pc8']:
            source_row = next(r for r in receipt['rows'] if r['candidate'] == source and r['file'] == file)
            raw = (BASE / 'tokens-and-output' / (source + '-' + file + '.tokens')).read_bytes()
            assert sha(raw) == source_row['tokens_sha256']
            tokens = [t[0] for t in struct.iter_unpack('<I',raw)]
            data = decode(tokens)
            assert sha(data) == source_row['input_sha256']
            frozen[source] = tokens
        assert decode(frozen['combo']) == data
        assert len(data) in [12000,28000]
        active, route = len(data) == 12000, 23 if len(data) == 12000 else 22
        input_path = OUT / (file + '.input')
        input_path.write_bytes(data)
        for label in LABELS:
            detail = {}
            if label in ['combo','strong']:
                tokens = frozen['combo' if label == 'combo' else 'tiny_pc8']
            elif active:
                tokens, detail = transform(frozen['tiny_pc8'],data,label)
            else:
                tokens, detail = frozen['tiny_pc8'], {'inactive_control':True,'transform_skipped':True}
            raw = pack(tokens)
            token_path = OUT / (label + '-' + file + '.tokens')
            token_path.write_bytes(raw)
            row = {'label':label,'file':file,'input_path':input_path.relative_to(ROOT).as_posix(),
                   'input_sha256':sha(data),'input_bytes':len(data),'tokens_path':token_path.relative_to(ROOT).as_posix(),
                   'tokens_sha256':sha(raw),'tokens':len(tokens),'valid_decode':True, 'detail':detail}
            row.update(inherited_route=route,component_active=active)
            if label in ['combo','strong']:
                prior = next(r for r in receipt['rows'] if r['candidate'] == ('combo' if label == 'combo' else 'tiny_pc8') and r['file'] == file)
                row['prior_output_sha256'] = prior['output_sha256']
            rows.append(row)
    spec = {'status':'VERIFIED_FROZEN_TOKEN_RULES_AND_FINITE_DECODE_ONLY','source_receipt':(BASE/'receipt.json').relative_to(ROOT).as_posix(),
            'source_receipt_sha256':sha((BASE/'receipt.json').read_bytes()),'codec_sha256':HELP.CODEC_SHA,'token_sha256':HELP.TOKEN_SHA,
            'rules':{'coverage5':'Keep code1 (length4, inherited probe minimum) and code28; choose exactly three remaining length codes by descending strong-token covered bytes, ascending code index ties; greedily split and literal remainder.',
                     'distance12':'Keep previously enabled distance codes; first activation requires original match length >= 12. Refused span becomes literals and does not enable the code.'},
            'parser_path':PARSER.relative_to(ROOT).as_posix(),'parser_sha256':PARSER_SHA,
            'native':'NOT_RUN','time':'NOT_RUN','proof':'NOT_RUN','rows':rows}
    dump(OUT/'fixture.json',spec)
    print(json.dumps({'status':spec['status'],'rows':[{k:r[k] for k in ['label','file','tokens']} for r in rows]},indent=2))


def preflight(spec=None):
    if spec is not None:
        assert spec.get('r26_a_replay') is True and not spec.get('native_encoder')
        assert not spec.get('gate_candidates') and not spec.get('extract_candidates')
    fixture = json.loads((OUT/'fixture.json').read_bytes())
    assert fixture['status'] == 'VERIFIED_FROZEN_TOKEN_RULES_AND_FINITE_DECODE_ONLY'
    assert sha(PARSER.read_bytes()) == fixture['parser_sha256'] == PARSER_SHA
    assert sha((ROOT/fixture['source_receipt']).read_bytes()) == fixture['source_receipt_sha256']
    for row in fixture['rows']:
        raw = (ROOT/row['tokens_path']).read_bytes()
        data = (ROOT/row['input_path']).read_bytes()
        assert sha(raw) == row['tokens_sha256'] and sha(data) == row['input_sha256']
        assert decode([x[0] for x in struct.iter_unpack('<I',raw)]) == data
    assert {(r['label'],r['file']) for r in fixture['rows']} == {(l,f) for l in LABELS for f in FILES}
    return fixture


HARNESS = r'''
#![allow(dead_code)]
#[path=TOKEN] mod token;
#[path=CODEC] mod codec;
#[path=OBSERVER] mod observed;
#[path=PARSER_PATH] mod parser;
fn main(){
  let args:Vec<_>=std::env::args().collect();
  let root=std::path::Path::new(&args[1]);let spool=std::path::Path::new(&args[2]);
  let cases:&[(&str,&str,&str,&str,usize)]=&[CASES];
  for &(label,file,tp,ip,route) in cases {
    let data=std::fs::read(root.join(ip)).unwrap();
    let raw=std::fs::read(root.join(tp)).unwrap();
    assert_eq!(raw.len()%4,0);
    let ts:Vec<u32>=raw.chunks_exact(4).map(|v|u32::from_le_bytes(v.try_into().unwrap())).collect();
    let mut decoded=Vec::new();
    for &t in &ts {match token::decode(t){token::Token::Literal(x)=>decoded.push(x),token::Token::Match{dist,len}=>{assert!(dist as usize<=decoded.len());for _ in 0..len{let x=decoded[decoded.len()-dist as usize];decoded.push(x);}},_=>panic!("invalid token")}}
    assert_eq!(decoded,data);
    assert_eq!(parser::route(&data),route);
    if label=="strong" || route!=23 {let mut fresh=vec![0;data.len()];let count=parser::parse(&data,&mut fresh);fresh.truncate(count);assert_eq!(fresh,ts);}
    println!("R25_CONTEXT {} {}",label,file);
    let original=codec::encode(&ts,data.len()).unwrap();let observed=observed::encode(&ts,data.len()).unwrap();
    assert_eq!(original,observed);
    std::fs::write(spool.join(format!("{}-{}.deflate",label,file)),&original).unwrap();
    println!("R26_RESULT {} {} {} {}",label,file,ts.len(),original.len());
  }
}
'''


def captured(argv,log,seconds):
    proc = subprocess.run(argv,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,timeout=seconds)
    log.write_text(proc.stdout)
    assert proc.returncode == 0, str(log)
    return proc.stdout


def run():
    assert os.environ.get('GITHUB_ACTIONS') == 'true' and os.environ.get('RUNNER_OS') == 'Linux'
    from round4 import validate
    spec = validate(os.environ['ROUND4_SPEC'])
    fixture = preflight(spec)
    upstream = Path(os.environ['DEFLATE_ROOT'])
    codec = upstream/'validator/measure/src/deflate.rs'
    token = codec.with_name('token.rs')
    codec_raw, token_raw = codec.read_bytes(), token.read_bytes()
    assert sha(codec_raw) == HELP.CODEC_SHA and sha(token_raw) == HELP.TOKEN_SHA
    build = Path(os.environ['RUNNER_TEMP'])/'r26-a-replay-build'
    build.mkdir()
    out = Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r26-a-replay'
    out.mkdir(parents=True)
    spool = out/'output'
    spool.mkdir()
    observer = build/'observed.rs'
    observer_raw = HELP.instrument(codec_raw)
    observer.write_bytes(observer_raw)
    cases = ',\n'.join('('+','.join(json.dumps(r[k]) for k in ['label','file','tokens_path','input_path'])+','+str(r['inherited_route'])+')' for r in fixture['rows'])
    harness = HARNESS.replace('TOKEN',json.dumps(str(token))).replace('CODEC',json.dumps(str(codec))).replace('OBSERVER',json.dumps(str(observer))).replace('PARSER_PATH',json.dumps(str(PARSER))).replace('CASES',cases)
    driver = build/'main.rs'
    driver.write_text(harness)
    (out/'harness.rs').write_text(harness)
    (out/'deflate-observed.rs').write_bytes(observer_raw)
    result = {'status':'STARTED_UNTIMED_ORIGINAL_ENCODER_REPLAY','git_sha':os.environ['GITHUB_SHA'],'run_id':os.environ['GITHUB_RUN_ID'],
              'batch':os.environ['ROUND4_SPEC'],'fixture_sha256':sha((OUT/'fixture.json').read_bytes()),'codec_sha256':HELP.CODEC_SHA,
              'parser_sha256':PARSER_SHA,
              'token_sha256':HELP.TOKEN_SHA,'observer_sha256':sha(observer_raw),'harness_sha256':sha(harness.encode()),
              'scope':'Frozen token transform; does not measure parser cost, timing, fold feedback, full correctness, private quality or official share.'}
    report = out/'receipt.json'
    dump(report,result)
    try:
        binary = build/'check'
        captured(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],out/'compile.log',180)
        log = captured([str(binary),str(ROOT),str(spool)],out/'run.log',180)
        traces, current = {}, None
        for line in log.splitlines():
            if line.startswith('R25_CONTEXT '):
                _, label, file = line.split()
                current = (label,file)
                assert current not in traces
                traces[current] = {'trees':[],'blocks':[],'choices':[]}
            elif line.startswith('R25_TREE '):
                _, n, bits, arrays = line.split(' ',3)
                freq, lengths, work = HELP.read_arrays(arrays)
                assert len(freq) == len(lengths) == int(n) and len(work) == len(HELP.TREE_FIELDS)
                traces[current]['trees'].append({'alphabet_size':int(n),'max_bits':int(bits),'frequency':freq,'code_lengths':lengths,'work':dict(zip(HELP.TREE_FIELDS,work))})
            elif line.startswith('R25_BLOCK '):
                vals=list(map(int,line.split()[1:]))
                assert len(vals)==8
                traces[current]['blocks'].append(dict(zip(['items','raw_bytes','hlit','hdist','hclen','dynamic_bits','fixed_bits','stored_bits'],vals)))
            elif line.startswith('R25_CHOICE '):
                traces[current]['choices'].append(line.split()[1])
        rows=[]
        for row in fixture['rows']:
            label,file=row['label'],row['file']
            encoded=(spool/(label+'-'+file+'.deflate')).read_bytes()
            data=(ROOT/row['input_path']).read_bytes()
            assert zlib.decompress(encoded,-15)==data
            if 'prior_output_sha256' in row:
                assert sha(encoded)==row['prior_output_sha256']
            summary=HELP.token_summary((ROOT/row['tokens_path']).read_bytes(),codec_raw.decode())
            trace=traces[(label,file)]
            assert summary['produced_bytes']==len(data)
            assert len(trace['trees'])==3 and len(trace['blocks'])==len(trace['choices'])==1
            assert trace['trees'][0]['frequency']==summary['litlen_frequency_including_eob']
            assert trace['trees'][1]['frequency']==summary['distance_frequency']
            assert trace['blocks'][0]['items']==summary['tokens']
            rows.append({**row,'output_sha256':sha(encoded),'output_bytes':len(encoded),'token_summary':summary,**trace})
        assert codec.read_bytes()==codec_raw and token.read_bytes()==token_raw
        result.update(status='VERIFIED_UNTIMED_ORIGINAL_ENCODER_REPLAY_AND_DUAL_DECODE',rows=rows)
    except Exception as exc:
        result.update(status='FAILED_OR_INCOMPLETE_REPLAY',error_type=type(exc).__name__,error=str(exc))
        dump(report,result)
        raise
    dump(report,result)
    print(json.dumps({'status':result['status'],'rows':[{'label':r['label'],'file':r['file'],'bytes':r['output_bytes'],'symbols':[t['work']['live_symbols'] for t in r['trees']]} for r in rows]},indent=2))


if __name__ == '__main__':
    parser=argparse.ArgumentParser()
    parser.add_argument('--prepare',action='store_true')
    parser.add_argument('--self-check',action='store_true')
    args=parser.parse_args()
    if args.prepare:
        prepare()
    elif args.self_check:
        fixture=preflight()
        print(json.dumps({'status':'VERIFIED_LIGHTWEIGHT_FIXTURE_PREFLIGHT','rows':len(fixture['rows'])}))
    else:
        run()
