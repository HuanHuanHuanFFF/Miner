from pathlib import Path
H=Path(__file__).parent;C=H/'census';s=(C/'fp_replay-frozen.py').read_text(encoding='utf-8-sig')
needle='''        ka=[list(map(m.key,a))for a in left];kb=[list(map(m.key,b))for b in right]'''
replacement='''        def domain(v):
            return all((1<=((w>>23)&255)<=254) or (w&0x7fffffff)==0 for w in v)
        self.input_domain_by_id={id(v):domain(v)for v in left+right}
        self.counter['outside_operand_vectors']+=sum(not self.input_domain_by_id[id(v)] for v in left+right)
        self.counter['prepared_operand_vectors']+=len(left)+len(right)
        ka=[list(map(m.key,a))for a in left];kb=[list(map(m.key,b))for b in right]'''
assert s.count(needle)==1;s=s.replace(needle,replacement)
needle='''        if accepted:assert q==expected,(q,expected)
        self.counter[reason]+=1'''
replacement='''        if accepted:assert q==expected,(q,expected)
        old_accepted=accepted
        operand_ok=self.input_domain_by_id[id(a)] and self.input_domain_by_id[id(b)]
        proposal_ok=2<=((q>>23)&255)<=253 and (q&0x7fffff)!=0
        self.counter['old_checker_accept']+=old_accepted
        if old_accepted and not operand_ok:
            accepted=False;reason='narrow_operand_domain';self.counter['additional_reject']+=1
        elif old_accepted and not proposal_ok:
            accepted=False;reason='narrow_proposal_domain';self.counter['additional_reject']+=1
        self.counter['proposal_outside_interior_nonpower']+=not proposal_ok
        self.counter[reason]+=1'''
assert s.count(needle)==1;s=s.replace(needle,replacement)
s=s.replace("dest=H/f'fp-census-{a.root}.json'","dest=H/f'fp-census-narrow-{a.root}.json'")
s=s.replace("status='INTEGER_F64_CHECKER_REPLAY_OLD_SEEN_COHORT_ONLY'","status='CONDITIONAL_NARROW_GUARD_COVERAGE_OLD_SEEN_COHORT'")
s=s.replace("'No Lean proof or full12 gate'","'No Lean proof or full12 gate','New guards are only replayed here; frozen runtime unchanged'")
(C/'fp_replay-narrow-domain.py').write_text(s,encoding='utf-8',newline='\n')
(C/'narrow-domain-option-snapshot.json').write_bytes((H.parent/'fp-cost/PROOF-DOMAIN-OPTION.json').read_bytes())
print('Narrow-domain exact coverage replay prepared')
