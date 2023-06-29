
#                   Pasul 1 - Definirea modelului si antrenarea
import numpy as np
import pandas as pd
import os
import re
from tensorflow import keras
from tensorflow.keras import layers
from sklearn.metrics import accuracy_score, confusion_matrix, f1_score
import cv2
import csv

def add_extension(x):
    x = x + ".png"
    return x


def generate_csv():
    dir_path = "/kaggle/input/unibuc-brain-ad/data/data"
    files = os.listdir(dir_path)
    png_files = [f for f in files if re.match(r'.*\.png', f)]

    with open('nume_fisiere.csv', mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(['id', 'class'])
        for f in png_files:
            writer.writerow([f, '0'])


# incarcarea imaginilor 
df = pd.read_csv('/kaggle/input/unibuc-brain-ad/data/train_labels.txt', dtype=str)
df['id'] = df['id'].apply(add_extension)
df['class'] = df['class'].astype(str)

# prelucrarea imaginilor si incarcarea in model
datagen = keras.preprocessing.image.ImageDataGenerator(rescale=1. / 255)

# functia flow_from_dataframe pentru a incarca datele din fisierul CSV
train_data = datagen.flow_from_dataframe(
    dataframe=df,
    directory='/kaggle/input/unibuc-brain-ad/data/data',
    x_col='id',
    y_col='class',
    target_size=(224, 224),
    batch_size=8,
    class_mode='binary'
)


#MODELUL
model = keras.Sequential([
    layers.Conv2D(16, (3,3), activation='relu', input_shape=(224, 224, 3)),
    layers.MaxPooling2D(pool_size=(2,2)),
    layers.Conv2D(32, (3,3), activation='relu'),
    layers.MaxPooling2D(pool_size=(2,2)),
    layers.Conv2D(64, (3,3), activation='relu'),
    layers.MaxPooling2D(pool_size=(2,2)),
    layers.Flatten(),
    layers.Dense(512, activation='relu'),
    layers.Dense(1, activation='sigmoid')
])

#antrenarea si salvarea modelului

model.compile(
    loss='binary_crossentropy',
    optimizer='adam',
    metrics=['accuracy']
)

#antrenarea pe 8 epoci
model.fit(
    train_data,
    epochs=8
)

model.save('tomography_classification_model00.h5')


# --------------------------------------------------------------------------------------------------#


#                           Pasul 2 - Generearea predictiilor

# import pandas as pd
# import numpy as np
# import os
# import csv
# import re
# from tensorflow import keras
# from tensorflow.keras import layers
# from tensorflow.keras.models import Sequential

input_csv_name = '/kaggle/input/unibuc-brain-ad/data/sample_submission.txt'
dir_path = "/kaggle/input/unibuc-brain-ad/data/data"
model_path = '/kaggle/working/tomography_classification_model00.h5'
output_csv = 'sample_submission_00.txt'


def add_extension(x):
    x = x + ".png"
    return x


def get_class(predictions):
    class_labels = ['1', '0']
    predicted_class_indices = np.argmax(predictions, axis=1)
    return [class_labels[predicted_class_indices[i]] for i in range(len(predicted_class_indices))]


# citirea fisierului CSV si incarcarea datelor
df = pd.read_csv(input_csv_name, dtype=str)
df['id'] = df['id'].apply(add_extension)

# prelucrarea imaginilor si incarcarea în model
datagen = keras.preprocessing.image.ImageDataGenerator(
    rescale=1. / 255)

# functia flow_from_dataframe pentru a incarca datele din fișierul CSV
test_generator = datagen.flow_from_dataframe(
    dataframe=df,
    directory=dir_path,
    x_col='id',
    target_size=(224, 224),
    batch_size=1,
    shuffle=False,
    class_mode=None
)
# incarcarea modelului antrenat
model = keras.models.load_model(model_path)

# generarea predictiilor modelului pe datele noi
predictions = model.predict(test_generator)

lst = []
for i in range(len(predictions)):
    if predictions[i][0] < 0.5:
        lst.append(0)
    else:
        lst.append(1)

# salvarea predictiilor intr-un fisier CSV
df_predictions = pd.DataFrame({'id': df['id'], 'class': lst})
df_predictions.to_csv(output_csv, index=False)



input_csv_name = '/kaggle/input/unibuc-brain-ad/data/sample_submission.txt'
dir_path = "/kaggle/input/unibuc-brain-ad/data/data"
model_path = '/kaggle/working/tomography_classification_model00.h5'
output_csv = 'sample_submission_00.txt'


def add_extension(x):
    x = x + ".png"
    return x


def get_class(predictions):
    class_labels = ['1', '0']
    predicted_class_indices = np.argmax(predictions, axis=1)
    return [class_labels[predicted_class_indices[i]] for i in range(len(predicted_class_indices))]


# citirea fisierului CSV si incarcarea datelor
df = pd.read_csv(input_csv_name, dtype=str)
df['id'] = df['id'].apply(add_extension)

# prelucrarea imaginilor si incarcarea în model
datagen = keras.preprocessing.image.ImageDataGenerator(
    rescale=1. / 255)

# functia flow_from_dataframe pentru a incarca datele din fișierul CSV
test_generator = datagen.flow_from_dataframe(
    dataframe=df,
    directory=dir_path,
    x_col='id',
    target_size=(224, 224),
    batch_size=1,
    shuffle=False,
    class_mode=None
)
# incarcarea modelului antrenat
model = keras.models.load_model(model_path)

# generarea predictiilor modelului pe datele noi
predictions = model.predict(test_generator)

lst = []
for i in range(len(predictions)):
    if predictions[i][0] < 0.5:
        lst.append(0)
    else:
        lst.append(1)

# salvarea predictiilor intr-un fisier CSV
df_predictions = pd.DataFrame({'id': df['id'], 'class': lst})
df_predictions.to_csv(output_csv, index=False)


# --------------------------------------------------------------------------------------------------#


#                           Pasul 3 - Modelarea rezultatului


with open("/kaggle/working/sample_submission_00.txt", "r") as f1, open("test_subm_00.csv", "w") as f2:
    f2.write("id,class\n")
    next(f1) # skip header line
    for line in f1:
        line = line.strip().split(",")
        id = line[0].replace(".png", "")
        clasa = True if line[1] == "1" else False
        f2.write("{},{}\n".format(id, clasa))

# --------------------------------------------------------------------------------------------------#
# Cum am obtinut matricea de confuzie si acuratetea:

y_pred = model.predict(test_generator)

# rotunjim predictiile la 0 sau 1, folosind 0,5 ca prag
y_pred = np.round(y_pred).astype(int)

# transformam etichetele din datele de testare intr-o matrice de coloane
y_test = np.array(test_labels).astype(int)
y_test = y_test.reshape(len(y_test), 1)

# calculam matricea de confuzie
cm = confusion_matrix(y_test, y_pred)

# calculam precizia, recall-ul și scorul F1
accuracy = accuracy_score(y_test, y_pred)
recall = recall_score(y_test, y_pred)
f1 = f1_score(y_test, y_pred)

# afisare
print("Matrice de confuzie:")
print(cm)
print("Accuracy:", accuracy)
print("Recall:", recall)
print("F1-score:", f1)
