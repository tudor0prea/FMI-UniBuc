import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.svm import SVC
from sklearn.metrics import accuracy_score, confusion_matrix, f1_score
import cv2
import csv


train_file = '/kaggle/input/unibuc-brain-ad/data/train_labels.txt'
train_dir = '/kaggle/input/unibuc-brain-ad/data/data/'
problem_file = '/kaggle/input/unibuc-brain-ad/data/sample_submission.txt'
solution_file = 'prediction_svm.csv'


def add_extension(x):
    x = x + ".png"
    return x


def class_bool(x):
    if x == '1':
        return True
    else:
        return False


def read_csv_data(file_path):
    # citim din csv si transformam coloanele
    data = pd.read_csv(file_path, dtype=str)
    data['file'] = data['id'].apply(add_extension)
    data['class'] = data['class'].apply(class_bool)
    return data;


# functia care citeste imaginile de antrenament le transforma in vectori numpy
def read_image(file_path):
    img = cv2.imread(file_path, cv2.IMREAD_GRAYSCALE)
    img = np.array(img)
    img = img.astype('float32')
    img /= 255.0
    img = np.expand_dims(img, axis=-1)
    return img


def write_output(predictions, predict_data, file):
    with open(file, mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(['id', 'class'])
        for i in range(len(predictions)):
            if predictions[i] == True:
                writer.writerow([predict_data['id'][i], '1'])
            else:
                writer.writerow([predict_data['id'][i], '0'])


def train_and_test(data):
    # definim setul de antrenament si setul de validare
    train_data, val_data = train_test_split(data, test_size=0.2, random_state=42)

    # transformam datele de antrenament si de validare in vectori numpy
    X_train = np.array([read_image(train_dir + img_name) for img_name in train_data['file'].values])
    y_train = train_data['class'].values
    X_val = np.array([read_image(train_dir + img_name) for img_name in val_data['file'].values])
    y_val = val_data['class'].values

    # antrenam un model SVM pe setul de antrenament
    svm = SVC(kernel='linear')
    svm.fit(X_train.reshape(X_train.shape[0], -1), y_train)

    # evaluam performanta modelului pe setul de validare
    y_pred = svm.predict(X_val.reshape(X_val.shape[0], -1))
    accuracy = accuracy_score(y_val, y_pred)
    f1 = f1_score(y_val, y_pred)
    cm = confusion_matrix(y_val, y_pred)

    print('Accuracy:', accuracy)
    print('F1 Score:', f1)
    print('Confusion Matrix:')
    print(cm)
    return svm


def predict(svm, predict_data):
    # transformam datele de antrenament si de validare in vectori numpy
    X_predict = np.array([read_image(train_dir + img_name) for img_name in predict_data['file'].values])
    y_pred = svm.predict(X_predict.reshape(X_predict.shape[0], -1))
    write_output(y_pred, predict_data, solution_file)


# citim datele de antrenament din fisierul CSV
data = read_csv_data(train_file)
svm_model = train_and_test(data)

predict_data = read_csv_data(train_file)
predict(svm_model, predict_data)

# predictions = svm.predict(train_data)