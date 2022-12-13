import pandas as pd
import numpy as np

from sklearn.tree import DecisionTreeClassifier
from sklearn.pipeline import make_pipeline
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split, GridSearchCV

data_path = '/home/thomastacheron/Documents/ROB/3A/EMBML/Features/features.csv'
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

clf = make_pipeline(StandardScaler(), DecisionTreeClassifier())
clf.fit(X_train, y_train)

score = clf.score(X_test, y_test)
print(score)

from sklearn.ensemble import RandomForestClassifier

clf2 = make_pipeline(StandardScaler(), RandomForestClassifier())
clf2.fit(X_train, y_train)

score = clf2.score(X_test, y_test)
print(score)

# TODO : Générer automatiquement le code C++

def get_code(tree, feature_names, function_name="decision_tree"):
    left = tree.tree_.children_left
    right = tree.tree_.children_right
    threshold = tree.tree_.threshold
    features = [feature_names[i] for i in tree.tree_.feature]
    value = tree.tree_.value

    def recurse(left, right, threshold, features, node, tabs):
        code = ''
        if threshold[node] != -2:
            code += '%sif (feature_vector.at(%s) <= %s) {\n' % (tabs * '\t', feature_names.index(features[node]), round(threshold[node], 2))
            tabs += 1

            if left[node] != -1:
                code += recurse(left, right, threshold, features, left[node], tabs)
            tabs -= 1
            code += '%s}\n%selse {\n' % (tabs * '\t', tabs * '\t')

            tabs += 1
            if right[node] != -1:
                code += recurse(left, right, threshold, features, right[node], tabs)
            tabs -= 1
            code += '%s}\n' % (tabs * '\t')

        else:
            code += '%sreturn %s;\n' % (tabs * '\t', value[node].argmax())

        return code

    code = "inline int %s(const std::vector<double> & feature_vector) \n{\n%s}" \
           % (function_name, recurse(left, right, threshold, features, 0, 1))
    return code


def save_code(tree, feature_names, class_names, function_name="decision_tree"):

    feature_string = ""
    for i in range(0, len(feature_names)):
        feature_string += 'feature_vector[%s] - %s\n' % (i, feature_names[i])
    classes_string = ""
    for i in range(0, len(class_names)):
        classes_string += '%s - %s\n' % (i, class_names[i])

    preamble = """
/*
This inline function was automatically generated using DecisionTreeToCpp Converter
It takes feature vector as single argument:
%s
It returns index of predicted class:
%s
Simply include this file to your project and use it
*/
""" % (feature_string, classes_string)

    code = '%s#include <vector>\n\n%s' % (preamble, get_code(tree, feature_names, function_name))

    with open(function_name + '.h', "w") as f:
        f.write(code)
        print("File %s was written" % (function_name + '.h'))

    return 0

feat_names = ["AVG" + str(i) for i in range(512)] + ["STD" + str(i) for i in range(512)]
print(get_code(clf.steps[1][1], feat_names))
save_code(clf.steps[1][1], feat_names, label_unique)
