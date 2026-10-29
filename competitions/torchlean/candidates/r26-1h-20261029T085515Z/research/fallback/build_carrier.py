from pathlib import Path
import datetime, hashlib, json, re

root = Path(__file__).resolve().parent
parts = [root / 'WordBlockRuntime.lean', root / 'IndexedInvariant.lean.inc']
optional = [root / 'FactorBridge.lean.inc', root / 'BlockComposition.lean.inc']
parts += [p for p in optional if p.exists()]
source = '\n'.join(p.read_text(encoding='utf-8-sig') for p in parts)
out = root / 'WordBlockCarrier.lean'
out.write_text(source, encoding='utf-8', newline='\n')
receipt = {
    'at_utc': datetime.datetime.now(datetime.timezone.utc).isoformat(),
    'status': 'SOURCE_ASSEMBLED_NOT_COMPILED',
    'output': out.name,
    'sha256': hashlib.sha256(out.read_bytes()).hexdigest(),
    'bytes': out.stat().st_size,
    'parts': {p.name: hashlib.sha256(p.read_bytes()).hexdigest() for p in parts},
    'imports': re.findall(r'^import\s+(.+)$', source, re.M),
    'forbidden_tokens': {s: bool(re.search(r'\b' + s + r'\b', source))
                         for s in ('sorry', 'admit', 'axiom', 'unsafe', 'native_decide', 'bv_decide')},
    'local_compile': 'NOT_RUN',
    'CI_owner': 'Droot',
}
(root / 'carrier-receipt.json').write_text(json.dumps(receipt, indent=2) + '\n', encoding='utf-8')
print(json.dumps(receipt, indent=2))
