from pathlib import Path

here = Path(__file__).resolve().parent
s = (here / 'IndexedPrefix.lean').read_text(encoding='utf-8')
pairs = [
    ('namespace Submission.R23IndexedPrefix', 'namespace Submission.R23NatPrefix'),
    ('end Submission.R23IndexedPrefix', 'end Submission.R23NatPrefix'),
    ('open R22IndexedResident8', 'open R22Resident8'),
    ('    (h : BlockBounds p n a c A.size cache.size)\n', ''),
    ('tiles p n a b c A B cache h', 'tiles p n a b c A B cache'),
    ('rows4 p n a b c A B cache h out', 'rows4 p n a b c A B cache out'),
    ('    (h : RowBounds m n p b A cache) : Prop :=', '    : Prop :='),
    (' A B cache (h r))', ' A B cache)'),
    ('    (h : RowBounds m n p b A cache) (hr : BlockReads f start m n p b A B cache h)',
     '    (hr : BlockReads f start m n p b A B cache)'),
    ('blocks m n p b A B cache h out', 'blocks m n p b A B cache out'),
    (' A B cache (h r) (hr r) acc ha', ' A B cache (hr r) acc ha'),
    (' (h : RowBounds m n p b A.toArray cache)', ''),
    ('A.toArray B.toArray cache h)', 'A.toArray B.toArray cache)'),
    ('rows m n p b A.toArray B.toArray cache h out', 'rows m n p b A.toArray B.toArray cache out'),
    ('A.toArray B.toArray cache h hr out ho', 'A.toArray B.toArray cache hr out ho'),
    (' (h : ∀ b : Fin batch, RowBounds m n p b.val A.toArray cache)', ''),
    ('A.toArray B.toArray cache (h b))', 'A.toArray B.toArray cache)'),
    ('cache (h b) (hr b) acc ha', 'cache (hr b) acc ha'),
    ('A.toArray B.toArray cache h⟩', 'A.toArray B.toArray cache⟩'),
    ('A.toArray B.toArray cache h,', 'A.toArray B.toArray cache,'),
    ('A B cache h hr', 'A B cache hr'),
]
for a, b in pairs:
    assert a in s, a
    s = s.replace(a, b)
s = s.replace('Exact indexed8 runtime', 'Exact Nat resident8 fallback runtime')
(here / 'NatPrefix.lean').write_text(s, encoding='utf-8', newline='\n')
print({'bytes': len(s.encode()), 'path': str(here/'NatPrefix.lean')})
