import matplotlib.pyplot as plt
import pandas as pd

for name in ["src/directRecursion.csv", "src/numerical.csv", "src/OnMethods.csv", "src/squaring.csv"]:
    df = pd.read_csv(name, index_col=[0], header=[0])
    df.plot()
    plt.savefig(name.split('.')[0] + ".png")
