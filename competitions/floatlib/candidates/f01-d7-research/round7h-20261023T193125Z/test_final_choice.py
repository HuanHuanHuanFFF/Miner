import importlib.util
from pathlib import Path
import unittest

s=importlib.util.spec_from_file_location('choice_under_test',Path(__file__).with_name('final-choice.py'))
c=importlib.util.module_from_spec(s);s.loader.exec_module(c)

class ChoiceTests(unittest.TestCase):
    pre={'new_candidate':'E5','new_sha256':'new','backup_candidate':'6c2d',
         'backup_sha256':'old','backup_first_clean_D_run':40044727137}
    def choice(self,full=True,ratio=.94,p05=.04,versus=.98,versus_p05=.005):
        return c.choose(self.pre,full,{'relative_normalized_ratio':ratio,'gain_p05':p05},
                        {'relative_normalized_ratio':versus,'gain_p05':versus_p05})
    def test_new_requires_all_four_original_conditions(self):
        self.assertEqual(self.choice()['candidate'],'E5')
        for change in ({'full':False},{'ratio':.97001},{'p05':0},{'versus':1},{'versus_p05':0}):
            with self.subTest(change=change):
                actual=self.choice(**change)
                self.assertEqual(actual['candidate'],'6c2d')
                self.assertEqual(actual['discovery'],40044727137)
    def test_backup_cannot_adopt_later_control_discovery(self):
        self.assertNotEqual(self.choice(versus=1.01)['discovery'],c.NEW_D)

if __name__=='__main__':unittest.main()
