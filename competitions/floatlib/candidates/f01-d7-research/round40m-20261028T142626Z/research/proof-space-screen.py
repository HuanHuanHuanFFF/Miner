"""Conservative proof-only source-size screen. No Lean/CI, no runtime mutation."""
from pathlib import Path
import hashlib,re,json,datetime,argparse
from collections import Counter
ROOT=next(p for p in Path(__file__).resolve().parents if (p/'AGENTS.md').is_file())
HERE=Path(__file__).resolve().parent
ap=argparse.ArgumentParser();ap.add_argument('--input');ap.add_argument('--stem',default='proof-space');ap.add_argument('--keep',action='append',default=[]);args=ap.parse_args()
source=Path(args.input).resolve() if args.input else ROOT/'competitions/floatlib/candidates/f01-r22-dev-indexed8-cost1/Kernel.lean'
assert source.is_relative_to(ROOT/'competitions/floatlib/candidates')
assert re.fullmatch(r'[a-z0-9-]+',args.stem)
raw=source.read_bytes()
if not args.input:assert hashlib.sha256(raw).hexdigest()=='8e27baf70ce7e3f10b669cc9f59d66d5fffaa17ee3dc6df934f3229139a5b0dd'
text=raw.decode();removed=[]
start=re.compile(r"(?m)^(?:(?:private|protected) )?(?:theorem|lemma)\s+([A-Za-z_][A-Za-z0-9_']*)\b")
boundary=re.compile(r'(?m)^(?:/[-*]|--|@\[|(?:(?:noncomputable|private|protected) )?(?:def|abbrev|theorem|lemma|structure|inductive|instance|example)\b|namespace |section\b|end\b|open |set_option |attribute |#)')
for iteration in range(80):
    selected=None
    counts=Counter(re.findall(r"[A-Za-z_][A-Za-z0-9_']*",text))
    for match in start.finditer(text):
        name=match.group(1)
        if name in {'add_spec','mul_spec','sum_spec','bmm_spec',*args.keep}:continue
        if counts[name]!=1:continue
        previous=next((x.strip() for x in reversed(text[:match.start()].splitlines()) if x.strip()),'')
        if previous.startswith(('@[','set_option')):continue
        end_match=boundary.search(text,match.end());end=end_match.start() if end_match else len(text)
        body=text[match.start():end]
        if ':=' not in body or ' by' not in body:continue
        if any(x in body for x in ('@[','attribute ','#','where\n')):continue
        selected=(match.start(),end,name,body);break
    if not selected:break
    a,b,name,body=selected
    removed.append(dict(iteration=iteration,name=name,bytes=len(body.encode()),sha256=hashlib.sha256(body.encode()).hexdigest(),body=body))
    text=text[:a]+text[b:]
# Deduplicate only byte-identical whole legal notices, retain a complete original.
notices=re.findall(r'/\-\nMIT License[\s\S]*?\-/',text)
legal_removed=0
if len(notices)==2 and notices[0]==notices[1]:
    at=text.rfind(notices[1]);text=text[:at]+text[at+len(notices[1]):];legal_removed=len(notices[1].encode())
compact=''.join(x for x in text.splitlines(keepends=True) if x.strip())
(HERE/(args.stem+'-base.NOT_RUN.lean')).write_text(compact,encoding='utf-8',newline='')
receipt=dict(checked_at_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),source=str(source.relative_to(ROOT)),source_sha256=hashlib.sha256(raw).hexdigest(),source_bytes=len(raw),
 output_bytes=len(compact.encode()),output_sha256=hashlib.sha256(compact.encode()).hexdigest(),headroom=256000-len(compact.encode()),removed_proof_count=len(removed),removed_proofs=removed,
 duplicate_legal_bytes_removed=legal_removed,complete_legal_notice_preserved=bool(notices),
 rule='Delete only theorem/lemma bodies whose leaf identifier occurs once, no attributes, keep all4 public *_spec; iterate dependency leaves. No def/structure/abbrev removed. Dedup two exact MIT blocks and remove blank lines.',
 limitation='NOT_RUN. Lexical name count is a source screen, not elaboration/dependency proof. Implicit automation resolution and namespace declarations require original gate; no correctness or speed claim.')
(HERE/(args.stem+'-screen.json')).write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:v for k,v in receipt.items() if k not in {'removed_proofs','rule','limitation'}}))
