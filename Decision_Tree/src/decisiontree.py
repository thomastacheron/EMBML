#!/usr/bin/python3
import pandas as pd
import numpy as np
import os

from sklearn.tree import DecisionTreeClassifier
from sklearn.pipeline import make_pipeline
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split, GridSearchCV

THIS_FOLDER = os.path.dirname(os.path.abspath(__file__))
data_path = THIS_FOLDER + '/../../Features/features.csv'
data = pd.read_csv(data_path, header=None)
X = data.loc[:, :1023]
y = data[1024]
filename = data[1025]

X_train, X_test, y_train, y_test, filename_train, filename_test = train_test_split(X, y, filename, test_size=0.33, random_state=42)

df_concat = pd.concat([X_test, y_test], axis = 1)
df_concat.to_csv('./storage/test_set.csv', header = False, index=False)

label_unique = np.unique(y)
train_label_unique = np.unique(y_train)
test_label_unique = np.unique(y_test)

print(f"Train set contains {len(train_label_unique)} labels")
print(f"Train set contains {X_train.shape[0]} features")
print(f"Test set contains {len(test_label_unique)} labels")
print(f"Test set contains {X_test.shape[0]} examples")

clf = make_pipeline(StandardScaler(), DecisionTreeClassifier())
clf.fit(X_train, y_train)

scaler = clf.named_steps['standardscaler']
scale = scaler.scale_
mean = scaler.mean_

np.savetxt('storage/scale.txt', scale)
np.savetxt('storage/mean.txt', mean)

score = clf.score(X_test, y_test)
print(score)

from sklearn.ensemble import RandomForestClassifier

clf2 = make_pipeline(StandardScaler(), RandomForestClassifier())
clf2.fit(X_train, y_train)

score = clf2.score(X_test, y_test)
print(score)

import emlearn
cmodel = emlearn.convert(clf.steps[1][1], method='inline')
cmodel.save(file='decision_tree0.h')

cmodel = emlearn.convert(clf2.steps[1][1], method='inline')
cmodel.save(file='random_forest0.h')

# TODO : Faire un dossier random forest et refaire la même (prendre des moreceaux de ce code)
