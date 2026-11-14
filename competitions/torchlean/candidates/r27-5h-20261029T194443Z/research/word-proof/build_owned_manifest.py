"""Inventory owned technical artifacts without Git, network or source rebuilds."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

ROOT = Path(__file__).resolve().parent
OUTPUT = ROOT/'PUBLIC-OWNED-MANIFEST.json'
ALLOWED = ('.lean', '.lean.inc', '.py', '.json', '.md', '.txt')
ACCEPTED = {
    '2612bcaeec659ba278695d345b224471887dac6842567eaaa39d3d738cac0aea':
        'Runtime helper elaborated; wrapper root only, run40945451009.',
    'c21efe437d955f7356671ef35c2a642634baa2f7a63e7b20d31fdfdf1102ba83':
        'Exact standalone modular helper accepted with4allowed-axiom roots, run40964374666. No actual Float kernel proof.'
}
FAILED = {
    '00c3ee19219dfe8e0d74215a69fbad09ddad042c457782779a0cf7d44c6b5b55':
        'Full helper failed; unknownabs_add then downstream timeout, run40948208583.',
    '40bd2cd7fdc74f67f6e7a73a688c609fdde00096561394019ae8fc5186e76b1b':
        'Full helper failed; Int addition orientation mismatch, run40952423982.'
}


def main():
    files, excluded = [], []
    resolved = ROOT.resolve()
    for path in sorted(ROOT.rglob('*')):
        if not path.is_file() or path == OUTPUT:
            continue
        rel = path.relative_to(ROOT).as_posix()
        if any(part in {'__pycache__', 'private', '.secrets', '.credentials'} for part in path.relative_to(ROOT).parts):
            excluded.append({'file':rel,'reason':'Excluded cache or private directory.'})
            continue
        if not path.resolve().is_relative_to(resolved):
            excluded.append({'file':rel,'reason':'Resolved file is outside role ownership.'})
            continue
        if path.name in {'Kernel.lean', 'Submission.c'} or not rel.endswith(ALLOWED):
            excluded.append({'file':rel,'reason':'Not an owned technical artifact type; no whole upstream Kernel/C allowed.'})
            continue
        raw = path.read_bytes()
        digest = hashlib.sha256(raw).hexdigest()
        state = ACCEPTED.get(digest) or FAILED.get(digest)
        if state is None:
            state = ('Source only; no independent Lean/native acceptance inherited.'
                     if rel.endswith(('.lean','.lean.inc'))
                     else 'Technical source/model/receipt/index; individual evidence scope remains authoritative.')
        files.append({'file':rel,'bytes':len(raw),'sha256':digest,'scope':state})
    result = {'at_utc':datetime.now(timezone.utc).isoformat(),
              'state':'OWNED_ARTIFACT_INVENTORY_NOT_PROJECT_GATE_OR_PUBLICATION',
              'owner':'R27 word-proof role','files':files,'file_count':len(files),
              'total_bytes':sum(f['bytes'] for f in files),'excluded':excluded,
              'publication_boundary':'Only self/peer-authored technical sources, finite models, receipts and handoffs. No whole unknown-license upstream Kernel/generatedC, private Pro chats, raw human chat or credentials copied by this role.',
              'Git_CI_owner':'Droot; this role did not commit,push,dispatchCI or run localLean/native.',
              'important_external_acceptance':'D reciprocal_u64_v4/013a5fd2 accepted4roots in40967910604; own ReciprocalNatCore file was not separately compiled.',
              'mutable_indexes':'HANDOFF/status/ledger/current requests may change during closeout; regenerate this manifest after their final update.'}
    OUTPUT.write_text(json.dumps(result,indent=2),encoding='utf8')
    for entry in files:
        raw = (ROOT/entry['file']).read_bytes()
        assert len(raw) == entry['bytes'] and hashlib.sha256(raw).hexdigest() == entry['sha256']
    print(json.dumps({'files':len(files),'bytes':result['total_bytes'],'excluded':len(excluded),'verified_current_file_hashes':True}))


if __name__ == '__main__':
    main()
