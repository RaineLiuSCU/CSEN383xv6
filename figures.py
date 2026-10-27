import matplotlib
import pandas as pd
from IPython.display import display

lottery_results = [[[8,7,4,1],[10,5,4,1],[10,7,2,1],[12,3,4,1],[10,6,2,1]], [[22,13,3,2],[18,13,4,5],[20,9,8,3],[22,13,4,1],[21,8,6,5]],
                   [[35,13,9,3],[28,16,12,4],[33,16,7,4],[31,21,4,4],[33,15,9,3]],[[37,21,12,10],[42,20,12,6],[41,21,14,4],[46,22,9,3],[43,23,9,5]],
                   [[51,31,12,6],[59,17,15,9],[52,29,13,6],[58,22,12,8],[51,27,12,10]]]
dfs = []
finaldf = pd.DataFrame(columns=["8 tickets", "4 tickets", "2 tickets", "1 ticket"])
for i in range(5):
    df = pd.DataFrame(lottery_results[i], columns = ["8 tickets", "4 tickets", "2 tickets", "1 ticket"], index=["run1","run2","run3","run4","run5"])
    finaldf.loc[str(20+20*i)+" ticks"] = df.mean()
    
display(finaldf)


