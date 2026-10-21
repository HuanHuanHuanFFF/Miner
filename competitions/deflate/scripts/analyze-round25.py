"""Use audited original-protocol analysis with the freshly captured official scorer."""
from pathlib import Path
import importlib
import round10_payability
ROOT=Path(__file__).resolve().parents[1]
round10_payability.SCORER_PATH=ROOT/'evidence/round25/official-rules-start/validator--scoring--pareto.py'
if __name__=='__main__':
    importlib.import_module('analyze-round18').main()
