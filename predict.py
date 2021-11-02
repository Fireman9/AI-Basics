import sys
import csv
import pandas as pd
from sklearn.linear_model import LinearRegression

data = pd.read_csv('Stats.csv')

x = data.iloc[:, 1:2].values
y = data.iloc[:, 2:3].values

regressor = LinearRegression()
regressor.fit(x, y)
x_pred = float(sys.argv[1].replace(",", "."))
y_pred = regressor.predict([[x_pred]])

with open('Predictions.csv', 'w') as f:
    writer = csv.writer(f)
    data = [sys.argv[2], x_pred, y_pred[0][0]]
    writer.writerow(data)

