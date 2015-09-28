import pandas as pd
import numpy as np
import matplotlib.pyplot as plt


B = pd.read_csv('Barabasi.csv', index_col=0)

ds = sorted(list(set(B.delta)))
bs = sorted(list(set(B.beta)))

B[(B.delta == ds[4] ) & (B.beta == bs[6])].
