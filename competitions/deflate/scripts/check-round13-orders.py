"""Check frozen order plans cannot omit/duplicate a control or a candidate."""
import copy
from round4 import screen_order

def main():
    names=['parent','candidate','identical-shadow']
    old={'screen_blocks':2}
    assert screen_order(old,1,names)==names and screen_order(old,2,names)==names[::-1]
    spec={'screen_blocks':4,'screen_orders':[
        ['parent','candidate','identical-shadow'],['identical-shadow','candidate','parent'],
        ['candidate','parent','identical-shadow'],['identical-shadow','parent','candidate']]}
    assert all(screen_order(spec,i,names)==spec['screen_orders'][i-1]for i in range(1,5))
    for change in('duplicate','omit','wrong_block_count'):
        bad=copy.deepcopy(spec)
        if change=='duplicate':bad['screen_orders'][2][0]='parent'
        elif change=='omit':bad['screen_orders'][2].pop()
        else:bad['screen_orders'].pop()
        try:screen_order(bad,1,names)
        except AssertionError:pass
        else:raise AssertionError('Invalid experiment plan accepted: '+change)
    print('PASS original reversal preserved; frozen permutations retained; missing/duplicate controls and blocks refused')

if __name__=='__main__':main()
