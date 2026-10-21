"""REJECTED PRECONDITION: retained negative prototype, never dispatched.

The proposed transfer was based on a false pc_HB=16 assumption. Both relevant
32768-head paths use 15 hash bits. See 539-vs582-PC-source-audit.json.
"""
from pathlib import Path
from datetime import datetime, timezone
import importlib.util
import json
import re

ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round18'


def main():
    sp = importlib.util.spec_from_file_location('builder', ROOT / 'scripts/build-round18-start.py')
    builder = importlib.util.module_from_spec(sp)
    sp.loader.exec_module(builder)
    source = ROOT / 'references/round18-public-539'
    rust, lean = (source / 'parse.rs').read_text(), (source / 'Parse.lean').read_text()
    parent582 = (ROOT / 'candidates/r17-dna-nofold-proof1/parse.rs').read_text()
    assert re.search(r'pub const pc_HB:\s*u32\s*=\s*16;', parent582)
    old = 'if H == 262144 {46u32} else if H == 131072 {47u32} else if H == 65536 {48u32} else {49u32}'
    assert rust.count(old) == 1
    variants = [
        ('r18-539-key3-hash48', 'H == 32768 && km == 4294967040',
         'Only the existing three-byte masked PC keys use bits48..63mod32768; four-byte text keys retain539bits49..63.'),
        ('r18-539-all32-hash48', 'H == 32768',
         'All32768-head PC keys use the582bit window; compare with key3-only to isolate the text-versus-structured-key interaction.'),
    ]
    entries = []
    for name, condition, mechanism in variants:
        new = old.replace('else {49u32}', 'else if ' + condition + ' {48u32} else {49u32}')
        changed = rust.replace(old, new)
        assert changed.count(new) == 1
        entry = builder.write_candidate(
            name, 'public539', changed, lean, mechanism,
            'New539nativeauditfoundCSV+25588Bbutlargelean/bundlegainsagainst582. BothprogramsalreadycontainPC.run1cwithmatchingtextparameters; a verifiedsourcecomparisonrevealedthat539uses15highhashbitsfor32768headswhere582takes16bitsandreducesmodH. Thisboundedkey-representationtransfertestsqualitycomplementarityatunchangedcapacity,depth,insertionandemission. It is not the older32bitmultiplicationhash32variant.',
            {'source': 'references/round18-public-539/source-receipt.json',
             'other_hash': 'candidates/r17-dna-nofold-proof1/parse.rs',
             'evidence': 'evidence/round18/public539-bd-decision.json',
             'ownership': 'Original539and582authorsretained; onlythehash-bitconditionisnew.'})
        entry.update(anchor='public539', comparison_baseline='public539', native_decode_reference='public539')
        entries.append(entry)
    spec = json.loads((E / 'public539-bd-native.json').read_bytes())
    for name in ('r18_function_profile', 'r15_profile_entry', 'r15_profile_functions'):
        spec.pop(name)
    spec['entries'] += entries
    spec['screen_orders'] = [[e['name'] for e in spec['entries']], [e['name'] for e in reversed(spec['entries'])]]
    spec['snapshot_pages'] = 'evidence/round18/official-extension-start/pareto-pages.json'
    spec['description'] = ('BG nativeboundedhash-bitinteraction: twochangedversionsofunmodified539, 28fileoriginalencoderanddecode, '
                           '539/582/514referencebytes. Key3-onlyversusall32768-headkeysisolateswhichpublicqualitydeltasarehashwindowdriven. '
                           'Cap15minutes. Evaluateactualbytes/tokensandcurrentfrontiercoordinategapbeforeoriginaltotal-timeorfullproofinvestment; '
                           'do notpresumetheold53921percentreward, zeroheadercostorprivategeneralization. Proofdraftretainsoriginalgenericboundslemma; fullgateunknown.')
    (E / 'hash-bg-native.json').write_bytes((json.dumps(spec, indent=2) + '\n').encode())
    (E / 'hash-bg-preflight.json').write_bytes((json.dumps({
        'declared_at_utc': datetime.now(timezone.utc).isoformat(),
        'gap': 'Which539versus582publicqualitydifferencescomefromPCkeybitselectionratherthansearchbudgetorclassdispatch?',
        'material_change': 'Use582hashbitwindowonlyforthree-bytekeysorforall32768-headkeys; allothersearch/emissionconditionsunchanged.',
        'minimum_operation': 'TwofrozenRustvariants, original28-fileencoder/decode, exact539and582comparisons.',
        'decision_boundary': 'Meaningfulqualityspaceearnsoriginalpairedtotal-timeandscorerreplay; lostqualityorcontradictoryfilesstopthisexactversion. Hash48doesnotautomaticallyimprovespeed.',
        'proof_preflight': '539PC.slot_of_m_specalreadyusesstepandbranchsplittingandprovesmodHbounds. AdditionalH/kmbranchmaybereusablebuthasnotcompiled; no newaxiomorfile-sizeincreaseinLean.',
        'cap_runner_minutes': 15, 'fixed_deadline_utc': '2026-10-10T04:32:51+00:00',
    }, indent=2) + '\n').encode())
    print(json.dumps(entries))


if __name__ == '__main__':
    raise SystemExit('REJECTED: false hash-width premise; no candidate or CI was created.')
