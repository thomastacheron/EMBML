#!/usr/bin/python3
import pandas as pd
import numpy as np

from sklearn.svm import LinearSVC
from sklearn.pipeline import make_pipeline
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split, GridSearchCV

import os
THIS_FOLDER = os.path.dirname(os.path.abspath(__file__))
data_path = THIS_FOLDER + '/../../Features/features.csv'
data = pd.read_csv(data_path, header=None)
X = data.loc[:, :1023]
y = data[1024]
filename = data[1025]

X_train, X_test, y_train, y_test, filename_train, filename_test = train_test_split(X, y, filename, test_size=0.33, random_state=42)

label_unique = np.unique(y)
train_label_unique = np.unique(y_train)
test_label_unique = np.unique(y_test)

print(f"Train set contains {len(train_label_unique)} labels")
print(f"Train set contains {X_train.shape[0]} features")
print(f"Test set contains {len(test_label_unique)} labels")
print(f"Test set contains {X_test.shape[0]} examples")

clf = make_pipeline(StandardScaler(), LinearSVC(random_state=0))
clf.fit(X_train, y_train)

scaler = clf.named_steps['standardscaler']
scale = scaler.scale_
mean = scaler.mean_

svc = clf.named_steps['linearsvc']
coef = svc.coef_
intercept = svc.intercept_

score = clf.score(X_test, y_test)
print("score: ",score)
print("- saving npy parameters -")

# Save the parameters to a file
np.save('scale.npy', scale)
np.save('mean.npy', mean)
np.save('coef.npy', coef)
np.save('intercept.npy', intercept)
